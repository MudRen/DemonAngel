//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/25
// saveroom by amgbell    Mon May 19 21:51:07 2003

#include <ansi.h>
inherit SHOP;
void create()
{
	set("short", "�̵�");
	set("long", @TEXT����һ���̵������ sell ��Ʒ��
TEXT
);
	set("type", "shop");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/open/sky/24",
]));

	setup();
	replace_program(SHOP);
}
