//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/amgbell_223.c
// saveitem by system @ Fri May 23 23:11:53 2003

#include <weapon.h>
#include <ansi.h>
inherit DAGGER;

void create() {
	set_name( "make27_tick54_sk82_str5", ({ /* sizeof() == 2 */
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
  "str" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("level",41);
		set("skill",82);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_dagger(13);
	setup();
}
