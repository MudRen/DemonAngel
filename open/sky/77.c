//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/77.c
// saveroom by pawlo @DA, Wed May 28 09:23:00 2003
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
  "Wed May 28 09:22:53 2003",
  "pawlo",
  "Wed May 28 09:23:00 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/16" : 1,
]));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"76",
]));

	setup();
	replace_program(ROOM);
}
