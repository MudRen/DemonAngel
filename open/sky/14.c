//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/14.c
// saveroom by pawlo    Wed May 14 21:43:39 2003

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�շ��� - ��ʹ�� set_short ���༭����");
	set("long", "����һ��ʲôҲû�еĿշ��䣬������ set_long ���༭����������\n");
	set("type", "normal");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/13",
]));

	setup();
	replace_program(ROOM);
}
