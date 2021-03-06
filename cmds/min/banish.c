//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/banish.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string *tuned_ch=({});

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式 : banish <某人>\n");

	// 不管你有没有在线上都读取资料
	if( !(ob = find_player(arg)) ) ob = load_player(arg);
	if( !ob ) return notify_fail("这个人已经不存在。\n");

	if( ob == me ) return notify_fail("不能将自己开除。\n");
	if( !ob->query("kingdom") ) return notify_fail("他不属于你的国家 !\n");
	if( ob->query("kingdom/minister") || ob->query("kingdom/king") ) return notify_fail("他贵为贵族，不得草率开除国籍 !!\n");
	if( !people_data(me->query("kingdom/id"), "sub", ob->query("id")) ) return notify_fail("他不属于你的国家 !\n");

	CHANNEL_D->do_channel(me, "kingdom", sprintf("我郑重宣布开除%s的国藉。", ob->name_id(1) ) );

	if( arrayp(tuned_ch = ob->query("channels")) ) {
		if( member_array("kingdom", tuned_ch)!=-1 ) {
			tuned_ch -= ({ "kingdom" });
			ob->set("channels", tuned_ch);
		}
	}
	ob->delete("kingdom");
	ob->save();
	if(find_player(arg)) tell_object( ob, "你成了没有国籍的浪人了。\n");
	if(!find_player(arg)) destruct(ob);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : banish <某人>

这是管理国家人口的指令, 将某人从王国中除名，国王和大臣都能使用，但只有
国王才能开除大臣。

相关讯息 : join, kingdom

HELP
	);
	return 1;
}
