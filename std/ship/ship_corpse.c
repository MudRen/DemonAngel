//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /std/ship/ship_corpse.c
// by bor @DA, 2/24 2003

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "船墓地");
	set("long", @TEXT
这里聚集了非常多的船只, 你不妨等待一下, 让其他船只通过后, 在启程。
TEXT
	);
	set("no_teleport", 1);
	set("no_cast", 1);
	set("no_summon", 1);
	set("no_fight", 1);

	setup();
}
