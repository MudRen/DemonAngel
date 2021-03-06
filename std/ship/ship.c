//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/ship/ship.c
// by bor @DA, 2/24 2003
/*
	船只的做法, 除了此法( item ) 外, 尚有不少的方式( NPC, ....)去做, 端看各位如何去撰写了
*/

#pragma optimize
#pragma save_binary

inherit ITEM;
#include <ansi.h>

void init()
{
	// 如果考量玩家有守卫的话, 请记得自己判定
	add_action("do_board", "board");
	add_action("do_out", "out");
}

int do_board(string arg)
{
	object me = this_player(), ob, *all;

	if( environment(me) == this_object() ) return 0;	// 你坐上船的话就不能在坐其他船
	if( !arg ) return notify_fail("你要坐哪一艘船？\n");
	if( me->is_busy() ) return notify_fail("你的动作还没有完成，不能移动。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	arg = lower_case(arg);
	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("你确定有这一艘船？\n");
	if( ob->query("type")!="ship" ) return 0;
	tell_room(environment(me), sprintf(YEL"%s登上了%s。\n"NOR, me->name_id(1), ob->short(1) ), ({me}));
	me->direct_move(ob);
	tell_room(environment(me), sprintf(HIB"%s登上%s。\n"NOR, me->name_id(1), ob->short(1) ), ({me}));
	return 1;
}

int do_out(string arg)
{
	object me = this_player(), ob;

	if( environment(me)!= this_object() ) return 0;
	if( this_object()->query("shiping") ) return notify_fail("船正行进中，不要随便跳下去。\n");

	tell_room(environment(me), sprintf(HIB"%s离开%s，走到外面去。\n"NOR, me->name_id(1), this_object()->name(1) ) , ({me}));

	if( !ob = find_object(this_object()->query("exits/out")) ) {
		call_other(this_object()->query("exits/out"), "???");
		ob = find_object(this_object()->query("exits/out"));
	}
	me->direct_move(ob);
	tell_room(environment(me), sprintf(HIB"%s从%s下来。\n"NOR, me->name_id(1), this_object()->name(1) ) , ({me}));
	return 1;
}
