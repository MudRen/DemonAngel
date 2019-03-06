//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/storm.c
// by bor @DA
// ��ѩ�籩(storm)
/*
> cast storm
   ������� : ÷��÷�� ���� �������� �� �������� ...

   ���ٻ���һ����ѩ�籩���ñ�ѩ��Ϯ�����ڳ��ĵ��ˡ�

*/

#include <ansi.h>

inherit SSERVER;

int cast_spell(object me, object target)
{
	if( me->is_busy() ) return notify_fail("����æ�š�\n");
	if( !me->is_fighting() ) return notify_fail("�㲢����ս���С�\n");
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("�Ҳ����κ�Ŀ��!!\n");
	}
	if( target == me ) return notify_fail("��Ҫ��Ŀ�����ʩ����\n");
	if( (int)me->query_mp() < 100 ) return notify_fail("��ķ���������\n");

	me->add("mp", -100);
	me->start_busy(4);
	message_vision(HIC+"$N����� : ÷��÷�� ���� �������� �� �������� ...\n"NOR, me);
	call_out("storm", 2, me, target);
	return 1;
}

int storm(object me, object target)
{
	object *enemy; 
	int damage;

	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		message_vision(HIY"$N�ٻ���һ����ѩ�籩���ñ�ѩ��Ϯ�����ڳ��ĵ��ˡ�\n"NOR, me);
		damage = (int)(me->query_int()/3+me->query_spell("magic",1)/8 - target->query_db()/2);
		if( damage <=0 ) damage=1;
		enemy = me->query_enemy();
		for(int i=0; i<sizeof(enemy); i++) {
			if( !enemy[i] || environment(enemy[i])!=environment(me) ) continue;
			if( enemy[i] && living(enemy[i]) ) {
				enemy[i]->start_busy(2);
				enemy[i]->receive_damage("hp", damage, me);
				COMBAT_D->report_status(enemy[i]);
			}
		}
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( me->is_busy() ) return notify_fail("����æ�š�\n");
	if( !me->is_fighting() ) return notify_fail("�㲢����ս���С�\n");
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("�Ҳ����κ�Ŀ��!!\n");
	}
	if( target == me ) return notify_fail("��Ҫ��Ŀ�����ʩ����\n");
	if( (int)me->query_mp() < 100 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -70);
 	me->start_busy(4);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 2, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	object *enemy; 
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
		message_vision(HIY"$N�ٻ���һ����ѩ�籩���ñ�ѩ��Ϯ�����ڳ��ĵ��ˡ�\n"NOR, me);
		damage = (int)(me->query_int()/3+me->query_spell("magic",1)/8 - target->query_db()/2);
		if( damage <=0 ) damage=1;
		enemy = me->query_enemy();
		for(int i=0; i<sizeof(enemy); i++) {
			if( !enemy[i] || environment(enemy[i])!=environment(me) ) continue;
			if( enemy[i] && living(enemy[i]) ) {
				enemy[i]->start_busy(2);
				enemy[i]->receive_damage("hp", damage, me);
				COMBAT_D->report_status(enemy[i]);
			}
		}
	}
	return 1;
}
