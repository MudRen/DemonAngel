//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
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
һ����մ��������ͷ����
LONG );
		set("unit","��");
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
