//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/armory/kid_5.c
// saveitem by system @ Mon May 19 17:38:51 2003

#include <armor.h>
#include <ansi.h>
inherit HEAD;

void create() {
	set_name( "ͷ��", ({ /* sizeof() == 2 */
  "head",
  "head"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ��������ͷ����
LONG );
		set("unit","��");
		set("type","head");
		set("add_attr", ([ /* sizeof() == 1 */
  "kar" : 2,
]) );
		set("armor_prop/ac", 2);
		set("armor_prop/db", 2);
		set("level",50);
		set("owner","kid");
		set("kingdom","sky");
	}
	setup();
}
