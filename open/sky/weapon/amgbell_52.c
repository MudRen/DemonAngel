//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/amgbell_52.c
// saveitem by amgbell @ Tue May 20 20:23:04 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make35_tick51_sk104_sta5", ({ /* sizeof() == 2 */
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
  "sta" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("level",52);
		set("skill",104);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_axe(17);
	setup();
}
