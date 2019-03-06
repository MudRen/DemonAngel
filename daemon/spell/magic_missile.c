//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/magic_missile.c
// by bor @DA
// ħ����(magic_missle)
/*
> cast magic_missle on c
  ���૆��� : ������� ���� ������� ...

  һ��ħ�������������г��� ...

  �����ɪ����ħ����, ����¡��һ��, ħ�����ڰ�ɪ������ը�� ...

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( me->is_busy() ) return notify_fail("����æ�š�\n");
	if( !target ) return notify_fail("�Ҳ����κ�Ŀ��!!\n");
	if( target == me ) return notify_fail("��Ҫ��Ŀ�����ʩ����\n");
	if( (int)me->query_mp() < 30 ) return notify_fail("��ķ���������\n");

	me->add("mp", -20);
	me->start_busy(1);
	message_vision(HIC+"$N�૆��� : ������� ���� ������� ...\n\n"NOR, me);
	call_out("magic_missle", 0, me, target);
	return 1;
}

int magic_missle(object me, object target)
{
	int damage;
	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		// ������ж�һ�ζԷ��Ƿ��ڱ���
		if(!target || environment(target)!=environment(me)) {
			write("���Ŀ���Ѿ��ܵ��ˡ�\n");
			return 1;
		}
		message_vision(HIY"һ��ħ��������$N���г��� ...\n\n"NOR, me);
		message_vision(HIY"$N��$n����ħ����, ����¡��һ��, ħ������$n������ը�� ...\n"NOR, me, target);
		damage = 20 + random(4);
		target->receive_damage("hp", damage, me);
		COMBAT_D->report_status(target);
		target->start_busy(1);
		me->kill_ob(target);
		target->kill_ob(me);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( me->is_busy() ) return notify_fail("����æ�š�\n");
	if( !target ) return notify_fail("�Ҳ����κ�Ŀ��!!\n");
	if( target == me ) return notify_fail("��Ҫ��Ŀ�����ʩ����\n");
	if( (int)me->query_mp() < 30 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -17);
 	me->start_busy(1);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	int damage;
	if( random(60) > (me->query_skill("invoke",1)*2/3 +me->query_kar()/4) ) {
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
		message_vision(HIY"һ��ħ��������$N���г��� ...\n\n"NOR, me);
		message_vision(HIY"$N��$n����ħ����, ����¡��һ��, ħ������$n������ը�� ...\n"NOR, me, target);
		damage = 20 + random(4);
		target->receive_damage("hp", damage, me);
		COMBAT_D->report_status(target);
		me->kill_ob(target);
		target->kill_ob(me);
		target->start_busy(1);
	}
	return 1;
}
