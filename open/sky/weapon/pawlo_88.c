//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/pawlo_88.c
// saveitem by system @ Fri May 23 22:20:07 2003

#include <weapon.h>
#include <ansi.h>
inherit WAND;

void create() {
	set_name( "make30_tick31_sk78_int3", ({ /* sizeof() == 2 */
  "wand",
  "wand"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ��������ħ�ȡ�
LONG );
		set("unit","��");
		set("type","wand");
		set("add_attr", ([ /* sizeof() == 1 */
  "int" : 3,
]) );
		set("weapon_prop/wl", 3);
		set("weapon_prop/Mh", 3);
		set("invoke_magic", "strong");
		set("level",39);
		set("skill",78);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_wand(13);
	setup();
}
