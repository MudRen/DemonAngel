//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/fire.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	int flag = 1;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式：fire <大臣>\n");
	arg = lower_case(arg);
	if( !ob = find_player(arg) ) {
		flag = -1;
		ob = load_player(arg);
	}
	if( !objectp(ob) ) return notify_fail("没有这位玩家\n");
	if( !userp(ob) ) return notify_fail(ob->name() + "他不是玩家。\n");
	if( ob == me ) return notify_fail("你不能开除自己。\n");
	if( !kingdom_data(me->query("kingdom/id"), "power", "sub", "minister", arg) ) return notify_fail("找不到该大臣资料。\n");

        ob->delete("home");
	ob->delete("kingdom/minister");
	if(flag == 1) ob->sub_path( ({"/cmds/min/"}) );
	ob->save();

	CHANNEL_D->do_channel(me, "kingdom", sprintf("我郑重宣布解除"+ob->name_id(1)+"为辅佐大臣的职务。"));
	if( flag == -1) destruct(ob);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : fire <某人>

这个指令可以将王国中的一位辅政大臣贬回英雄。辅政大臣的行政权几乎和国王
相当，有着十分重要的地位，如果国王的辅政大臣行为失当，极有可能激起民变。
一个国家最多能有六位辅政大臣。

相关讯息 : appoint, kingdom_stat

HELP
	);
	return 1;
}
