//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/68.c
// saveroom by pawlo @DA, Mon May 26 11:03:14 2003
#include <ansi.h>
inherit GATE;

void create()
{
	set("short", "�ؿ�");
	set("long", @LONG
������һ���ؿ���·���Ը���\\\��һ������ڣ�·���뻹���ž�������\\\\n��ǹִ��������������վ�Լ�����ˣ������������չ�·˰��
LONG
	);
	set("type", "gate");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 10:52:11 2003",
  "pawlo",
  "Mon May 26 11:03:14 2003"
}));
	set("limit", ([ /* sizeof() == 2 */
  "pass" : "minister_only",
  "exit" : "south",
]));
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"69",
  "north" : __DIR__"67",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(GATE);
}
