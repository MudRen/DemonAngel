//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/test/kingdom.c
// saveroom by testlife @ Sat Mar 08 22:54:05 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "体验王座");
	set("long", @LONG
王座是国家最重要的地方，也是国家的精神象征，平时国王与大
臣们谈论国家重要政策的最佳场所，王座的存在与否关系着国家能不
能存在，所谓座在国在，座亡国亡，希望国民能好好保护这里。
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "testlife",
  "Sat Mar 08 22:54:01 2003",
  "testlife",
  "Sat Mar 08 22:54:05 2003"
}));
	set("kingdom_id", "test");
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"1",
]));
	set("no_delete", 1);

	setup();
	replace_program(ROOM);
}
