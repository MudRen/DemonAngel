//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
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

	if( !arg ) return notify_fail("你要经由时空门到哪里去?\n");
	if(!userp(me)) return 0;
	arg = lower_case(arg);
	if(!check_kingdom(arg)) return notify_fail("你对着魔法阵祈祷，但是什么事也没发生。\n");
	if( !stringp(file = kingdom_data(arg, "other", "query_par", "time_gate")) )
		return notify_fail("该国没有设定时空门。\n");
	if( file_size(file) == -1) return notify_fail("该国家没有设定时空门。\n");

	if( !ob = load_object(file) ) {
		ob = new(file);
	}
	message_vision("$N踩着飞盘一溜烟地遁走了。\n", me);
	me->start_busy(2);
	me->move(ob);
	return 1;
}
