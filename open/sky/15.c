//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/15
// saveroom by pawlo    Wed May 14 21:43:59 2003

#include <ansi.h>
inherit BOARD;
void create()
{
	set("short", "���԰�");
	set("long", "����һ����ͨ�����԰档
");
	set("type", "board");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/open/sky/1",
]));

	setup();
	replace_program(BOARD);
}
