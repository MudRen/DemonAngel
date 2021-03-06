//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/magic_shield.c
// by bor @DA
/*
> cast magic_shield
你喃喃唸道 : 梅尔梅尔 ～～ 赛尔 ...
> 你面前的空气在魔法下凝聚起来, 形成一面飘浮的魔法盾 ...

*/

#include <ansi.h>

int cast_spell(object me, object target)
{
	if(!target) target = me;
	if( target->query_condition("magic_shield") )	{
		write(target==me?"你已经有魔法盾了。\n":"他已经有魔法盾了。\n");
		return 0;
	}
        if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
        if( (int)me->query("mp") < 12+me->query("int")/2 ) return notify_fail("你的法力不够！\n");

        me->add("mp", -(12+me->query("int")/2));
	me->start_busy(1);
	message_vision(HIC"$N喃喃唸道 : 梅尔梅尔 ～～ 赛尔 ...\n"NOR,me);
	call_out("magic_shield",1,me,target);
	return 1;
}

int magic_shield(object me,object target)
{	
	if( random( 60 ) > me->query_spell("magic_shield")/3 + me->query("int")/3 + me->query("magic")/3 )
		message_vision("邪神并没有听见。\n", me);
	else {
		// 最后在判定一次对方是否在本格
		if(!target || environment(target)!=environment(me) ) {
			write("你的目标已经跑掉了。\n");
			return 1;
		}
		// 再判定一次对方是否有 cast 该法术
		if( target->query_condition("magic_shield") )	{
			write(target==me?"你已经有魔法盾了。\n":"他已经有魔法盾了。\n");
			return 1;
		} else {
			target->apply_condition("magic_shield", 3+random( me->query("int")/10 ));
			message_vision(HIY"$N面前的空气在魔法下凝聚起来, 形成一面飘浮的魔法盾 ...\n"NOR, target);
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
		write(target==me?"你已经有魔法盾了。\n":"他已经有魔法盾了。\n");
		return 0;
	}
	if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	if( (int)me->query("mp") < 12+me->query("int")/2 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

        me->add("mp", -(12+me->query("int")/2));
	me->start_busy(2);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random(60) > (me->query_skill("invoke",1)*2/3 + me->query_kar()*4) ) {
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
		if( target->query_condition("magic_shield") )	{
			write(target==me?"你已经有魔法盾了。\n":"他已经有魔法盾了。\n");
			return 1;
		} else {
			me->start_busy(1);
			target->apply_condition("magic_shield",3+random( me->query("int")/10 ));
			message_vision(HIY"$N面前的空气在魔法下凝聚起来, 形成一面飘浮的魔法盾 ...\n"NOR, target);
			target->add("apply/ac", 12);
			target->add("apply/db", 8);
		}
	}
	return 1;
}
