//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/condition/ogre_power.c
// by bor @DA
// str:12

#include <ansi.h>

int update_condition(object me, int time)
{
	if( time <= 0 ) {
		tell_object(me, HIC"�㽥��ƽ��������\n"NOR );
		me->add("apply/str", -12);
		return 0;
	} else 	me->apply_condition("ogre_power", time - 1);
	return 1;
}
