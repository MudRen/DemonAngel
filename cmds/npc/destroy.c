//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /cmds/npc/destroy.c
// by bor @DA, 3/7 2003
// actionroom ÔÚ±»ÆÆ»µºó£¬ÔõÃ´´ò¿ª action ? ÓĞ¿ÕÏëÏë°É
// 

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
inherit "/cmds/min/declare";			// ¸ø¹¥ÆÆÍõ×ùÊ¹ÓÃ

#include <ansi.h>

int main(object me, string arg)
{
	string id, enemy_id;
	object env, ob, *inv;
	int money;

	seteuid(getuid());
	if(arg) return notify_fail("Äã²»ÄÜÆÆ»µÄÇ¸ö¶«Î÷!!\n");
	if(!(id= me->query("kingdom/id"))) return notify_fail("ÎŞ¹ú¼®²»ÄÜÂÒÆÆ»µ¡£\n");
	if(!objectp(env = environment(me))) return notify_fail("ÕâÀïµÄ»·¾³ÊôÓÚ¿ÕĞé¡£\n");
	if( !(enemy_id = env->query("kingdom_id")) ) return notify_fail("ÕâÀïÊÇÏµÍ³µÄÇøÓò !!");
	if( enemy_id == id ) return notify_fail("ÄãÏëÅÑ¹úÂğ ?\n");
	if(!kingdom_data(id, "war", "check")) return notify_fail("¹ó¹úÄ¿Ç°Ã»ÓĞÈÎºÎÒ»³¡Õ½Õù·¢Éú!!\n");
	if(!kingdom_data(id, "war", "check", enemy_id, 1)) return notify_fail("¹ó¹úÃ»ÓĞºÍ¸Ã¹ú¼ÒÕ½Õù¡£\n");
	if(env->query_temp("destroy")) return notify_fail("ÕâÀïÒÑ¾­±»ÆÆ»µÒ»¿Õ¡£\n");

	if( env->query("type")=="normal"&&env->query("no_delete")==1 ) { // Èç¹û¸Ã·¿¼äÎªÍõ×ù
		if( me->is_busy() ) return notify_fail("ÄãµÄ¶¯×÷»¹Ã»ÓĞÍê³É¡£\n");
		if( me->is_fighting() ) return notify_fail("Äã»¹ÔÚÕ½¶·ÖĞ¡£\n");

		// Èç¹ûÍõ×ùÓĞ guard , ÄÇÃ´¾ÍÏŞÖÆµĞÈË²»ÄÜÆÆ»µµÄ»°
		inv = all_inventory(env);
		for(int i=0; i<sizeof(inv); i++) { // ¼ì²é¸Ã·¿¼äÊÇ·ñÓĞµĞÈËµÄ mob£¬ÈôÓĞÔò²»ÄÜÆÆ»µ
			if( inv[i]->query("kingdom")&& kingdom_data(id, "war", "check", inv[i]->query("kingdom"), 1) )
				return notify_fail("ÕâÀï»¹ÓĞµĞÈË´æÔÚ, ÎŞ·¨·ÙÉÕ½¨ÖşÎï!!\n");
		}

		message_vision("[1;30m$NÄÃÆğ»ğ°Ñ½«ÕâÀï·ÙÉÕ´ù¾¡¡£[m\n", me);
		money = 1300 + random(500);
		message_vision("[1;30m$N¾¡ÇéµÄµ½´¦ËÑ¹Î, ËÑ³ö "+money+" Ã¶½ğ±Ò¡£[m\n", me);
		env->add_temp("destroy_normal", 1); // Ã¿´ÎÔö¼ÓÒ»£¬Ö±µ½ 5£¬¾Í±»ÆÈÍ£Õ½
		me->got_money(money);
		me->add("war_score/gold", money);

		kingdom_data(id, "war", "add", enemy_id, ({"gold", money}));
		kingdom_data(enemy_id, "war", "add", id, ({"gold_", money}));

		kingdom_data(enemy_id, "data", "sub", "gold", money);

		for(int i=0;i<2;i++) {
			// ¸ù¾İ»ù±¾µÄÊØÎÀ³öÀ´, Ë³±ã¿´Òª²¹É¶×ÊÑ¶... ÀıÈç, Äã¿ÉÒÔÒÀÕÕ¸÷¹ú¼ÒµÄÄ³·¢Õ¹À´¾ö¶¨³ö npc µÄ level
			// ¶¼¿ÉÒÔÔÚ´Ë²¹½øÈ¥
			ob = new("/d/obj/npc/guard_1.c");
			ob->set("kingdom", enemy_id);
			ob->move(env);
		}
		message_vision("$N´ÓÍõ×ùÄÚ³å³öÀ´£¬±£»¤×îºóµÄ·ÀÏß¡£\n", ob);
		if( env->query_temp("destroy_normal")>=5 ) {
			env->set_temp("destroy", 1);
			me->add("war_score/building", 1);
			kingdom_data(id, "war", "add", enemy_id, ({"building",1}) );
			kingdom_data(enemy_id, "war", "add", id, ({"building_",1}) );

			shout(HIR+full_kingdom(id)+"Ç¿ĞĞ¹¥Ïİ"+full_kingdom(enemy_id)+"µÄÍõ×ù"+NOR+"\n\n");
			write(HIR+full_kingdom(id)+"Ç¿ĞĞ¹¥Ïİ"+full_kingdom(enemy_id)+"µÄÍõ×ù"+NOR+"\n\n");
			call_out("do_wait_war_end", 0, id, enemy_id);
		}
//	} else if() {	// ÌØÊâ½¨ÖşÎïµÄÅĞ¶¨, Ä¿Ç°²»Ìá¹©, ÇëÓĞ¿Õ×Ô¼º²¹½øÈ¥
	} else {	// ÆäËûµÄÒ»°ã·¿¼ä
		env->set_temp("destroy", 1);
		message_vision("[1;30m$NÄÃÆğ»ğ°Ñ½«ÕâÀï·ÙÉÕ´ù¾¡¡£[m\n", me);
		kingdom_data(id, "war", "add", enemy_id, ({"room",1}) );
		kingdom_data(enemy_id, "war", "add", id, ({"room_",1}) );
		me->add("war_score/room", 1);
	}
	return 1;
}

