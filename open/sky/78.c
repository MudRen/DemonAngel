//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/78
// saveroom by pawlo    Wed May 28 09:40:12 2003

#include <ansi.h>
inherit CHURCH;
void create()
{
	set("short", "����");
	set("long", @TEXT
���߽�һ���ľ��Ľ��ã����ݶ��ϵ��߲�������͸��Ĺ�â�У�����Լ\n������Щ��ʦ������⻷�Ƶļ�̳ǰ��������ר�������г�ݵ����}��ͨ��
��Ȼ������ĵ�����
TEXT
);
	set("type", "church");
	set("refresh_data", ({ "pawlo", "Wed May 28 09:40:12 2003", "pawlo", "Wed May 28 09:40:12 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/75",
]));

	setup();
	replace_program(CHURCH);
}
