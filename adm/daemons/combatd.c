//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
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
	CYN "$Nע����$n���ж�����ͼѰ�һ�����֡�\n" NOR,
	CYN "$N������$n��һ��һ������ʱ׼���������ơ�\n" NOR,
	CYN "$N�������ƶ��Ų�����Ҫ�ҳ�$n��������\n" NOR,
	CYN "$NĿ��ת���ض���$n�Ķ�����Ѱ�ҽ��������ʱ����\n" NOR,
	CYN "$N�������ƶ��ŽŲ����Ż����֡�\n" NOR,
});

string *winner_msg = ({
	CYN "\n$N������Ц��˵���������ˣ�\n\n" NOR,
	CYN "\n$N˫��һ����Ц��˵�������ã�\n\n" NOR,
	CYN "\n$Nʤ�����У����Ծ�����ߣ�Ц�������ã�\n\n" NOR,
	CYN "\n$n��ɫ΢�䣬˵��������������\n\n" NOR,
	CYN "\n$n������˼�����˵�����ⳡ�����������ˣ�����������\n\n" NOR,
	CYN "\n$n���һ�ݣ�������Ҿ˵�����������ղ�������Ȼ������\n\n" NOR,
});

*/
string *catch_hunt_msg = ({
	HIW"$Nһ��Ƴ��$n, ���ߡ���һ�����˹��� !\n"NOR,
	HIW"$N����$n��� :���ɶ�, ������ !! ��\n"NOR,
	HIW"$N��$n������������ۺ�, ���̴������� !!\n"NOR,
	HIW"$N��$nһ����, ������˵�ʹ������� !!\n"NOR,
	HIW"$Nһ����$n, ���һ㶣���� :���������� !! ��\n"NOR,
});

void create()
{
	seteuid(getuid());
	set("name", "ս������");
	set("id", "combatd");
}

//string damage_msg(int damage, string type)
string damage_msg(int damage)
{
/*	string str;

//	return "��� " + damage + " ��" + type + "��\n";

	if( damage == 0 ) return "���û������κ��˺���\n";

	switch( type ) {
	case "���":
	case "����":
		if( damage < 10 ) return "���ֻ������ػ���$p��Ƥ�⡣\n";
		else if( damage < 20 ) return "�����$p$l����һ��ϸ����Ѫ�ۡ�\n";
		else if( damage < 40 ) return "������͡���һ������һ���˿ڣ�\n";
		else if( damage < 80 ) return "������͡���һ������һ��Ѫ���ܵ��˿ڣ�\n";
		else if( damage < 160 ) return "������͡���һ������һ���ֳ�������˿ڣ�����$N������Ѫ��\n";
		else return "���ֻ����$nһ���Һ���$w����$p$l����һ������ǵĿ����˿ڣ���\n";
		break;
	case "����":
		if( damage < 10 ) return "���ֻ������ش���$p��Ƥ�⡣\n";
		else if( damage < 20 ) return "�����$p$l�̳�һ�����ڡ�\n";
		else if( damage < 40 ) return "������ۡ���һ��������$n$l����\��\n";
		else if( damage < 80 ) return "������ۡ���һ���̽�$n��$l��ʹ$p�������������˼�����\n";
		else if( damage < 160 ) return "��������͡���һ����$w����$p$l�̳�һ��Ѫ���ɺ���Ѫ������\n";
		else return "���ֻ����$nһ���Һ���$w����$p��$l�Դ���������Ѫ�������أ���\n";
		break;
	case "����":
		if( damage < 10 ) return "���ֻ����������������Ĳ�Ӭ��΢���˵㡣\n";
		else if( damage < 20 ) return "�����$p��$l���һ�����ࡣ\n";
		else if( damage < 40 ) return "���һ�����У�$n��$l��ʱ����һ���ϸߣ�\n";
		else if( damage < 80 ) return "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���\n";
		else if( damage < 120 ) return "������顱��һ����$n����������\n";
		else if( damage < 160 ) return "�����һ�¡��顱��һ�����$n�����˺ü�������һ��ˤ����\n";
		else if( damage < 240 ) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n";
		else return "���ֻ�������顱��һ�����죬$n��һ�����ݰ���˳�ȥ����\n";
		break;
	default:
		if( !type ) type = "�˺�";
		if( damage < 10 ) str =  "���ֻ����ǿ���һ����΢";
		else if( damage < 20 ) str = "��������΢��";
		else if( damage < 30 ) str = "������һ��";
		else if( damage < 50 ) str = "������һ������";
		else if( damage < 80 ) str = "��������Ϊ���ص�";
		else if( damage < 120 ) str = "�������൱���ص�";
		else if( damage < 170 ) str = "������ʮ�����ص�";
		else if( damage < 230 ) str = "�����ɼ������ص�";
		else str =  "�����ɷǳ����µ�����";
		return str + type + "��\n";
	}*/
	string str;
	if( damage <= 0) str = "����û������κ��˺���";
	if( damage >0 && damage <= 5 ) str =  "���ֻ�Ǵ��Ա߲�����";
	if( damage >= 6 && damage <= 10) str =  "��������΢���˺���";
	if( damage >= 11 && damage <= 20) str = "������һ���˺� !";
	if( damage >= 21 && damage <= 30) str = "���һ�����ص��˺� !";
	if( damage >= 31 && damage <= 40) str = "��������Ϊ���ص��˺� !";
	if( damage >= 41 && damage <= 60) str = "�������൱���ص��˺� !";
	if( damage >= 61 && damage <= 90) str = "������ʮ�����ص��˺� !";
	if( damage >= 91 && damage <= 150) str = "�����ɼ������ص��˺� !";
	if( damage >= 151 && damage <= 210) str = "�����ɷǳ����µĴ��� !";
	if( damage >= 211 && damage <= 270) str = "�����ɼ�����µĴ��� !";
	if( damage >= 271) str = "���������$n˺�� !";
	return str+"\n";

}

