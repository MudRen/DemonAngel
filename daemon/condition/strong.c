//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/condition/strong.c
// by bor @DA
// str:9

#include <ansi.h>
int update_condition(object me, int time)
{
	if( time <= 0 ) {
		tell_object(me, HIG"你的力量逐渐消失！\n"NOR );
		me->add("apply/str", -9);
		return 0;
	} else 	me->apply_condition("strong", time - 1);
	return 1;
}
