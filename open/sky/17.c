//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/17
// saveroom by pawlo    Wed May 14 22:28:34 2003

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
  "south" : "/open/sky/4",
]));

	setup();
	replace_program(SMITH);
}
