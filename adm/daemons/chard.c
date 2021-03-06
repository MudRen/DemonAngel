//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/daemons/chard.c

#include <race.h>

#pragma optimize
#pragma save_binary

void add_corpse(object ob);

static mapping corpse_gourd = ([]);

void create()
{
	seteuid(getuid());
	call_out("refresh_corpse", 30);
}

void setup_char(object ob)
{
	string race;
//	mapping my;

	if( !stringp(race = ob->query("race")) ) {
		race = "人类";
		ob->set("race", "人类");
	}
		
	switch(race) {
		case "人类":
			HUMAN_RACE->setup_human(ob);
			break;
		case "妖魔":
			MONSTER_RACE->setup_monster(ob);
			break;
		case "野兽":
			BEAST_RACE->setup_beast(ob);
			break;
		default:
			error("Chard: undefined race " + race + ".\n");
	}

/*	my = ob->query_entire_dbase();

	if( undefinedp(my["hp"]) ) my["hp"] = my["max_hp"];
	if( undefinedp(my["mp"]) ) my["mp"] = my["max_mp"];

	if( !ob->query_max_encumbrance() )
		ob->set_max_encumbrance( my["str"] * 5000 );
*/
	ob->reset_action();
}

varargs object make_corpse(object victim, object killer)
{
	object corpse, ob;

	if( !killer ) killer = victim->query_temp("last_opponent");
	if( !killer ) killer = victim;

	all_inventory(victim)->owner_is_killed(killer);

//	if( victim->is_ghost() ) return 0;

	corpse = new(CORPSE_OB);
	corpse->set_name( victim->name(1) + "的尸体", ({ "corpse" }) );
	corpse->set("long","这是" + victim->name(1) + "的尸体 - 被 " + killer->short() + " 所杀。\n");
//	corpse->set("age", victim->query("age"));
	corpse->set("gender", victim->query("gender"));
	corpse->set("victim_name", victim->name(1));
	victim->set_temp("corpse", corpse);			// 可用于复活术，不然哪知道你之前是哪一个尸体

	corpse->set_weight( victim->query_weight() );
	corpse->set_max_encumbrance( victim->query_max_encumbrance() );
	corpse->move(environment(victim));
	
	// Don't let wizard left illegal items in their corpses.
	if( !wizardp(victim) ) {
		all_inventory(victim)->owner_killed(killer);
		foreach(object inv in all_inventory(victim)) {
			if(!objectp(inv)) continue;
			if(!inv->move(corpse)) inv->move(environment(victim));
		}
		if(victim->query("gold")>0) {
			ob = new(GOLD_OB);
			ob->set_amount(victim->query("gold"));
			victim->set("gold",0);
			ob->move(corpse);
		}
		if( objectp(killer) ) killer->gain_score("kills", 1);
	}
	// 统一管理尸体的整个运作
	if(objectp(corpse)) add_corpse(corpse);
	return corpse;
}


void add_corpse(object ob)
{
	if(corpse_gourd[ob]) return;
	corpse_gourd[ob] = 10;
	return;
}

void refresh_corpse()
{
	if(zerop(keys(corpse_gourd))||!mapp(corpse_gourd)) {
		call_out("refresh_corpse", 38);
		return;
	}

	map_delete(corpse_gourd, 0);		// 避免被净化掉了
	if(sizeof(keys(corpse_gourd))>0)
	foreach(object ob, int tmp in corpse_gourd) {
		corpse_gourd[ob] -= 1;
		switch(tmp) {
			case 3:
				if(objectp(ob)&&environment(ob)) tell_room(environment(ob), ob->name(1)+"被风吹干了, 变成一具骸骨。\n");
				if(objectp(ob)) {
					ob->set_name("一具枯\干的骸骨", ({"skeleton"}) );
					ob->set("long", "这副骸骨已经躺在这里很久了。\n");
				}
			break;
			case 0:
				if(objectp(ob)&&environment(ob)) tell_room(environment(ob), "一阵风吹过, 把" + ob->name(1)+"化成骨灰吹散了。\n");
				if(objectp(ob)) {
					map_delete(corpse_gourd, ob);
					destruct(ob);
				}
			break;
		}
	}
	call_out("refresh_corpse", 38);
	return;
}
