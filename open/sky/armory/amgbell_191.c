//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/amgbell_191.c
// saveitem by system @ Tue May 27 00:19:40 2003

#include <armor.h>
#include <ansi.h>
inherit HEAD;

void create() {
	set_name( "make23_tick32_lv30_str3", ({ /* sizeof() == 2 */
  "head",
  "head"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的头盔。
LONG );
		set("unit","件");
		set("type","head");
		set("add_attr", ([ /* sizeof() == 1 */
  "str" : 3,
]) );
		set("armor_prop/ac", 3);
		set("armor_prop/db", 3);
		set("level",30);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
