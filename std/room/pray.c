//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/pray.c
// by bor @DA, 2/22 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit ROOM;

void init()
{
	add_action("do_pray","pray");
}

int do_pray(string arg)
{
	object ob, me;
	string file;

	me = this_player();

	if( !arg ) return notify_fail("��Ҫ����ʱ���ŵ�����ȥ?\n");
	if(!userp(me)) return 0;
	arg = lower_case(arg);
	if(!check_kingdom(arg)) return notify_fail("�����ħ������������ʲô��Ҳû������\n");
	if( !stringp(file = kingdom_data(arg, "other", "query_par", "time_gate")) )
		return notify_fail("�ù�û���趨ʱ���š�\n");
	if( file_size(file) == -1) return notify_fail("�ù���û���趨ʱ���š�\n");

	if( !ob = load_object(file) ) {
		ob = new(file);
	}
	message_vision("$N���ŷ���һ���̵ض����ˡ�\n", me);
	me->start_busy(2);
	me->move(ob);
	return 1;
}
