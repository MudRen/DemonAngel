//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/27
// saveroom by pawlo    Tue May 20 13:50:32 2003

#include <ansi.h>
inherit TAVERN;
void create()
{
	set("short", "杂货店");
	set("long", @TEXT
	杂货店
TEXT
);
	set("type", "tavern");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/26",
]));

	setup();
	replace_program(TAVERN);
}
