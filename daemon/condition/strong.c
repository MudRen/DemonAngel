//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/condition/strong.c
// by bor @DA
// str:9

#include <ansi.h>
int update_condition(object me, int time)
{
	if( time <= 0 ) {
		tell_object(me, HIG"�����������ʧ��\n"NOR );
		me->add("apply/str", -9);
		return 0;
	} else 	me->apply_condition("strong", time - 1);
	return 1;
}
