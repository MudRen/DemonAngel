//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/73
// saveroom by pawlo    Mon May 26 16:08:31 2003

#include <ansi.h>
inherit MAGIC_TOWER;
void create()
{
	set("short", "������ϰӪ");
	set("long", @TEXT
������һ��������������ϰ��, ��ϰ�ҵ�������һ�ų�����, ��������
ֱ���ݶ������, ���ϰ��˻�����ʽ��ַ��ŵ��鼮, �󲿷����й�ħ����,
������, ����Է�����(list)��ʲô�ʺ���Ŀǰ�̶ȵķ�����ѧ, Ҳ���Ծ�
��������ϰ(study)������
TEXT
);
	set("type", "magic_tower");
	set("refresh_data", ({ "pawlo", "Mon May 26 16:08:31 2003", "pawlo", "Mon May 26 16:08:31 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "down" : "/open/sky/72",
]));

	setup();
	replace_program(MAGIC_TOWER);
}
