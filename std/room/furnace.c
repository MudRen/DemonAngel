//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /std/room/furnace.c
// by bor @DA

#pragma optimize
#pragma save_binary

//#define DEBUG

inherit ROOM;

#include <ansi.h>

int	flag=-1,		// ÊÇ·ñÕıÔÚ¹àÂ¯, ÄÚ¶¨Ã»ÓĞ¹àÂ¯
	mp,			// Ä¿Ç° charge ·¨Á¦µÄÊıÖµ
	furnace_count_ini,	// µ±Äã load Ê±Ä§Á¦Â¯ÂÒÊı¾ö¶¨µÄ×ªÊı
	furnace_count,		// ¼ÍÂ¼Ä¿Ç°×ª¼¸È¦ÁË, ÓÃÀ´¼ÆËãÊıÖµ±ä»¯
	lost_count;		// ¼ÍÂ¼Ê§°ÜµÄ´ÎÊı

object ob, env;

private int into_furnace( object me );
private int furnace_reward();

void setup()
{
	seteuid(getuid());
	env = this_object();
	::setup();
}

void init()
{
	if( userp(this_player()) && ( wizardp(this_player()) || this_player()->query("kingdom/id")==env->query("kingdom_id")  )  ) {
		add_action("do_load", "load");
	}
	add_action("do_charge", "charge");
}

private int do_load(string arg)
{
	object me = this_player();
	string item;

	if( !userp(me) ) return 0;
	if( flag==1 ) return 0;
	if(me->query("kingdom/id")!=environment(me)->query("kingdom_id")) return notify_fail("What£¿\n");
	if(!me->query("kingdom/king") && !me->query("kingdom/minister") ) return notify_fail("What£¿\n");
	if( !arg ) return notify_fail("load <ÎïÆ·> into furnace\n");
	if( sscanf(arg, "%s into furnace", item)!=1 ) return notify_fail("load <ÎïÆ·> into furnace\n");
	if( !objectp( ob = present(item, me) ) ) return notify_fail("ÄãÉíÉÏÃ»ÓĞ´ËÎïÆ·!!\n");
	if( !ob->query("armor_type") && !ob->query("skill_type") )
		return notify_fail("Õâ²»ÊÇÒ»¼ş×°±¸!!\n");
	if( !ob->query("new") ) return notify_fail("Õâ¼ş×°±¸²»ÊÇĞÂ»õ!!\n");
	if( ob->query("equipped") ) return notify_fail("ÄãÕı×°±¸×Å!!\n");

	if( !ob->query("kingdom") || ob->query("kingdom")!=me->query("kingdom/id") )
	if( !ob->query("kingdom/king") && ob->query("owner")!=ob->query("id") )
		return notify_fail("Õâ¼şÎïÆ·ÓµÓĞÕß²»ÊÇÄã!!\n");

	if( ob->query("level")<23 ) return notify_fail("Õâ¼şÎïÆ·Ì«´àÈõÁË£¬²»ÄÜÀûÓÃÄ§·¨¸ÄÖÊ¡£\n");

	mp = random(30) + 10;			// µ±×÷³õÊ¼Öµ

	furnace_count_ini = random(53)+7;	// ×îÉÙ 6 ´Î
	flag = 1;				// ²»ÈÃÆäËûÈËÒ²ÄÜ load
	into_furnace(me);
	return 1;
}

object furnace_msg_ob()
{
	object *inv;
	
	inv = all_inventory(env);
	if( zerop(inv) ) return 0;
	return inv[random(sizeof(inv))];
}

private int into_furnace( object me )
{
	ob->move(VOID_OB);
	message_vision(WHT"$N°Ñ$nËÍÈëÄ§Á¦Â¯ÖĞ¡£\n\n"NOR, me, ob);
	message_vision(HIM"Ä§Á¦Â¯·¢³ö°×É«µÄ¹âÃ¢, ´¥Ğë¿ªÊ¼Èä¶¯¡£\n\n\n"NOR, me);
	furnace_count = 0;
	call_out("furnace_count_msg", 2 );
	return 1;
}

