//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/33.c
// saveroom by pawlo @DA, Fri May 23 19:32:04 2003
#include <ansi.h>
inherit GATE;

void create()
{
	set("short", "�ؿ�");
	set("long", @LONG
�ؿ�
LONG
	);
	set("type", "gate");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 20 14:41:16 2003",
  "pawlo",
  "Fri May 23 19:32:04 2003"
}));
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"32",
  "east" : __DIR__"34",
]));
	set("kingdom_id", "sky");
	set("limit", ([ /* sizeof() == 2 */
  "pass" : "king_only",
  "exit" : "east",
]));

	setup();
	replace_program(GATE);
}
