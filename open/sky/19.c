//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/19.c
// saveroom by amgbell @DA, Sun May 18 22:38:37 2003
#include <ansi.h>
inherit FURNACE;

void create()
{
	set("short", "��˹¯");
	set("long", @LONG
����ͷ�Ž�ȥ,����,��������.........
LONG
	);
	set("type", "furnace");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sat May 17 02:48:45 2003",
  "amgbell",
  "Sun May 18 22:38:37 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "up" : __DIR__"24",
  "west" : __DIR__"22",
  "south" : __DIR__"18",
  "east" : __DIR__"23",
]));

	setup();
	replace_program(FURNACE);
}
