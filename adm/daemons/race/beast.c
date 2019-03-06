//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/race/beast.c

#include <race/beast.h>

inherit F_DBASE;

mapping combat_action =
([
	"hoof": ([
		"action":		"$N�ú�����$n��$l����һ��",
		"damage":		100,
		"damage_type":	"����",
	]),
	"bite": ([
		"action":		"$N������������$n��$l�ݺݵ�һҧ",
		"damage":		20,
		"damage_type":	"ҧ��",
	]),
	"claw": ([
		"action":		"$N��צ����$n��$lһץ",
		"damage_type":	"ץ��",
	]),
	"poke": ([
		"action":		"$N������$n��$lһ��",
		"damage":		30,
		"damage_type":	"����",
	]),
]);

string *actions;

void create()
{
	actions = keys(combat_action);
	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );
}

void setup_beast(object ob)
{
	mapping my;
	string *attr_list = ({"int","dex","con","str","kar","sta"});
	int wg;

	my = ob->query_entire_dbase();

	ob->set("default_actions", (: call_other, __FILE__, "query_action" :));

	if( undefinedp(my["age"]) ) my["age"] = random(13) + 3;
	if( undefinedp(my["gender"]) ) my["gender"] = "����";
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

	wg = BASE_WEIGHT + my["level"] * 2/3 + my["str"] * 950;
	if( wg < 100 ) wg = my["level"] * my["level"] * 10 + 500;

	//	NOTE: beast has no initial limbs defined, you must define it yourself.
	//	ob->init_limbs(LIMBS);
	if( !ob->query_weight() ) ob->set_weight( BASE_WEIGHT );
	ob->set_max_encumbrance( wg );
}

mapping query_action(object me)
{
	string *act;

	act = me->query("verbs");
	return combat_action[act[random(sizeof(act))]];
}
