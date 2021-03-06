//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/storm.c
// by bor @DA
// 冰雪风暴(storm)
/*
> cast storm
   你喃喃念道 : 梅加梅加 ～～ 雷依波尔 ～ 雷依凯特 ...

   你召唤出一场冰雪风暴，让冰雪吹袭所有在场的敌人。

*/

#include <ansi.h>

inherit SSERVER;

int cast_spell(object me, object target)
{
	if( me->is_busy() ) return notify_fail("你正忙着。\n");
	if( !me->is_fighting() ) return notify_fail("你并不在战斗中。\n");
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("找不到任何目标!!\n");
	}
	if( target == me ) return notify_fail("你要有目标才能施法。\n");
	if( (int)me->query_mp() < 100 ) return notify_fail("你的法力不够！\n");

	me->add("mp", -100);
	me->start_busy(4);
	message_vision(HIC+"$N喃喃念道 : 梅加梅加 ～～ 雷依波尔 ～ 雷依凯特 ...\n"NOR, me);
	call_out("storm", 2, me, target);
	return 1;
}

int storm(object me, object target)
{
	object *enemy; 
	int damage;

	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		message_vision(HIY"$N召唤出一场冰雪风暴，让冰雪吹袭所有在场的敌人。\n"NOR, me);
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
	if( me->is_busy() ) return notify_fail("你正忙着。\n");
	if( !me->is_fighting() ) return notify_fail("你并不在战斗中。\n");
	if( !target ) {
		if( !(target = offensive_target(me)) )
			return notify_fail("找不到任何目标!!\n");
	}
	if( target == me ) return notify_fail("你要有目标才能施法。\n");
	if( (int)me->query_mp() < 100 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -70);
 	me->start_busy(4);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 2, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	object *enemy; 
	int damage;

	if( random(60) > (me->query_skill("invoke",1)*2/3 +me->query_kar()/4) ) {
		message_vision(HIG"$N启动封印失败, $n出现一道裂痕\n", me, wp);
		wp->add_temp("broken", 20);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N手中的$n碎成一堆碎片...\n", me, wp);
		destruct(wp);
	} else {
		message_vision(HIY"$N召唤出一场冰雪风暴，让冰雪吹袭所有在场的敌人。\n"NOR, me);
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
