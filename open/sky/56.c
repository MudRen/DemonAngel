//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/56
// saveroom by pawlo    Mon May 26 10:18:46 2003

#include <ansi.h>
inherit GATE;
void create()
{
	set("short", "关卡");
	set("long", @TEXT
这里是一个关卡，路两旁各盖\了一作检查哨，路中央还横着拒马，几个\\n横枪执刀的卫兵正在哨站旁检查行人，并且向他们收过路税。
TEXT
);
	set("type", "gate");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:18:46 2003", "pawlo", "Mon May 26 10:18:46 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/55",
]));

	setup();
	replace_program(GATE);
}
