//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/test/kingdom.c
// saveroom by testlife @ Sat Mar 08 22:54:05 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����ǹ�������Ҫ�ĵط���Ҳ�ǹ��ҵľ���������ƽʱ�������
����̸�۹�����Ҫ���ߵ���ѳ����������Ĵ�������ϵ�Ź����ܲ�
�ܴ��ڣ���ν���ڹ��ڣ�����������ϣ�������ܺúñ������
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "testlife",
  "Sat Mar 08 22:54:01 2003",
  "testlife",
  "Sat Mar 08 22:54:05 2003"
}));
	set("kingdom_id", "test");
	set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"1",
]));
	set("no_delete", 1);

	setup();
	replace_program(ROOM);
}
