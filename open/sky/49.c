//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/49
// saveroom by amgbell    Fri May 23 22:35:47 2003

#include <ansi.h>
inherit SMITH;
void create()
{
	set("short", "����");
	set("long", @TEXT
���߽�һ�����̣����ȵ��ȷ����������������������Ĺ�����������
�������е��������䣬�е����������������������ø���ͣ����ߵĵ��ϣ�
���м�����������Χ��һ�����ԣ���̯�����ϵ�һ�Ŵ����ͼ�����š�
TEXT
);
	set("type", "smith");
	set("refresh_data", ({ "amgbell", "Fri May 23 22:35:47 2003", "amgbell", "Fri May 23 22:35:47 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/24",
]));

	setup();
	replace_program(SMITH);
}
