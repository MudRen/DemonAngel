//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/36.c
// saveroom by pawlo @DA, Mon May 26 10:22:29 2003
#include <ansi.h>
inherit MAGIC_TOWER;

void create()
{
	set("short", "������ϰӪ");
	set("long", @LONG
����һ�䷨����ϰӪ�������ʹ�� list ���鿴����ѧϰ�ķ���, �Լ�ʹ�� study ��ѧϰ��
LONG
	);
	set("type", "magic_tower");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Thu May 22 14:46:33 2003",
  "pawlo",
  "Mon May 26 10:22:29 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "down" : __DIR__"kingdom",
]));

	setup();
	replace_program(MAGIC_TOWER);
}
