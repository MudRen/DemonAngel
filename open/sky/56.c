//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/56
// saveroom by pawlo    Mon May 26 10:18:46 2003

#include <ansi.h>
inherit GATE;
void create()
{
	set("short", "�ؿ�");
	set("long", @TEXT
������һ���ؿ���·���Ը���\��һ������ڣ�·���뻹���ž�������\\n��ǹִ��������������վ�Լ�����ˣ������������չ�·˰��
TEXT
);
	set("type", "gate");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:18:46 2003", "pawlo", "Mon May 26 10:18:46 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/55",
]));

	setup();
	replace_program(GATE);
}
