//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/6.c
// saveroom by pawlo @DA, Thu May 22 13:49:22 2003
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
  "Wed May 14 21:42:56 2003",
  "pawlo",
  "Thu May 22 13:49:22 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/1" : 1,
]));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"7",
  "west" : __DIR__"5",
]));

	setup();
	replace_program(ROOM);
}
