//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/firefly.c
// by bor @DA
// 萤光术(firefly)
/*
cast firefly
你喃喃唸道 : 光之神提洛啊 ～～ 赐您的光芒给您的仆人吧 ...
> 四周无数小光粒向你聚集, 你的身体竟然发出萤光来。

你身上的萤光渐渐淡去, 最后恢复正常。

*/

#include <ansi.h>

inherit SKILL;

int cast_spell(object me, object target)
{
	if( !target ) target = me;

	// 不想用 condition 的型态撰写
	if( target->query_temp("light") ) {
		write(target==me?"你四周围绕着许\多光芒。\n":"他四周围绕着许\多光芒。\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");

	me->add("mp", -10);
	me->start_busy(1);
	message_vision(HIC+"$N喃喃唸道 : 芙兰多纳 ～～ 贺鲁 ...\n"NOR,me);
	call_out("magefire", 0, me, target);
	return 1;
}

int magefire(object me, object target)
{
	if( random( 40 ) > me->query_skill("cast",1)*2/3 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		// 最后在判定一次对方是否在本格
		if(!target||environment(target)!=environment(me)) {
			write("你的目标已经跑掉了。\n");
			return 1;
		}
		// 再判定一次对方式否有 cast 该法术
		if( target->query_temp("light") ) {
			write(target==me?"你四周围绕着许\多光芒。\n":"他四周围绕着许\多光芒。\n");
			return 1;
		}
		target->add_temp("light",1);
		call_out("remove_magefire", 200, target);
		message_vision(HIY"一颗火球在$N两掌之间成形, 缓缓飘上空中 ...\n"NOR, target);
	}
	return 1;
}

int remove_magefire(object target)
{
	if(!target) return 1;
	if(!target->query_temp("light")) return 1;
	target->delete_temp("light");
	message_vision(HIY"飘浮在$N前方的魔法火焰闪了几闪, 消失了。\n"NOR, target);
	return 1;
}

int invoke(object me, object target, object wp)
{
	if( !target ) target = me;
	if( target->query_temp("light") ) {
		write(target==me?"你四周围绕着许\多光芒。\n":"他四周围绕着许\多光芒。\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -10);
	me->start_busy(1);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(40) > (me->query_skill("invoke",1)*2/3 +me->query_kar()/4) ) {
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
		// 再判定一次对方式否有 cast 该法术
		if( target->query_temp("light") )	{
			write(target==me?"你四周围绕着许\多光芒。\n":"他四周围绕着许\多光芒。\n");
			return 1;
		}
		target->add_temp("light", 1);
		message_vision(HIY"一颗火球在$N两掌之间成形, 缓缓飘上空中 ...\n"NOR, target);
		call_out("remove_magefire", 200, target);
	}
	return 1;
}
