//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/66
// saveroom by pawlo    Mon May 26 10:49:12 2003

#include <ansi.h>
inherit STABLE;
void create()
{
	set("short", "��");
	set("long", @TEXT
���߽�һ������˲�����ζ�������������Կ���һЩ׳˶�ߴ�ǿ׳��\n����������һ���ߵ��ֿ����ߵ����Ա��ֳ�һ���ģ��е���������\n�Ļ����š��м������������Ŷ��Ų��ϵĳ��ӣ��Ѳ��ϲ�������ǰ��ʳ����\n�������������˻����������䣬����������������Զ��������������ǿ
�������֣���Ҫ����Щ��������Ʊ�����Ҫ���Լ�ȥѱ�����ǣ����������
����������Ǡ������˵ġ�
TEXT
);
	set("type", "stable");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:49:12 2003", "pawlo", "Mon May 26 10:49:12 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/38",
]));

	setup();
	replace_program(STABLE);
}
