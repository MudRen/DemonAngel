//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/char/misc_shop.c
// 这是一个继承档
// type == misc_shop 时会用到

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit NPC;

string *got_list( string dir );
void reset_list();
object find_list(string id);

void setup()
{
	seteuid(getuid());
	reset_list();
	::setup();
}

void init()
{
	object ob = previous_object();

	if( userp(ob) && random( 10 ) > 7 ) {
		message_vision(HIC"$N看到$n, 说道 : 来唷, 来唷, 要买东西找我就对了 !!\n"NOR, this_object(),ob);
	}
	add_action("do_list","list");
	add_action("do_buy","buy");
	::init();
	return;
}

int do_list(string arg)
{
	string msg="", *str, *list=({});

	msg += "目前提供的商品如下, 欢迎购买(buy):\n";

	list = got_list( "/obj/potion/" );

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		msg += sprintf("    %-35s %5d 枚金币  还有 %3d %s\n",
			list[i]->short(1), list[i]->query("value"),
			tmp_dbase["list"][list[i]], list[i]->query("unit"));
	this_player()->start_more(msg);
	return 1;
}

string *got_list( string dir )
{
	string *str, *list=({});

	str = get_dir(dir);
	for(int i=0;i<sizeof(str);i++) {
		if( file_size( dir+str[i] )<0 ) continue;
		if( member_array( dir+str[i], list) != -1 ) continue;
		list += ({ dir+str[i] });
	}
	return list;
}

int do_buy(string arg)
{
	int count = 1;
	string id, file;
	object ob;

	if(!arg) return notify_fail("你要买什么 ?\n");
	if(sscanf(arg,"%d %s", count, id) != 2) id = arg;

	if( !objectp(ob = find_list(id)) )
		return notify_fail("你要买什么东西？\n");

	file = full_name(ob);

	for(int i=0; i<count; i++) {
		if(tmp_dbase["list"][file] < 1) return notify_fail("对不起, 这样东西已经卖完了, 请待会再来。\n");
		if( ob->query("base_value") )
			if(!this_player()->can_afford(ob->query("base_value"))) return notify_fail("你的钱不够。\n");
		else 
			if(!this_player()->can_afford(ob->query("value"))) return notify_fail("你的钱不够。\n");
		if(!ob->move(this_player())) {
			destruct(ob);
			return notify_fail("你拿不动了.\n");
		}
		tmp_dbase["list"][file] -= 1;
		if( ob->query("base_value") )
			this_player()->pay_money(ob->query("base_value"));
		else this_player()->pay_money(ob->query("value"));
		message_vision("$N买下了一"+ob->query("unit")+"$n。\n",this_player(), ob);
	}
	return 1;
}

object find_list(string id)	// 检查你输入要购买的物件是否存在
{
	string *list;
	object ob;

	list = got_list( "/obj/potion/" );

	if( sizeof(list)>0 )
	for(int i=0; i<sizeof(list); i++) {
		ob = new(list[i]);
		if( id != ob->query("id") ) {
			destruct(ob);
			continue;
		}
		return ob;
	}
	return 0;
}

void reset_list()
{
	string *list;
	list = got_list( "/obj/potion/" );
	set_temp("list", ([]));				// 先设定为 [], 方便后来设定

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		tmp_dbase["list"][list[i]] = 30;	// tmp_dbase 的使用方法请参考 dbase.c
	return;
}

nomask void setup_npc()
{
	int level;
	object ob;
	mapping my, skill;

	seteuid(getuid());
	ob = this_object();

	my = ob->query_entire_dbase();
	skill = allocate_mapping(100);
	skill = ob->query_skills();

	if( undefinedp(my["level"]) ) my["level"] = 1;
	if( undefinedp(my["gender"]) ) my["gender"] = "男性";
        if( undefinedp(my["class"]) ) my["class"] = "冒险者";
        if( undefinedp(my["type"]) ) my["type"] = "misc_shop";
        if( undefinedp(my["race"]) ) my["race"] = "人类";
        if( undefinedp(my["unit"]) ) my["unit"] = "位";

	level = my["level"];

// 定义 各属性
	if( undefinedp(my["int"])) my["int"] = level + 7;
	if( undefinedp(my["con"])) my["con"] = level + 7;
	if( undefinedp(my["str"]) ) my["str"] = level + 6;
	if( undefinedp(my["dex"]) ) my["dex"] = level + 6;
	if( undefinedp(my["sta"]) ) my["sta"] = level + 6;
	if( undefinedp(my["kar"]) ) my["kar"] = level + 6;

// 定义 hp, mp, base_hp, 
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
