//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/50
// saveroom by amgbell    Fri May 23 22:35:56 2003

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
	set("refresh_data", ({ "amgbell", "Fri May 23 22:35:56 2003", "amgbell", "Fri May 23 22:35:56 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/24",
]));

	setup();
	replace_program(ARMORY);
}
