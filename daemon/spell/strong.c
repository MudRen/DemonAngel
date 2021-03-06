//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/strong.c
// by bor @ DA

#include <ansi.h>

int cast_spell(object me, object target)
{
        if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	if( !target ) target=me;
	if( target->query_condition("strong") )	{
		write(target==me?"你已经够强壮了。\n":"他已经够强壮了。\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");

	me->add("mp", -20);
	me->start_busy(2);
	message_vision(HIC"$N喃喃念道 : 斯特创 ～ 抛尔 ～ ...\n"NOR,me);
	call_out("strong", 1, me, target);
	return 1;
}

int strong(object me, object target)
{
	me->start_busy(1);

	if(!target) return 0;

	if( random( 40 ) > me->query_skill("cast",1)*3 + me->query_spell("strong", 1)/10 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		// 再判定一次对方是否有 cast 该法术
		if( target->query_condition("strong") ) {
			write(target==me?"你已经够强壮了。\n":"他已经够强壮了。\n");
			return 1;
		} else {
			target->add("apply/str", 9);
			target->apply_condition("strong", 35 );
			message_vision(HIR"$N"HIR"的身边泛起一道红光，$N"HIR"看起来强壮多了！\n\n"NOR, target);
			me->start_busy(1);
		}
	}
	return 1;
}

int invoke(object me, object target, object wp)
{
        if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	if( !target ) target=me;
	if( target->query_condition("strong") )	{
		write(target==me?"你已经够强壮了。\n":"他已经够强壮了。\n");
		return 1;
	}
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -20);
	me->start_busy(2);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random( 40 ) > me->query_skill("invoke",1)*2/3 + me->query_spell("strong", 1)/10 + me->query_kar()*4 ) {
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
		// 再判定一次对方是否有 cast 该法术
		if( target->query_condition("strong") ) {
			write(target==me?"你已经够强壮了。\n":"他已经够强壮了。\n");
			return 1;
		} else {
			target->add("apply/str", 9);
			target->apply_condition("strong", 35 );
			message_vision(HIR"$N"HIR"的身边泛起一道红光，$N"HIR"看起来强壮多了！\n\n"NOR, target);
			me->start_busy(1);
		}
	}
	return 1;
}
