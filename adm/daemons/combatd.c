//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/daemons/combatd.c
// modify by bor @DA, 3/6 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

/*string *guard_msg = ({
	CYN "$N注视着$n的行动，企图寻找机会出手。\n" NOR,
	CYN "$N正盯着$n的一举一动，随时准备发动攻势。\n" NOR,
	CYN "$N缓缓地移动脚步，想要找出$n的破绽。\n" NOR,
	CYN "$N目不转睛地盯着$n的动作，寻找进攻的最佳时机。\n" NOR,
	CYN "$N慢慢地移动着脚步，伺机出手。\n" NOR,
});

string *winner_msg = ({
	CYN "\n$N哈哈大笑，说道：承让了！\n\n" NOR,
	CYN "\n$N双手一拱，笑着说道：承让！\n\n" NOR,
	CYN "\n$N胜了这招，向后跃开三尺，笑道：承让！\n\n" NOR,
	CYN "\n$n脸色微变，说道：佩服，佩服！\n\n" NOR,
	CYN "\n$n向后退了几步，说道：这场比试算我输了，佩服，佩服！\n\n" NOR,
	CYN "\n$n向后一纵，躬身做揖说道：阁下武艺不凡，果然高明！\n\n" NOR,
});

*/
string *catch_hunt_msg = ({
	HIW"$N一眼瞥见$n, “哼”的一声冲了过来 !\n"NOR,
	HIW"$N对着$n大喝 :“可恶, 又是你 !! ”\n"NOR,
	HIW"$N和$n仇人相见分外眼红, 立刻打了起来 !!\n"NOR,
	HIW"$N和$n一碰面, 二话不说就打了起来 !!\n"NOR,
	HIW"$N一见到$n, 愣了一愣，大叫 :“我宰了你 !! ”\n"NOR,
});

void create()
{
	seteuid(getuid());
	set("name", "战斗精灵");
	set("id", "combatd");
}

//string damage_msg(int damage, string type)
string damage_msg(int damage)
{
/*	string str;

//	return "造成 " + damage + " 点" + type + "。\n";

	if( damage == 0 ) return "结果没有造成任何伤害。\n";

	switch( type ) {
	case "斫伤":
	case "割伤":
		if( damage < 10 ) return "结果只是轻轻地划破$p的皮肉。\n";
		else if( damage < 20 ) return "结果在$p$l划出一道细长的血痕。\n";
		else if( damage < 40 ) return "结果“嗤”地一声划出一道伤口！\n";
		else if( damage < 80 ) return "结果“嗤”地一声划出一道血淋淋的伤口！\n";
		else if( damage < 160 ) return "结果“嗤”地一声划出一道又长又深的伤口，溅得$N满脸鲜血！\n";
		else return "结果只听见$n一声惨嚎，$w已在$p$l划出一道深及见骨的可怕伤口！！\n";
		break;
	case "刺伤":
		if( damage < 10 ) return "结果只是轻轻地刺破$p的皮肉。\n";
		else if( damage < 20 ) return "结果在$p$l刺出一个创口。\n";
		else if( damage < 40 ) return "结果“噗”地一声刺入了$n$l寸许\！\n";
		else if( damage < 80 ) return "结果“噗”地一声刺进$n的$l，使$p不由自主地退了几步！\n";
		else if( damage < 160 ) return "结果“噗嗤”地一声，$w已在$p$l刺出一个血肉馍糊的血窟窿！\n";
		else return "结果只听见$n一声惨嚎，$w已在$p的$l对穿而出，鲜血溅得满地！！\n";
		break;
	case "瘀伤":
		if( damage < 10 ) return "结果只是轻轻地碰到，比拍苍蝇稍微重了点。\n";
		else if( damage < 20 ) return "结果在$p的$l造成一处瘀青。\n";
		else if( damage < 40 ) return "结果一击命中，$n的$l登时肿了一块老高！\n";
		else if( damage < 80 ) return "结果一击命中，$n闷哼了一声显然吃了不小的亏！\n";
		else if( damage < 120 ) return "结果“砰”地一声，$n退了两步！\n";
		else if( damage < 160 ) return "结果这一下“砰”地一声打得$n连退了好几步，差一点摔倒！\n";
		else if( damage < 240 ) return "结果重重地击中，$n“哇”地一声吐出一口鲜血！\n";
		else return "结果只听见“砰”地一声巨响，$n像一捆稻草般飞了出去！！\n";
		break;
	default:
		if( !type ) type = "伤害";
		if( damage < 10 ) str =  "结果只是勉强造成一处轻微";
		else if( damage < 20 ) str = "结果造成轻微的";
		else if( damage < 30 ) str = "结果造成一处";
		else if( damage < 50 ) str = "结果造成一处严重";
		else if( damage < 80 ) str = "结果造成颇为严重的";
		else if( damage < 120 ) str = "结果造成相当严重的";
		else if( damage < 170 ) str = "结果造成十分严重的";
		else if( damage < 230 ) str = "结果造成极其严重的";
		else str =  "结果造成非常可怕的严重";
		return str + type + "！\n";
	}*/
	string str;
	if( damage <= 0) str = "但是没有造成任何伤害。";
	if( damage >0 && damage <= 5 ) str =  "结果只是从旁边擦过。";
	if( damage >= 6 && damage <= 10) str =  "结果造成轻微的伤害。";
	if( damage >= 11 && damage <= 20) str = "结果造成一处伤害 !";
	if( damage >= 21 && damage <= 30) str = "结果一处严重的伤害 !";
	if( damage >= 31 && damage <= 40) str = "结果造成颇为严重的伤害 !";
	if( damage >= 41 && damage <= 60) str = "结果造成相当严重的伤害 !";
	if( damage >= 61 && damage <= 90) str = "结果造成十分严重的伤害 !";
	if( damage >= 91 && damage <= 150) str = "结果造成极其严重的伤害 !";
	if( damage >= 151 && damage <= 210) str = "结果造成非常可怕的创伤 !";
	if( damage >= 211 && damage <= 270) str = "结果造成极其可怕的创伤 !";
	if( damage >= 271) str = "结果几乎将$n撕裂 !";
	return str+"\n";

}

