//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/12.c
// savenpc by pawlo    Mon May 26 11:49:49 2003

inherit STABLE_NPC;

#include <ansi.h>

void create()
{
	set_name("����", ({"horse", "h", "ho"}) );
	set("long", @TEXT
�㿴��һλ��ʮ��������
TEXT
	);
	set("type", "stable");
	set("level", 10);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 11:49:49 2003",
  "pawlo",
  "Mon May 26 11:49:49 2003"
}));
	set("gender", "����");
	set("race", "Ұ��");
	set("unit", "λ");
	set("home", "/open/sky/67");
	set("kingdom", "sky");
	setup_npc();

}
