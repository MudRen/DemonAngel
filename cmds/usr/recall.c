//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/recall.c
// by bor @RG,

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <login.h>

inherit F_CLEAN_UP;  

int main(object me, string arg)
{
	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成，不能移动。\n");
	if(me->is_fighting()) return notify_fail("你在战斗中，无法移动。\n");
	if(!wizardp(me)&&environment(me)->query("no_recall")) {
		message_vision("$N祈求鸭子把$N带回一切根源之地．．．\n"
		"但是鸭子装作听不见。\n",me);
		return 1;
	}
	message_vision(HIC"$N仰头向鸭子祈求把$N带回一切根源之地\n"
		HIW"突然身影化作一道白光, $P消逝于天空中。\n"NOR, me);
	me->move(START_ROOM);
	if(!wizardp(me)) me->start_busy(3);
	message_vision(HIC"一道白光从天空打破寂静, $N身影渐渐显现。\n"NOR,me);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : recall

当你被困住时, 你可以使用这个指令使你立刻回到冒险者之家。
这个指令只在非战斗状态才有效。

相关讯息 :

HELP
	);
	return 1;
}
