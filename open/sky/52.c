//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/52
// saveroom by pawlo    Sun May 25 20:59:06 2003

#include <ansi.h>
inherit POST_OFFICE;
void create()
{
	set("short", "�ʾ�");
	set("long", @TEXT
���߽�һ��С�ʾ�, �����ʲ�������һ�������Ա������ż�, ���Ǳ���
��߰��ż����벻ͬ�������С������������Ӧ��Ҳ����İ�, ������뿴
����û�������, ��������ҿ���û���������(search mailbox)��
TEXT
);
	set("type", "post_office");
	set("refresh_data", ({ "pawlo", "Sun May 25 20:59:06 2003", "pawlo", "Sun May 25 20:59:06 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/40",
]));

	setup();
	replace_program(POST_OFFICE);
}
