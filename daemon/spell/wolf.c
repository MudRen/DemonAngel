//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/wolf.c
// by bor @DA
/*
�� ������(wolf)
   �ٻ���һֻ��õ��ǣ�����ķ�����Чǰ�����ᾡȫ�������㡣

> ���૆��� : ÷��÷�� ���� ���� ...
> һ�Ź����������зɳ����ڵ���, գ�ۼ���һͷ���� ...
ħ�ǿ�ʼ�����㡣
ħ���ƶ�����ǰ�棬������ܹ�����

l wo
�㿴��һֻ������ɫƤë�ͼ���Ȯ�ݵĴ���, ������ħ��ʦ��ħ��
����Ļ���, ֻΪ�����������˶�ս��
�����������״��, û�����ˡ�
> ���ħ��ͻȻ����һ��, ��ʧ�ˡ�
ħ��ֹͣ�����㡣
ħ��ֹͣ�����㡣

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");

	me->add("mp", -10);
	me->start_busy(1);
	message_vision(HIC+"$N�૆��� : ÷��÷�� ���� ���� ...\n"NOR,me);
	target = new("/obj/npc/wolf");
	call_out("wolf", 0, me, target);
	return 1;
}

int wolf(object me, object target)
{
	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
		destruct(target);
	} else {
		call_out("remove_wolf", 200, me, target);
		message_vision(HIY"һ�Ź����$N�����зɳ����ڵ���, գ�ۼ���һͷ���� ...\n"NOR, me);
		target->move(environment(me));
		target->set_leader(me);
		message_vision("$N������ʼ����$nһ���ж���\n", target, me);
		target->guard_ob(me);
	}
	return 1;
}

int remove_wolf(object me, object target)
{
	if(!target) return 1;
	if(me) message_vision(HIY"$N��ħ��ͻȻ����һ��, ��ʧ�ˡ�\n"NOR, me);
	if(target) target->set_leader(0);
	me->remove_guard(target);
	destruct(target);
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -10);
	me->start_busy(1);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	target = new("/obj/npc/wolf");
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(40) > (me->query_skill("invoke",1)*2/3 +me->query_kar()*4) ) {
		message_vision(HIG"$N������ӡʧ��, $n����һ���Ѻ�\n"NOR, me, wp);
		wp->add_temp("broken", 20);
		destruct(target);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N���е�$n���һ����Ƭ...\n", me, wp);
		destruct(wp);
		destruct(target);
	} else {
		call_out("remove_wolf", 200, me, target);
		message_vision(HIY"һ�Ź����$N�����зɳ����ڵ���, գ�ۼ���һͷ���� ...\n"NOR, me);
		target->move(environment(me));
		target->set_leader(me);
		message_vision("$N������ʼ����$nһ���ж���\n", target, me);
		target->guard_ob(me);
	}
	return 1;
}
