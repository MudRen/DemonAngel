//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/70.c
// saveroom by pawlo @DA, Mon May 26 10:58:17 2003
#include <ansi.h>
inherit HERB_SHOP;

void create()
{
	set("short", "ҩ��");
	set("long", @LONG
���߽�һ�ҳ���ҩ��ζ��ҩ��, ��������Ÿ���ƿƿ�޹�, ���������
���򵽸�����ҩ������������, �������øò�һ����, ������ list ��
����ʲô��ɫ, �ٿ���Ҫ��Ҫ��(buy)��
LONG
	);
	set("type", "herb_shop");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 10:55:35 2003",
  "pawlo",
  "Mon May 26 10:58:17 2003"
}));
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"69",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(HERB_SHOP);
}
