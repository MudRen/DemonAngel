//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/67.c
// saveroom by pawlo @DA, Mon May 26 11:49:49 2003
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
  "Mon May 26 10:52:02 2003",
  "pawlo",
  "Mon May 26 11:49:49 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"41",
  "south" : __DIR__"68",
]));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/12" : 1,
]));

	setup();
	replace_program(ROOM);
}
