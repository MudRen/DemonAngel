//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/pawlo_7.c
// saveitem by system @ Mon May 19 17:36:35 2003

#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create() {
	set_name( "����", ({ /* sizeof() == 2 */
  "boots",
  "boots"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ļ��ߡ�
LONG );
		set("unit","��");
		set("type","boots");
		set("add_attr", ([ /* sizeof() == 1 */
  "sta" : 1,
]) );
		set("armor_prop/ac", 1);
		set("armor_prop/db", 1);
		set("level",5);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	setup();
}
