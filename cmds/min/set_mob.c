//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /cmds/min/set_mob.c
// by bor @DA, 4/25 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

void show_npc( object mob );
private int check_legal_name(string name);
private int check_legal_id(string id);

int main(object me, string arg)
{
	object env, ob;
	string arg1, arg2, type, set, *list=({}), mob_file;
string *set_type = ({ "name", "id", "long", "nickname", "level", "unit",
	"gender", "aggressive", "no_corpse", "die_msg", "home", "chasing",
	"polite", "reward"
});
	int value, npc_cost;
	mapping dbase;

	seteuid(getuid());
	if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½ : set_mob <ÉúÎïÃû³Æ> <²ÎÊıÀàĞÍ> <Éè¶¨Öµ>\n");
	env = environment(me);
	if( ob = present(arg, env) ) {	// ²éÑ¯¸Ã npc ×ÊÁÏ
		if( !ob->query("kingdom") || ob->query("kingdom")!=me->query("kingdom/id") )
			return notify_fail("What?");
		show_npc(ob);
		return 1;
	}
	if( sscanf(arg, "%s %s", arg1, arg2) != 2 )
		return notify_fail("Ö¸Áî¸ñÊ½ : set_mob <ÉúÎïÃû³Æ> <²ÎÊıÀàĞÍ> <Éè¶¨Öµ>\n");
	if( !(ob = present(arg1, env)) ) {
		// Èç¹ûÄãÃ»ÏÂ¹ı home change µÄ»°£¬¾ÍÖ»ÊÇÒ»°ãµÄ mob ĞŞ¸Ä¶øÒÑ
		if( !( ob = me->query_temp("change_mob") ) ) return notify_fail("Ã»ÓĞÕâ¸ö MOB !!\n");
	}
	if( file_size(full_name(ob)) == -1) return notify_fail("Ã»ÓĞÕâ¸ö MOB !!\n");
	if( ob->is_character() && userp(ob) ) return notify_fail("Õâ²»ÊÇÒ»Ö»ÉúÎï¡£\n");
	if( ob->query("kingdom") != me->query("kingdom/id") )
		return notify_fail("Õâ²»ÊÇ¹ó¹úµÄÉúÎï¡£\n");

	if( sscanf(arg2, "%s %s", type, set) != 2 ) {
		return notify_fail("Ö¸Áî¸ñÊ½ : set_mob <ÉúÎïÃû³Æ> <²ÎÊıÀàĞÍ> <Éè¶¨Öµ>\n");
	}
	if( !mapp(dbase = ob->query_entire_dbase()) ) return 0;

	if( !arrayp(list = ob->query("refresh_data")) && sizeof(list)==4)
		return notify_fail("¸ÃÉúÎï×ÊÁÏÓĞÎó, ÎŞ·¨ÅĞ¶¨È¨ÏŞ¡£\n");

	// ÅĞ¶¨ÄãÓĞÃ»ÓĞÈ¨Àû¸Ä NPC
	if( list[0]!=me->query("id") && !me->query("kingdom/king") )
		return notify_fail("ÄãÈ¨ÏŞ²»¹», Ã»°ì·¨ĞŞ¸Ä¸ÃÉúÎï¡£\n");

	if( ob->query_temp("barracks") )
		return notify_fail("ËûÕıÀëÓª×´Ì¬, ²»ÄÜ×÷ĞŞ¸Ä¡£\n");

//	if( file_size(ob->query("home")+".c") == -1 )
//		return notify_fail("ËûµÄ¼ÒÒÑ¾­±»Ïú»Ù£¬ÎŞ·¨Éú´æÏÂÈ¥ÁË !!\n");

	if( member_array(type, set_type) == -1) return notify_fail("Ã»ÓĞÕâÑùµÄ²ÎÊıÀàĞÍ¡£\n");

	switch(type) {
		case "name":
		case "nickname":
			if( type == "nickname" && set =="-d") {
				if( !dbase["nickname"] ) return notify_fail("OK !\n");
				ob->delete("nickname");
			} else {
				if(strlen(set)>30) return notify_fail("ÄãµÄ²ÎÊıÌ«³¤ÁË¡£\n");
				set = ansi_color(set);
				if( !check_legal_name(set) ) return notify_fail("²»ºÃÒâË¼£¬ÄãÈ¡µÄ name ²»·ûºÏ¹æ¶¨ !!\n");
				if( sscanf(set, "[%*s") || sscanf(set, "%*s[%*s") ) dbase[type]=set+"[0m";
				else dbase[type]=set;
			}
			break;
		case "id":
			if(strlen(set)>30) return notify_fail("ÄãµÄ²ÎÊıÌ«³¤ÁË¡£\n");

			if(type=="id") {
				if( !check_legal_id(set) ) return notify_fail("Ó¢ÎÄÄÚ°üº¬²»ºÏ·¨µÄµ¥×Ö»ò²»µ±Ê¹ÓÃ¡£\n");
			}
			dbase[type] = set;
			break;
		case "long":
			if( !sscanf(set, "%d", value) ) value = 0;
			switch( value ) {
				case 0:	// ²»»á×Ô¶¯ÅÅ°æ
				case 1:	// ×Ô¶¯ÅÅ°æ
					me->edit( (: call_other, __FILE__, "do_changelong", ob, value :) );
					return 1;
					break;
				default:
					return notify_fail("Ã»ÓĞÕâÑùµÄ²ÎÊı¡£\n");
			}
			break;
		case "polite":
		case "no_corpse":
		case "aggressive":
		case "chasing":
			value = atoi(set);
			if( value<0 ) return notify_fail("²»ÄÜÉè¶¨ÕâÑùµÄ²ÎÊı¡£\n");
			if( value != 0 && value != 1 ) return notify_fail("²»ÄÜÉè¶¨ÕâÑùµÄ²ÎÊı¡£\n");
			if(type =="polite") {
				if( dbase["type"]!="barracks" ) return notify_fail("ÉúÎïÖ»ÓĞ¾üÈËÀàĞÍ£¬²ÅÄÜÉè¶¨´Ë²ÎÊı¡£\n");
			}
			dbase[type] = value;
			write(dbase["name"]+"("+dbase["id"]+")µÄ "+ type +" Éè¶¨Îª " + value +"\n");
			break;
		case "level":
			if( me->is_busy() ) return notify_fail("ÄãµÄ¶¯×÷»¹Ã»ÓĞÍê³É¡£\n");
			if( me->is_fighting() ) return notify_fail("Äã»¹ÔÚÕ½¶·ÖĞ¡£\n");

			value = atoi(set);
			if( value==-1 ) return notify_fail("²»ÄÜÉè¶¨ÕâÑùµÄ²ÎÊı¡£\n");
			if( value == dbase["level"] ) return notify_fail("MOB µÄµÈ¼¶±¾À´¾ÍÊÇÕâ¸öµÈ¼¶ !!\n");
			if( value > 50 ) return notify_fail("MOB µÈ¼¶²»ÄÜ³¬¹ı 50¡£\n");
			if( value < 1 ) return notify_fail("MOB µÄµÈ¼¶²»ÄÜÕâÃ´µÍ !!\n");
			if( value > dbase["level"] ) {
				npc_cost = ( value - dbase["level"] ) * 5000;
				if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < npc_cost )
					return notify_fail("¹ó¹ú¹ú¿â½ğ¶î²»×ã¡£\n");
				dbase["level"] = value;
				write(dbase["name"]+"µÄµÈ¼¶Éè¶¨Îª "+ value +"\n");
				kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", npc_cost );
			} else {
				dbase["level"] = value;
				write(dbase["name"]+"µÄµÈ¼¶Éè¶¨Îª "+ value +"\n");
			}
			break;
		case "die_msg":
			if( set == "-d") {
				ob->delete("die_msg");
				break;
			}
			set = ansi_color( set );
			set = kill_all_bug(set);
			dbase[type] = set+"\n";
			break;
		default:
			write("Ä¿Ç°ÔİÊ±²»¿ª·Å´Ë²ÎÊıÀàĞÍ¡£\n");
			return 1;
	}

	if( !save_npc(ob) ) return notify_fail("´¢´æ MOB ×ÊÁÏÊ§°Ü, Çë»Ø±¨¸ø¹ÜÀíÕß !!\n");
	write("OK !\n");

	mob_file = base_name(ob);

	if(objectp(ob)) destruct(ob);
	if(find_object(mob_file)) destruct(find_object(mob_file));
	ob = new(mob_file);
	ob->move(env);			// ÄÄÒ»¸ñ¸Ä mob ¾Í°Ñ mob ÒÆµ½¸Ã¸ñ¾Í¿É

	refresh_room(env);
        return 1;
}

