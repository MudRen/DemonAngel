//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/62
// saveroom by pawlo    Mon May 26 10:44:34 2003

#include <ansi.h>
inherit BARRACKS;
void create()
{
	set("short", "军营");
	set("long", @TEXT
你走近一座军营的大门, 几个持矛的士兵正在木寨围成的拒马前站着,
穿过大门, 你可以看见一片操场, 象征着军纪的军旗正在操场上飘扬着。
操场边缘有一长列营房, 许多士兵正在靠营房的操场边活动操练。
TEXT
);
	set("type", "barracks");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:44:34 2003", "pawlo", "Mon May 26 10:44:34 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/38",
]));

	setup();
	replace_program(BARRACKS);
}
