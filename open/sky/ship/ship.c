//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// file : /open/sky/ship/ship.c
// save ship by bor @DA, Tue Mar 11 13:11:09 2003
#include <ansi.h>
inherit SHIP;

void create()
{
	set("short", "铁壳船(Iron Ship)");
	set_name( "铁壳船(Iron Ship)", ({ /* sizeof() == 3 */
  "iron ship",
  "iron",
  "ship"
}) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("long", @TEXT
你看到一个破旧的铁制的船只，不少人看着它都不禁摇头不敢
搭乘，宁可绕远路搭乘别的船只，也不愿意靠近，生怕所坐的船只
在半路上触礁而沉没。
TEXT
	);
		set("type", "ship");
		set("port1", "/d/gourd/ship_port.c");
		set("port2", "/open/sky/1.c");
		set("max_load", 15);
		set("value", 1);
		set("unit", "艘");
		set("no_kill", 1);
		set("no_get", 1);
		set("kingdom_id", "sky");
	}
	setup();
}
