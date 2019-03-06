//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// room : /u/b/bor/workroom.c

#include <ansi.h>
#include <login.h>

inherit ROOM;
void create()
{
	set("short", "[1;36mĞ¡Ë®Ñ¼µÄ³¬¼¶¹¤×÷ÊÒ[2;37;0m");
	set("long", @LONG
³¬¼¶¹¤×÷ÊÒ¡£
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "out" : START_ROOM
]));
	setup();
	load_object("/obj/board/bor_board");
}
