//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /feature/attack.c

#include <ansi.h>
#include <dbase.h>
#include <name.h>
#include <origin.h>
#include <skill.h>

#define MAX_OPPONENT	4

static object *enemy = ({});
static string *killer = ({});
static object charge_target = 0;
static object *guarding = ({}), *guarded = ({});

// prototypes

object *query_enemy() { return enemy; }
string *query_killer() { return killer; }
object query_charging() { return charge_target; }
object *query_guarding() { return guarding; }
object *query_guarded() { return guarded; }

void fight_ob(object ob);

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_fighting(object ob)
{
	if( !ob ) return sizeof(enemy) > 0;

	return member_array(ob, enemy)!=-1;
}

// This function returns 1 if we are fighting anyone (or with ob)
varargs int is_killing(string id)
{
	if( !id ) return sizeof(killer) > 0;

	return member_array(id, killer)!=-1;
}

varargs int is_guarding(object ob)
{
	if( !ob ) return sizeof(guarding) > 0;

	return member_array(ob, guarding)!=-1;
}

varargs int is_guarded(object ob)
{
	if( !ob ) return sizeof(guarded) > 0;

	return member_array(ob, guarded)!=-1;
}


// add_guard()
//
// Let someone guard us when another one try to kill us.

void add_guard(object ob)
{
    if( member_array(ob, guarded) >= 0 ) return;

    tell_object(this_object(), HIY + ob->name() + "��ʼ�����㡣\n" NOR);
    guarded += ({ ob });
}

// remove_guard()
//
// Remove someone who is not guarding us any more.

void remove_guard(object ob)
{
    if( member_array(ob, guarded) < 0 ) return;

    guarded -= ({ ob, 0 });
    tell_object(this_object(), HIY + ob->name() + "���ٱ������ˡ�\n"+ 
	NOR);
}

void sub_guard(object ob)
{
	if( objectp(ob) ) {
		guarding -= ({ ob });
		ob->remove_guard(this_object());
	}
}

// wake_guard()
//
// This function returns awaken guards that is not yet fighting specific
// enemy. Visibility of enemy and presence of guard is also checked.

object *wake_guard(object target)
{
    return filter(guarded, (:
	objectp($1)
	&& living($1)
	&& environment($1)==environment()
	&& (!$1->is_fighting($(target)))
	&& $(target)->visible($1) :),
    );
}

// activate_guard()
//
// Activate guarding action upon specific target. Default action is to fight
// target.

void activate_guard(object target)
{
    fight_ob(target);
}

// guard_ob()
//
// Set this character to guard someone. guard_ob(0) to clear guarding status.

void
guard_ob(object ob)
{
	if( objectp(ob) ) {
		if( member_array(ob, guarding)==-1 ) guarding += ({ ob });
		ob->add_guard(this_object());
	}
}

//This function starts fight between this_object() and ob
void fight_ob(object ob)
{
	object *guard;

	if(!ob || ob==this_object()) return;

	if( sizeof(guarding)>0 && member_array(ob, guarding)!=-1 ) {
		tell_object(this_object(), HIY + ob->name() + "���ٱ������ˡ�\n" NOR);
		guarding -= ({ ob });
		ob->remove_guard(this_object());
	}

	set_heart_beat(1);

	if( member_array(ob, enemy)==-1 ) 
		enemy += ({ ob });

	// Check if any characters is guarding the target, and let them join
	// the fight.
	guard = ob->wake_guard(this_object());
	if( sizeof(guard) ) {
//		message("system", HIY + ob->name() + "�����ܹ���������ǰ��ս��\n" NOR, guard);
		guard->activate_guard(this_object());
		enemy += guard;
	}

}

// This function starts killing between this_object() and ob
void kill_ob(object ob)
{
	if( sizeof(guarded)>0 && member_array(ob, guarded)!=-1 ) {
		tell_object(this_object(), HIY + ob->name() + "���ٱ������ˡ�\n" NOR);
		guarded -= ({ ob });
		ob->remove_guard(this_object());
	}

	if( member_array(ob->query("id"), killer)==-1 ) killer += ({ ob->query("id") });
//	tell_object(ob, HIR "������" + this_object()->name() + "��ɱ���㣡\n" NOR);

	fight_ob(ob);
}

// charge_ob()
//
// This function promotes ob to the first target to attack.
void
charge_ob(object ob)
{
	if( ! ob ) { charge_target = 0; return; }

	if( member_array(ob, enemy) < 0 ) enemy += ({ ob });
	tell_object(this_object(), HIY "�㿪ʼ��" + ob->name() + "������Ҫ����Ŀ�꣡\n" NOR);
	charge_target = ob;
}

void clean_up_enemy()
{
	if( sizeof(enemy) > 0 ) {
		for(int i=0; i<sizeof(enemy); i++) {
			if( !objectp(enemy[i])
//			||	environment(enemy[i])!=environment()
			||	(!living(enemy[i]) && !is_killing(enemy[i]->query("id"))) )
				enemy[i] = 0;
		}
		enemy -= ({ 0 });
	}
}

