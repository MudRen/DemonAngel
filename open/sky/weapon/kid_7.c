//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/kid_7.c
// saveitem by system @ Sun May 18 22:43:47 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "斧头", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的斧头。
LONG );
		set("unit","把");
		set("type","axe");
		set("level",80);
		set("skill",160);
		set("add_attr","con");
		set("weapon_prop/con", 1);
		set("owner","kid");
		set("kingdom","sky");
	}
	init_axe(2613);
	setup();
}
