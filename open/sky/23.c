//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/23
// saveroom by pawlo    Sat May 17 20:36:24 2003

#include <ansi.h>
inherit ARMORY;
void create()
{
	set("short", "������");
	set("long", @TEXT���߽�һ�ҹ���Ƥ������Ͳ��ϵĵ��̣��÷��������ڹ�̨�����һ��
�����߱�����߽�һ�����Ŀ��׷�������������м�λ������������һ����
����֦���ƺ����������ơ�
TEXT
);
	set("type", "armory");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/19",
]));

	setup();
	replace_program(ARMORY);
}