string eff_status_msg(int ratio)
{
	if( ratio >= 100 ) return HIC "正处于最佳状况, 没有受伤。" NOR;
	if( ratio >= 80 ) return HIG "似乎受了点伤, 但是看起来并不要紧。" NOR;
	if( ratio >= 60 ) return HIG "受了几处伤, 但是没有伤到要害。" NOR;
	if( ratio >= 40 ) return HIY "伤到不少地方, 流了许\多鲜血。" NOR;
	if( ratio >= 25 ) return HIY "身上到处都是伤口, 血流不止。" NOR;
	if( ratio >= 10 ) return HIM "浑身是血, 受伤极重, 有生命危险。" NOR;
	return HIR "已经奄奄一息了。" NOR;
}

string status_msg(int ratio)
{
/*	if( ratio==100 ) return HIG "看起来充满活力，一点也不累。" NOR;
	if( ratio > 95 ) return HIG "似乎有些疲惫，但是仍然十分有活力。" NOR;
	if( ratio > 90 ) return HIY "看起来可能有些累了。" NOR;
	if( ratio > 80 ) return HIY "动作似乎开始有点不太灵光，但是仍然有条不紊。" NOR;
	if( ratio > 60 ) return HIY "气喘嘘嘘，看起来状况并不太好。" NOR;
	if( ratio > 40 ) return HIR "似乎十分疲惫，看来需要好好休息了。" NOR;
	if( ratio > 30 ) return HIR "已经一副头重脚轻的模样，正在勉力支撑着不倒下去。" NOR;
	if( ratio > 20 ) return HIR "看起来已经力不从心了。" NOR;
	if( ratio > 10 ) return RED "摇头晃脑、歪歪斜斜地站都站不稳，眼看就要倒在地上。" NOR;
	return RED "已经陷入半昏迷状态，随时都可能摔倒晕去。" NOR;*/
	if( ratio >= 100 ) return HIC "( $N正处于最佳状况, 没有受伤。 )" NOR;
	if( ratio >= 80 ) return HIG "( $N似乎受了点伤, 但是看起来并不要紧。 )" NOR;
	if( ratio >= 60 ) return HIG "( $N受了几处伤, 但是没有伤到要害。 )" NOR;
	if( ratio >= 40 ) return HIY "( $N伤到不少地方, 流了许\多鲜血。 )" NOR;
	if( ratio >= 25 ) return HIY "( $N身上到处都是伤口, 血流不止。 )" NOR;
	if( ratio >= 10 ) return HIM "( $N浑身是血, 受伤极重, 有生命危险。 )" NOR;
	return HIR "( $N已经奄奄一息了。 )" NOR;
}

