//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/stone.c
// by bor @DA

#include <ansi.h>

inherit SSERVER;

int cast_spell(object me, object target)
{
	if( me->is_busy() ) return notify_fail("����æ�š�\n");
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("�Ҳ����κ�Ŀ��!!\n");
	}
	if( target == me ) return notify_fail("��Ҫ��Ŀ�����ʩ����\n");
	if((int)me->query_mp() < (80+me->query_base_mp()/8) ) return notify_fail("��ķ���������\n");

	me->add("mp", -(40+me->query_base_mp()/8));
	me->start_busy(2);
	message_vision(HIC"$N����� : ���� �� ����÷�� ...\n"NOR, me);
	call_out("stone", 1, me, target);
	return 1;
}

int stone(object me, object target)
{
	if( random( 60 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		target->start_busy(5);
		me->kill_ob(target);
		target->kill_ob(me);
		message_vision(HIY"$N��ָ��$nһָ����$n���ʯͷ��\n"NOR, me, target);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("�Ҳ����κ�Ŀ��!!\n");
	}
	if( target == me ) return notify_fail("��Ҫ��Ŀ�����ʩ����\n");
	if((int)me->query_mp() < (80+me->query_base_mp()/8) ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -(40+me->query_base_mp()/10));
	me->start_busy(2);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 1, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
        if( !wp ) {
                write("������û������ !!\n");
                return 1;
        }
	if( random( 50 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision(HIG"$N������ӡʧ��, $n����һ���Ѻ�\n", me, wp);
		wp->add("broken", 20);
		return 1;
	}
        if( wp->query("broken") >= 100 ) {
		message_vision(HIG"$N���е�$n���һ����Ƭ...\n", me, wp);
		destruct(wp);
        } else {
		target->start_busy(5);
		me->kill_ob(target);
		target->kill_ob(me);
		message_vision(HIY"$N��ָ��$nһָ����$n���ʯͷ��\n"NOR, me, target);
	}
	return 1;
}
