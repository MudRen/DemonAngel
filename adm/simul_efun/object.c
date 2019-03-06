//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/simul_efun/object.c

varargs int getoid(object ob)
{
	int id;

	if (!ob) ob = previous_object();
	sscanf(file_name(ob), "%*s#%d", id);
	return id;
}

// Get the owner of a file.  Used by log_error() in master.c.
string file_owner(string file)
{
    string name, rest, dir;

    if (file[0] != '/') {
        file = "/" + file;
    }
    if (sscanf(file, "/u/%s/%s/%s", dir, name, rest) == 3) {
        return name;
    }
    return 0;
}

// domain_file should return the domain associated with a given file.
string domain_file(string file)
{
	string domain;

	if( sscanf(file, "/d/%s/%*s", domain) )
		return domain;

	return ROOT_UID;
}

// creator_file should return the name of the creator of a specific file.
string creator_file(string file)
{
	string *path, euid;

	path = explode(file, "/") - ({ 0 });
	switch(path[0]) {
		case "adm":
		case "cmds":
			return ROOT_UID;
		case "u":
			if( this_player(1) ) euid = getuid(this_player(1));
			if( !euid ) euid = geteuid(previous_object(1));
			if( euid && euid != ROOT_UID ) return euid;
			return "NONAME";
		case "d":
		case "open":
			return DOMAIN_UID;
		default:
			return MUDLIB_UID;
	}
}

// author_file should return the name of the author of a specific file.
string author_file(string file)
{
	string name;

	if( sscanf(file, "/u/%*s/%s/%*s", name) )
		return name;
	return ROOT_UID;
}

void destruct(object ob)		// es2 1.2b
{
	string err;

	if (ob) {
		if( previous_object() )
			err = catch(ob->remove( geteuid(previous_object()) ));
		else
			err = catch(ob->remove(0));
		if( err ) {
			if( userp(ob) && geteuid(previous_object())!=ROOT_UID ) return;
			log_file("destruct", sprintf("[%s]%O[%O]\n%s\n", ctime(time()), ob, geteuid(previous_object()), err));
		}
		efun::destruct(ob);
	}
}
int zerop(mixed arg)
{
	if(sizeof(arg) == 0) return 1;
	return 0;
}

object load_player(string id)			// by bor @DA, 3/9 2003
{
	object ob;

	if(strsrch(id, ".") != -1) return 0;
	if(find_player(id)) return 0;
	ob = new(LOADUSER_OB);		// ���λȥ׷������ restore �Ĺ���, ��λ��֪��Ϊʲô��Ҫ��Ū�� LOADUSER_OB��
	ob->set("id", id);		// LOADUSER_OB �ο��� LOGIN_OB ��д����
	if(!ob->restore()) return 0;	// ԭ�ȵ� USER_OB û�취���� set("id", xx) �ķ�ʽȥ restore() �� object �����޸�
	return ob;			// USER_OB �� query_save_file(), ��˼�Ȼ��û����, Ūһ�� LOADUSER_OB����Ҳ�޲���
}

int exec( object to, object from )
{
	if(file_name(previous_object() ) != "/adm/daemons/logind" && file_name(previous_object() ) !="/cmds/wiz/update" )
		error("EXEC error somebody use ...");
	efun::exec(to, from);
}
