//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/71
// saveroom by pawlo    Mon May 26 11:01:40 2003

#include <ansi.h>
inherit MISC_SHOP;
void create()
{
	set("short", "�ӻ���");
	set("long", @TEXT
�������ӻ��꣬��������Ÿ�ʽ����ð���õ��ӻ���Ʒ��������Ŭ������\n�ҿ����Ƿ������Լ���Ҫ����������Ҫ�ĵĶ������� list ��������Ҫ�Ķ���\n�ɡ�
TEXT
);
	set("type", "misc_shop");
	set("refresh_data", ({ "pawlo", "Mon May 26 11:01:40 2003", "pawlo", "Mon May 26 11:01:40 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/69",
]));

	setup();
	replace_program(MISC_SHOP);
}
