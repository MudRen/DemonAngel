//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/amgbell_343.c
// saveitem by system @ Sun May 25 15:14:21 2003

#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create() {
	set_name( "make27_tick53_sk82_dex5", ({ /* sizeof() == 2 */
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
		set("invoke_magic", "strong");
		set("level",41);
		set("skill",82);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_staff(13);
	setup();
}
