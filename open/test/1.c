//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// room : /open/test/1.c
// saveroom by testlife @DA, Mon Mar 10 23:07:24 2003
#include <ansi.h>
inherit PORT;

void create()
{
	set("short", "[35m³¬¼¶¸Û¿Ú[0m");
	set("long", @LONG
ÕâÊÇÒ»¼äÊ²Ã´Ò²Ã»ÓĞµÄ¿Õ·¿¼ä£¬ÇëÀûÓÃ set_long À´±à¼­·¿¼äĞğÊö¡£
LONG
	);
	set("type", "port");
	set("refresh_data", ({ /* sizeof() == 4 */
  "testlife",
  "Sat Mar 08 22:54:05 2003",
  "testlife",
  "Mon Mar 10 23:07:24 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/1" : 1,
]));
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"kingdom",
  "south" : __DIR__"2",
]));
	set("kingdom_id", "test");

	setup();
	replace_program(PORT);
}
