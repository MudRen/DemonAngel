//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/kingdom.c
// saveroom by amgbell @DA, Wed May 28 19:31:37 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����ǹ�������Ҫ�ĵط���Ҳ�ǹ��ҵľ���������ƽʱ�������
����̸�۹�����Ҫ���ߵ���ѳ����������Ĵ�������ϵ�Ź����ܲ�
�ܴ��ڣ���ν���ڹ��ڣ�����������ϣ�������ܺúñ������
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sun Mar 09 20:23:57 2003",
  "amgbell",
  "Wed May 28 19:31:37 2003"
}));
	set("kingdom_id", "sky");
	set("objects", ([ /* sizeof() == 4 */
  __DIR__"npc/16" : 1,
  __DIR__"npc/18" : 1,
  __DIR__"npc/19" : 1,
  __DIR__"npc/17" : 1,
]));
	set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"26",
  "west" : __DIR__"18",
  "east" : __DIR__"1",
  "up" : __DIR__"72",
]));
	set("no_delete", 1);

	setup();
	replace_program(ROOM);
}
