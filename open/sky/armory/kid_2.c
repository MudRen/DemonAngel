//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/kid_2.c
// saveitem by system @ Mon May 19 17:40:31 2003

#include <armor.h>
#include <ansi.h>
inherit SHIELD;

void create() {
	set_name( "����", ({ /* sizeof() == 2 */
  "shield",
  "shield"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ķ��ơ�
LONG );
		set("unit","��");
		set("type","shield");
		set("add_attr", ([ /* sizeof() == 1 */
  "Mh" : 6,
]) );
		set("armor_prop/ac", 3);
		set("armor_prop/db", 3);
		set("level",26);
		set("owner","kid");
		set("kingdom","sky");
	}
	setup();
}