varargs void report_status(object ob, int effective)
{
	message_vision( status_msg((int)ob->query_hp() * 100 / (int)ob->query_base_hp() )+"\n", ob);
//	if( effective ) 
//		message_vision( "( $N" + eff_status_msg(
//			(int)ob->query("eff_kee") * 100 / (int)ob->query("max_kee") ) 
//			+ " )\n", ob);
//	else
//		message_vision( "( $N" + status_msg(
//			(int)ob->query("kee") * 100 / (int)ob->query("max_kee") ) 
//			+ " )\n", ob);
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs int skill_power(object ob, string skill, int usage)
{
	int status, level, power;

//	write("skill_power...\n");
	if( !living(ob) ) return 0;

	level = ob->query_skill(skill);

	switch(usage) {
		case SKILL_USAGE_ATTACK:
			level += ob->query_temp("apply/attack");
			break;
		case SKILL_USAGE_DEFENSE:
			level += ob->query_temp("apply/defense");
			break;
	}

	if( !level ) return ob->query("level")*4;

//	if( (status = ob->query("max_sen")) > 0 )
//		power = (level*level*level) / 3 * (int)ob->query("sen") / status;
//	else
//		power = (level*level*level) / 3;

	power += power*3;

	return power;
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
	mapping my, your, action;
	string limb, *limbs, result;
	string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
	mixed foo;
	int ap, dp, pp;
	int damage, damage_bonus, defense_factor;
	int wounded = 0;
	int cost;

	my = me->query_entire_dbase();
	your = victim->query_entire_dbase();

	//
	// (1) Find out what action the offenser will take.
	//

//	write("fighting...\n");
	action = me->query("actions");
	if( !mapp(action) ) {
		me->reset_action();
		action = me->query("actions");
		if( !mapp(action) ) {
			CHANNEL_D->do_channel( this_object(), "sys",
				sprintf("%s(%s): bad action = %O",
					me->name(1), me->query("id"), me->query("actions", 1)));
			return 0;
		}
	}
	result = action["action"] + ", ";

	//
	// (2) Prepare AP, DP for checking if hit.
	//
	if( objectp(weapon) )	attack_skill = weapon->query("skill_type");
	else					attack_skill = "unarmed";

	limbs = victim->query("limbs");
	limb = limbs[random(sizeof(limbs))];

	ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK);
	if( ap < 1) ap = 1;

	dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
	if( dp < 1 ) dp = 1;
	if( victim->is_busy() ) dp /= 3;

	//
	// (3) Fight!
	//     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
	//     AP and DP are greater than zero, so we always have chance to hit
	//     or be hit.
	//
	if( random(ap + dp) < dp ) { 		// Does the victim dodge this hit?

		dodge_skill = victim->query_skill_mapped("dodge");
		if( !dodge_skill ) dodge_skill = "dodge";
		result += SKILL_D(dodge_skill)->query_dodge_msg(limb);

		if( dp < ap && (!userp(victim) || !userp(me)) 
		&&	random(victim->query_hp()*100/victim->query_base_hp() + your["int"]) > 50 ) {
//			your["combat_exp"] += 1;
//			victim->improve_skill("dodge", 1);
		}

		// This is for NPC only. NPC have chance to get exp when fail to hit.
		if( (ap < dp) && !userp(me) ) {
//			if( random(my["int"]) > 15 ) my["combat_exp"] += 1;
//			me->improve_skill(attack_skill, random(my["int"]));
		}
		damage = RESULT_DODGE;

	} else {

		//
		//	(4) Check if the victim can parry this attack.
		//
		if( victim->query_temp("weapon") ) {
			pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE);
			if( !weapon ) pp *= 2;
		} else {
			if( weapon ) pp = 0;
			else pp = skill_power(victim, "unarmed", SKILL_USAGE_DEFENSE);
		}

		if( victim->is_busy() ) pp /= 3;
		if( pp < 1 ) pp = 1;

		if( random(ap + pp)< pp ) {

			parry_skill = victim->query_skill_mapped("parry");
			if( !parry_skill ) parry_skill = "parry";
			// change to SKILL_D(parry_skill) after added parry msg to those
			// martial arts that can parry.
			result += SKILL_D("parry")->query_parry_msg(weapon);

			if( dp < ap && (!userp(victim) || !userp(me)) 
			&&	random(victim->query_hp()*100/victim->query_base_hp() + your["int"]) > 50 ) {
//				your["combat_exp"] += 1;
//				victim->improve_skill("parry", 1);
			}
			damage = RESULT_PARRY;

		} else {

			//
			//	(5) We hit the victim and the victim failed to parry
			//

			damage = me->query_temp("apply/damage");
			damage = (damage + random(damage)) / 2;
			if( action["damage"] )
				damage += action["damage"] * damage / 100;

			damage_bonus = me->query_str();

			// Let force skill take effect.
//			if( my["force_factor"] && (my["force"] > my["force_factor"]) ) {
//				if( force_skill = me->query_skill_mapped("force") ) {
//					foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["force_factor"]);
//					if( stringp(foo) ) result += foo;
//					else if( intp(foo) ) damage_bonus += foo;
//				}
//			}

//			if( action["force"] )
//				damage_bonus += action["force"] * damage_bonus / 100;

			if( martial_skill = me->query_skill_mapped(attack_skill) ) {
				foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			// Let weapon or monster have their special damage.
			if( weapon ) {
				foo = weapon->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			} else {
				foo = me->hit_ob(me, victim, damage_bonus);
				if( stringp(foo) ) result += foo;
				else if(intp(foo) ) damage_bonus += foo;
			}

			if( damage_bonus > 0 )
				damage += (damage_bonus + random(damage_bonus))/2;
			if( damage < 0 ) damage = 0;

			// Let combat exp take effect
//			defense_factor = your["combat_exp"];
//			while( random(defense_factor) > my["combat_exp"] ) {
//				damage -= damage / 3;
//				defense_factor /= 2;
//			}

			//
			//	(6) Inflict the damage.
			//

			damage = victim->receive_damage("hp", damage, me );

//			if( (me->is_killing(victim) || weapon)
//			&& random(damage) > (int)victim->query_temp("apply/armor") ) {
				// We are sure that damage is greater than victim's armor here.
//				victim->receive_wound("hp",
//					damage - (int)victim->query_temp("apply/armor"), me);
//				wounded = 1;
//			}

//			result += damage_msg(damage, action["damage_type"]);
			result += damage_msg(damage);

			//
			//	(7) Give experience
			//

			if( !userp(me) || !userp(victim) ) {
				if( (ap < dp)
				&&	(random(me->query_hp()*100/me->query_base_hp() + my["int"]) > 30) ) {
//					my["combat_exp"] += 1;
//					if( my["potential"] - my["learned_points"] < 100 )
//						my["potential"] += 1;
	//				me->improve_skill(attack_skill, 1);
				}
//				if( random(your["max_kee"] + your["kee"]) < damage ) {
//					your["combat_exp"] += 1;
//					if( your["potential"] - your["learned_points"] < 100 )
//						your["potential"] += 1;
//				}
			}
		}
	} 

	result = replace_string( result, "$l", limb );
	if( objectp(weapon) )
		result = replace_string( result, "$w", weapon->name() );
	else if( stringp(action["weapon"]) )
		result = replace_string( result, "$w", action["weapon"] );

	message_vision(result, me, victim );

	if( wizardp(me) && (string)me->query("env/combat")=="verbose" ) {
		if( damage > 0 )
			tell_object(me, sprintf( GRN "AP：%d，DP：%d，PP：%d，伤害力：%d\n" NOR,
				ap/100, dp/100, pp/100, damage));
		else
			tell_object(me, sprintf( GRN "AP：%d，DP：%d，PP：%d\n" NOR,
				ap/100, dp/100, pp/100));
	}

	if( damage > 0 ) {
		report_status(victim, wounded);
		if( victim->is_busy() ) victim->interrupt_me(me);
//		if( (!me->is_killing(victim)) && (!victim->is_killing(me)) ) {
//			me->remove_enemy(victim);
//			victim->remove_enemy(me);
//			message_vision( winner_msg[random(sizeof(winner_msg))], me, victim);
//		}
	}

	if( functionp(action["post_action"]) )
		evaluate( action["post_action"], me, victim, weapon, damage);

	// See if the victim can make a riposte.
/*	if( attack_type==TYPE_REGULAR
	&&	damage < 1
	&&	victim->query_temp("guarding") ) {
		victim->set_temp("guarding", 0);
		if( random(my["cps"]) < 5 ) {
			message_vision("$N一击不中，露出了破绽！\n", me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
		} else {
			message_vision("$N见$n攻击失误，趁机发动攻击！\n", victim, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
		}
	}*/

	if( damage < 1 && random(17) < 1  || random(53)<1 ) {
		if( random(my["kar"]) < random(victim->query("kar")) ) {
			message_vision("$N一击不中，露出了破绽！\n", me);
			do_attack(victim, me, victim->query_temp("weapon"));
		} else {
			message_vision("$N见$n攻击失误，趁机发动攻击！\n", me, victim);
			do_attack(me, victim, me->query_temp("weapon"));
		}
	}


}

