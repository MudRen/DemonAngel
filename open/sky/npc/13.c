//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// NPC : /open/sky/npc/13.c
// savenpc by pawlo    Tue May 27 00:52:26 2003

inherit STABLE_NPC;

#include <ansi.h>

void create()
{
	set_name("Ұ��", ({"horse", "h", "ho"}) );
	set("long", @TEXT
�㿴��һλ�ڶ�ʮһ����Ұ��
TEXT
	);
	set("type", "stable");
	set("level", 21);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 27 00:52:26 2003",
  "pawlo",
  "Tue May 27 00:52:26 2003"
}));
	set("gender", "����");
	set("race", "Ұ��");
	set("unit", "λ");
	set("home", "/open/sky/3");
	set("kingdom", "sky");
	setup_npc();

}
