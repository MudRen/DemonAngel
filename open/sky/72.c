//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/72.c
// saveroom by pawlo @DA, Mon May 26 16:08:31 2003
#include <ansi.h>
inherit TRAINYARD;

void create()
{
	set("short", "ѵ����");
	set("long", @LONG
������һ������ź�ˮ���������ѵ����, ���Ĵ�������һ������\\n�Ĺ㳡, ����\�������ڳ��������ض�����, �������뵶��ײ�������ϴ���\\n, �㳡�߶�����һЩѵ�����ߺ�����װ��, �������������ǽ���ģ������
��վ�ڳ��߶��ų��ϵ���ָָ��㡣�����������ѵ��(train)���ܡ���\\n��(advance)�ȼ����鿴(list)���������ѵ���������(cost)��
LONG
	);
	set("type", "trainyard");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 16:08:21 2003",
  "pawlo",
  "Mon May 26 16:08:31 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "up" : __DIR__"73",
  "down" : __DIR__"kingdom",
]));

	setup();
	replace_program(TRAINYARD);
}
