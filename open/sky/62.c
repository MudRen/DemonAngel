//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/62
// saveroom by pawlo    Mon May 26 10:44:34 2003

#include <ansi.h>
inherit BARRACKS;
void create()
{
	set("short", "��Ӫ");
	set("long", @TEXT
���߽�һ����Ӫ�Ĵ���, ������ì��ʿ������ľկΧ�ɵľ���ǰվ��,
��������, ����Կ���һƬ�ٳ�, �����ž��͵ľ������ڲٳ���Ʈ���š�
�ٳ���Ե��һ����Ӫ��, ���ʿ�����ڿ�Ӫ���Ĳٳ��߻������
TEXT
);
	set("type", "barracks");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:44:34 2003", "pawlo", "Mon May 26 10:44:34 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/38",
]));

	setup();
	replace_program(BARRACKS);
}
