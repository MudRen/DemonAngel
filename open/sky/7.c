//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/7.c
// saveroom by pawlo @DA, Tue May 27 09:31:04 2003
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
  "Wed May 14 21:42:58 2003",
  "pawlo",
  "Tue May 27 09:31:04 2003"
}));
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"8",
  "west" : __DIR__"6",
]));
	set("kingdom_id", "sky");
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/15" : 1,
]));

	setup();
	replace_program(ROOM);
}
