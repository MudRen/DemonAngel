//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /feature/damage.c
// modify by bor @DA, 

#include <ansi.h>
#include <dbase.h>
#include <login.h>
#include <move.h>


int query_hp();
int query_mp();
int query_base_hp();
int query_base_mp();

//int ghost = 0;

//int is_ghost() { return ghost; }

varargs int receive_damage(string type, int damage, object who)
{
	int val;

	if( damage < 0 ) error("F_DAMAGE: �˺�ֵΪ��ֵ��\n");
	if( type!="hp" && type!="mp" )
		error("F_DAMAGE: �˺��������( ֻ���� hp, mp ����֮һ )��\n");

	if( objectp(who) ) set_temp("last_damage_from", who);
	val = (int)query(type) - damage;

	if( val >= 0 ) set(type, val);
	else set( type, -1 );

	set_heart_beat(1);

	return damage;
}

/*
varargs int receive_wound(string type, int damage, object who)
{
	int val;

	if( damage < 0 ) error("F_DAMAGE: �˺�ֵΪ��ֵ��\n");
	if( type!="hp" && type!="mp" )
		error("F_DAMAGE: �˺��������( ֻ���� hp, mp ����֮һ )��\n");

	if( objectp(who) ) set_temp("last_damage_from", who);
	val = (int)query(type) - damage;

	if( val >= 0 ) set(type, val);
	else {
		set( type, -1 );
		val = -1;
	}

	if( (int)query(type) > val ) set(type, val);

	set_heart_beat(1);

	return damage;
}
*/

int receive_heal(string type, int heal)
{
	int val;

	if( heal < 0 ) error("F_DAMAGE: �ָ�ֵΪ��ֵ��\n");
	if( type!="hp" && type!="mp" )
		error("F_DAMAGE: �ָ��������( ֻ���� hp, mp ����֮һ )��\n");

	val = (int)query(type) + heal;

	if( val > (int)query("base_" + type) ) set(type, (int)query("base_" + type));
	else set( type, val );

	return heal;
}

/*
int receive_curing(string type, int heal)
{
	int max, val;

	if( heal < 0 ) error("F_DAMAGE: �ָ�ֵΪ��ֵ��\n");
	if( type!="hp" && type!="mp" )
		error("F_DAMAGE: �ָ��������( ֻ���� hp, mp ����֮һ )��\n");

	val = (int)query("eff_" + type);
	max = (int)query("base_" + type);

	if( val + heal > max ) {
		set("eff_" + type, max);
		return max - val;
	} else {
		set( "eff_" + type, val + heal);
		return heal;
	}
}
*/
void unconcious()
{
	object defeater;

	if( !living(this_object()) ) return;
	if( wizardp(this_object()) && query("env/immortal") ) return;

	if( objectp(defeater = query_temp("last_damage_from")) )
		COMBAT_D->winner_reward(defeater, this_object());

	this_object()->remove_all_enemy();

	message("system", HIR "\n�����ǰһ�ڣ�����ʲôҲ��֪����....\n\n" NOR,
		this_object());
	this_object()->disable_player(" <���Բ���>");
	set("hp", 0);
	set("mp", 0);
	set_temp("block_msg/all", 1);
	COMBAT_D->announce(this_object(), "unconcious");

	call_out("revive", random(100 - query("con")) + 30);
}

varargs void revive(int quiet)
{
	remove_call_out("revive");
	while( environment()->is_character() )
		this_object()->move(environment(environment()));
	this_object()->enable_player();
	if( !quiet ) {
		COMBAT_D->announce(this_object(), "revive");
		set_temp("block_msg/all", 0);
		message("system", HIY "\n������������������֪��....\n\n" NOR,
			this_object());
	} else
		set_temp("block_msg/all", 0);
}

void die()
{
	object corpse, killer;
	int i;

	this_object()->remove_all_enemy();
	this_object()->remove_all_killer();
	this_object()->dismiss_team();
	this_object()->clear_condition();

	tell_object(this_object(), "\n�����ˡ�\n\n");
	if( !living(this_object()) ) revive(1);
	if( wizardp(this_object()) && query("env/immortal") ) return;

	set_temp("block_msg/all", 1);

	COMBAT_D->announce(this_object(), "dead");
	if( objectp(killer = query_temp("last_damage_from")) ) {
		set_temp("my_killer", killer->query("id"));
		COMBAT_D->killer_reward(killer, this_object());
	}

	if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
		corpse->move(environment());

//	all_inventory(environment())->remove_killer(this_object());

	if( userp(this_object()) ) {
		set("hp", 30);
		set("mp", 30);
//		ghost = 1;
		this_object()->move(DEATH_ROOM);
		this_object()->disable_player();
		call_out("delay_move_recall", 13+random(3), this_object() );
//		this_object()->move(DEATH_ROOM);
//		DEATH_ROOM->start_death(this_object());
	} else
		destruct(this_object());
}

void delay_move_recall(object ob)
{
	ob->enable_player();
	set_temp("block_msg/all", 0);
	tell_object(ob, HIY"\n������������������֪��������\n\n"NOR);
	ob->move(START_ROOM);
//	ghost = 0;
	return;
}

//void reincarnate()
//{
//	ghost = 0;
//}

int heal_up()
{
	int update_flag, tmp;
	mapping my;

	update_flag = 0;

	my = query_entire_dbase();

	if( this_object()->is_fighting() ) {	// ս����
		if( query_hp() < query_base_hp() ) {
			tmp = my["con"] / 5;
			if( tmp<1 ) tmp = 1;
			my["hp"] += tmp;
			if( query_hp()> query_base_hp() )
				my["hp"] -= (query_hp()-query_base_hp());
			update_flag++;
		}
		if( query_mp() < query_base_mp() ) {
			tmp = my["int"] / 5;
			if( tmp<1 ) tmp = 1;
			my["mp"] += tmp;
			if( query_mp()> query_base_mp() )
				my["mp"] -= (query_mp()-query_base_mp());
			update_flag++;
		}
	} else {
		if( query_hp() < query_base_hp() ) {
			tmp = my["con"] / 3;
			if( tmp<1 ) tmp = 1;
			my["hp"] += tmp;
			if( query_hp()> query_base_hp() )
				my["hp"] -= (query_hp()-query_base_hp());
			update_flag++;
		}
		if( query_mp() < query_base_mp() ) {
			tmp = my["int"] / 5;
			if( tmp<1 ) tmp = 1;
			my["mp"] += tmp;
			if( query_mp()> query_base_mp() )
				my["mp"] -= (query_mp()-query_base_mp());
			update_flag++;
		}
	}
	return update_flag;
}

int query_hp()
{
	return (int)query("hp");
}
int query_mp()
{
	return (int)query("mp");
}

int query_base_hp()
{
	return 34 + (int)query("con")*5 + (int)query("apply/con")*3 + (int)query_temp("apply/con")*2;
}

int query_base_mp()
{
	return 20 + (int)query("int")*5 + (int)query("apply/int")*3 + (int)query_temp("apply/int")*2;
}
