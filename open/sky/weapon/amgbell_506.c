//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/amgbell_506.c
// saveitem by system @ Sun May 25 15:47:27 2003

#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create() {
	set_name( "make28_tick51_sk84_dex5", ({ /* sizeof() == 2 */
  "staff",
  "staff"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ĺ�����
LONG );
		set("unit","��");
		set("type","staff");
		set("add_attr", ([ /* sizeof() == 1 */
  "dex" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("invoke_magic", "wolf");
		set("level",42);
		set("skill",84);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_staff(14);
	setup();
}
