//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// room : /open/sky/1.c
// saveroom by pawlo @DA, Wed May 14 21:43:59 2003
#include <ansi.h>
inherit PORT;

void create()
{
	set("short", "[1;36m³ØÌÁ[0m");
	set("long", @LONG
ÕâÊÇÒ»¼äÊ²Ã´Ò²Ã»ÓĞµÄ¿Õ·¿¼ä£¬ÇëÀûÓÃ set_long À´±à¼­·¿¼äĞğÊö¡£
LONG
	);
	set("type", "port");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sun Mar 09 20:24:01 2003",
  "pawlo",
  "Wed May 14 21:43:59 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"15",
  "west" : __DIR__"kingdom",
  "east" : __DIR__"3",
  "south" : __DIR__"2",
]));

	setup();
	replace_program(PORT);
}