string eff_status_msg(int ratio)
{
	if( ratio >= 100 ) return HIC "���������״��, û�����ˡ�" NOR;
	if( ratio >= 80 ) return HIG "�ƺ����˵���, ���ǿ���������Ҫ����" NOR;
	if( ratio >= 60 ) return HIG "���˼�����, ����û���˵�Ҫ����" NOR;
	if( ratio >= 40 ) return HIY "�˵����ٵط�, ������\����Ѫ��" NOR;
	if( ratio >= 25 ) return HIY "���ϵ��������˿�, Ѫ����ֹ��" NOR;
	if( ratio >= 10 ) return HIM "������Ѫ, ���˼���, ������Σ�ա�" NOR;
	return HIR "�Ѿ�����һϢ�ˡ�" NOR;
}

string status_msg(int ratio)
{
/*	if( ratio==100 ) return HIG "����������������һ��Ҳ���ۡ�" NOR;
	if( ratio > 95 ) return HIG "�ƺ���Щƣ����������Ȼʮ���л�����" NOR;
	if( ratio > 90 ) return HIY "������������Щ���ˡ�" NOR;
	if( ratio > 80 ) return HIY "�����ƺ���ʼ�е㲻̫��⣬������Ȼ�������ɡ�" NOR;
	if( ratio > 60 ) return HIY "�������꣬������״������̫�á�" NOR;
	if( ratio > 40 ) return HIR "�ƺ�ʮ��ƣ����������Ҫ�ú���Ϣ�ˡ�" NOR;
	if( ratio > 30 ) return HIR "�Ѿ�һ��ͷ�ؽ����ģ������������֧���Ų�����ȥ��" NOR;
	if( ratio > 20 ) return HIR "�������Ѿ����������ˡ�" NOR;
	if( ratio > 10 ) return RED "ҡͷ���ԡ�����бб��վ��վ���ȣ��ۿ���Ҫ���ڵ��ϡ�" NOR;
	return RED "�Ѿ���������״̬����ʱ������ˤ����ȥ��" NOR;*/
	if( ratio >= 100 ) return HIC "( $N���������״��, û�����ˡ� )" NOR;
	if( ratio >= 80 ) return HIG "( $N�ƺ����˵���, ���ǿ���������Ҫ���� )" NOR;
	if( ratio >= 60 ) return HIG "( $N���˼�����, ����û���˵�Ҫ���� )" NOR;
	if( ratio >= 40 ) return HIY "( $N�˵����ٵط�, ������\����Ѫ�� )" NOR;
	if( ratio >= 25 ) return HIY "( $N���ϵ��������˿�, Ѫ����ֹ�� )" NOR;
	if( ratio >= 10 ) return HIM "( $N������Ѫ, ���˼���, ������Σ�ա� )" NOR;
	return HIR "( $N�Ѿ�����һϢ�ˡ� )" NOR;
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
			tell_object(me, sprintf( GRN "AP��%d��DP��%d��PP��%d���˺�����%d\n" NOR,
				ap/100, dp/100, pp/100, damage));
		else
			tell_object(me, sprintf( GRN "AP��%d��DP��%d��PP��%d\n" NOR,
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
			message_vision("$Nһ�����У�¶����������\n", me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_QUICK);
		} else {
			message_vision("$N��$n����ʧ�󣬳û�����������\n", victim, me);
			do_attack(victim, me, victim->query_temp("weapon"), TYPE_RIPOSTE);
		}
	}*/

	if( damage < 1 && random(17) < 1  || random(53)<1 ) {
		if( random(my["kar"]) < random(victim->query("kar")) ) {
			message_vision("$Nһ�����У�¶����������\n", me);
			do_attack(victim, me, victim->query_temp("weapon"));
		} else {
			message_vision("$N��$n����ʧ�󣬳û�����������\n", me, victim);
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
	message_vision("$N��һ������������ɨ�����ڳ���ÿһ���ˡ�\n", me);

	if(	(int)me->query("force") > (random(bellicosity) + bellicosity)/2 ) return;

	if( bellicosity > (int)me->query("score") 
	&&	!wizardp(obj) ) {
		message_vision("$N����$n�ȵ���" + RANK_D->query_self_rude(me)
			+ "����ʵ�ںܲ�˳�ۣ�ȥ���ɡ�\n", me, obj);
		me->kill_ob(obj);
	} else {
		message_vision("$N����$n�ȵ���ι��" + RANK_D->query_rude(obj)
			+ "��" + RANK_D->query_self_rude(me) + "�������˴�ܣ����������ְɣ�\n",
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
			message_vision("\n$N���ˡ�\n\n", ob);
			break;
//		case "unconcious":
//			message_vision("\n$N����һ�����ȣ����ڵ���һ��Ҳ�����ˡ�\n\n", ob);
//			break;
		case "revive":
			message_vision("\n$N���������۾��������˹�����\n\n", ob);
			break;
	}
}

void winner_reward(object killer, object victim)
{
	killer->defeated_enemy(victim);
}

void killer_reward(object killer, object victim)
{	// killer: ɱ����, victim: ��ɱ����
	string id, enemy_id, *arrest_list, file;	// id: killer �Ĺ���, enemy_id: victim �Ĺ���
	int flag = 1, ARR_gold = 5000, gold, lv, exp;	// ARR_gold: ͨ���Ļ������

	// flag = 1	һ�㱻npc����, ��10%
	// flag = 2	��ͨ��, �� 20%
	// flag = 3	war, �� 20%
	// flag = -1	���ۼ���

	if( userp(victim) ) {	// ���������
		// 1. �ж�ɱ���ߵ���֣��Լ������Ѷ
		if( userp(killer) ) { // ɱ����Ϊ���, �ж��Ƿ��� war ��, �� �����з� arrest
			if( !(id = killer->query("kingdom/id")) ) {	// ���ɱ����û����������û�� arrest, �Ǿͱ��ɱ�װ�
				if( !(arrest_list = victim->query("arrest") ) || zerop(arrest_list) ) {
					killer->apply_condition("pker", 300);
					killer->skill_death_penalty(1);
					flag = -1;

					log_file("pk", sprintf("[%s] %s pk %s on %s\n",
						ctime(time())[0..19], killer->name_id(1),
						victim->name_id(1), base_name(environment(killer))
					));
				} else { // �Է��б�ͨ��
					if( !(enemy_id = victim->query("kingdom/id")) ) {	// û�й������Ͳ����ж��Ƿ�war��
						gold = ARR_gold * sizeof(arrest_list);	// ����ͨ��������˳��ȥ������ҵ�ͨ�������Ƿ����
						tell_object( killer,HIY"��ɱ����ͨ�����õ� "+gold+" ö��ҡ�\n"NOR);
						killer->got_money(gold);
						flag = 2;
					}
				}
			} else {	// ��������й���
				if( !(arrest_list = victim->query("arrest") ) || zerop(arrest_list) ) {
					if( !(enemy_id = victim->query("kingdom/id")) ) {
						killer->apply_condition("pker", 300);
						killer->skill_death_penalty(1);
						flag = -1;

						log_file("pk", sprintf("[%s] %s pk %s on %s\n",
							ctime(time())[0..19], killer->name_id(1),
							victim->name_id(1), base_name(environment(killer))
						));
					} else { // �Է��й���, �Ǿ�Ҫ�ж��Ƿ� war
						if( !kingdom_data(id, "war", "check", enemy_id, 1) ) {
							killer->apply_condition("pker", 300);
							killer->skill_death_penalty(1);
							flag = -1;

							log_file("pk", sprintf("[%s] %s pk %s on %s\n",
								ctime(time())[0..19], killer->name_id(1),
								victim->name_id(1), base_name(environment(killer))
							));
						} else {	// ����Է����Լ����� war ..., �Ǿͼ�ս����
							killer->add("war_score/enemy", 1);	// ɱ��������һ
							gold = victim->query("level") * 500;
							killer->add("war_score/gold", gold);
							killer->got_money(gold);

							kingdom_data(id, "war", "add", enemy_id, ({"gold",gold}) );
							kingdom_data(id, "war", "add", enemy_id, ({"enemy",1}) );

							kingdom_data(enemy_id, "war", "add", id, ({"gold_",gold}) );
							kingdom_data(enemy_id, "war", "add", id, ({"enemy_",1}) );

							kingdom_data(enemy_id, "data", "sub", "gold", gold);

							tell_object( killer,HIY"��ɱ�����˵õ� "+gold+" ö��ҡ�\n"NOR);
							flag = 3;
						}
					}
				} else { // �Է��б�ͨ��
					gold = ARR_gold * sizeof(arrest_list);	// ����ͨ��������˳��ȥ������ҵ�ͨ�������Ƿ����
					killer->got_money(gold);
					tell_object( killer,HIY"��ɱ����ͨ�����õ� "+gold+" ö��ҡ�\n"NOR);
					flag = 2;
				}
			}
		}

		// 2. ��ʾ
		CHANNEL_D->do_channel(this_object(), "rumor",
			sprintf("%s��%sɱ���ˡ�", victim->name_id(1), killer->name_id(1) ));

	} else {	// ������߲������
		// 1. �ж�ɱ���ߵ���֣��Լ������Ѷ
		if( userp(killer) ) { // ���ɱ�� npc, ���ж� npc �Ƿ��ǵй��İ�
			if( !(enemy_id = victim->query("kingdom") )	// ɱ��û�й���? ϵͳ NPC?
			|| enemy_id && !check_kingdom(enemy_id)		// �����Ҳ���? �����? or ...
			|| !(id = killer->query("kingdom/id"))		// �Լ�û�й����Ͳ����ж� war
			) {	// �����λд�� npc ������ʾ�� "kingdom" ��
				exp = victim->query("exp");
				lv = victim->query("level");
				if( lv<=0 || lv>50 ) lv = random(30) + 1;
				if( exp <= 0 || exp >= 300000 ) exp = lv*lv*2 + 1000;
				tell_object(killer, "( ��õ� " + exp + " �㾭��ֵ��)\n");
				killer->got_exp(exp);
			} else { // �ж��Ƿ�Ϊ�й��� npc
				if( !kingdom_data(id, "war", "check", enemy_id, 1) ) {
					exp = victim->query("exp");
					lv = victim->query("level");
					if( lv<=0 || lv>50 ) lv = random(30) + 1;
					if( exp <= 0 || exp >= 300000 ) exp = lv*lv*2 + 1000;
					tell_object(killer, "( ��õ� " + exp + " �㾭��ֵ��)\n");
					killer->got_exp(exp);
				} else {
					killer->add("war_score/npc", 1);	// ɱ����������һ
					gold = victim->query("level") * 200;
					killer->add("war_score/gold", gold);
					killer->got_money(gold);
					kingdom_data(id, "war", "add", enemy_id, ({"gold",gold}) );
					kingdom_data(id, "war", "add", enemy_id, ({"npc",1}) );

					kingdom_data(enemy_id, "war", "add", id, ({"gold_",gold}) );
					kingdom_data(enemy_id, "war", "add", id, ({"enemy_",1}) );
					kingdom_data(enemy_id, "data", "sub", "gold", gold);

					tell_object( killer,HIY"��ɱ�������õ� "+gold+" ö��ҡ�\n"NOR);
				}
			}
		} //else {	// npc ɱ�� npc .. ������
//		}
	}

	if( flag == 2 || flag == 3) victim->delete("arrest");

	if(userp(victim)) {
		// �����ۼ���, �Լ����ÿ�Ҫ�۶���, �Լ�ȥ /feature/skill.c �� skill_death_penalty() �����ж�
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

		shout(MAG"��"HIR"ս����"NOR+MAG"��" + victim->name_id(1) + " ��ʵϰս�����˶���, ȡ����ꡣ\n"NOR);
		write(MAG"��"HIR"ս����"NOR+MAG"��" + victim->name_id(1) + " ��ʵϰս�����˶���, ȡ����ꡣ\n"NOR);

		log_file("nuke", sprintf("[%s] system nuke %s for Arrest.\n",
			ctime(time())[0..15], id ));
		destruct(victim);
	}

}