void show_npc( object mob )
{
	string str;
	object me = this_player();
	mapping dbase;

	dbase = mob->query_entire_dbase();

	str = sprintf("[1;30m"+dbase["name"]+"("+dbase["id"]+")"+"µÄ×ÊÁÏÈçÏÂ :\n\n[m");

	str += sprintf("name : %s\t\tid : %s\tlevel : %d\n", dbase["name"], dbase["id"], dbase["level"] );
	str += sprintf("nickname : %s\n", dbase["nickname"]?dbase["nickname"]:"ÎŞ");
	str += sprintf("race : %s\t\tgender : %s\t\tunit : %s\n", dbase["race"], dbase["gender"], dbase["unit"] );
	str += sprintf("aggressive : %d\t\tchasing : %d\t\treward : %s\n", dbase["aggressive"], dbase["chasing"], dbase["reward"]?dbase["reward"]:"ÎŞ" );
	str += sprintf("no_corpse : %d\t\twimpy : %d\t\tpolite : %d\n", dbase["no_corpse"], dbase["wimpy"], dbase["polite"] );
	str += sprintf("die_msg : %s\n", dbase["die_msg"]?dbase["die_msg"]:"ÎŞ" );
	str += "long :\n";
	str += sprintf("%s\n", dbase["long"] );

	me->start_more(str);
	return ;
}

