//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /cmds/min/set_short
// by bor @RG

#pragma optimize
#pragma save_binary

//#include <ansi.h>

int main(object me,string arg)
{
	string *str;
	object env;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("ÄãµÄ¶¯×÷»¹Ã»ÓĞÍê³É¡£\n");
	if( me->is_fighting() ) return notify_fail("Äã»¹ÔÚÕ½¶·ÖĞ¡£\n");
	if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½£ºset_short <ÄÚÈİ>\n");
	if( !env = environment(me)) return notify_fail("ÕÒ²»µ½»·¾³¡£\n");
	if( env->query("no_change") ) return notify_fail("ÕâÀï²»ÄÜ±ä¸ü·¿¼äµÄ×ÊÁÏ¡£\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("ÕâÀï²»ÊÇÎÒ¹úµÄÁìÍÁ¡£\n");

	arg = kill_all_bug(arg);
	arg = ansi_color(arg);

	str = explode(arg, "[");
	if( strlen(arg) > 30+sizeof(str)*4 ) return notify_fail("ÄãµÄ²ÎÊıÌ«³¤ÁË¡£\n");

	if( sscanf(arg, "[%*s") || sscanf(arg, "%*s[%*s") ) env->set("short", arg+"[0m");
	else env->set("short", arg);

	do_saveroom(env);
	write("Íê³É¡£\n");
	return 1;
}

int help(object me)
{
	write(@HELP

Ö¸Áî¸ñÊ½ : set_short <·¿¼äÃû³Æ>

ÕâÊÇ¹úÍõÓë´ó³¼ÓÃÀ´¿ª·¢¹úÍÁµÄÖ¸Áî, Õâ¸öÖ¸ÁîÓÃÀ´¸Ä±äËûËù½¨Á¢µÄ·¿¼äµÄ
Ãû³Æ, ¾ÍÊÇÄãÓÃ look Ê±¿´µ½µÄ¶ÌÃèÊö¡£Õâ¸öÖ¸ÁîÖ»ÊÇ¸Ä±äÃû³Æ¶øÒÑ, Èô·¿
¼äµÄÒ»ÇĞ¶¼ÅªºÃÁË, Òª¼ÇµÃÓÃ saveroom °Ñ·¿¼ä´æÆğÀ´¡£

        set_short       : Éè¶¨·¿¼äµÄÃû×Ö, ¾ÍÊÇÄã¿´µ½µÄµÚÒ»ĞĞ¡£
        set_long        : Éè¶¨·¿¼äµÄÃèÊö, ¾ÍÊÇÄã¿´µ½µÄÄÇ¶ÑÃèÊö¡£
        add_mob         : ÎªÕâ¸ö·¿¼äÌí¼ÓÒ»Ğ©ÉúÎï¡£
        add_desc        : ÎªÕâ¸ö·¿¼ä¼ÓÈëÒ»Ğ©¿ÉÒÔ¿´µÄÃèÊö¡£
        saveroom        : µ±Äã°Ñ·¿¼äµÄÒ»ÇĞ¶¼Éè¶¨ºÃÁË,¼ÇµÃÒ»¶¨Òª´æÆğÀ´¡£

µ±ÄãµÄ·¿¼äÓĞÉÏÉ«µÄ»°£¬×îºóÒ»¸ö×Ö»áÌæÄã²¹ÉÏÑÕÉ«»¹Ô­Âë $NOR$£¬
Äã¿ÉÒÔ²»ÓÃ×Ô¼º²¹ÉÏ¡£

ÆäËûÏà¹Ø×ÊÑ¶ :  set_short, set_long, add_mob, add_desc,
		saveroom, ansi

HELP
	);
	return 1;
}
