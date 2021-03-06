//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/summon.c
// by bor @ RG,

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( !arg ) return notify_fail("指令格式：summon <某人>\n");
	arg = lower_case(arg);
	if( !ob = find_player(arg) ) return notify_fail("没有这个人。\n");
	if( ob == me ) return notify_fail("你不能招唤自己。\n");

	if( !ob->query("kingdom/id")
	|| ob->query("kingdom/id") != me->query("kingdom/id") )
		return notify_fail("他并非国民 !!\n");
	if( ob->query("kingdom/king") ) return notify_fail("你不能召唤国王 !!\n");
	if( environment(me)->query("no_summon") ) return notify_fail("这一格不能召唤别人过来。\n");
	if( ob->is_fighting() ) return notify_fail("他正在战斗中。\n");

	tell_room(environment(ob), ob->query("name")+"突然接到"+me->name_id(1)+"的召唤令, 急急忙忙的走了。\n", ob);
	ob->move(environment(me));
	write("你把"+ob->query("name")+"召到你的面前。\n");
	tell_object(ob, me->name_id(1)+"突然派人来召唤你, 你足不点地的被带走了。\n");
	tell_room(environment(ob), ob->query("name")+"突然出现在你眼前。\n",({me,ob}));
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式：summon <某人>

此指令可以让你快速的将国民移到你面前。

相关讯息 : teleport, prison

HELP
	);
	return 1;
}