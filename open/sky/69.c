//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/69.c
// saveroom by pawlo @DA, Wed May 28 09:22:45 2003
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
  "Mon May 26 10:55:28 2003",
  "pawlo",
  "Wed May 28 09:22:45 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"68",
  "south" : __DIR__"75",
  "east" : __DIR__"70",
  "west" : __DIR__"71",
]));

	setup();
	replace_program(ROOM);
}
