//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/char/barracks.c
// 这是一个继承档
// type == barracks 时会用到

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit NPC;

void init()
{
	object ob = previous_object();

	if(this_object()->query("polite") && userp(ob) && ob->query("level")>=20 )
	if( ob->query("kingdom/id")==this_object()->query("kingdom") ) {
		message_vision(HIC"$N向$n行礼致敬说道 : 非常欢迎$n的到来。\n"NOR, this_object(),ob);
	}

	// 各位如果要补上, 当 npc == barracks 时, 且战争时自动杀敌人, 请在此作判定
	// 或是追杀通缉犯, 还是世仇阿 ... 之类的, 都可以在此写入判定

	::init();
	return;
}

nomask void setup_npc()
{
	int level;
	object ob;
	mapping my, skill;

	seteuid(getuid(this_object()));
	ob = this_object();

	my = ob->query_entire_dbase();
	skill = allocate_mapping(100);
	skill = ob->query_skills();

	if( undefinedp(my["level"]) ) my["level"] = 1;
	if( undefinedp(my["gender"]) ) my["gender"] = "男性";
        if( undefinedp(my["class"]) ) my["class"] = "战士";
        if( undefinedp(my["type"]) ) my["type"] = "barracks";
        if( undefinedp(my["race"]) ) my["race"] = "人类";
        if( undefinedp(my["unit"]) ) my["unit"] = "位";

	level = my["level"];

// 定义 各属性
	if( undefinedp(my["dex"])) my["dex"] = level + 12;
	if( undefinedp(my["con"])) my["con"] = level + 12;
	if( undefinedp(my["str"]) ) my["str"] = level + 7;
	if( undefinedp(my["int"]) ) my["int"] = level + 7;
	if( undefinedp(my["sta"]) ) my["sta"] = level + 7;
	if( undefinedp(my["kar"]) ) my["kar"] = level + 7;

// 定义 hp, mp, base_hp, base_mp
	if( undefinedp(my["base_hp"])) my["base_hp"] = 34 + ob->query("con")*5 + ob->query("apply/con")*3 + ob->query_temp("apply/con")*2;
	if( undefinedp(my["hp"])) my["hp"] = my["base_hp"];
	if( undefinedp(my["base_mp"])) my["base_mp"] = 20 + ob->query("int")*5 + ob->query("apply/int")*3 + ob->query_temp("apply/int")*2;
	if( undefinedp(my["mp"])) my["mp"] = my["base_mp"];

// 所学习的技能
	if(!ob->query_skill("parry")) ob->set_skill("parry", 5 + level * 5);
	if(!ob->query_skill("block")) ob->set_skill("block", 5 + level * 5);
	if(!ob->query_skill("dodge")) ob->set_skill("dodge", 5 + level * 5);
	if(!ob->query_skill("unarmed")) ob->set_skill("unarmed", 5 + level * 5);

// 定义各武器所能使用的最大 skill, 其他武器请自行补上....
	if(!ob->query_skill("sword")) ob->set_skill("sword", 5 + level * 5);
	if(!ob->query_skill("spear")) ob->set_skill("spear", 5 + level * 5);
	if(!ob->query_skill("wand")) ob->set_skill("wand", 5 + level * 5);
	if(!ob->query_skill("hammer")) ob->set_skill("hammer", 5 + level * 5);
	if(!ob->query_skill("axe")) ob->set_skill("axe", 5 + level * 5);
	if(!ob->query_skill("dagger")) ob->set_skill("dagger", 5 + level * 5);
	if(!ob->query_skill("blade")) ob->set_skill("blade", 5 + level * 5);
	if(!ob->query_skill("fork")) ob->set_skill("fork", 5 + level * 5);
	if(!ob->query_skill("throwing")) ob->set_skill("throwing", 5 + level * 5);
	if(!ob->query_skill("whip")) ob->set_skill("whip", 5 + level * 5);
	if(!ob->query_skill("staff")) ob->set_skill("staff", 5 + level * 5);

// 补上防御力
	if( undefinedp(ob->query_temp("apply/ac")) ) ob->set_temp("apply/ac", level*5+random(7));
	if( undefinedp(ob->query_temp("apply/db")) ) ob->set_temp("apply/db", level*6+random(7));
	if( undefinedp(ob->query_temp("apply/wl")) ) ob->set_temp("apply/wl", 5 + level*4);
	if( undefinedp(ob->query_temp("apply/Mh")) ) ob->set_temp("apply/Mh", level*2+random(3));
	if( undefinedp(ob->query_temp("apply/mh")) ) ob->set_temp("apply/mh", ob->query_temp("apply/Mh")/2+1 );

	setup();
}
