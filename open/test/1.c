//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/test/1.c
// saveroom by testlife @DA, Mon Mar 10 23:07:24 2003
#include <ansi.h>
inherit PORT;

void create()
{
	set("short", "[35m超级港口[0m");
	set("long", @LONG
这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。
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