// This function checks if the current opponent is available or
// select a new one.
object select_opponent()
{
	int which;

	if( !sizeof(enemy) ) return 0;

	which = random(MAX_OPPONENT);

	return which < sizeof(enemy) ? enemy[which] : enemy[0];
}

// Stop fighting ob.
int remove_enemy(object ob)
{
	if( is_killing(ob->query("id")) ) return 0;

	enemy -= ({ ob });
	return 1;
}

// Stop killing ob.
int remove_killer(object ob)
{
	if( is_killing(ob->query("id")) ) {
		killer -= ({ ob->query("id") });
		remove_enemy(ob);
		return 1;
	}

	return remove_enemy(ob);
}

// remove_charge()
//
// Stop charging specific object;

int remove_charge()
{
	charge_target = 0;
}

// Stop all fighting, but killer remains.
void remove_all_enemy()
{
	for(int i=0; i<sizeof(enemy); i++) {
		// We ask our enemy to stop fight, but not nessessary to confirm
		// if the fight is succeffully stopped, bcz the fight will start
		// again if our enemy keeping call COMBAT_D->fight() on us.
		if( objectp(enemy[i]) ) enemy[i]->remove_enemy(this_object());
		enemy[i] = 0;;
	}

	enemy = ({});
}

// Stop all fighting and killing.
void remove_all_killer()
{
	killer = ({});
	enemy -= ({ 0 });

	for(int i=0; i<sizeof(enemy); i++)
		if( enemy[i]->remove_killer(this_object()) )
			enemy[i] = 0;;

	enemy -= ({ 0 });
}

// reset_action()
//
// This function serves as a interface of F_ATTACK and wielded, worn objects.
// When the living's fighting action need update, call this function.
//
void reset_action()
{
	object ob;
	string type, skill;

	if( ob = query_temp("weapon") )
		type = ob->query("skill_type");
	else 
		type = "unarmed";

	if( stringp(skill = query_skill_mapped(type)) ) {
		// If using a mapped skill, call the skill daemon.
		set("actions", (: call_other, SKILL_D(skill), "query_action" :) );
	} else {
		// Else, let weapon handle it.
		if( ob ) set("actions", ob->query("actions",1) );
		else set("actions", query("default_actions",1) );
	}
}

// This is called in heart_beat() to perform attack action.
//private int attack()
int attack()
{
	object opponent;

	clean_up_enemy();

	opponent = select_opponent();
	if( objectp(opponent) ) {
		set_temp("last_opponent", opponent);
		COMBAT_D->fight(this_object(), opponent);
		return 1;
	} else
		return 0;
}

//
// init() - called by MudOS when another object is moved to us.
//
/*
void init()
{
	object ob;
	string vendetta_mark;

	// We check these conditions here prior to handle auto fights. Although
	// most of these conditions are checked again in COMBAT_D's auto_fight()
	// function, these check reduces lots of possible failure in the call_out
	// launched by auto_fight() and saves some overhead.
	if(	is_fighting()
	||	!living(this_object())
	||	!(ob = this_player()) 
	||	environment(ob)!=environment()
	||	!living(ob)
	||	ob->query("linkdead") )
		return;

	// Now start check the auto fight cases.
	if( userp(ob) && is_killing(ob->query("id")) ) {
		COMBAT_D->auto_fight(this_object(), ob, "hatred");
		return;
	} else if( stringp(vendetta_mark = query("vendetta_mark"))
	&& ob->query("vendetta/" + vendetta_mark) ) {
		COMBAT_D->auto_fight(this_object(), ob, "vendetta");
		return;
	} else if( userp(ob) && (string)query("attitude")=="aggressive" ) {
		COMBAT_D->auto_fight(this_object(), ob, "aggressive");
		return;
	} else if( random((int)query("bellicosity") / 40) > (int)query("cps") ) {
		COMBAT_D->auto_fight(this_object(), ob, "berserk");
		return;
	} 
}
*/

void init()
{
//	object who = this_player();

	// �� this_player() ������������������ս����
//	if( !this_object()->visible(this_player()) ) return;

	if( userp(this_player()) && query("aggressive")==1 ) {
		COMBAT_D->auto_fight(this_object(), this_player(), "aggressive");
		return;
	}

	// ��˫������������У���ʼս����
	if( this_player()->is_killing(this_object()) ) {
		COMBAT_D->auto_fight(this_object(), this_player(), "hatred");
		return;
	}

	// ��˫���м����ޣ���ʼս����
	if( this_player()->query("vendetta/" + query("vendetta_mark")) ) {
		COMBAT_D->auto_fight(this_player(), this_object(), "vendetta");
		return;
	}

	switch( query("attitude") ) {
		case "aggressive":
		// ��������������
			COMBAT_D->auto_fight(this_object(), this_player(), "aggressive");
			break;
		case "peaceful":
			break;
		default:
			break;
	}
}
