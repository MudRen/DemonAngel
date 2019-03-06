//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/2.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "街道");
	set("long", @LONG
一般的街道 ...
LONG
	);
	set("exits", ([
		"south" : "/d/gourd/gourd_recall.c",
		"west" : "/d/gourd/swear.c",
		"east" : "/d/gourd/wedding.c",
		"north" : "/d/gourd/3.c",
	]));
	setup();
	replace_program(ROOM);
}
