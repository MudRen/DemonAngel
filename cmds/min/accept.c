//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/accept.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string *tuned_ch=({});

	seteuid(getuid(me));
	if( !arg ) return notify_fail("指令格式：accept <某人>\n");
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !( ob = present(arg, environment(me)) ) ) return notify_fail("他人不在你身边。\n");
	if( !userp(ob) || !ob->query_temp("join") ) return notify_fail("他并没有提出国籍申请 !\n");
	if( ob == me) return notify_fail("你已经是这个国家的人民了。\n");
	if( !(ob->query_temp("join")==me) ) return notify_fail("他并没有向你提出入国申请 !\n");
	if(!people_data(me->query("kingdom/id"), "add", ob->query("id"))) return notify_fail("资料有误，无法收人。\n");

	if( !arrayp(tuned_ch = ob->query("channels")) ) {
		ob->set("channels", ({"kingdom"}));
	} else {
		if( member_array("kingdom", tuned_ch)==-1 ) {
			tuned_ch += ({ "kingdom" });
			ob->set("channels", tuned_ch);
		}
	}

	ob->delete_temp("join");
	ob->set("kingdom/id", me->query("kingdom/id"));
	ob->save();
	message_vision( "$N决定收$n当国民。\n", me, ob);
	CHANNEL_D->do_channel(ob, "kingdom",
		sprintf("我 - %s即日起宣示效忠%s。", ob->name_id(1), full_kingdom(ob->query("kingdom/id")) ));
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : accept <某人>

这个指令可以用来是否接受对方加入本国的申请，但是只限于贵族方
能使用。

相关讯息 : join, kingdom_stat, people

HELP
	);
	return 1;
}
