//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/obj/npc/wp/thin_sword.c

#include <weapon.h>

inherit SWORD;

void create()
{
	set_name("细剑", ({ "thin sword", "sword", "thin" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("value", 700);
		set("material", "steel");
		set("long", "这是一把又细又长的剑，轻飘飘的像是女孩子家的玩意。\n");
		set("wield_msg", "$N抽出一把剑身细长的剑，握在手中。\n");
		set("unequip_msg", "$N放下手中的$n。\n");
	}
	init_sword(10);
	setup();
}
