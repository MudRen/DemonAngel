//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/post_office
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit ROOM;

void init()
{
	add_action("do_search","search");
}

int do_search(string arg)
{
	object obj, me;
	me = this_player();

	if( !arg || arg!="mailbox" ) {
		message_vision("$N�����ﵽ�����ң�����ʲô���Ҳ�����\n", me);
		return 1;
	}
	if( me->query_temp("mail") ) {
		message_vision("$N�����ﵽ�����ң�����ʲô���Ҳ�����\n", me);
		return 1;
	}
	message_vision("[1;30m$N����������ҳ��Լ������䡣\n[m", me);
	obj = new("obj/mailbox");
	obj->move(me);
	me->set_temp("mail", 1);
	return 1;
}

int valid_leave(object me)
{
	object obj;
	if( me->query_temp("mail") ) {
		obj = present("mailbox", me);
		me->delete_temp("mail");
		message_vision("$N�����䶪��������С�\n", me);
		destruct(obj);
	}
	return 1;
}