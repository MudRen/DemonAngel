//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/14.c
// savenpc by pawlo    Tue May 27 00:52:33 2003

inherit TAVERN_NPC;

#include <ansi.h>

void create()
{
	set_name("����", ({"man", "m", "ma"}) );
	set("long", @TEXT
�㿴��һλ�ڶ�ʮһ���ľ���
TEXT
	);
	set("type", "tavern");
	set("level", 21);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 27 00:52:33 2003",
  "pawlo",
  "Tue May 27 00:52:33 2003"
}));
	set("gender", "����");
	set("race", "����");
	set("unit", "λ");
	set("home", "/open/sky/4");
	set("kingdom", "sky");
	setup_npc();

}
