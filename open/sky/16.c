//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/16
// saveroom by pawlo    Wed May 14 21:44:10 2003

#include <ansi.h>
inherit ARMORY;
void create()
{
	set("short", "������");
	set("long", @TEXT
���߽�һ�ҹ���Ƥ������Ͳ��ϵĵ��̣��÷��������ڹ�̨�����һ��
�����߱�����߽�һ�����Ŀ��׷�������������м�λ������������һ����
����֦���ƺ����������ơ�
TEXT
	);
	set("type", "armory");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/open/sky/3",
]));

	setup();
	replace_program(ARMORY);
}
