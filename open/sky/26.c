//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/26.c
// saveroom by pawlo @DA, Tue May 20 14:05:51 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "空房间 - 请使用 set_short 来编辑标题");
	set("long", @LONG
这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 20 13:50:32 2003",
  "pawlo",
  "Tue May 20 14:05:51 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"27",
  "west" : __DIR__"28",
  "north" : __DIR__"kingdom",
  "south" : __DIR__"29",
]));

	setup();
	replace_program(ROOM);
}
