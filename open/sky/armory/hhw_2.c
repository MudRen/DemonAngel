//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/hhw_2.c
// saveitem by system @ Sun May 25 22:20:49 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make30_tick17_lv35_dex1", ({ /* sizeof() == 2 */
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
  "dex" : 1,
]) );
		set("armor_prop/ac", 1);
		set("armor_prop/db", 1);
		set("level",35);
		set("owner","hhw");
		set("kingdom","sky");
	}
	setup();
}
