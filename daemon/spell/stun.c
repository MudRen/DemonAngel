//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/stun.c
// by bor @DA

#include <ansi.h>

inherit SSERVER;

int cast_spell(object me, object target)
{
	if( !me->is_fighting() ) return notify_fail("�㲢����ս���С�\n");
	if( me->is_busy() ) return notify_fail("����æ�š�\n");
	target = offensive_target(me);
	if((int)me->query_mp() < (30+me->query_base_mp()/10) ) return notify_fail("��ķ���������\n");

	me->add("mp", -(30+me->query_base_mp()/10));
	me->start_busy(1);
	message_vision(HIC"$N����� : ˿�� �� �׶� �� ...\n"NOR, me);
	call_out("stun", 1, me, target);
	return 1;
}

int stun(object me, object target)
{
	object *enemy; 
	int damage;

	if( random( 60 ) > me->query_skill("cast",1)*2/3 + me->query_kar()/2 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		enemy = me->query_enemy();
		for(int i=0; i<sizeof(enemy); i++) {
			if( !enemy[i] || environment(enemy[i])!=environment(me) ) continue;
			if( enemy[i] && living(enemy[i]) ) {
				damage = (int)(me->query_int()/3+me->query_spell("magic",1)/10 - enemy[i]->query_db()/2);
				if( damage <=0 ) damage=1;
				enemy[i]->start_busy(3);
				enemy[i]->receive_damage("hp", damage, me);
				COMBAT_D->report_status(enemy[i]);
			}
		}
		message_vision(HIY"$N������糡��������е��ˡ�\n"NOR,me);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !me->is_fighting() ) return notify_fail("�㲢����ս���С�\n");
	if((int)me->query_mp() < (30+me->query_base_mp()/10) ) return notify_fail("��ķ���������\n");
	if( (int)me->query_mp() < (25+me->query_base_mp()/12) ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -(25+me->query_base_mp()/12) );
	me->start_busy(1);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	object *enemy; 
	int damage;

        if( !wp ) {
                write("������û������ !!\n");
                return 1;
        }
	if( random( 60 ) > me->query_skill("invoke",1)*2/3 + me->query_kar()/2 ) {
		message_vision(HIG"$N������ӡʧ��, $n����һ���Ѻ�\n", me, wp);
		wp->add("broken", 20);
		return 1;
	}
        if( wp->query("broken") >= 100 ) {
		message_vision(HIG"$N���е�$n���һ����Ƭ...\n", me, wp);
		destruct(wp);
        } else {
		enemy = me->query_enemy();
		for(int i=0; i<sizeof(enemy); i++) {
			if( !enemy[i] || environment(enemy[i])!=environment(me) ) continue;
			if( enemy[i] && living(enemy[i]) ) {
				damage = (int)(me->query_int()/3+me->query_spell("magic",1)/10 - enemy[i]->query_db()/2);
				if( damage <=0 ) damage=1;
				enemy[i]->start_busy(3);
				enemy[i]->receive_damage("hp", damage, me);
				COMBAT_D->report_status(enemy[i]);
			}
		}
		message_vision(HIY"$N������糡��������е��ˡ�\n"NOR,me);
	}
	return 1;
}