//	fight()
//
//	This is called in the attack() defined in F_ATTACK, which handles fighting
//	in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
        if( !living(me) ) return;
        if (environment(me)!=environment(victim) ) return;
        if( victim->is_busy() || !living(victim) ) {
                me->set_temp("guarding", 0);
                do_attack(me, victim, me->query_temp("weapon"), TYPE_REGULAR);
        } else {
                me->set_temp("guarding", 1);
                do_attack(victim, me, victim->query_temp("weapon"), TYPE_REGULAR);
                return;
        }
        if( !victim->is_fighting(me) ) victim->kill_ob(me);


/*	if( !living(me) ) return;

	if( !victim->is_fighting(me) ) victim->fight_ob(me);

	do_attack(me, victim, me->query_temp("weapon"));
	return;*/
}

//	auto_fight()
//
//	This function is to start an automatically fight. Currently this is
//	used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
//	write("auto_fight.....\n");
	// Don't let NPC autofight NPC.
	if( !userp(me) && !userp(obj) ) return;

	// Because most of the cases that we cannot start a fight cannot be checked
	// before we really call the kill_ob(), so we just make sure we have no 
	// aggressive callout wating here.
	if( me->query_temp("looking_for_trouble") ) return;
	me->set_temp("looking_for_trouble", 1);

	// This call_out gives victim a chance to slip trough the fierce guys.
	call_out( "start_" + type, 0, me, obj);
}

