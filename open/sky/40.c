//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/40.c
// saveroom by pawlo @DA, Sun Jun 08 16:20:03 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�շ��� - ��ʹ�� set_short ���༭����");
	set("long", @LONG
����һ��ʲôҲû�еĿշ��䣬������ set_long ���༭����������
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Fri May 23 08:22:57 2003",
  "pawlo",
  "Sun Jun 08 16:20:03 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"41",
  "north" : __DIR__"38",
  "west" : __DIR__"52",
]));

	setup();
	replace_program(ROOM);
}
