//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/15.c
// savenpc by pawlo    Tue May 27 09:31:04 2003

inherit STABLE_NPC;

#include <ansi.h>

void create()
{
	set_name("Ұ��", ({"horse", "h", "ho"}) );
	set("long", @TEXT
�㿴��һλ��ʮ�弶��Ұ��
TEXT
	);
	set("type", "stable");
	set("level", 15);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 27 09:31:04 2003",
  "pawlo",
  "Tue May 27 09:31:04 2003"
}));
	set("gender", "����");
	set("race", "Ұ��");
	set("unit", "λ");
	set("home", "/open/sky/7");
	set("kingdom", "sky");
	set("ridable", 1);
	setup_npc();

}
