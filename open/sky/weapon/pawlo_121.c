//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/pawlo_121.c
// saveitem by pawlo @ Sun May 25 16:24:03 2003

#include <weapon.h>
#include <ansi.h>
inherit WAND;

void create() {
	set_name( "[1;31m��֮��[2;37;0m", ({ /* sizeof() == 2 */
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
  "str" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("invoke_magic", "strong");
		set("level",45);
		set("skill",90);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_wand(15);
	setup();
}
