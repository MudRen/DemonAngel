//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/30
// saveroom by pawlo    Tue May 20 14:06:03 2003

#include <ansi.h>
inherit HERB_SHOP;
void create()
{
	set("short", "ҩ��");
	set("long", @TEXT
ҩ��
TEXT
);
	set("type", "herb_shop");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/29",
]));

	setup();
	replace_program(HERB_SHOP);
}
