//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/test/2.c
// saveroom by testlife @DA, Mon Mar 10 20:24:47 2003
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
  "testlife",
  "Mon Mar 10 20:23:45 2003",
  "testlife",
  "Mon Mar 10 20:24:47 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/0" : 1,
]));
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"1",
]));
	set("kingdom_id", "test");

	setup();
	replace_program(ROOM);
}
