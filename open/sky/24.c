//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/24.c
// saveroom by amgbell @DA, Fri May 23 22:35:56 2003
#include <ansi.h>
inherit FURNACE;

void create()
{
	set("short", "���¯");
	set("long", @LONG
�򿪿��ؾͿ���������,��ͷ�ǵò���.......
LONG
	);
	set("type", "furnace");
	set("refresh_data", ({ /* sizeof() == 4 */
  "amgbell",
  "Mon May 19 21:51:07 2003",
  "amgbell",
  "Fri May 23 22:35:56 2003"
}));
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"25",
  "down" : __DIR__"19",
  "west" : __DIR__"49",
  "east" : __DIR__"50",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(FURNACE);
}