private int check_legal_id(string id)
{
	int i;
	string *banned_id = ({"bor","zethus","fuck","sbada"});

	i = strlen(id);
        
	if( (strlen(id) < 2) || (strlen(id) > 20 ) ) return 0;
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) return 0;
	for(i=0;i<sizeof(banned_id);i++) {
		if(strsrch(id, banned_id[i]) != -1) {
			write("¶Ô²»Æğ£¬ÄãµÄÄÚÈİÓĞ²¿·İÎÄ×Ö½«»áÔì³É±ğÈËÀ§ÈÅ¡£\n");
			return 0;
		}
	}
	return 1;
}

private int check_legal_name(string name)
{
        int i;
string *banned_name = ({
	"Äã", "Äã", "ÎÒ", "Ëû", "Ëı", " ­", "Ëü", "µk", "Äú", "¸É", "¼ú",
	"ËûÂèµÄ", "¼úÈË", "Ñ¼", "Ò¡Æ¨Æ¨Ğ¡Ë®Ñ¼","Ò¹ÔÆ","»á·ÉµÄÑ¼×Ó","ÑÙÑÙÒ»Ï¢"
});
	i = strlen(name);
        
	if( (strlen(name) < 4) || (strlen(name) > 30 ) ) return 0;
	while(i--) {
		if( name[i]<=' ' ) return 0;
		if( i%2==0 && !is_chinese(name[i..<0]) ) return 0;
	}
	for(i=0;i<sizeof(banned_name);i++) {
		if(strsrch(name, banned_name[i]) != -1) return 0;
	}
	return 1;
}

