//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/68.c
// saveroom by pawlo @DA, Mon May 26 11:03:14 2003
#include <ansi.h>
inherit GATE;

void create()
{
	set("short", "关卡");
	set("long", @LONG
这里是一个关卡，路两旁各盖\\\了一作检查哨，路中央还横着拒马，几个\\\\n横枪执刀的卫兵正在哨站旁检查行人，并且向他们收过路税。
LONG
	);
	set("type", "gate");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 10:52:11 2003",
  "pawlo",
  "Mon May 26 11:03:14 2003"
}));
	set("limit", ([ /* sizeof() == 2 */
  "pass" : "minister_only",
  "exit" : "south",
]));
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"69",
  "north" : __DIR__"67",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(GATE);
}
