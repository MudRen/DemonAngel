//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/pawlo_16.c
// saveitem by pawlo @ Tue May 20 10:20:18 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make50_41tick_sk140_int4", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������ĸ�ͷ��
LONG );
		set("unit","��");
		set("type","axe");
		set("add_attr", ([ /* sizeof() == 1 */
  "int" : 4,
]) );
		set("weapon_prop/wl", 4);
		set("weapon_prop/Mh", 4);
		set("level",70);
		set("skill",140);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(23);
	setup();
}
