//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/amgbell_85.c
// saveitem by amgbell @ Mon May 19 22:37:16 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make23_tick31_lv30_sta3", ({ /* sizeof() == 2 */
  "ring",
  "ring"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ľ�ָ��
LONG );
		set("unit","��");
		set("type","ring");
		set("add_attr", ([ /* sizeof() == 1 */
  "sta" : 3,
]) );
		set("armor_prop/ac", 3);
		set("armor_prop/db", 3);
		set("level",30);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
