//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/35.c
// saveroom by amgbell @DA, Tue May 27 00:15:42 2003
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
  "amgbell",
  "Tue May 27 00:15:42 2003",
  "amgbell",
  "Tue May 27 00:15:42 2003"
}));
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"74",
  "north" : __DIR__"32",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(ROOM);
}
