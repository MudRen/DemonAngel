//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/amgbell_57.c
// saveitem by amgbell @ Tue May 20 20:20:23 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make35_tick54_sk106_sta5", ({ /* sizeof() == 2 */
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
  "sta" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("level",53);
		set("skill",106);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_axe(17);
	setup();
}
