//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/race/monster.c

#include <race/monster.h>

void setup_monster(object ob)
{
	mapping my;
	string *attr_list = ({"int","dex","con","str","kar","sta"});
	int wg;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));

	if( undefinedp(my["age"]) ) my["age"] = random(13) + 3;

	if( undefinedp(my["level"]) ) my["level"] = 1;

/*	for(int i=0; i<sizeof(attr_list); i++) {
		my["max_"+attr_list[i]] = my["level"] + 1;
	}

	my["max_hp"] = my["max_con"]* 5 + ob->query("apply/con") * 3;
	my["max_mp"] = my["max_int"]* 7 + ob->query("apply/int") * 5;

	if( undefinedp(my["hp"]) ) my["hp"] = my["max_hp"];
	if( undefinedp(my["mp"]) ) my["mp"] = my["max_mp"];

	for(int i=0; i<sizeof(attr_list); i++) {
		my["max_"+attr_list[i]] = my["level"] + 1;
		if( undefinedp(my[attr_list[i]]) ) my[attr_list[i]] = 1;
	}
*/

	for(int i=0; i<sizeof(attr_list); i++) {
		if( undefinedp(my[attr_list[i]]) ) my[attr_list[i]] = my["level"]+1;
	}

//	��ĸ�� hp	����			����			װ��
	my["base_hp"] = 34 + ob->query("con")*5 + ob->query("apply/con")*3 + ob->query_temp("apply/con")*2;
	my["base_mp"] = 20 + ob->query("int")*5 + ob->query("apply/int")*3 + ob->query_temp("apply/int")*2;

	if( undefinedp(my["hp"]) ) my["hp"] = my["base_hp"];
	if( undefinedp(my["mp"]) ) my["mp"] = my["base_mp"];

	ob->set_default_object(__FILE__);

	wg = BASE_WEIGHT + my["level"] * 2/3 + my["str"] * 1000;
	if( wg < 100 ) wg = my["level"] * my["level"] * 10 + 500;

	if( !ob->query_weight() ) ob->set_weight( BASE_WEIGHT );
	ob->set_max_encumbrance( wg );
}