/*
void start_berserk(object me, object obj)
{
	int bellicosity;

	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	bellicosity = (int)me->query("bellicosity");
	message_vision("$N用一种异样的眼神扫视着在场的每一个人。\n", me);

	if(	(int)me->query("force") > (random(bellicosity) + bellicosity)/2 ) return;

	if( bellicosity > (int)me->query("score") 
	&&	!wizardp(obj) ) {
		message_vision("$N对着$n喝道：" + RANK_D->query_self_rude(me)
			+ "看你实在很不顺眼，去死吧。\n", me, obj);
		me->kill_ob(obj);
	} else {
		message_vision("$N对着$n喝道：喂！" + RANK_D->query_rude(obj)
			+ "，" + RANK_D->query_self_rude(me) + "正想找人打架，陪我玩两手吧！\n",
			me, obj);
		me->fight_ob(obj);
	}
}
*/
void start_hatred(object me, object obj)
{
//	write("start_hatred ...\n");
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We found our hatred! Charge!
	message_vision( catch_hunt_msg[random(sizeof(catch_hunt_msg))], me, obj);
	me->kill_ob(obj);
	obj->kill_ob(me);
}

void start_vendetta(object me, object obj)
{
//	write("start_vendetta...\n");
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We found our vendetta opponent! Charge!
	me->kill_ob(obj);
	obj->kill_ob(me);
}

void start_aggressive(object me, object obj)
{
//	write("start_aggressive...\n");
	if( !me || !obj ) return;				// Are we still exist( not becoming a corpse )?

	me->set_temp("looking_for_trouble", 0);

	if(	me->is_fighting(obj)				// Are we busy fighting?
	||	!living(me)							// Are we capable for a fight?
	||	environment(me)!=environment(obj)	// Are we still in the same room?
	||	environment(me)->query("no_fight") 	// Are we in a peace room?
	)	return;

	// We got a nice victim! Kill him/her/it!!!
	me->kill_ob(obj);
	obj->kill_ob(me);
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
	switch(event) {
		case "dead":
			message_vision("\n$N死了。\n\n", ob);
			break;
//		case "unconcious":
//			message_vision("\n$N脚下一个不稳，跌在地上一动也不动了。\n\n", ob);
//			break;
		case "revive":
			message_vision("\n$N慢慢睁开眼睛，清醒了过来。\n\n", ob);
			break;
	}
}

