//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/51
// saveroom by pawlo    Sat May 24 18:01:24 2003

#include <ansi.h>
inherit TRAINYARD;
void create()
{
	set("short", "ѵ����");
	set("long", @TEXT
������һ������ź�ˮ���������ѵ����, ���Ĵ�������һ������
�Ĺ㳡, ����h�����ڳ��������ض�����, �������뵶��ײ�������ϴ���
, �㳡�߶�����һЩѵ�����ߺ�����װ��, �������������ǽ���ģ������
��վ�ڳ��߶��ų��ϵ���ָָ��㡣�����������ѵ��(train)���ܡ���
��(advance)�ȼ����鿴(list)���������ѵ���������(cost)��
TEXT
);
	set("type", "trainyard");
	set("refresh_data", ({ "pawlo", "Sat May 24 18:01:24 2003", "pawlo", "Sat May 24 18:01:24 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "down" : "/open/sky/37",
]));

	setup();
	replace_program(TRAINYARD);
}
