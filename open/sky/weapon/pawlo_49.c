//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/pawlo_49.c
// saveitem by system @ Wed May 21 11:50:14 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make25_tick15_sk56_str1", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的斧头。
LONG );
		set("unit","把");
		set("type","axe");
		set("add_attr", ([ /* sizeof() == 1 */
  "str" : 1,
]) );
		set("weapon_prop/wl", 1);
		set("weapon_prop/Mh", 1);
		set("level",28);
		set("skill",56);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(9);
	setup();
}
