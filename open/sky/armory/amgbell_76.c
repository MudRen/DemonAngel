//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/amgbell_76.c
// saveitem by amgbell @ Mon May 19 22:00:47 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make21_tick43_lv30_sta4", ({ /* sizeof() == 2 */
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
  "sta" : 4,
]) );
		set("armor_prop/ac", 4);
		set("armor_prop/db", 4);
		set("level",30);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
