//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/wiz/kickout.c
// by bor @DA

#include <command.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
	seteuid(getuid());
	set("channel_id", "离线精灵(Kickout)");
}

int main(object me, string arg)
{
	object ob;

	if( !arg || arg=="" ) return notify_fail("指令格式：kickout <玩家 id>\n");
	if( !( ob = find_player(arg) )) return notify_fail("没有这个人\n");
	if( wiz_level(me) <= wiz_level(ob) ) return notify_fail("你没有这个权力。\n");

	foreach(object inv in all_inventory(ob) ) {
		if( !inv->query_autoload() ) DROP_CMD->do_drop(ob, inv);
	}
	ob->save();
	CHANNEL_D->do_channel(this_object(), "rumor", ob->name() + "被系统踢出了游戏。");
	destruct(ob);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式: kickout <玩家>

将玩家强迫离开本 mud 。

HELP
	);
	return 1;
}
