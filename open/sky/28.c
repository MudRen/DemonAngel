//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/28
// saveroom by pawlo    Tue May 20 13:57:39 2003

#include <ansi.h>
inherit MISC_SHOP;
void create()
{
	set("short", "杂货店");
	set("long", @TEXT
	杂货店
TEXT
);
	set("type", "misc_shop");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/26",
]));

	setup();
	replace_program(MISC_SHOP);
}
