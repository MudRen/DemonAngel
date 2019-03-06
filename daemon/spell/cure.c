//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/cure.c
// by bor @DA
// ������(cure)
/*
cast cure
���ͷ�૆��� : �Ȱ�֮�������Ű� ... ������������ͽ�� !
> һ��ʥ����������, ���Եþ���ö���...

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( !target ) target = me;
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");

	me->add("mp", -10);
	me->start_busy(1);
	message_vision(HIC+"$N��ͷ�૆��� : �Ȱ�֮�������Ű� ... ������������ͽ�� !\n"NOR, me);
	call_out("cure", 0, me, target);
	return 1;
}

int cure(object me, object target)
{
	if( random( 50 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*2 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		// ������ж�һ�ζԷ��Ƿ��ڱ���
		if(!target||environment(target)!=environment(me)) {
			write("���Ŀ���Ѿ��ܵ��ˡ�\n");
			return 1;
		}
		target->receive_heal("hp", 10+random(2) );
		message_vision(HIY"һ��ʥ��������$N, $N�Եþ���ö���...\n"NOR, target);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !target ) target = me;
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
		if(!target||environment(target)!=environment(me)) {
			write("���Ŀ���Ѿ��ܵ��ˡ�\n");
			return 1;
		}
		target->receive_heal("hp", 10+random(2) );
		message_vision(HIY"һ��ʥ��������$N, $N�Եþ���ö���...\n"NOR, target);
	}
	return 1;
}
