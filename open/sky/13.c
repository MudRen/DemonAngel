//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/13.c
// saveroom by pawlo @DA, Wed May 14 21:43:39 2003
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
  "Wed May 14 21:43:39 2003",
  "pawlo",
  "Wed May 14 21:43:39 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"12",
  "east" : __DIR__"14",
]));

	setup();
	replace_program(ROOM);
}