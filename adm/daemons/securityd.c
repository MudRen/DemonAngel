//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/securityd.c

#pragma optimize
#pragma save_binary

#include <login.h>

// By Annihilator@Eastern.Stories (11/25/94)

// This is the "effective" access status compare to the "status" property
// in login object that this mapping determine wizards' access rights
// directly. It is important to make the "status" property matches this
// mapping for wizards higher than regular wizard such as sage, arch and
// admin. For thoese users whose name doesnot appear in this mapping, they
// are divided into three groups (wizard),(player) and (object) using
// wizardp() and interactive() efun.
// The parenthesis is nessessary to prevend players naming themself "admin"
// to hack the security system.
// 
// 01/14/95 Annihilator - wiz_status are defined outside this daemon in the
//                        WIZLIST file.

//#define DEBUG

private mapping wiz_status = ([]);

private string *wiz_levels = ({
	"(player)",
	"(wizard)",
	"(admin)"
});

// A valid write attempt must pass 2 checks: your uid or status must not be
// "excluded" and must be "trusted" on that directory in order to write in 
// that directory. The directories containing the file is searched backward
// from the current directory to root. And exclude is checked prior than
// trusted.

private mapping trusted_write = ([
	"/": 		({ ROOT_UID, "(admin)", "(wizard)" }),
	"/d":		({ DOMAIN_UID }),
	"/open":	({ DOMAIN_UID }),
	"/data":	({ DOMAIN_UID }),
	"/data/daemon":	({ MUDLIB_UID }),
	"/obj/board":	({ DOMAIN_UID }),
]);

private mapping exclude_write = ([
	"/adm":		({ "(wizard)" }),
	"/feature":	({ "(wizard)" }),
	"/log":		({ "(wizard)" }),
	"/u":		({ "(player)" }),
]);

private mapping trusted_read = ([
	"/":		({ ROOT_UID, MUDLIB_UID, "(admin)", "(wizard)" }),
	"/daemon":	({ DOMAIN_UID }),
	"/data":	({ DOMAIN_UID }),
	"/d":		({ DOMAIN_UID }),
	"/open":	({ DOMAIN_UID }),
	"/obj":		({ DOMAIN_UID }),
]);

private mapping exclude_read = ([
	"/u":		({ "(wizard)" }),
	"/log":		({ "(player)" }),
]);

private void create()
{
	string *wizlist, wiz_name, wiz_level;
	int i;

	seteuid(getuid());
	wizlist = explode(read_file(WIZLIST), "\n");
	wiz_status = allocate_mapping(sizeof(wizlist));
	for(i=0; i<sizeof(wizlist); i++) {
		if( wizlist[i][0]=='#' 
		|| sscanf(wizlist[i], "%s %s", wiz_name, wiz_level)!=2 ) continue;
		wiz_status[wiz_name] = wiz_level;
	}
}

string *query_wizlist() { return keys(wiz_status); }

// This function returns the status of an uid.
string get_status(mixed ob)
{
	string euid;
	
	if( objectp(ob) ) {
		euid = geteuid(ob);
		if( !euid ) euid = getuid(ob);
	}
	else if( stringp(ob) ) euid = ob;

	if( !undefinedp(wiz_status[euid]) ) return wiz_status[euid];
	else if( member_array(euid, wiz_levels)!=-1 ) return euid;
	else return "(player)";
}

int get_wiz_level(object ob)
{
	return member_array(get_status(ob), wiz_levels);
}

int set_status(mixed ob, string status)
{
	string uid, *wiz, wizlist;
	int i;

	if( geteuid(previous_object())!= ROOT_UID ) return 0;

	if( userp(ob) )			uid = getuid(ob);
	else if(stringp(ob))	uid = ob;
	else return 0;
	
	if( status == "(player)" )
		map_delete(wiz_status, uid);
	else
		wiz_status[uid] = status;
	wiz = keys(wiz_status);
	for(wizlist = "", i=0; i<sizeof(wiz); i++)
		wizlist += wiz[i] + " " + wiz_status[wiz[i]] + "\n";
	rm(WIZLIST);
	write_file(WIZLIST, wizlist);
	log_file( "static/promotion", capitalize(uid)
	 + " become a " + status + " on " + ctime(time()) + "\n" );
	return 1;
}

string *get_wizlist() { return keys(wiz_status); }

// valid_write - called by the master object to determine whether if an user
//               is allowed to write on a certain file.
// NOTE:
//     The argument user should be an object according to the source code
// of driver. However, it is a mixed type in the released docs. We assume
// it is an object in normal case here and issue an error if it was not
// an object. 												- Annihilator

