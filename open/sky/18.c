//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/18.c
// saveroom by pawlo @DA, Thu May 22 22:34:59 2003
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
  "Fri May 16 11:49:57 2003",
  "pawlo",
  "Thu May 22 22:34:59 2003"
}));
	set("exits", ([ /* sizeof() == 3 */
  "south" : __DIR__"38",
  "north" : __DIR__"19",
  "east" : __DIR__"kingdom",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(ROOM);
}
