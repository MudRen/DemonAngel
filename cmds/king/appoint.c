//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/appoint.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式 : appoint <某人> \n");
	if( !me->query("kingdom/id") ) return 0;
	if( !(ob = present(arg, environment(me)) )) return notify_fail("你想任命谁为大臣？\n");
	if( !userp(ob) ) return notify_fail(ob->name() + "不是玩家身份。\n");

	if( ob == me ) return notify_fail("你不能任命自己为大臣。\n");
	if( !ob->query("kingdom/id")
	|| ob->query("kingdom/id") != me->query("kingdom/id") )
		return notify_fail("你想任命外国人为大臣？\n");

	if( ob->query("kingdom/minister") ) return notify_fail("他本来就是大臣 !!\n");
//	if( ob->query("level")<25 ) return notify_fail("他的等级至少要超过 25 级，才能任命为大臣。\n");

	if( sizeof(kingdom_data(me->query("kingdom/id"), "power", "minister", "query_all"))>=6 ) return notify_fail("每个国家最多只能有六位辅佐大臣 !!\n");
	if( !kingdom_data(me->query("kingdom/id"), "power", "add", "minister", ob->query("id")) ) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");

	ob->set("kingdom/minister", ob->query("id"));
	ob->set("home",KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c");
	// 设定大臣基本权力
	ob->add_path( ({"/cmds/min/"}) );
	ob->save();
	CHANNEL_D->do_channel(me, "kingdom", sprintf("我郑重宣布任命"+ob->name_id(1)+"为辅佐大臣。"));
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : appoint <某人>

这个指令可以指定王国中的一位英雄出任辅政大臣。辅政大臣的行政权几乎和国王
相当，有着十分重要的地位，如果国王的辅政大臣行为失当，极有可能激起民变。
一个国家最多能有六位辅政大臣。

相关讯息 : fire, kingdom_stat

HELP
	);
	return 1;
}
