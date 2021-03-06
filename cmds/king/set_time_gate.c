//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/set_time_gate.c
// by bor @DA, 2/22 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env;
	string file;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式：set_time_gate <here | cancel>\n");
	if( arg!="here" && arg!="cancel" ) return notify_fail("指令格式：set_time_gate <here | cancel>\n");

	switch(arg) {
		case "cancel":
			if( !kingdom_data(me->query("kingdom/id"), "other", "del", "time_gate") )
				return notify_fail("贵国还没有设定时空门。\n");
			message_vision("$N取消了时空门。\n", me);
			break;
		case "here":
			if( !objectp(env = environment(me)) ) return notify_fail("这里属于虚无之地，没办法设定时空门。\n");
			if( file_size(file = base_name(env)+".c") == -1) return notify_fail("你要设定哪里作为贵国的时空门？\n");
			// 我建议各位 Admin 可以将判定是否为贵国房间，写成一个函数，固定判定用，这样可以避免写很多次
			if( !me->query("kingdom/id") || !env->query("kingdom_id")
			|| env->query("kingdom_id") != me->query("kingdom/id")
			) return notify_fail("这里不是贵国的土地。\n");
			kingdom_data(me->query("kingdom/id"), "other", "set", "time_gate", file);
			message_vision("$N将此地设立成时空门。\n", me);
			break;
		default:
	}
	return 1;
}

int help()
{
	write(@HELP

指令格式：set_time_gate <here | cancel>

设定该房间作为连接国家与系统的地点，称之为[时空门]。以后别人可以透过时空门降临贵国
来观光。
	<cancel>	取消时空门

HELP
	);
	return 1;
}
