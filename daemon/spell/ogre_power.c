//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/ogre_power.c
// by bor @ DA
/*
	��ħ֮��(ogre_power)

   ������� : ����÷�� ���� ����÷�� ...
   
   ����һ����������������׹� ...

   (��ʧʱ)
   �㽥��ƽ��������

*/
#include <ansi.h>

int cast_spell(object me, object target)
{
        if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	target = me;
	if( target->query_condition("ogre_power") )	{
		write(target==me?"���Ѿ��ڿ�״̬�ˡ�\n":"���Ѿ��ڿ�״̬�ˡ�\n");
		return 1;
	}
	if( (int)me->query_mp() < 30 ) return notify_fail("��ķ���������\n");

	me->add("mp", -25);
	me->start_busy(2);
	message_vision(HIC"$N����� : ����÷�� ���� ����÷�� ...\n"NOR, me);
	call_out("ogre_power", 1, me, target);
	return 1;
}

int ogre_power(object me, object target)
{
	me->start_busy(1);

	if(!target) return 1;

	if( random( 40 ) > me->query_skill("cast",1)*3 + me->query_spell("strong", 1)/10 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		// ���ж�һ�ζԷ��Ƿ��� cast �÷���
		if( target->query_condition("ogre_power") ) {
			write(target==me?"���Ѿ��ڿ�״̬�ˡ�\n":"���Ѿ��ڿ�״̬�ˡ�\n");
			return 1;
		} else {
			target->add("apply/str", 12);
			target->apply_condition("ogre_power", 60 );
			me->start_busy(1);
			message_vision(HIR"$N���һ����������������׹� ...\n"NOR, target);
		}
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
        if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	target = me;
	if( target->query_condition("ogre_power") )	{
		write(target==me?"���Ѿ��ڿ�״̬�ˡ�\n":"���Ѿ��ڿ�״̬�ˡ�\n");
		return 1;
	}
	if( (int)me->query_mp() < 30 ) return notify_fail("��ķ���������\n");
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
	if( random( 40 ) > me->query_skill("invoke",1)*2/3 + me->query_kar()*2 ) {
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
		if( target->query_condition("ogre_power") ) {
			write(target==me?"���Ѿ���ǿ׳�ˡ�\n":"���Ѿ���ǿ׳�ˡ�\n");
			return 1;
		} else {
			target->add("apply/str", 12);
			target->apply_condition("ogre_power", 60 );
			me->start_busy(1);
			message_vision(HIR"$N���һ����������������׹� ...\n"NOR, target);
		}
	}
	return 1;
}
