//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/5.c
// saveroom by pawlo @DA, Thu May 22 13:49:30 2003
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
  "Wed May 14 21:42:55 2003",
  "pawlo",
  "Thu May 22 13:49:30 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/2" : 1,
]));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"6",
  "west" : __DIR__"4",
]));

	setup();
	replace_program(ROOM);
}
