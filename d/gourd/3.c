//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/3.c

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
		"south" : "/d/gourd/2.c",
		"east" : "/d/gourd/gourd-gift_shop.c",
		"west"	: "/d/gourd/pet.c",
		"north" : "/d/gourd/4.c"
	]));
	set("objects", ([
		__DIR__"npc/mob1" : 1,
	]) );

	setup();
	replace_program(ROOM);
}
