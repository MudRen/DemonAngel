//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/pawlo_6.c
// saveitem by system @ Mon May 19 17:37:27 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "��ָ", ({ /* sizeof() == 2 */
  "ring",
  "ring"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ľ�ָ��
LONG );
		set("unit","��");
		set("type","ring");
		set("add_attr", ([ /* sizeof() == 1 */
  "con" : 1,
]) );
		set("armor_prop/ac", 1);
		set("armor_prop/db", 1);
		set("level",4);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	setup();
}