void winner_reward(object killer, object victim)
{
	killer->defeated_enemy(victim);
}

void killer_reward(object killer, object victim)
{	// killer: 杀人者, victim: 被杀的人
	string id, enemy_id, *arrest_list, file;	// id: killer 的国家, enemy_id: victim 的国家
	int flag = 1, ARR_gold = 5000, gold, lv, exp;	// ARR_gold: 通缉的基本金额

	// flag = 1	一般被npc砍死, 扣10%
	// flag = 2	被通缉, 扣 20%
	// flag = 3	war, 扣 20%
	// flag = -1	不扣技能

	if( userp(victim) ) {	// 死者是玩家
		// 1. 判定杀人者的身分，以及相关资讯
		if( userp(killer) ) { // 杀人者为玩家, 判定是否在 war 中, 或 死者有否被 arrest
			if( !(id = killer->query("kingdom/id")) ) {	// 如果杀人者没国籍且死者没被 arrest, 那就变成杀凶吧
				if( !(arrest_list = victim->query("arrest") ) || zerop(arrest_list) ) {
					killer->apply_condition("pker", 300);
					killer->skill_death_penalty(1);
					flag = -1;

					log_file("pk", sprintf("[%s] %s pk %s on %s\n",
						ctime(time())[0..19], killer->name_id(1),
						victim->name_id(1), base_name(environment(killer))
					));
				} else { // 对方有被通缉
					if( !(enemy_id = victim->query("kingdom/id")) ) {	// 没有国籍，就不用判定是否war中
						gold = ARR_gold * sizeof(arrest_list);	// 建议通缉名单内顺便去查各国家的通缉名单是否符合
						tell_object( killer,HIY"你杀死了通缉犯得到 "+gold+" 枚金币。\n"NOR);
						killer->got_money(gold);
						flag = 2;
					}
				}
			} else {	// 如果本身有国家
				if( !(arrest_list = victim->query("arrest") ) || zerop(arrest_list) ) {
					if( !(enemy_id = victim->query("kingdom/id")) ) {
						killer->apply_condition("pker", 300);
						killer->skill_death_penalty(1);
						flag = -1;

						log_file("pk", sprintf("[%s] %s pk %s on %s\n",
							ctime(time())[0..19], killer->name_id(1),
							victim->name_id(1), base_name(environment(killer))
						));
					} else { // 对方有国籍, 那就要判定是否 war
						if( !kingdom_data(id, "war", "check", enemy_id, 1) ) {
							killer->apply_condition("pker", 300);
							killer->skill_death_penalty(1);
							flag = -1;

							log_file("pk", sprintf("[%s] %s pk %s on %s\n",
								ctime(time())[0..19], killer->name_id(1),
								victim->name_id(1), base_name(environment(killer))
							));
						} else {	// 如果对方跟自己国家 war ..., 那就加战功吧
							killer->add("war_score/enemy", 1);	// 杀敌数增加一
							gold = victim->query("level") * 500;
							killer->add("war_score/gold", gold);
							killer->got_money(gold);

							kingdom_data(id, "war", "add", enemy_id, ({"gold",gold}) );
							kingdom_data(id, "war", "add", enemy_id, ({"enemy",1}) );

							kingdom_data(enemy_id, "war", "add", id, ({"gold_",gold}) );
							kingdom_data(enemy_id, "war", "add", id, ({"enemy_",1}) );

							kingdom_data(enemy_id, "data", "sub", "gold", gold);

							tell_object( killer,HIY"你杀死敌人得到 "+gold+" 枚金币。\n"NOR);
							flag = 3;
						}
					}
				} else { // 对方有被通缉
					gold = ARR_gold * sizeof(arrest_list);	// 建议通缉名单内顺便去查各国家的通缉名单是否符合
					killer->got_money(gold);
					tell_object( killer,HIY"你杀死了通缉犯得到 "+gold+" 枚金币。\n"NOR);
					flag = 2;
				}
			}
		}

		// 2. 显示
		CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("%s被%s杀死了。", victim->name_id(1), killer->name_id(1) ));

	} else {	// 如果死者不是玩家
		// 1. 判定杀人者的身分，以及相关资讯
		if( userp(killer) ) { // 玩家杀死 npc, 那判定 npc 是否是敌国的吧
			if( !(enemy_id = victim->query("kingdom") )	// 杀到没有国籍? 系统 NPC?
			|| enemy_id && !check_kingdom(enemy_id)		// 国籍找不到? 被灭国? or ...
			|| !(id = killer->query("kingdom/id"))		// 自己没有国籍就不用判定 war
			) {	// 假设各位写的 npc 国籍标示于 "kingdom" 内
				exp = victim->query("exp");
				lv = victim->query("level");
				if( lv<=0 || lv>50 ) lv = random(30) + 1;
				if( exp <= 0 || exp >= 300000 ) exp = lv*lv*2 + 1000;
				tell_object(killer, "( 你得到 " + exp + " 点经验值。)\n");
				killer->got_exp(exp);
			} else { // 判定是否为敌国的 npc
				if( !kingdom_data(id, "war", "check", enemy_id, 1) ) {
					exp = victim->query("exp");
					lv = victim->query("level");
					if( lv<=0 || lv>50 ) lv = random(30) + 1;
					if( exp <= 0 || exp >= 300000 ) exp = lv*lv*2 + 1000;
					tell_object(killer, "( 你得到 " + exp + " 点经验值。)\n");
					killer->got_exp(exp);
				} else {
					killer->add("war_score/npc", 1);	// 杀守卫数增加一
					gold = victim->query("level") * 200;
					killer->add("war_score/gold", gold);
					killer->got_money(gold);
					kingdom_data(id, "war", "add", enemy_id, ({"gold",gold}) );
					kingdom_data(id, "war", "add", enemy_id, ({"npc",1}) );

					kingdom_data(enemy_id, "war", "add", id, ({"gold_",gold}) );
					kingdom_data(enemy_id, "war", "add", id, ({"enemy_",1}) );
					kingdom_data(enemy_id, "data", "sub", "gold", gold);

					tell_object( killer,HIY"你杀死守卫得到 "+gold+" 枚金币。\n"NOR);
				}
			}
		} //else {	// npc 杀死 npc .. 那算了
//		}
	}

	if( flag == 2 || flag == 3) victim->delete("arrest");

	if(userp(victim)) {
		// 死掉扣技能, 自己斟酌看要扣多少, 自己去 /feature/skill.c 的 skill_death_penalty() 补上判定
		victim->skill_death_penalty(flag);
		victim->save();
	}

	lv = victim->query("level");
	if( flag == 2 && !victim->query("kingdom/king") && lv==1 ) {
		if( id = victim->query("kingdom/id") ) {
			if(victim->query("kingdom/minister")) {
				kingdom_data(id, "power", "sub", "minister", victim->query("id"));
			} else {
				people_data(id, "sub", victim->query("id"));
			}
		}
		id = victim->query("id");
		file = id[0..0] +"/" + id + __SAVE_EXTENSION__;
		assure_file(DATA_DIR+"nuke/login/"+file);
		rename(DATA_DIR+"login/"+file, DATA_DIR+"nuke/login/"+file);
		assure_file(DATA_DIR+"nuke/user/"+file);
		rename(DATA_DIR+"user/"+file, DATA_DIR+"nuke/user/"+file);

		file = id[0..0]+"/"+id+__SAVE_EXTENSION__;
		assure_file(DATA_DIR+"nuke/mail/"+file);
		if( file_size(DATA_DIR+"mail/"+file) != -1)
			rename(DATA_DIR+"mail/"+file, DATA_DIR+"nuke/mail/"+file );

		shout(MAG"“"HIR"战神精灵"NOR+MAG"”" + victim->name_id(1) + " 被实习战神摸了肚脐, 取走灵魂。\n"NOR);
		write(MAG"“"HIR"战神精灵"NOR+MAG"”" + victim->name_id(1) + " 被实习战神摸了肚脐, 取走灵魂。\n"NOR);

		log_file("nuke", sprintf("[%s] system nuke %s for Arrest.\n",
			ctime(time())[0..15], id ));
		destruct(victim);
	}

}
