//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/19.c
// savenpc by amgbell    Wed May 28 19:31:37 2003

inherit TAVERN_NPC;

#include <ansi.h>

void create()
{
	set_name("С��", ({"child", "c", "ch"}) );
	set("long", @TEXT
�㿴��һλ��һ����С����
TEXT
	);
	set("type", "tavern");
	set("level", 1);
	set("refresh_data", ({ /* sizeof() == 4 */
  "amgbell",
  "Wed May 28 19:31:37 2003",
  "amgbell",
  "Wed May 28 19:31:37 2003"
}));
	set("gender", "����");
	set("race", "����");
	set("unit", "λ");
	set("home", "/open/sky/kingdom");
	set("kingdom", "sky");
	setup_npc();

}
