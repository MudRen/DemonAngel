//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/27
// saveroom by pawlo    Tue May 20 13:50:32 2003

#include <ansi.h>
inherit TAVERN;
void create()
{
	set("short", "�ӻ���");
	set("long", @TEXT
	�ӻ���
TEXT
);
	set("type", "tavern");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/26",
]));

	setup();
	replace_program(TAVERN);
}
