//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/74
// saveroom by amgbell    Tue May 27 00:15:42 2003

#include <ansi.h>
inherit TAVERN;
void create()
{
	set("short", "�ù�");
	set("long", @TEXT
������һ��С�ùݣ�ר�Ź�����·���ÿ���ЪЪ���õģ�����ķ���װ
�εķǳ����ʣ����������˶����˺���������;���ۣ��㶼���������ﰲ
�ĵ������������������±��˴��ţ�������һ��������������صķ����
һ�Ե���һλ�൱�ɰ���Ů�̣����ڵ��Ÿ�λ����Ҫ���˽�����Ϣ��
TEXT
);
	set("type", "tavern");
	set("refresh_data", ({ "amgbell", "Tue May 27 00:15:42 2003", "amgbell", "Tue May 27 00:15:42 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/35",
]));

	setup();
	replace_program(TAVERN);
}
