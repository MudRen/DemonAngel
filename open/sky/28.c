//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/28
// saveroom by pawlo    Tue May 20 13:57:39 2003

#include <ansi.h>
inherit MISC_SHOP;
void create()
{
	set("short", "�ӻ���");
	set("long", @TEXT
	�ӻ���
TEXT
);
	set("type", "misc_shop");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/26",
]));

	setup();
	replace_program(MISC_SHOP);
}
