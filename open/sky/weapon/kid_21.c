//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/kid_21.c
// saveitem by system @ Tue May 20 21:30:29 2003

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create() {
	set_name( "make30_tick31_sk78_con3", ({ /* sizeof() == 2 */
  "sword",
  "sword"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ľ���
LONG );
		set("unit","��");
		set("type","sword");
		set("add_attr", ([ /* sizeof() == 1 */
  "con" : 3,
]) );
		set("weapon_prop/wl", 3);
		set("weapon_prop/Mh", 3);
		set("level",39);
		set("skill",78);
		set("owner","kid");
		set("kingdom","sky");
	}
	init_sword(13);
	setup();
}
