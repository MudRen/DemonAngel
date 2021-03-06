//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/home.c
// by bor @RG
// modify by bor @DA, 3/9 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if(!me->query("home")) return notify_fail("国家被灭国了, 无法回去了。\n");

	if(!arg) {
		if(environment(me)->query("no_recall"))
			return notify_fail("你突然忘了你的家在哪里？\n");
		message_vision("$N迫不及待的回到自己国内。\n", me);
		if( !me->query("home") || file_size(me->query("home")) == -1 ) {	// 如果你的 home 的档案被砍掉了
			if( file_size(KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c")==-1 ) 
				return notify_fail("国家被灭国了, 无法回去了。\n");
			write("你的家已经被砍掉了，暂时设定家在王座。\n");
			me->set("home", KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c" );
		}
		me->move(me->query("home"));
		me->start_busy(2);
		return 1;
	}
	if(arg=="here") {
		if( !environment(me)->query("kingdom_id")
		|| environment(me)->query("kingdom_id") != me->query("kingdom/id") )
			return notify_fail("这里不是你的国家。\n");
		me->set("home", base_name(environment(me))+".c" );
		write("你把这里当作家了，以后用 home 会回到这里。\n");
	}
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : home <here>

这是国王与大臣用的瞬间传送指令, 可以传送回自己的家。你可以用
home here 来设定自己的家，如果没有设定，会把你传回王座。

HELP
	);
	return 1;
}
