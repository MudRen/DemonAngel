//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /daemon/spell/coating.c
// by bor @DA
// 魔法镀膜 (coating)
/*
> cast coating
你喃喃唸道 : 厄多厄多 ～～
> 你将魔法力场布在邪龙杖上, 直到邪龙杖发出闪闪光芒 ...

*/
#include <ansi.h>

int cast_spell(object me, object target)
{
	object *ob;
	if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	// target 要装备... 才能 cast
	if( objectp(target) ) {
		if(!target->query("skill_type") || !target->query("equipped"))
			return notify_fail("你必须有武器才能布魔法力场。\n");
	}
	if( !target ) {
		if( sizeof(all_inventory(me)))
		ob = filter(all_inventory(me), (: objectp($1) && $1->query("skill_type") && $1->query("equipped")
		:)  );
		if( sizeof(ob) )target = ob[0];
	}
	if( !target || !target->query("equipped") ) return notify_fail("你必须有武器才能布魔法力场。\n");
	if( target->query_temp("spell_effect/coating") ) return notify_fail("这把武器上已经有魔法力场了。\n");
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");

	me->start_busy(2);
	me->add("mp", -15);
	message_vision(HIC"$N喃喃唸道 : 厄多厄多 ...\n"NOR, me);
	call_out("coating", 0, me, target);
	return 1;
}

int coating(object me, object target)
{
	me->start_busy(1);

	if(!target) return 0;

	if( random( 40 ) > me->query_skill("cast",1)*3 + me->query_spell("coating", 1)/10 + me->query_kar()*4 ) {
		message_vision("$N施法失败了。\n", me);
	} else {
		// 再判定一次 wp 是否有 cast 该法术
		if( target->query_temp("spell_effect/coating") ) {
			write("这把武器上已经有魔法力场了。\n");
			return 1;
		} else {
			string *list=({});
			me->add_temp("apply/str", 1);
			me->add_temp("apply/damage", 10);
			if( !(list = target->query_temp("spell_effect")) )
				target->set_temp("spell_effect", ({ "coating" }));
			else {
				if( member_array("coating", list)==-1 ) {
					list += ({ "coating" });
					target->set_temp("sprll_effect", list);
				}
			}
			target->set_temp("coating_ob", me);
			message_vision(HIY"$N将魔法力场布在$n上, 直到$n发出闪闪光芒 ...\n"NOR, me, target);
			target->set_temp("short", RED"泛红"NOR+ target->query("name") );
			call_out("remove_coating", 60, target);
			me->start_busy(1);
		}
	}
	return 1;
}

int remove_coating(object target)
{
	object ob;

	if( objectp(target) )
		ob = target->query_temp("coating_ob");

	if( objectp(ob) ) {
		ob->add_temp("apply/str", -1);
		ob->add_temp("apply/damage", -10);
	}

	if(objectp(target)) {	// 武器没被销毁
		string *list = ({});
		if( arrayp(list = target->query_temp("spell_effect") ) )
			if( member_array("coating", list) != -1 )
				list -= ({ "coating" });
		if( zerop(list) ) target->delete_temp("spell_effect");
		else target->set_temp("spell_effect", list);

		if( target->query_temp("apply") ) target->delete_temp("apply");

		target->delete_temp("short");
		target->delete_temp("coating_ob");
	}
	message_vision(HIY"飘浮在$N前方的魔法火焰闪了几闪, 消失了。\n"NOR, target);
	return 1;
}

int invoke(object me, object target, object wp)
{
	object *ob;
	if( me->is_busy() ) return notify_fail("你上一个动作还没有完成。\n");
	if( objectp(wp)) target = wp;

	// target 要装备... 才能 cast
	if( objectp(target) ) {
		if(!target->query("skill_type") || !target->query("equipped"))
			return notify_fail("你必须有武器才能布魔法力场。\n");
	}
	if( !target ) {
		if( sizeof(all_inventory(me)))
		ob = filter(all_inventory(me), (: objectp($1) && $1->query("skill_type") && $1->query("equipped")
		:)  );
		if( sizeof(ob) )target = ob[0];
	}
	if( !target || !target->query("equipped") ) return notify_fail("你必须有武器才能布魔法力场。\n");
	if( target->query_temp("spell_effect/coating") ) return notify_fail("这把武器上已经有魔法力场了。\n");
	if( (int)me->query_mp() < 20 ) return notify_fail("你的法力不够！\n");
	if( !wp ) return notify_fail("你身上没有这种东西。\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("这把武器的封印已耗尽了...\n");

	me->add("mp", -10);
	me->start_busy(2);
        message_vision(HIY"$N专心启动$n中封印的力量...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random( 60 ) > me->query_skill("invoke",1)*2/3 + me->query_kar()/4 ) {
		message_vision(HIG"$N启动封印失败, $n出现一道裂痕\n", me, wp);
		wp->add_temp("broken", 20);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N手中的$n碎成一堆碎片...\n", me, wp);
		destruct(wp);
	} else {
		// 再判定一次 wp 是否有 cast 该法术
		if( target->query_temp("spell_effect/coating") ) {
			write("这把武器上已经有魔法力场了。\n");
			return 1;
		} else {
			string *list=({});
			me->add_temp("apply/str", 1);
			me->add_temp("apply/damage", 10);
			if( !(list = target->query_temp("spell_effect")) )
				target->set_temp("spell_effect", ({ "coating" }));
			else {
				if( member_array("coating", list)==-1 ) {
					list += ({ "coating" });
					target->set_temp("sprll_effect", list);
				}
			}
			target->set_temp("coating_ob", me);
			message_vision(HIY"$N将魔法力场布在$n上, 直到$n发出闪闪光芒 ...\n"NOR, me, target);
			target->set_temp("short", RED"泛红"NOR+ target->query("name") );
			call_out("remove_coating", 60, target);
			me->start_busy(1);
		}
	}
	return 1;
}
