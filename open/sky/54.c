//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/54
// saveroom by pawlo    Mon May 26 10:17:50 2003

#include <ansi.h>
inherit CHURCH;
void create()
{
	set("short", "����");
	set("long", @TEXT
���߽�һ���ľ��Ľ��ã����ݶ��ϵ��߲�������͸��Ĺ�â�У�����Լ\\n������Щ��ʦ������⻷�Ƶļ�̳ǰ��������ר�������г�ݵ����}��ͨ��
��Ȼ������ĵ�����
TEXT
);
	set("type", "church");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:17:50 2003", "pawlo", "Mon May 26 10:17:50 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/41",
]));

	setup();
	replace_program(CHURCH);
}
