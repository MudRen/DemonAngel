//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/amgbell_130.c
// saveitem by amgbell @ Mon May 19 23:16:15 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make20_tick27_lv25_mh5", ({ /* sizeof() == 2 */
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
  "Mh" : 5,
]) );
		set("armor_prop/ac", 2);
		set("armor_prop/db", 2);
		set("level",25);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
