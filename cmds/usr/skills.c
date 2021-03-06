//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/skills.c
// by bor @DA

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mapping sk;
	string *sk_name, msg="";

	seteuid(getuid());
	if( !arg ) ob = me;
	else {
		if( wizardp(me) ) {	// 如果你是巫师，则可以察看玩家的技能
			arg = lower_case(arg);
			if( !ob = present(arg, environment(me)) )
				ob = find_player(arg);
			if( !ob ) ob = load_player(arg);
			if( !ob ) return notify_fail("没有这位玩家资料。\n");
		} else ob = me;
	}

	if( zerop(sk = ob->query_skills()) )
		return notify_fail( (ob==me?"你":ob->name_id())+"目前并没有学会任何技能。\n");

	sk_name  = keys(sk);

	if( ob == me ) msg += "你目前所学过的技能：\n\n";
	else msg += ob->name_id()+"目前所学过的技能：\n\n";

	for(int i=0; i<sizeof(sk_name); i++) {
		msg += sprintf("%-40s%3d\n",to_chinese(sk_name[i])+"("+sk_name[i]+")",
			sk[sk_name[i]] );
	}

	if( userp(ob) && !find_player(ob->query("id")) ) destruct(ob);
	reset_eval_cost();
	me->start_more(msg);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : skills

这个指令可以让你(你)查询所学过的技能。

相关讯息 : attribute, list, cost, kingdom, die

HELP
	);
	return 1;
}
