//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/42
// saveroom by pawlo    Fri May 23 08:23:10 2003

#include <ansi.h>
inherit STABLE;
void create()
{
	set("short", "���\");
	set("long", @TEXT
���߽�һ������˲�����ζ�����A�������Կ���һЩ׳˶�ߴ�ǿ׳��
���������Qһ���ߵ��ֿ����ߵ����Ա��ֳ�һ���ģ��е���������
�Ļ����š��м������������Ŷ��Ų��ϵĳ��ӣ��Ѳ��ϲ�������ǰ��ʳ����
�������������˻����������䣬����������������Զ��������������ǿ
�������֣���Ҫ����Щ��������Ʊ�����Ҫ���Լ�ȥѱ�����ǣ����������
����������Ǡ������˵ġ�
TEXT
);
	set("type", "stable");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/38",
]));

	setup();
	replace_program(STABLE);
}
