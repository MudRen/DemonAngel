//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/kid_20.c
// saveitem by system @ Tue May 20 21:29:14 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make30_tick41_sk84_con4", ({ /* sizeof() == 2 */
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
  "con" : 4,
]) );
		set("weapon_prop/wl", 4);
		set("weapon_prop/Mh", 4);
		set("level",42);
		set("skill",84);
		set("owner","kid");
		set("kingdom","sky");
	}
	init_axe(14);
	setup();
}
