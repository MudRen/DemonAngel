//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/29.c
// saveroom by pawlo @DA, Tue May 20 14:08:25 2003
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
  "Tue May 20 14:06:03 2003",
  "pawlo",
  "Tue May 20 14:08:25 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "east" : __DIR__"31",
  "west" : __DIR__"30",
  "north" : __DIR__"26",
  "south" : __DIR__"32",
]));

	setup();
	replace_program(ROOM);
}
