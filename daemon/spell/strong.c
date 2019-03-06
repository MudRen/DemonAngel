//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/strong.c
// by bor @ DA

#include <ansi.h>

int cast_spell(object me, object target)
{
        if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	if( !target ) target=me;
	if( target->query_condition("strong") )	{
		write(target==me?"���Ѿ���ǿ׳�ˡ�\n":"���Ѿ���ǿ׳�ˡ�\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");

	me->add("mp", -20);
	me->start_busy(2);
	message_vision(HIC"$N����� : ˹�ش� �� �׶� �� ...\n"NOR,me);
	call_out("strong", 1, me, target);
	return 1;
}

int strong(object me, object target)
{
	me->start_busy(1);

	if(!target) return 0;

	if( random( 40 ) > me->query_skill("cast",1)*3 + me->query_spell("strong", 1)/10 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		// ���ж�һ�ζԷ��Ƿ��� cast �÷���
		if( target->query_condition("strong") ) {
			write(target==me?"���Ѿ���ǿ׳�ˡ�\n":"���Ѿ���ǿ׳�ˡ�\n");
			return 1;
		} else {
			target->add("apply/str", 9);
			target->apply_condition("strong", 35 );
			message_vision(HIR"$N"HIR"����߷���һ����⣬$N"HIR"������ǿ׳���ˣ�\n\n"NOR, target);
			me->start_busy(1);
		}
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
        if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	if( !target ) target=me;
	if( target->query_condition("strong") )	{
		write(target==me?"���Ѿ���ǿ׳�ˡ�\n":"���Ѿ���ǿ׳�ˡ�\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -20);
	me->start_busy(2);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random( 40 ) > me->query_skill("invoke",1)*2/3 + me->query_spell("strong", 1)/10 + me->query_kar()*4 ) {
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
		// ���ж�һ�ζԷ��Ƿ��� cast �÷���
		if( target->query_condition("strong") ) {
			write(target==me?"���Ѿ���ǿ׳�ˡ�\n":"���Ѿ���ǿ׳�ˡ�\n");
			return 1;
		} else {
			target->add("apply/str", 9);
			target->apply_condition("strong", 35 );
			message_vision(HIR"$N"HIR"����߷���һ����⣬$N"HIR"������ǿ׳���ˣ�\n\n"NOR, target);
			me->start_busy(1);
		}
	}
	return 1;
}
