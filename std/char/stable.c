//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/char/stable.c
// 这是一个继承档
// type == stable 时会用到

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit NPC;

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
	if( undefinedp(my["gender"]) ) my["gender"] = "雄性";
//        if( undefinedp(my["class"]) ) my["class"] = "牧师";
        if( undefinedp(my["type"]) ) my["type"] = "stable";
        if( undefinedp(my["race"]) ) my["race"] = "野兽";
        if( undefinedp(my["unit"]) ) my["unit"] = "只";

	level = my["level"];

// 定义 各属性
	if( undefinedp(my["int"])) my["int"] = level + 12;
	if( undefinedp(my["con"])) my["con"] = level + 8;
	if( undefinedp(my["str"]) ) my["str"] = level + 6;
	if( undefinedp(my["dex"]) ) my["dex"] = level + 6;
	if( undefinedp(my["sta"]) ) my["sta"] = level + 6;
	if( undefinedp(my["kar"]) ) my["kar"] = level + 6;

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

// 补上防御力
	if( undefinedp(ob->query_temp("apply/ac")) ) ob->set_temp("apply/ac", level*5+random(7));
	if( undefinedp(ob->query_temp("apply/db")) ) ob->set_temp("apply/db", level*6+random(7));
	if( undefinedp(ob->query_temp("apply/wl")) ) ob->set_temp("apply/wl", 5 + level*4);
	if( undefinedp(ob->query_temp("apply/Mh")) ) ob->set_temp("apply/Mh", level*2+random(3));
	if( undefinedp(ob->query_temp("apply/mh")) ) ob->set_temp("apply/mh", ob->query_temp("apply/Mh")/2+1 );

	setup();
}
