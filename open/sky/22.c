//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/22
// saveroom by pawlo    Sat May 17 20:36:18 2003

#include <ansi.h>
inherit SMITH;
void create()
{
	set("short", "����");
	set("long", @TEXT���߽�һ�����̣����ȵ��ȷ����������������������Ĺ�����������
�������е��������䣬�е����������������������ø���ͣ����ߵĵ��ϣ�
���м�����������Χ��һ�����ԣ���̯�����ϵ�һ�Ŵ����ͼ�����š�
TEXT
);
	set("type", "smith");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/19",
]));

	setup();
	replace_program(SMITH);
}
