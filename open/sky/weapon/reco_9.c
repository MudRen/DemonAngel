//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
#include <weapon.h>
#include <ansi.h>
inherit AXE;
void create() {
	set_name("斧头", ({"axe"}) );
	set_weight(10); 
	set("new", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的斧头。
LONG );
		set("unit","把");
		set("weapon_prop/wl",4);
		set("weapon_prop/Mh",4);
		set("type","axe");
		set("level",40);
		set("skill",80);
		set("owner","reco");
		set("kingdom","sky");
	}
	init_axe(13);
	setup();
}