private int furnace_count_msg()
{
	object ob2;
	furnace_count_ini --;

	ob2 = furnace_msg_ob();
	if( furnace_count>10+random(2) )
		mp = mp - (54+random(2));		// Ã¿×ªºóÊ£ÓàµÄ·¨Á¦
	else mp = mp - ( 105+random(3) );

#ifdef DEBUG
	message_vision("init:"+furnace_count_ini+", lost_count:"+lost_count+", furnace_count:"+furnace_count+"\n\n", ob2);
#endif

	if( furnace_count_ini ) {	// ×ª°¢×ª°¢
		// ÈıÖÖÇé¿ö, ¿ÉÒÔ½« furnace Í£ÏÂÀ´[µ«ÖÁÉÙÒª 7 È¦ºó, ²ÅÄÜµô]
		if( furnace_count>6 ) {
			if( ( mp>4000 && 50>random(100) )
			|| ( lost_count<=5 && lost_count>=3 && 3>random(100) )
			|| ( 2>random(100) )
			) {
				call_out("furnace_drop", 0 );
				return 1;
			} else if( 50>random(100) && (mp <= -2500 || lost_count>=7) ) {	// Èç¹û mp ÑÏÖØ²»×ã¾Í³ÔµôÎïÆ·
				if(ob2) message_vision(HIC"Ä§Á¦Â¯Í»È»¾çÁÒÕğ¶¯, È»ºóËùÓĞµÄ´¥Ğë½¥½¥Í£Ö¹ÁË»î¶¯ ...\n\n"NOR, ob2);
				destruct(ob);
				flag = -1;
				return 1;
			}
		}

		if( mp<0 ) {
			lost_count += 1;
			if(ob2) message_vision("[1;5;31mÄ§Á¦Â¯µÄÄÜÁ¿²»×ã, ·¢³öµÄ¹âÃ¢¿ªÊ¼¼õÈõ ...[0m\n", ob2);
		} else {
			furnace_count += 1;
			lost_count = 0;
//			if(ob2) message_vision(HIY"Ä§Á¦Â¯µÄ´¥ĞëÎÈ¶¨µØÓÎ¶¯, ·¢³öÇ¿ÁÒµÄÄ§·¨¹âÃ¢ ...[µÚ "+furnace_count+" È¦]\n\n"NOR, ob2);
			if(ob2) message_vision(HIY"Ä§Á¦Â¯µÄ´¥ĞëÎÈ¶¨µØÓÎ¶¯, ·¢³öÇ¿ÁÒµÄÄ§·¨¹âÃ¢ ...\n\n"NOR, ob2);
		}
		call_out("furnace_count_msg", 0 );
	} else {	// ½áÊø×ª¶¯
		if(ob2) message_vision(WHT"Ä§Á¦Â¯µÄ»î¶¯½¥½¥¼õÂı, ÔÚ×îºóµÄ¹âÃ¢É¢È¥ºó, Ä§Á¦Â¯ÍêÈ«»Ö¸´¾²Ö¹ ...\n"NOR, ob2);
		call_out("furnace_drop", 0 );
	}
	return 1;
}

private int furnace_drop()
{
	flag = -1;

	// ×ªµÄÈ¦ÊıÈç¹ûĞ¡ÓÚ 8 , ÄÇÃ´µ±×÷µô³öÀ´, ²»´¦ÀíÊıÖµ
	if( furnace_count > 7 ) {
		ob->set("new", 0);
		furnace_reward();
	}
	ob->move(env);
//	message_vision(WHT"\n$N¡°Å¾¡±µØÒ»Éù´ÓÄ§Á¦Â¯ÖĞµôÁË³öÀ´¡£[ÍÚÁĞ... ²Å "+ furnace_count+" È¦]\n"NOR, ob);
	message_vision(WHT"\n$N¡°Å¾¡±µØÒ»Éù´ÓÄ§Á¦Â¯ÖĞµôÁË³öÀ´¡£\n"NOR, ob);
	return 1;
}

