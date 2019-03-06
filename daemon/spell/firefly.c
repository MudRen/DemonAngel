//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/firefly.c
// by bor @DA
// ө����(firefly)
/*
cast firefly
���૆��� : ��֮�����尡 ���� �����Ĺ�â���������˰� ...
> ��������С��������ۼ�, ������徹Ȼ����ө������

�����ϵ�ө�⽥����ȥ, ���ָ�������

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( !target ) target = me;

	// ������ condition ����̬׫д
	if( target->query_temp("light") ) {
		write(target==me?"������Χ������\���â��\n":"������Χ������\���â��\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");

	me->add("mp", -10);
	me->start_busy(1);
	message_vision(HIC+"$N�૆��� : ܽ������ ���� ��³ ...\n"NOR,me);
	call_out("magefire", 0, me, target);
	return 1;
}

int magefire(object me, object target)
{
	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		// ������ж�һ�ζԷ��Ƿ��ڱ���
		if(!target||environment(target)!=environment(me)) {
			write("���Ŀ���Ѿ��ܵ��ˡ�\n");
			return 1;
		}
		// ���ж�һ�ζԷ�ʽ���� cast �÷���
		if( target->query_temp("light") ) {
			write(target==me?"������Χ������\���â��\n":"������Χ������\���â��\n");
			return 1;
		}
		target->add_temp("light",1);
		call_out("remove_magefire", 200, target);
		message_vision(HIY"һ�Ż�����$N����֮�����, ����Ʈ�Ͽ��� ...\n"NOR, target);
	}
	return 1;
}

int remove_magefire(object target)
{
	if(!target) return 1;
	if(!target->query_temp("light")) return 1;
	target->delete_temp("light");
	message_vision(HIY"Ʈ����$Nǰ����ħ���������˼���, ��ʧ�ˡ�\n"NOR, target);
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !target ) target = me;
	if( target->query_temp("light") ) {
		write(target==me?"������Χ������\���â��\n":"������Χ������\���â��\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -10);
	me->start_busy(1);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(40) > (me->query_skill("invoke",1)*2/3 +me->query_kar()/4) ) {
		message_vision(HIG"$N������ӡʧ��, $n����һ���Ѻ�\n", me, wp);
		wp->add_temp("broken", 20);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N���е�$n���һ����Ƭ...\n", me, wp);
		destruct(wp);
	} else {
		// ������ж�һ�ζԷ��Ƿ��ڱ���
		if(!target || environment(target)!=environment(me) ) {
			write("���Ŀ���Ѿ��ܵ��ˡ�\n");
			return 1;
		}
		// ���ж�һ�ζԷ�ʽ���� cast �÷���
		if( target->query_temp("light") )	{
			write(target==me?"������Χ������\���â��\n":"������Χ������\���â��\n");
			return 1;
		}
		target->add_temp("light", 1);
		message_vision(HIY"һ�Ż�����$N����֮�����, ����Ʈ�Ͽ��� ...\n"NOR, target);
		call_out("remove_magefire", 200, target);
	}
	return 1;
}
