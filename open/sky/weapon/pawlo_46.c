//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/pawlo_46.c
// saveitem by system @ Wed May 21 12:30:39 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make25_tick24_sk62_db4", ({ /* sizeof() == 2 */
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
  "db" : 4,
]) );
		set("weapon_prop/wl", 2);
		set("weapon_prop/Mh", 2);
		set("level",31);
		set("skill",62);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(10);
	setup();
}
