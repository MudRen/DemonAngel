//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /cmds/usr/chfn.c
// by bor @DA, 3/17 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int check_legal_name(string name);

int main(object me, string arg)
{
	string *name;
	seteuid(getuid(me));

	if(!arg) return notify_fail("Ö¸Áî¸ñÊ½ : chfn <ÖĞÎÄÃû×Ö>\n");
	if(!wizardp(me)) {
		if( strlen(arg) > 12) return notify_fail("ÄãµÄÃû×ÖÌ«³¤£¬ÇëÈ¡¸ö³¬ìÅµÄÃû×Ö°É !!\n");
		if(!check_legal_name(arg)) return notify_fail("ÄãµÄÃû×Ö°üº¬²»ºÏ·¨µÄ×ÖÑÛÔÚÄÚ¡£\n");
		if( !me->query("kingdom/king") && !me->query("kingdom/minister") )
		if( me->query("level")<10 ) return notify_fail("ÄãµÈ¼¶Ì«µÍ£¬²»ÄÜ¸ÄÀ´¸ÄÈ¥¡£\n");

		if( !me->query("name_time") ) me->set("name_time", 0);
		if( (time()-me->query("name_time")) <= 1200) return notify_fail("Äã²»¾ÃÇ°²Å¸Õ»»¹ıÃû×Ö£¬ÍíµãÔÙ»»°É !!\n");
	}
	me->set("name", arg);
	me->set("name_time", time());
	write("Íê³É¡£\n");
	me->save();
	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);

	if( (strlen(name) < 4) || (strlen(name) > 12 ) ) {
		write("¶Ô²»Æğ£¬ÄãµÄÖĞÎÄÃû×Ö±ØĞëÊÇ 2 µ½ 6 ¸öÖĞÎÄ×Ö¡£\n");
		return 0;
	}
	while(i--) {
		if( name[i]<='' ) {
			write("¶Ô²»Æğ£¬ÄãµÄÖĞÎÄÃû×Ö²»ÄÜÓÃ¿ØÖÆ×ÖÔª¡£\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("¶Ô²»Æğ£¬ÇëÄúÓÃ¡°ÖĞÎÄ¡±È¡Ãû×Ö¡£\n");
			return 0;
		}
		if( name[i..i+1]=="¡¡" ) {
			write("¶Ô²»Æğ£¬Çë²»ÒªÓÃ¿Õ°××ÖÔªÈ¡Ãû×Ö¡£\n");
			return 0;
		}
	}
	return 1;
}

int help(object me)
{
	write(@HELP

Ö¸Áî¸ñÊ½ : chfn <ÖĞÎÄÃû×Ö>
 
Õâ¸öÖ¸Áî¿ÉÒÔÈÃÄã¸ÄÃû×Ö£¬ÓĞ³¤¶ÈÏŞÖÆÇÒ²»ÄÜÁ¬Ğø¸ü»»¡£

HELP
	);
	return 1;
}