int valid_write(string file, mixed user, string func)
{
	string euid, status, *path, dir;
	int i;

	if( !objectp(user) )
		error("TRUST_D->valid_write: Invalid argument type of user.\n");

	if( sscanf(file, LOG_DIR + "%*s") && func=="write_file" ) return 1;

	// Let user save their save file
	if( func=="save_object" ) {
		if( sscanf(base_name(user), "/obj/%*s")
		&&	sscanf(file, "/data/%*s")
		&&	file == (string)user->query_save_file()+".o" )
			return 1;
	}

#ifdef DEBUG
	log_file("securityd", sprintf("%s:[Write]func->%s, %s\n", ctime(time())[0..19], func, base_name(user)) );
#endif

	// Get the euid and status of the user.
	euid = geteuid(user);
	if( !euid ) return 0;
	status = get_status(user);

#ifdef DEBUG
	log_file("securityd", sprintf("%s:[Write]euid->%s, status->%s\n", ctime(time())[0..19], euid, status) );
#endif

	if( euid==ROOT_UID ) return 1;

	path = explode(file, "/") - ({ "" });

	if( sizeof(path)>=3 && euid[0]>='a' && euid[0]<='z'
	&& path[0]=="u" && path[1]==euid[0..0] && path[2]==euid ) return 1;

	// Check if we are excluded in one of the directories containing the file.
	for(i=sizeof(path)-1; i>=0; i--) {
		dir = "/" + implode(path[0..i], "/");
		if( undefinedp(exclude_write[dir]) ) continue;
		if( member_array(euid, exclude_write[dir])!=-1
		|| member_array(status, exclude_write[dir])!=-1 ) {
#ifdef DEBUG
			log_file("securityd", sprintf("%s:[Write]exclude_write_dir_Deny->%s\n", ctime(time())[0..19], dir) );
#endif
			return 0;
		}
	}

	// And then check if we are trusted in one of the directories containing
	// the file.
	if( member_array(euid, trusted_write["/"])!=-1
	|| member_array(status, trusted_write["/"])!=-1 )
		return 1;

	for(i=sizeof(path)-1; i>=0; i--) {
		dir = "/" + implode(path[0..i], "/");
		if( undefinedp(trusted_write[dir]) ) continue;
		if( member_array(euid, trusted_write[dir])!=-1
		|| member_array(status, trusted_write[dir])!=-1 ) {
#ifdef DEBUG
			log_file("securityd", sprintf("%s:[Write]trusted_write_dir_OK->%s\n", ctime(time())[0..19], dir) );
#endif
			return 1;
		}
	}

//	LOG("FILES", sprintf("%s(%s) write attempt on %s failed.\n", euid, status, file);
	return 0;
}

int valid_read(string file, mixed user, string func)
{
	string euid, status, *path, dir;
	int i;

	if( !objectp(user) )
		error("TRUST_D->valid_read: Invalid argument type of user.\n");

	if( func=="restore_object" ) {
		if( sscanf(base_name(user), "/obj/%*s")
		&&	sscanf(file, "/data/%*s")
		&&	file == (string)user->query_save_file()+".o" )
			return 1;
	}

#ifdef DEBUG
	log_file("securityd", sprintf("%s:[Read]func->%s, %s\n", ctime(time())[0..19], func, base_name(user)) );
#endif

	if( base_name(user)==SIMUL_EFUN_OB || base_name(user)==MASTER_OB  ) return 1;

	// Get the euid and status of the user.
	if( !(euid = geteuid(user)) ) return 0;
	status = get_status(user);

#ifdef DEBUG
	log_file("securityd", sprintf("%s:[Read]euid->%s, status->%s\n", ctime(time())[0..19], euid, status) );
#endif

	if( euid==ROOT_UID ) return 1;

	path = explode(file, "/") - ({ "" });
	if( file[0] != '/' ) file = "/" + file;

	/* ������ʦ��ȡ�Լ���Ŀ¼ */
	if( sizeof(path)>=3 && euid[0]>='a' && euid[0]<='z'
	&& path[0]=="u" && path[1]==euid[0..0] && path[2]==euid ) return 1;

	// Check if we are excluded in one of the directories containing the file.
	for(i=sizeof(path)-1; i>=0; i--) {
		dir = "/" + implode(path[0..i], "/");
		if( undefinedp(exclude_read[dir]) ) continue;
		if( (member_array(euid, exclude_read[dir])>=0)
		|| (member_array(status, exclude_read[dir])>=0) ) {
#ifdef DEBUG
			log_file("securityd", sprintf("%s:[Read]exclude_read_dir_Deny->%s\n", ctime(time())[0..19], dir) );
#endif
			return 0;
		}
	}

	/* ����Ƿ��С������ȡ�������� */
	if( member_array(euid, trusted_read["/"])!=-1 ) return 1;
	if( member_array(status, trusted_read["/"])!=-1 ) return 1;

	for(i=sizeof(path)-1; i>=0; i--) {
		dir = "/" + implode(path[0..i], "/");
		if( undefinedp(trusted_read[dir]) ) continue;
		if( (member_array(euid, trusted_read[dir])>=0)
		|| (member_array(status, trusted_read[dir])>=0) ) {
#ifdef DEBUG
			log_file("securityd", sprintf("%s:[Read]trusted_read_dir_OK->%s\n", ctime(time())[0..19], dir) );
#endif
			return 1;
		}
	}
	return 0;
}

int valid_seteuid( object ob, string uid )
{
	if( uid==0 ) return 1;
	if( uid==getuid(ob) ) return 1;
	if( getuid(ob)==ROOT_UID ) return 1;
	if( sscanf(file_name(ob), "/adm/%*s") ) return 1;
	if( wiz_status[uid] != "(admin)"
	&&	wiz_status[getuid(ob)] == "(admin)" )
		return 1;
	return 0;
}