private int furnace_reward()
{
	int tmp, num, ac, db, wl, Mh, lv;
	string attr;
	string *add_normal = ({ "ac", "db", "wl", "Mh" });

	// 1. ¸ù¾İÄ§Á¦Â¯È«²¿µÄ×ªÊı(furnace_count) À´¾ö¶¨µô³öÀ´µÄ
	tmp = random(60);

	if( tmp>=45  ) attr = add_normal[random(sizeof(add_normal))];
	else if( tmp<45 && tmp>=35 )	attr = "kar";
	else if( tmp<35 && tmp>=25 )	attr = "sta";
	else if( tmp<25 && tmp>=18 )	attr = "con";
	else if( tmp<18 && tmp>=10 )	attr = "str";
	else if( tmp<10 && tmp>=5 )	attr = "dex";
	else attr = "int";

	if( member_array(attr, add_normal)!=-1 ) num = furnace_count/5;
	else num = furnace_count/10;
	if(num<1) num=1;

	ac = furnace_count/10;
	db = furnace_count/10;
	wl = furnace_count/10;
	Mh = furnace_count/10;

	lv = ob->query("level") + ob->query("level") * furnace_count/100;

	if( ob->query("armor_type") ) {
		ob->set("armor_prop/ac", ac);
		ob->set("armor_prop/db", db);
	} else {
		ob->set("weapon_prop/wl", wl);
		ob->set("weapon_prop/Mh", Mh);
	}

	if( ob->query("type")=="wand" || ob->query("type")=="staff" ) {
		string *spell_list;
		// È¡µÃ invoke_magic ·½Ê½ÓĞºÜ¶àÖÖ... ÒÔÏÂÖ»½éÉÜÁ½ÖÖ:
		// 1. Ö±½ÓÈ¡µÃ /daemon/spell/
		// spell_list = get_dir("/daemon/spell/");
		// ob->set("invoke_magic", replace_string(spell_list[random(sizeof(spell_list))], ".c", "") );

		// 2. ÓÉÓÚÎÒ½« /daemon/spell/ µ×ÏÂ»®·ÖÎª¸÷Ö°Òµ¿ÉÑ§µÄÄ¿Â¼, Èç /daemon/spell/Ä§·¨Ê¦/
		//    Òò´Ë, ÎÒ¶îÍâ»®·ÖÒ»¸öÄ¿Â¼·ÅÖÃµ½µ×ÓĞÄÄĞ©·¨Êõ¿É¹©µ±×÷ invoke_magic, ÈçÏÂ:
		spell_list = get_dir("/daemon/furnace/spell/");
		ob->set("invoke_magic", spell_list[random(sizeof(spell_list))] );
	}

#ifdef DEBUG
	if( ob->query("armor_type") )
		ob->set_name("make"+ob->query("level")+"_tick"+furnace_count+"_lv"+lv+"_"+attr+num, ({ ob->query("id") }) );
	else ob->set_name("make"+ob->query("level")+"_tick"+furnace_count+"_sk"+(lv*2)+"_"+attr+num, ({ ob->query("id") }) );
#endif

	ob->set("level", lv);
	ob->set("add_attr/"+attr, num);			// ¸½¼ÓÖµ, ±ÜÃâÓë ac, db, wl, Mh, ... µÈÖØ¸´, ºÃ´¦: Î¨Ò»ĞÔ

	if( !do_saveitem(ob) ) return 0;
	return 1;
}

private int do_charge(string arg)
{
	object me=this_player();

	message_vision("$NÎÕ½ôÄ§Á¦Â¯µÄ´¥ÊÖ, °ÑËùÓĞµÄ¾«ÉñÁ¦ÊäËÍ½øÈ¥¡£\n\n", me);
	call_out("charge_furnace", 0, me, arg );
	return 1;
}

private int charge_furnace(object me, string arg)
{
	object ob;
	if( arg=="corpse" ) {
		ob = present(arg, env);
		if(!ob) ob = present(arg, me);
		if( ob && ob->is_corpse() ) mp += (600 + random(100));
		destruct(ob);
	} else if( arg=="furnace" ) {
		if( flag==1 ) mp += me->query("mp");
		me->set("mp", 0);
	}
	message_vision("Ä§Á¦Â¯Í»È»Éú³öÒ»¹ÉÇ¿ÁÒµÄÎüÒıÁ¦, °Ñ$NµÄ¾«ÉñÁ¦ÎüµÃÒ»¸É¶ş¾» !\n", me);
	message_vision("$NÍ»È»±»Ä§Á¦Â¯µ¯¿ª¡£\n", me);
	return 1;
}
