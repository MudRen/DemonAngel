//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
  // Room: /d/city/recall_s_w.c

#include <ansi.h>

inherit ROOM;

int check_legal_id(string id);
int check_legal_name(string name);

void create()
{
	set("short", "Ô²¶¥½¨Öş");
	set("long", @LONG
ºÚÊĞ£¬×¨ÃÅÂò¹ú¼ÒµÄ¡£

	Ê¹ÓÃ¸ñÊ½£ºbuy_kingdom <ÖĞÎÄ> <Ó¢ÎÄ>

LONG
	);
	set("exits", ([
        "east": __DIR__"recall_s_1"
	]));
	set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_buy", "buy_kingdom");
}

int do_buy(string arg)
{
	object me = this_player();
	string name, id;

        seteuid(getuid());
	if(!me->query_temp("kingdom_build")) return notify_fail("ÔİÊ±²»¿ª·Å½¨¹úÁË...²»È»ÈËÈË¶¼ÊÇ¹úÍõ .. ÓĞµã¹îÒì¡£\n");
	if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½£ºbuy_kingdom <ÖĞÎÄ> <Ó¢ÎÄ>\n");
	if( me->query("kingdom") ) return notify_fail("½¨¹ú±ØĞëÆ½Ãñ²ÅĞĞ¡£\n");
	if( sscanf(arg, "%s %s", name, id)!=2 )
		return notify_fail("Ö¸Áî¸ñÊ½£ºbuy_kingdom <ÖĞÎÄ> <Ó¢ÎÄ>\n");
//	if( !(me->can_afford(300000)) )
//		return notify_fail("ÄãÉíÉÏ²»¹» 30 Íò½ğ±Ò£¬ÎŞ·¨½¨¹ú !!\n");
	if(!check_legal_name(name)||!check_legal_id(id)) return 1;
	if( check_kingdom(id) ) return notify_fail("´Ë¹úºÅÒÑ¾­ÓĞ¹ú¼ÒÕıÔÚÊ¹ÓÃ£¬Çë»»¸öÓ¢ÎÄ !!\n");
	if( file_size(DATA_DIR+"nuke/kingdom/"+id) == -2 )
		return notify_fail("´Ë¹úºÅÔø¾­³öÏÖÔÚÀúÊ·ÉÏ£¬Çë»»¸öÓ¢ÎÄ¡£\n");
	mkdir(KINGDOM_DIR+id);
	mkdir(DATA_DIR+"nuke/kingdom/"+id);
	mkdir(DATA_DIR+"kingdom/"+id);
	KINGDOM_D->creat_kingdom_data(id, name, me);
	create_kingdom(me, id, name);

	shout(HIM"¡¾½¨¹ú×ÊÑ¶¡¿"+HIY+"ÓÉ"+me->name_id(1)+HIY+"ËùÁìµ¼µÄ¹ú¼Ò -- "+name+"("+id+")ÕıÊ½³ÉÁ¢¡£\n"+NOR);
	write(HIM"¡¾½¨¹ú×ÊÑ¶¡¿"+HIY+"ÓÉ"+me->name_id(1)+HIY+"ËùÁìµ¼µÄ¹ú¼Ò -- "+name+"("+id+")ÕıÊ½³ÉÁ¢¡£\n"+NOR);

//	me->pay_money(300000);
	me->save();

        return 1;
}

int check_legal_name(string name)
{
	int i;

	if(name=="") return 0;

	i = strlen(name);
        
	if( (strlen(name) < 4) || (strlen(name) > 12 ) ) {
		write("¹ú¼ÒÖĞÎÄÃû×Ö±ØĞëÊÇ 2 µ½ 6 ¸öÖĞÎÄ×Ö¡£\n");
		return 0;
	}
	while(i--) {
		if( name[i]<='' ) {
			write("¹ú¼ÒÖĞÎÄÃû×Ö²»ÄÜÓÃ¿ØÖÆ×ÖÔª¡£\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("ÇëÄúÓÃ¡°ÖĞÎÄ¡±È¡¹ú¼ÒÃû×Ö¡£\n");
			return 0;
		}
	}
	return 1;
}

int check_legal_id(string id)
{
	int i;

	if(id=="") return 0;
	i = strlen(id);

	if( i < 3 || i > 15 ) {
		write("¹ú¼ÒÓ¢ÎÄÃû×Ö±ØĞëÊÇ 3 µ½ 15 ¸öÓ¢ÎÄ×ÖÄ¸¡£\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z')
		if( id[i] != '_') {
			write("ÄãÖ»ÄÜÊ¹ÓÃÓ¢ÎÄ»òÕß _ µÄ·ûºÅÀ´µ±×÷¹ú¼ÒµÄÓ¢ÎÄ¡£\n");
			return 0;
		}

	return 1;
}
