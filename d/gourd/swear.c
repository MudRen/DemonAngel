//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/swear.c

#include <room.h>

inherit SWEAR;

void create()
{
	set("short", "天地庙");
	set("long", @LONG
结拜, 收养的的地方...
结拜:
	swear <对象>
收养:
	adopt <对象> as child        跟<对象>表达收养的意愿。
	adopt <对象> as parent       跟<对象>表达愿意被收养的意愿。

LONG
	);
	set("exits", ([
		"east" : "/d/gourd/2.c",
	]));
	setup();
	replace_program(SWEAR);
}
