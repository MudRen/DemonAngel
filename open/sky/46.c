//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/46.c
// saveroom by pawlo @DA, Fri May 23 15:00:02 2003
#include <ansi.h>
inherit BARRACKS;

void create()
{
	set("short", "��Ӫ");
	set("long", @LONG
���߽�һ�������Ĵ��ţ�������ì��ʿ������ľկΧ�ɵľ���ǰվ�ţ�
����Կ���������ǰ��һ��ľ��������һ�Ų��棬����д���йشӾ�ļ����
���ڷ��������顣������Կ���һƬ�ٳ��������ž��͵ľ������ڲٳ���
Ʈ���š��̿˶�ʼҾ��Ӳ���ֻ��ս��ʱ����ս��ɱ�У�������ƽ�գ�Ҳ��
Ŭ��ά�ֹ����ΰ���Ҫ�����˷����������ǻ��ǻ��ղ�����ġ�
LONG
	);
	set("type", "barracks");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Fri May 23 14:51:27 2003",
  "pawlo",
  "Fri May 23 15:00:02 2003"
}));
	set("data", ({ /* sizeof() == 1 */
  __DIR__"npc/8"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"38",
]));

	setup();
	replace_program(BARRACKS);
}
