//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/1.c
// savenpc by pawlo    Thu May 22 13:49:22 2003

inherit TAVERN_NPC;

#include <ansi.h>

void create()
{
	set_name("����", ({"man", "m", "ma"}) );
	set("long", @TEXT
�㿴��һλ��ʮ���ľ���
TEXT
	);
	set("type", "tavern");
	set("level", 10);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Thu May 22 13:49:22 2003",
  "pawlo",
  "Thu May 22 13:49:22 2003"
}));
	set("gender", "����");
	set("race", "����");
	set("unit", "λ");
	set("home", "/open/sky/6");
	set("kingdom", "sky");
	setup_npc();

}
