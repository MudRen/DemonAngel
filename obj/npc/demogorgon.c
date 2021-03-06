//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /obj/npc/demogorgon.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name( HIW "鬼王" NOR, ({ "ghost king" }) );
	set("long",
		"侮天鬼王神情倨傲地站在你面前，他高大的身躯跟一股令人窒息的\n"
		"可怕杀气正压得你几乎喘不过气来，你的心里似乎有一个声音在告\n"
		"诉你：“ 快 逃 ！！”\n");

	set("level", 100);
	setup();
}

void start_shutdown(int min)
{
	if( geteuid(previous_object()) != ROOT_UID ) return;
	message("system", HIY"本 Mud 将在 "+min+" 分钟后重新启动。\n"NOR, users() );
	call_out("countdown", 60, 1);
}

private void countdown(int min)
{
	object link_ob;
	min--;

	if( min ) {
		message("system" ,HIY"本 Mud 将在 "+min+" 分钟后重新启动。\n"NOR, users() );
		call_out("countdown", 60, min);
	} else {
		message("system" ,"游戏重新启动，请稍候一分钟再 login 。\n", users() );
		foreach(object user in users()) {
			if( !objectp(user) ) continue;
			if( !environment(user) ) continue;
			user->set("startroom", base_name(environment(user)));
			user->set("last_on", time());
			user->save();
			if( objectp(link_ob = user->query_temp("link_ob")) )
				link_ob->save();
			reset_eval_cost();
		}
		shutdown(0);
	}
}
