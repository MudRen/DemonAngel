//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/75.c
// saveroom by pawlo @DA, Wed May 28 10:44:04 2003
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
  "Wed May 28 09:22:45 2003",
  "pawlo",
  "Wed May 28 10:44:04 2003"
}));
	set("exits", ([ /* sizeof() == 3 */
  "east" : __DIR__"78",
  "north" : __DIR__"69",
  "south" : __DIR__"76",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/19" : 1,
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(ROOM);
}
