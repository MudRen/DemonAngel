//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/magic_missile.c
// by bor @DA
// 魔法弹(magic_missle)
/*
> cast magic_missle on c
  你喃喃唸道 : 厄多纳纳 ～～ 厄多纳纳 ...

  一颗魔法弹逐渐在你手中成形 ...

  你向巴瑟丢出魔法弹, “轰隆”一声, 魔法弹在巴瑟的脸上炸开 ...

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( me->is_busy() ) return notify_fail("你正忙着。\n");
	if( !target ) return notify_fail("找不到任何目标!!\n");
	if( target == me ) return notify_fail("你要有目标才能施法。\n");
	if( (int)me->query_mp() < 30 ) return notify_fail("你的法力不够！\n");

	me->add("mp", -20);
	me->start_busy(1);
	message_vision(HIC+"$N喃喃唸道 : 厄多纳纳 ～～ 厄多纳纳 ...\n\n"NOR, me);
	call_out("magic_missle", 0, me, target);
	return 1;
}

int magic_missle(object me, object target)
{
	int damage;
	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		// 最后在判定一次对方是否在本格
		if(!target || environment(target)!=environment(me)) {
			write("你的目标已经跑掉了。\n");
			return 1;
		}
		message_vision(HIY"一颗魔法弹逐渐在$N手中成形 ...\n\n"NOR, me);
		message_vision(HIY"$N向$n丢出魔法弹, “轰隆”一声, 魔法弹在$n的脸上炸开 ...\n"NOR, me, target);
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
	if( me->is_busy() ) return notify_fail("你正忙着。\n");
	if( !target ) return notify_fail("找不到任何目标!!\n");
	if( target == me ) return notify_fail("你要有目标才能施法。\n");
	if( (int)me->query_mp() < 30 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -17);
 	me->start_busy(1);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
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
		// 最后在判定一次对方是否在本格
		if(!target || environment(target)!=environment(me) ) {
			write("你的目标已经跑掉了。\n");
			return 1;
		}
		message_vision(HIY"一颗魔法弹逐渐在$N手中成形 ...\n\n"NOR, me);
		message_vision(HIY"$N向$n丢出魔法弹, “轰隆”一声, 魔法弹在$n的脸上炸开 ...\n"NOR, me, target);
		damage = 20 + random(4);
		target->receive_damage("hp", damage, me);
		COMBAT_D->report_status(target);
		me->kill_ob(target);
		target->kill_ob(me);
		target->start_busy(1);
	}
	return 1;
}
