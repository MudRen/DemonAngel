//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/condition/ogre_power.c
// by bor @DA
// str:12

#include <ansi.h>

int update_condition(object me, int time)
{
	if( time <= 0 ) {
		tell_object(me, HIC"你渐渐平静下来。\n"NOR );
		me->add("apply/str", -12);
		return 0;
	} else 	me->apply_condition("ogre_power", time - 1);
	return 1;
}
