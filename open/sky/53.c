//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/53
// saveroom by pawlo    Mon May 26 10:15:41 2003

#include <ansi.h>
inherit TAVERN;
void create()
{
	set("short", "�ù�");
	set("long", @TEXT
������һ��С�ùݣ�ר�Ź�����·���ÿ���ЪЪ���õģ�����ķ���װ\\n�εķǳ����ʣ����������˶����˺���������;���ۣ��㶼���������ﰲ
�ĵ������������������±��˴��ţ�������һ��������������صķ����
һ�Ե���һλ�൱�ɰ���Ů�̣����ڵ��Ÿ�λ����Ҫ���˽�����Ϣ��
TEXT
);
	set("type", "tavern");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:15:41 2003", "pawlo", "Mon May 26 10:15:41 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/41",
]));

	setup();
	replace_program(TAVERN);
}