int help(object me)
{
	write(@HELP
Ö¸Áî¸ñÊ½ : destroy

ÕâÊÇ´İ»Ù½»Õ½¹ú½¨ÖşÎïµÄÖ¸Áî£¬µ±ÄãÏÂÁËÕâ¸öÖ¸Áî£¬¶Ô·½µÄ½¨ÖşÎï»áÒÀÆä·À
Óù³Ì¶È½øĞĞ·´»÷£¬ÉõÖÁ»¹»áÓĞ¸÷ÖÖÉúÎï³öÀ´¹¥»÷Äã¡£²»¹ı£¬Ö»ÒªÄãÄÜ¿Ë·şÒ»
ÇĞÕÏ°­£¬Äã¾Í¿ÉÒÔ¶Ô·½µÄ½¨ÖşÎïËğ»µ£¬²¢ÇÒËÑ¹Îµ½Ò»´ó±ÊÇ®¡£´İ»Ù½¨ÖşÎï»á
°ïÄãµÄ¹ú¼Ò´óÁ¿ÌáÉıÕ½Ê¤µãÊı£¬²¢ÇÒÊ¹µĞ·½µÄ¹úÁ¦ÃÉÊÜËğÊ§£¬µ±È»£¬ÄãµÄÕ½
¼¨ºÍÕ½¹¦Ò²»á´ó´óµÄ¼ÇÉÏÒ»±Ê¡£

ÁíÍâ£¬µĞÈËËù½¨Ôì·¿¼äÒ²¿ÉÒÔÓÃÕâ¸öÖ¸ÁîÇå³ı£¬Ö»ÊÇÃ»ÓĞÕ½¹¦Ò²ËÑ²»µ½Ç®¡£
ÕâĞ©·Ç½¨ÖşÎïµÄ·¿¼ä±»´İ»Ùºó²»ÄÜĞŞ¸´£¬ÔÚÏÂÒ»´Î reboot ºó¾Í»á»Ö¸´Õı³£¡£

µ±ÄãÕ¶É±µĞÈË»ò´İ»ÙµĞ·½½¨ÖşÎïºó, Äã»áÔö¼ÓÄãµÄÕ½Õù¾­Ñé, ÕâĞ©¾­Ñé¿ÉÄÜ
»á¶ÔÄãµÄÄÜÁ¦ÌáÉıÓĞËù°ïÖú¡£Äã¿ÉÒÔÔÚ¹úÄÚµÄÓ¢ĞÛ»á¹İÀûÓÃ show À´²éÑ¯Äã
ËùÀÛ»ıµÄÕ½Õù¾­Ñé¡£

Èç¹ûÄãµÄ½¨ÖşÔÚÕ½ÕùÖĞ±»´İ»Ù£¬Äã¿ÉÒÔÓÃ set_room ÖĞµÄ repair µÄ²ÎÊı°Ñ
½¨ÖşĞŞºÃ¡£

Ïà¹ØÑ¶Ï¢ : kill, kingdoms, declare, set_room

HELP
	);
	return 1;
}
