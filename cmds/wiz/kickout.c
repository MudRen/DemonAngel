//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/wiz/kickout.c
// by bor @DA

#include <command.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
	seteuid(getuid());
	set("channel_id", "���߾���(Kickout)");
}

int main(object me, string arg)
{
	object ob;

	if( !arg || arg=="" ) return notify_fail("ָ���ʽ��kickout <��� id>\n");
	if( !( ob = find_player(arg) )) return notify_fail("û�������\n");
	if( wiz_level(me) <= wiz_level(ob) ) return notify_fail("��û�����Ȩ����\n");

	foreach(object inv in all_inventory(ob) ) {
		if( !inv->query_autoload() ) DROP_CMD->do_drop(ob, inv);
	}
	ob->save();
	CHANNEL_D->do_channel(this_object(), "rumor", ob->name() + "��ϵͳ�߳�����Ϸ��");
	destruct(ob);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ: kickout <���>

�����ǿ���뿪�� mud ��

HELP
	);
	return 1;
}