void do_changelong(object ob, int flag, string str)  // Éè¶¨ mob long
{
	string *str_arg;

	str = ansi_color( str );

	if( strlen(str) > 8192 ) {
		write("ÄãµÄ²ÎÊıÌ«³¤ÁË¡£\n");
		return;
	}
	str_arg = explode(str, "\n");

	if( sizeof(str_arg) > 11 ) {
		write("Çë¿ØÖÆÔÚÊ®ĞĞÒÔÄÚ¡£\n");
		return;
	}
	str = kill_all_bug(str);

	if( flag==0 || flag ==1) ob->set("long", str);

	if( save_npc(ob) ) write("OK !\n");
	else write("[1;30mĞŞ¸ÄÊ§°Ü¡£\n[m");
        return ;
}

int help(object me)
{
        write(@HELP
Ö¸Áî¸ñÊ½ : set_mob <ÉúÎïÃû³Æ> <²ÎÊıÀàĞÍ> <Éè¶¨Öµ>

ÕâÊÇ¹úÍõÓë´ó³¼ÓÃÀ´°ï mob ×öÉè¶¨µÄÖ¸Áî£¬ÓÃÕâ¸öÖ¸ÁîËû¿ÉÒÔ¸Ä±äÒ»Ğ© mob
µÄ²ÎÊı£¬Ê¹Ëû¿´ÆğÀ´¸üÊÊºÏ»·¾³¡£
ÒÔÏÂÊÇÄ¿Ç°¿ª·ÅÉè¶¨µÄ²ÎÊıÀàĞÍ :
 name   :       Éè¶¨ÉúÎïµÄÖĞÎÄÃû×Ö¡£
 id     :       Éè¶¨ÉúÎïµÄÓ¢ÎÄÃû×Ö¡£
 nickname:      Éè¶¨ÉúÎïµÄ´ÂºÅ¡£ÀıÈç set_mob ruby nickname ´óÄ§Íõ
                Äã¾Í¿ÉÒÔ¿´µ½ ¡°´óÄ§Íõ¡±Èã±È(Ruby)¡£
                Äã¿ÉÒÔÓÃ nickname -d °ÑÔ­ÏÈµÄ nickname Ïû³ı¡£
                nickname µÄÉ«²ÊÓÃ·¨Çë²Î¿¼ help nick
 long   :       Éè¶¨ÉúÎïµÄÃèÊö, ¾ÍÊÇÄã¿´µ½µÄÄÇ¶ÑÃèÊö¡£
 race   :       Éè¶¨ÖÖ×å£¬Ä¿Ç°ÓĞ : ÈËÀà¡¢Ò°ÊŞ¡¢ÑıÄ§¡¢ÄñÀà ...
 unit   :       Éè¶¨µ¥Î»£¬ÀıÈç : Î»¡¢Ö»¡¢Í·¡¢Ìõ ...
 gender :       ÄĞĞÔ»òÅ®ĞÔ¡¢ĞÛĞÔ»ò´ÆĞÔ¡£
 aggressive :   Èç¹ûÉèÁËÕâ¸öÖµÎª 1£¬ÕâÖ»ÉúÎï¾Í»á×¥¿ñÁË ...
 chasing :      ÈÃ mob »áÖ÷¶¯×·»÷µĞÈË£¬Èç¹ûµĞÈËÔÚÕ½¶·ÖĞÌÓÅÜ£¬Ëû»á¾¡Á¦µØ
                ×·É±ÌÓÅÜµÄµĞÈË£¬Ö±µ½×·¶ªÁËÎªÖ¹¡£Éè 0 ¾Í»á½â³ı×·É±¡£
                  Àı×Ó : set_mob <mob> chasing <1/0>

 ask    :       Éè¶¨ÉúÎï¶ÔÄ³Ğ©ÎÊÌâµÄ´ğ¸²£¬ÀıÈç :
                set_mob soldier ask ruby£¬ÕâÊ±»á»Ø´ğÄãÔÚ±à¼­Æ÷ÖĞÊäÈë
                µÄÑ¶Ï¢£¬Èç¹ûÊ²Ã´¶¼Ã»Ğ´£¬ÉúÎï¶ÔÕâ¸öÎÊÌâ¾Í²»»á»Ø´ğ¡£
                Äã¿ÉÒÔÓÃ set_mob <id> ask what À´²éÑ¯Õâ¸öÉúÎïÄ¿Ç°»á»Ø´ğ
                µÄËùÓĞÎÊÌâ¡£
 ask -d  :      °ÑÄ³¸öÎÊÌâµÄ´ğ¸²È¡Ïû

 chat_msg :     Éè¶¨ÉúÎï»áÒ»Ö±à«à«Ëµ×ÅÄ³Ğ©Ñ¶Ï¢, ÀıÈç :
                set_mob bagger chat_msg ÆòØ¤À­×ÅÄãµÀ : ´óÒ¯ !! ¿ÉÁ¯Ğ¡µÄ°É !!
                Äã¿ÉÒÔÓÃ set_mob <id> chat_msg what À´²éÑ¯Õâ¸öÉúÎïÄ¿Ç°Ëù
                ÓĞ»á½²µÄÑ¶Ï¢
 chat_msg -d <Ñ¶Ï¢±àºÅ> : É¾³ıÕâÖ»ÉúÎïµÄÄ³Ğ©»á½²µÄÑ¶Ï¢¡£
 chat_msg_combat : Éè¶¨ÉúÎïÔÚÕ½¶·Ê±»á½²µÄ»°, ÓÃ·¨¸ú chat_msg ÏàÍ¬
                  set_mob beggar chat_msg_combat ÆòØ¤°§µÀ : ±ğ´òÁË !! ¾ÈÈË°¡ !!

 reward :       µ± mob ±»´òËÀºó£¬Ëû»á¶à³öÕâÒ»¼şÒÅÎï¡£²»¹ıÕâ¼ş¶«Î÷Ö»ÄÜÊÇÈÎÎñ
                ×¨ÓÃÎïÆ·¡£ÀıÈç : set_mob dragon reward gem£¬µ±È»£¬ÄãÒªÓĞ gem
                ÕâÑùµ±ÄãÃ¿´Î¸Éµô dragon£¬Äã¾Í»á¼ñµ½Ò»¿é±¦Ê¯
                Èç¹ûÄãÒªÈ¡Ïû rewared, ¿ÉÒÔÓÃ set_mob <mob> reward none

 no_corpse :    Éè³É 1 Ê±£¬µ± mob ±»´òËÀ£¬Ëû²»»áÁôÏÂÊ¬Ìå£¬ÉíÉÏµÄ×°±¸Ò²²»»áÁô
                ÏÂÀ´¡£Éè³É 0 ¾Í¿ÉÒÔ½â³ıÕâÖÖ×´¿ö¡£

 die_msg :      µ± mob ±»´òËÀÊ±£¬×îºóÁôÏÂµÄÑ¶Ï¢¡£ÀıÈç :
                ¶ñÄ§Á³ÉÏÂ¶³ö²»ÄÜÏàĞÅµÄ±íÇé£¬¶Ô×Å$N´óºğ : ÔõÃ´¿ÉÄÜ ?? ÎÒÊÇ²»
                »á±»´ò°ÜµÄ !!
                ËûÏëÒªÓÃÁ¦×¥×¡$N£¬µ«ÊÇÖÕÓÚ»¯³ÉÒ»¿éÊ¯Í·¡£
                ÕâÀïµÄ $N ÊÇ±íÊ¾´ò°ÜËûµÄÈËµÄÃû×Ö¡£
 die_msg -d :   É¾³ı die_msg

 home   :       Òª mob °á¼Ò¡£ÀıÈç :
                  ÏÈÕÒµ½Òª°á¼ÒµÄ mob£¬ÏÂ set_mob dog home change Ö¸Áî£¬È»ºó
                  ×ßµ½ËûµÄĞÂ¼Ò£¬ÔÙÏÂ set_mob dog home here¡£ÕâÑù¹·¹·¾Í»á°áµ½
                  ĞÂ¼ÒÁË¡£Èç¹û²»ÏëËû°á¼Ò£¬ÓÃ set_mob dog home cancel¡£

 owner  :       °ï mob »»ĞÂÖ÷ÈË, ĞÂÖ÷ÈË±ØĞëÒ²ÊÇ´ó³¼¡£Ö»ÓĞÔ­Ö÷ÈËºÍ¹úÍõÄÜÓÃ¡£

 level  :       °ï mob ±ä¸üµÈ¼¶£¬µ±È»¸Ã»¨µÄÇ®»¹ÊÇ»á»¨µÄ¡£

 sp_attack :    °ï mob Éè¶¨ÌØÊâ¹¥»÷µÄĞÍÌ¬ºÍÑ¶Ï¢£¬ÀıÈç :
                  Ôö¼ÓÌØ¹¥ : set_mob <mob> sp_attack <ÌØ¹¥ĞÍÌ¬> <ÌØ¹¥Ñ¶Ï¢>
                  È¡ÏûÌØ¹¥ : set_mob <mob> sp_attack -d <ÌØ¹¥ĞÍÌ¬>
                ÌØ¹¥Ñ¶Ï¢µÄĞ´·¨ : $NºİºİµØÔÚ$nµÄ½ÅÉÏÒ§ÁËÒ»¿Ú¡£
                        $N ±íÊ¾ÕıÔÚÊ¹ÓÃÌØ¹¥µÄÉúÎïÃû×Ö
                        $n±íÊ¾±»¹¥»÷µÄ¶ÔÏóµÄÃû×Ö
                ÌØÊâ¹¥»÷µÄĞÍÌ¬Çë²Î¿¼ help special_attack

 path   :       ÈÃ mob »áÔÚÌØ¶¨µÄÂ·ÏßÀ´»Ø×ß¶¯£¬ÀıÈç :
                 Éè¶¨Â·Ïß  set_mob <mob> path east, east, west, west
                 È¡ÏûÂ·Ïß  set_mob <mob> path -d
                mob ×ß¶¯µÄÂ·Ïß±ØĞèÊÇÒ»¸ö»ØÂ·£¬ÈÃËü¿ÉÒÔÖÜ¶ø¸´Ê¼µÄÒ»Ö±×ß¶¯,
                Â·ÏßµÄÃ¿¸ö·½Ïò¶¼±ØĞèÍêÕû£¬¶øÇÒÓÃ¶ºµã¸ô¿ª¡£ËùÓĞµÄÉúÎïÖĞ£¬
                Ö»ÓĞ¾üÊÂÀàµÄÉúÎï»áÔÚ×ß¶¯Ê±Í¬Ê±ËÑÑ°µĞÈË¡£Â·ÏßµÄÉè¶¨ÓëÏû³ı
                ¶¼Ö»ÄÜÔÚ mob µÄ¼Ò²ÅÄÜ½øĞĞ£¬¶øÇÒ²»ÄÜÈÃËû×ß³ö¹ú¾³¡£

 wimpy :        µ± mob ±»´òµ½ÌåÁ¦µÍÓÚÉè¶¨µÄÊıÖµÊ±Ëû¾Í»áµ½´¦ÂÒÌÓ¡£
                set_mob <mob> wimpy <ÊıÖµ>

 polite :       ¸ø¾üÓªÀàÉúÎïµÄ²ÎÊı£¬Èç¹ûÉè¶¨£¬Ëû¾Í»á¶ÔÓ¢ĞÛÒÔÉÏµÄÈË¾´Àñ¡£
                Àı : set_mob soldier polite <1 or 0>

Èç¹ûÄãÔÚ set_mob ºóÃæÖ±½Ó¼Ó mob µÄ id, ÄÇ¾Í¿ÉÒÔ¿´µ½¸Ã mob µÄËùÓĞÉè¶¨Öµ¡£

Àı : set_mob dog name ·è¹·

ÆäËûÏà¹Ø×ÊÑ¶ :  add_mob, build, delete_mob


HELP);
	return 1;
}
