//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/2.c
// saveroom by pawlo @DA, Mon Mar 10 20:59:54 2003
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
  "Sun Mar 09 20:24:18 2003",
  "pawlo",
  "Mon Mar 10 20:59:54 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/0" : 1,
]));
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"1",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(ROOM);
}
