//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/wiz/nuke.c
// by bor @DA, 3/9 2003

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string id, file;

	seteuid(geteuid(me));
	if(!wizardp(me)) return 0;
	if (!arg) return notify_fail("ָ���ʽ : nuke <���>\n");
	arg = lower_case(arg);

	ob = find_player(arg);
	if( !ob ) return notify_fail("û�������ҡ�\n");
	if( wizardp(ob) ) return notify_fail("�㲻����㿳��ʦ��\n");

	if( id = ob->query("kingdom/id") ) {	// ������й���, ��ȥ����ʾ
		if( ob->query("kingdom/king") ) {	// ��� !? or ����Լ����ù��ҹ���?
			"/cmds/adm/delete_kingdom.c"->main(me, id);
		} else if(ob->query("kingdom/minister")) {
			kingdom_data(id, "power", "sub", "minister", arg);
			ob->delete("home");
			ob->delete("kingdom/minister");
			ob->sub_path( ({"/cmds/min/"}) );
			ob->save();
		} else {
			people_data(id, "sub", ob->query("id"));
			ob->delete("kingdom");
		}
	}

	file = arg[0..0] +"/" + arg + __SAVE_EXTENSION__;
	assure_file(DATA_DIR+"nuke/login/"+file);
	if( rename(DATA_DIR+"login/"+file, DATA_DIR+"nuke/login/"+file) )
		write( arg + "�� LOGIN ���Ѿ�ɾ����\n");
	assure_file(DATA_DIR+"nuke/user/"+file);
	if( rename(DATA_DIR+"user/"+file, DATA_DIR+"nuke/user/"+file) )
		write( arg + "�� USER ���Ѿ�ɾ����\n");

	file = arg[0..0]+"/"+arg+__SAVE_EXTENSION__;
	assure_file(DATA_DIR+"nuke/mail/"+file);
	if( file_size(DATA_DIR+"mail/"+file) != -1)
		if( rename(DATA_DIR+"mail/"+file, DATA_DIR+"nuke/mail/"+file ) )
			write(arg+ "�� Mail ���Ѿ�ɾ����\n");

	CHANNEL_D->do_channel(me, "chat", sprintf("%s ������Ǵ��ʧ�������磮", arg ));

	destruct(ob);
	log_file("nuke", sprintf("[%s] %s nuke %s from <%s>.\n",
		ctime(time())[0..15], geteuid(me), arg, query_ip_name(me) ));

	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : nuke <���>

����ҵ�����
 
HELP
	);
	return 1;
}
