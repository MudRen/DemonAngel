//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/pawlo_44.c
// saveitem by system @ Tue May 20 09:12:19 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "戒指", ({ /* sizeof() == 2 */
  "ring",
  "ring"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的戒指。
LONG );
		set("unit","件");
		set("type","ring");
		set("add_attr", ([ /* sizeof() == 1 */
  "Mh" : 6,
]) );
		set("armor_prop/ac", 3);
		set("armor_prop/db", 3);
		set("level",26);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	setup();
}
