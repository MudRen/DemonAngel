//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/tavern.c
// by bor @DA

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

void setup()
{
	seteuid(getuid());
	::setup();
}

void init()
{
	add_action("do_check_in","check_in");		// ���������õ�
	add_action("do_list", "list");			// �������ķ�չ���
}

int do_check_in(string arg)
{
	object me, rest_room;

	me = this_player();

	if( !me->can_afford(50) ) return notify_fail("���Ǯ������\n");

	me->add("gold", -50);

	message_vision(HIY"$N����Ǯ, �߽������ķ��䡣"+NOR+"\n", me);
	rest_room = new("/obj/rest.c");
	rest_room->set("exits/out", base_name(environment(me)) );
	me->move(rest_room);
	return 1;
}

int do_list()
{
	string msg;

	msg = "�ù�Ŀǰ�ķ�չΪ :\n";

	msg += "\t"+develop_data(environment(this_player())->query("kingdom_id"), "query_par", "tavern", "dev")+"\n";

	write(msg);
	return 1;
}
