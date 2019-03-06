//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/char/misc_shop.c
// ����һ���̳е�
// type == misc_shop ʱ���õ�

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
		message_vision(HIC"$N����$n, ˵�� : ���, ���, Ҫ�������ҾͶ��� !!\n"NOR, this_object(),ob);
	}
	add_action("do_list","list");
	add_action("do_buy","buy");
	::init();
	return;
}

int do_list(string arg)
{
	string msg="", *str, *list=({});

	msg += "Ŀǰ�ṩ����Ʒ����, ��ӭ����(buy):\n";

	list = got_list( "/obj/potion/" );

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		msg += sprintf("    %-35s %5d ö���  ���� %3d %s\n",
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

	if(!arg) return notify_fail("��Ҫ��ʲô ?\n");
	if(sscanf(arg,"%d %s", count, id) != 2) id = arg;

	if( !objectp(ob = find_list(id)) )
		return notify_fail("��Ҫ��ʲô������\n");

	file = full_name(ob);

	for(int i=0; i<count; i++) {
		if(tmp_dbase["list"][file] < 1) return notify_fail("�Բ���, ���������Ѿ�������, �����������\n");
		if( ob->query("base_value") )
			if(!this_player()->can_afford(ob->query("base_value"))) return notify_fail("���Ǯ������\n");
		else 
			if(!this_player()->can_afford(ob->query("value"))) return notify_fail("���Ǯ������\n");
		if(!ob->move(this_player())) {
			destruct(ob);
			return notify_fail("���ò�����.\n");
		}
		tmp_dbase["list"][file] -= 1;
		if( ob->query("base_value") )
			this_player()->pay_money(ob->query("base_value"));
		else this_player()->pay_money(ob->query("value"));
		message_vision("$N������һ"+ob->query("unit")+"$n��\n",this_player(), ob);
	}
	return 1;
}

object find_list(string id)	// ���������Ҫ���������Ƿ����
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
	set_temp("list", ([]));				// ���趨Ϊ [], ��������趨

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		tmp_dbase["list"][list[i]] = 30;	// tmp_dbase ��ʹ�÷�����ο� dbase.c
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
	if( undefinedp(my["gender"]) ) my["gender"] = "����";
        if( undefinedp(my["class"]) ) my["class"] = "ð����";
        if( undefinedp(my["type"]) ) my["type"] = "misc_shop";
        if( undefinedp(my["race"]) ) my["race"] = "����";
        if( undefinedp(my["unit"]) ) my["unit"] = "λ";

	level = my["level"];

// ���� ������
	if( undefinedp(my["int"])) my["int"] = level + 7;
	if( undefinedp(my["con"])) my["con"] = level + 7;
	if( undefinedp(my["str"]) ) my["str"] = level + 6;
	if( undefinedp(my["dex"]) ) my["dex"] = level + 6;
	if( undefinedp(my["sta"]) ) my["sta"] = level + 6;
	if( undefinedp(my["kar"]) ) my["kar"] = level + 6;

// ���� hp, mp, base_hp, 
	if( undefinedp(my["base_hp"])) my["base_hp"] = 34 + ob->query("con")*5 + ob->query("apply/con")*3 + ob->query_temp("apply/con")*2;
	if( undefinedp(my["hp"])) my["hp"] = my["base_hp"];
	if( undefinedp(my["base_mp"])) my["base_mp"] = 20 + ob->query("int")*5 + ob->query("apply/int")*3 + ob->query_temp("apply/int")*2;
	if( undefinedp(my["mp"])) my["mp"] = my["base_mp"];

// ��ѧϰ�ļ���
	if(!ob->query_skill("parry")) ob->set_skill("parry", 5 + level * 5);
	if(!ob->query_skill("block")) ob->set_skill("block", 5 + level * 5);
	if(!ob->query_skill("dodge")) ob->set_skill("dodge", 5 + level * 5);
	if(!ob->query_skill("unarmed")) ob->set_skill("unarmed", 5 + level * 5);

// �������������ʹ�õ���� skill, �������������в���....
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

// ���Ϸ�����
	if( undefinedp(ob->query_temp("apply/ac")) ) ob->set_temp("apply/ac", level*5+random(7));
	if( undefinedp(ob->query_temp("apply/db")) ) ob->set_temp("apply/db", level*6+random(7));
	if( undefinedp(ob->query_temp("apply/wl")) ) ob->set_temp("apply/wl", 5 + level*4);
	if( undefinedp(ob->query_temp("apply/Mh")) ) ob->set_temp("apply/Mh", level*2+random(3));
	if( undefinedp(ob->query_temp("apply/mh")) ) ob->set_temp("apply/mh", ob->query_temp("apply/Mh")/2+1 );

	setup();
}
