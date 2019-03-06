//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/magic_shield.c
// by bor @DA
/*
> cast magic_shield
���૆��� : ÷��÷�� ���� ���� ...
> ����ǰ�Ŀ�����ħ������������, �γ�һ��Ʈ����ħ���� ...

*/

#include <ansi.h>

int cast_spell(object me, object target)
{
	if(!target) target = me;
	if( target->query_condition("magic_shield") )	{
		write(target==me?"���Ѿ���ħ�����ˡ�\n":"���Ѿ���ħ�����ˡ�\n");
		return 0;
	}
        if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
        if( (int)me->query("mp") < 12+me->query("int")/2 ) return notify_fail("��ķ���������\n");

        me->add("mp", -(12+me->query("int")/2));
	me->start_busy(1);
	message_vision(HIC"$N�૆��� : ÷��÷�� ���� ���� ...\n"NOR,me);
	call_out("magic_shield",1,me,target);
	return 1;
}

int magic_shield(object me,object target)
{	
	if( random( 60 ) > me->query_spell("magic_shield")/3 + me->query("int")/3 + me->query("magic")/3 )
		message_vision("а��û��������\n", me);
	else {
		// ������ж�һ�ζԷ��Ƿ��ڱ���
		if(!target || environment(target)!=environment(me) ) {
			write("���Ŀ���Ѿ��ܵ��ˡ�\n");
			return 1;
		}
		// ���ж�һ�ζԷ��Ƿ��� cast �÷���
		if( target->query_condition("magic_shield") )	{
			write(target==me?"���Ѿ���ħ�����ˡ�\n":"���Ѿ���ħ�����ˡ�\n");
			return 1;
		} else {
			target->apply_condition("magic_shield", 3+random( me->query("int")/10 ));
			message_vision(HIY"$N��ǰ�Ŀ�����ħ������������, �γ�һ��Ʈ����ħ���� ...\n"NOR, target);
			target->add("apply/ac", 12);
			target->add("apply/db", 8);
		}
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if(!target) target = me;
	if( target->query_condition("magic_shield") )	{
		write(target==me?"���Ѿ���ħ�����ˡ�\n":"���Ѿ���ħ�����ˡ�\n");
		return 0;
	}
	if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	if( (int)me->query("mp") < 12+me->query("int")/2 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

        me->add("mp", -(12+me->query("int")/2));
	me->start_busy(2);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(60) > (me->query_skill("invoke",1)*2/3 + me->query_kar()*4) ) {
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
		if( target->query_condition("magic_shield") )	{
			write(target==me?"���Ѿ���ħ�����ˡ�\n":"���Ѿ���ħ�����ˡ�\n");
			return 1;
		} else {
			me->start_busy(1);
			target->apply_condition("magic_shield",3+random( me->query("int")/10 ));
			message_vision(HIY"$N��ǰ�Ŀ�����ħ������������, �γ�һ��Ʈ����ħ���� ...\n"NOR, target);
			target->add("apply/ac", 12);
			target->add("apply/db", 8);
		}
	}
	return 1;
}
