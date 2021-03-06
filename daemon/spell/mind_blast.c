//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/mind_blast.c
// by bor @DA
/*
心灵爆破(mind_blast) 

*/
#include <ansi.h>

inherit SSERVER;

int cast_spell(object me, object target)
{
	if( !me->is_fighting() ) return notify_fail("你并不在战斗中。\n");
	if( me->is_busy() ) return notify_fail("你正忙着。\n");
	if(!target) target = offensive_target(me);
	if((int)me->query_mp() < (30+me->query_base_mp()/10) ) return notify_fail("你的法力不够！\n");

	me->add("mp", -(30+me->query_base_mp()/10));
	me->start_busy(5);
	message_vision(HIC"$N在$N的面前画出各种心灵与魔力的符咒 ...\n"NOR, me);
	call_out("spell_continue", 2, me, target);
	return 1;
}

int spell_continue(object me, object target)
{
	message_vision(HIY"$N画出的符咒开始发出强烈的光芒...\n"NOR, me);
	call_out("spell_continue2", 2, me, target);
}

int spell_continue2(object me, object target)
{
	me->start_busy(2);
	message_vision(HIY"$N朗声念道 :“梦魇的妖精与恐惧的恶魔啊 ～～ 在脆弱的心灵里爆发你的力量吧 !!”\n"NOR, me);
	call_out("mind_blast", 0, me, target);
}

int mind_blast(object me, object target)
{
	object *enemy; 
	int damage, mp=0;

	if( random( 70 ) > me->query_skill("cast",1)*2/3 + me->query_kar()/2 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		enemy = me->query_enemy();
		message_vision(HIR"$N手中一挥，$N面前的符咒突然爆发出强烈的光芒 ...\n"NOR, me);
		for(int i=0; i<sizeof(enemy); i++) {
			if( !enemy[i] || environment(enemy[i])!=environment(me) ) continue;
			if( enemy[i] && living(enemy[i]) ) {
				damage = (int)(me->query_int()/3+me->query_spell("magic",1)/10 - enemy[i]->query_db()/2);
				if( damage <=0 ) damage=1;
				mp += damage/5;
				enemy[i]->start_busy(3);
				enemy[i]->receive_damage("hp", damage, me);
				COMBAT_D->report_status(enemy[i]);
			}
		}
		me->receive_heal("mp", mp);
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !me->is_fighting() ) return notify_fail("你并不在战斗中。\n");
	if((int)me->query_mp() < (30+me->query_base_mp()/10) ) return notify_fail("你的法力不够！\n");
	if( (int)me->query_mp() < (25+me->query_base_mp()/12) ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -(25+me->query_base_mp()/12) );
	me->start_busy(4);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("invoke_continue", 1, me, target, wp);
	return 1;
}

int invoke_continue(object me, object target, object wp)
{
	message_vision(HIY"$N画出的符咒开始发出强烈的光芒...\n"NOR, me);
	call_out("invoke_continue2", 2, me, target);
}

int invoke_continue2(object me, object target, object wp)
{
	me->start_busy(2);
	message_vision(HIY"$N朗声念道 :“梦魇的妖精与恐惧的恶魔啊 ～～ 在脆弱的心灵里爆发你的力量吧 !!”\n"NOR, me);
	call_out("check_wand", 0, me, target);
}

int check_wand(object me, object target, object wp)
{
	object *enemy; 
	int damage, mp=0;

        if( !wp ) {
                write("你身上没有武器 !!\n");
                return 1;
        }
	if( random( 70 ) > me->query_skill("invoke",1)*2/3 + me->query_kar()/2 ) {
		message_vision(HIG"$N启动封印失败, $n出现一道裂痕\n", me, wp);
		wp->add("broken", 20);
		return 1;
	}
        if( wp->query("broken") >= 100 ) {
		message_vision(HIG"$N手中的$n碎成一堆碎片...\n", me, wp);
		destruct(wp);
        } else {
		enemy = me->query_enemy();
		message_vision(HIR"$N手中$n一挥，$N面前的符咒突然爆发出强烈的光芒 ...\n"NOR, me, wp);
		for(int i=0; i<sizeof(enemy); i++) {
			if( !enemy[i] || environment(enemy[i])!=environment(me) ) continue;
			if( enemy[i] && living(enemy[i]) ) {
				damage = (int)(me->query_int()/3+me->query_spell("magic",1)/10 - enemy[i]->query_db()/2);
				if( damage <=0 ) damage=1;
				mp += damage/5;
				enemy[i]->start_busy(3);
				enemy[i]->receive_damage("hp", damage, me);
				COMBAT_D->report_status(enemy[i]);
			}
		}
		me->receive_heal("mp", mp);
	}
	return 1;
}
