//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/32.c
// saveroom by pawlo @DA, Tue May 20 16:28:23 2003
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
  "Tue May 20 14:40:01 2003",
  "pawlo",
  "Tue May 20 16:28:23 2003"
}));
	set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"29",
  "south" : __DIR__"35",
  "east" : __DIR__"33",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(ROOM);
}
