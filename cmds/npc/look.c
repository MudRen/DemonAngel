//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /cmds/npc/look.c

#include <room.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	int result;

	if( !arg ) result = look_room(me, environment(me));
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = look_living(me, obj);
		else result = look_item(me, obj);
	} else result = look_room_item(me, arg);

	return result;
}

int look_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string str, *dirs;

	if( !env ) {
		write("ÄãµÄËÄÖÜ»Ò÷÷µØÒ»Æ¬£¬Ê²Ã´Ò²Ã»ÓĞ¡£\n");
		return 1;
	}
	str = sprintf( "%s - %s\n    %s%s",
		env->query_temp("destroy")?"[1;33m(»ÙËğ)[0m"+env->query("short"):env->query("short"),
		wizardp(me)? file_name(env): "",
		env->query("long"),
		env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = env->query("exits")) ) {
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
				dirs[i] = 0;
		dirs -= ({ 0 });
		if( sizeof(dirs)==0 )
			str += "    ÕâÀïÃ»ÓĞÈÎºÎÃ÷ÏÔµÄ³öÂ·¡£\n";
		else if( sizeof(dirs)==1 )
			str += "    ÕâÀïÎ¨Ò»µÄ³ö¿ÚÊÇ " + BOLD + dirs[0] + NOR + "¡£\n";
		else
			str += sprintf("    ÕâÀïÃ÷ÏÔµÄ³ö¿ÚÊÇ " + BOLD + "%s" + NOR + " ºÍ " + BOLD + "%s" + NOR + "¡£\n",
				implode(dirs[0..sizeof(dirs)-2], "¡¢"), dirs[sizeof(dirs)-1]);
	}
//	str += env->door_description();

	inv = all_inventory(env);
	for(i=0; i<sizeof(inv); i++) {
		if( inv[i]==me ) continue;
		if( !me->visible(inv[i]) ) continue;
		str += "  " + inv[i]->short() + "\n";
	}

	write(str);
	return 1;
}

int look_item(object me, object obj)
{
	mixed *inv;

	write(obj->long());
	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("ÀïÃæÓĞ£º\n  %s\n",
			implode(inv, "\n  ") ), me);
	}
	return 1;
}

int look_living(object me, object obj)
{
	string str, limb_status, pro;
	mixed *inv;
	mapping my_fam, fam;

	if( me!=obj )
		message("vision", me->name() + "Õı¶¢×ÅÄã¿´£¬²»ÖªµÀ´òĞ©Ê²Ã´Ö÷Òâ¡£\n", obj);

	str = obj->long();

	pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));

//	if( (string)obj->query("race")=="ÈËÀà"
//	&&	intp(obj->query("age")) )
//		str += sprintf("%s¿´ÆğÀ´Ô¼%s¶àËê¡£\n", pro, chinese_number(obj->query("age") / 10 * 10));

	// If we both has family, check if we have any relations.
//	if( obj!=me
//	&&	mapp(fam = obj->query("family"))
//	&&	mapp(my_fam = me->query("family")) 
//	&&	fam["family_name"] == my_fam["family_name"] ) {
	
//		if( fam["generation"]==my_fam["generation"] ) {
//			if( (string)obj->query("gender") == "ÄĞĞÔ" )
//				str += sprintf( pro + "ÊÇÄãµÄ%s%s¡£\n",
//					my_fam["master_id"] == fam["master_id"] ? "": "Í¬ÃÅ",
//					my_fam["enter_time"] > fam["enter_time"] ? "Ê¦ĞÖ": "Ê¦µÜ");
//			else
//				str += sprintf( pro + "ÊÇÄãµÄ%s%s¡£\n",
//					my_fam["master_id"] == fam["master_id"] ? "": "Í¬ÃÅ",
//					my_fam["enter_time"] > fam["enter_time"] ? "Ê¦½ã": "Ê¦ÃÃ");
//		} else if( fam["generation"] < my_fam["generation"] ) {
//			if( my_fam["master_id"] == obj->query("id") )
//				str += pro + "ÊÇÄãµÄÊ¦¸¸¡£\n";
//			else if( my_fam["generation"] - fam["generation"] > 1 )
//				str += pro + "ÊÇÄãµÄÍ¬ÃÅ³¤±²¡£\n";
//			else if( fam["enter_time"] < my_fam["enter_time"] )
//				str += pro + "ÊÇÄãµÄÊ¦²®¡£\n";
//			else
//				str += pro + "ÊÇÄãµÄÊ¦Êå¡£\n";
//		} else {
//			if( fam["generation"] - my_fam["generation"] > 1 )
//				str += pro + "ÊÇÄãµÄÍ¬ÃÅÍí±²¡£\n";
//			else if( fam["master_id"] == me->query("id") )
//				str += pro + "ÊÇÄãµÄµÜ×Ó¡£\n";
//			else
//				str += pro + "ÊÇÄãµÄÊ¦Ö¶¡£\n";
//		}
//	}

	if( obj->query_base_hp() )
		str += pro + COMBAT_D->eff_status_msg((int)obj->query_hp() * 100 / (int)obj->query_base_hp()) + "\n";

	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
			str += sprintf( obj->is_corpse() ? "%sµÄÒÅÎïÓĞ£º\n%s\n" : "%sÉíÉÏ´ø×Å£º\n%s\n",
				pro, implode(inv, "\n") );
	}

	message("vision", str, me);

	if( obj!=me 
	&&	living(obj)
	&&	random((int)obj->query("bellicosity")/10) > (int)me->query("per") ) {
		write( obj->name() + "Í»È»×ª¹ıÍ·À´µÉÄãÒ»ÑÛ¡£\n");
		COMBAT_D->auto_fight(obj, me, "berserk");
	}

	return 1;
}

string inventory_look(object obj, int flag)
{
	string str;

	str = obj->short();
	if( obj->query("equipped") )
		str = HIC "  ¡¦" NOR + str;
	else if( !flag )
		str = "    " + str;
	else
		return 0;

	return str;
}

int look_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !objectp(env = environment(me)) )
		return notify_fail("ÕâÀïÖ»ÓĞ»Ò÷÷µØÒ»Æ¬£¬Ê²Ã´Ò²Ã»ÓĞ¡£\n");

	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
		if( stringp(item[arg]) )
			write(item[arg]);
		else if( functionp(item[arg]) )
			write((string)(*item[arg])(me));
			
		return 1;
	}
	if( mapp(exits = env->query("exits")) && !undefinedp(exits[arg]) ) {
		if( objectp(env = find_object(exits[arg])) )
			look_room(me, env);
		else {
			call_other(exits[arg], "???");
			look_room(me, find_object(exits[arg]));
		}
		return 1;
	}
	return notify_fail("ÄãÒª¿´Ê²Ã´£¿\n");
}

int help (object me)
{
	write(@HELP
Ö¸Áî¸ñÊ½: look [<ÎïÆ·>|<ÉúÎï>|<·½Ïò>]
 
Õâ¸öÖ¸ÁîÈÃÄã²é¿´ÄãËùÔÚµÄ»·¾³¡¢Ä³¼şÎïÆ·¡¢ÉúÎï¡¢»òÊÇ·½Ïò¡£
 
HELP
);
	return 1;
}
