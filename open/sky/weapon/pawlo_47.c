//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/pawlo_47.c
// saveitem by system @ Wed May 21 12:28:59 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make25_tick11_sk54_sta1", ({ /* sizeof() == 2 */
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
  "sta" : 1,
]) );
		set("weapon_prop/wl", 1);
		set("weapon_prop/Mh", 1);
		set("level",27);
		set("skill",54);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(9);
	setup();
}
