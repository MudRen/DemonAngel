//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/pawlo_71.c
// saveitem by system @ Fri May 23 20:46:41 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make50_tick48_sk148_Mh9", ({ /* sizeof() == 2 */
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
  "Mh" : 9,
]) );
		set("weapon_prop/wl", 4);
		set("weapon_prop/Mh", 4);
		set("level",74);
		set("skill",148);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(24);
	setup();
}
