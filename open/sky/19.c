//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/19.c
// saveroom by amgbell @DA, Sun May 18 22:38:37 2003
#include <ansi.h>
inherit FURNACE;

void create()
{
	set("short", "瓦斯炉");
	set("long", @LONG
把猪头放进去,开火,就煮熟了.........
LONG
	);
	set("type", "furnace");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sat May 17 02:48:45 2003",
  "amgbell",
  "Sun May 18 22:38:37 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "up" : __DIR__"24",
  "west" : __DIR__"22",
  "south" : __DIR__"18",
  "east" : __DIR__"23",
]));

	setup();
	replace_program(FURNACE);
}
