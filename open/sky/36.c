//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/36.c
// saveroom by pawlo @DA, Mon May 26 10:22:29 2003
#include <ansi.h>
inherit MAGIC_TOWER;

void create()
{
	set("short", "法术研习营");
	set("long", @LONG
这是一间法术研习营，你可以使用 list 来查看你能学习的法术, 以及使用 study 来学习。
LONG
	);
	set("type", "magic_tower");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Thu May 22 14:46:33 2003",
  "pawlo",
  "Mon May 26 10:22:29 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "down" : __DIR__"kingdom",
]));

	setup();
	replace_program(MAGIC_TOWER);
}
