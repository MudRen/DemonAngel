//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/condition/magic_shield.c

#include <ansi.h>
#include <condition.h>

int update_condition(object me, int time)
{
	if(time <= 0) {
		me->add("apply/ac", -12);
		me->add("apply/db", -8);
		message("vision",HIY+gender_self(me->query("gender"))+"��ħ������ʧ�ˡ�\n"NOR, me);
		message("vision",HIY+me->name(1)+"��ħ������ʧ�ˡ�\n"NOR, environment(me), me);

		return 0;
	}
	else me->apply_condition("magic_shield", time - 1);
	return 1;
}
