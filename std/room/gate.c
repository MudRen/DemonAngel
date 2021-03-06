//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/gate.c
// by amgbell @DA, 

inherit ROOM;
#include <ansi.h>

object env = this_object();

void setup()
{
	seteuid(getuid());
	::setup();
}

void init() {

	int change=0;

	add_action("do_limit","limit");


	if (!query("long") || query("long")=="0\n" || query("long")=="0\n\n") {
		set("long",@LONG
这里是一个关卡，路两旁各盖了一作检查哨，路中央还横着拒马，几个
横枪执刀的卫兵正在哨站旁检查行人，并且向他们收过路税。
LONG);
	change=1;
}

	if (!query("short")) {
		set("short","关卡");
		change=1;
	}

	if (!query("limit/pass"))  set("limit/pass","all");

}

int do_limit(string arg){

	string *exits,*limits;
	object me;

	me=this_player();
	exits=(keys(environment(me)->query("exits")));
	limits=({"king_only","minister_only","civil_only","ally_only","all"});
        

	if (!me->query("kingdom/king")) return notify_fail("What？\n");
	if (query("kingdom_id")!=me->query("kingdom/id")) return notify_fail("What？\n");

	if (!arg) {
		write("目前本关卡的限制 : "+query("limit/pass")+"\n" );
		write("限制的方向 : "+query("limit/exit")+"\n");
		return 1;
	}

	if (member_array(arg,exits)!=-1) {
		environment(me)->set("limit/exit",arg);
		do_saveroom(environment(me));
		write("ok!\n");
		return 1;
	}

	if (member_array(arg,limits)!=-1) {
		environment(me)->set("limit/pass",arg);
		do_saveroom(environment(me));
		write("ok!\n");
		return 1;
	}


	return notify_fail(@TEXT
	limit 的指令格式如下 :

	limit               看看目前检查站的限定状态
	limit <方向>        设定往哪个方向的人要检查
	limit <限制性质>    设定限制条件的开关
TEXT);
}

int valid_leave(object me, string dir)	// by bor @DA
{
	if( wizardp(me) ) {
		printf(HIC"[关卡]-> 限制: %s, 方向: %s\n"NOR, env->query("limit/pass"), env->query("limit/exit") );
		return 1;
	}

	if( !env->query("limit/exit")
	|| dir != env->query("limit/exit")
	) return ::valid_leave(me, dir);

	if( env->query("limit/pass")=="all" ) {	// 没有限制的关卡, 可以收税
		int gold;
		gold = kingdom_data(env->query("kingdom_id"), "data", "query_par", "tax");
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") ) {
			if(!me->can_afford(gold) ) return notify_fail("你的钱不够付关税。\n");
			message_vision("$N付了 "+gold+" 枚金币后通过检查哨。\n", me);
			me->pay_money(gold);
			kingdom_data(env->query("kingdom_id"), "data", "add", "gold", gold);
		}
	} else if( env->query("limit/pass")=="king_only" ) {
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") )
			return notify_fail("这里只准本国国王通过。\n");
		else {
			if( !me->query("kingdom/king") ) return notify_fail("这里只准本国国王通过。\n");
		}
	} else if( env->query("limit/pass")=="minister_only" ) {
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") )
			return notify_fail("这里只准本国大臣通过。\n");
		else {
			if( !me->query("kingdom/minister") && !me->query("kingdom/king") )
				return notify_fail("这里只准本国大臣通过。\n");
		}
	} else if( env->query("limit/pass")=="ally_only" ) {
		if( !me->query("kingdom/id") ) return notify_fail("这里只准同盟国通过。\n");
		if( me->query("kingdom/id")!=env->query("kingdom_id") ) {
			if(!kingdom_data(env->query("kingdom_id"), "ally","check", me->query("kingdom/id")))
				return notify_fail("这里只准同盟国通过。\n");
		}
	} else if( env->query("limit/pass")=="civil_only" ) {
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") )
			return notify_fail("这里只准本国国民通过。\n");
	}
	return ::valid_leave(me, dir);
}
