//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/7.c
// savenpc by pawlo    Fri May 23 13:14:05 2003

inherit BARRACKS_NPC;

#include <ansi.h>

void create()
{
	set_name("����", ({"guard", "g", "gu"}) );
	set("long", @TEXT
�㿴��һλ��ʮ����������
TEXT
	);
	set("type", "barracks");
	set("level", 10);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Fri May 23 13:14:05 2003",
  "pawlo",
  "Fri May 23 13:14:05 2003"
}));
	set("gender", "����");
	set("race", "����");
	set("unit", "λ");
	set("home", "/open/sky/45");
	set("kingdom", "sky");
	setup_npc();

}
