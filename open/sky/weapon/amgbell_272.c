//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/amgbell_272.c
// saveitem by system @ Fri May 23 22:47:28 2003

#include <weapon.h>
#include <ansi.h>
inherit DAGGER;

void create() {
	set_name( "make27_tick56_sk84_sta5", ({ /* sizeof() == 2 */
  "dagger",
  "dagger"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ��������ذ�ס�
LONG );
		set("unit","��");
		set("type","dagger");
		set("add_attr", ([ /* sizeof() == 1 */
  "sta" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("level",42);
		set("skill",84);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_dagger(14);
	setup();
}
