//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/pawlo_44.c
// saveitem by system @ Tue May 20 09:12:19 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "��ָ", ({ /* sizeof() == 2 */
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
