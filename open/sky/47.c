//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/47
// saveroom by pawlo    Fri May 23 17:49:53 2003

#include <ansi.h>
inherit BANK;
void create()
{
	set("short", "����");
	set("long", @TEXT
���߽���һ������, ��Ա�����ڹ񖟺�æµ��, ����������ľ�����\n�ݺݵĶ����㿴��һ�����΢Ц�İ���Ա���˹���, ����Ϊ�����������
���������Ĵ���̲�˿�������, ���������Ǯ��Ȼ���԰�ȫ, ����ȴû��
Ϣ��������������(deposit)/��(withdraw)���ת��(transfer)��
TEXT
);
	set("type", "bank");
	set("refresh_data", ({ "pawlo", "Fri May 23 17:49:53 2003", "pawlo", "Fri May 23 17:49:53 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/40",
]));

	setup();
	replace_program(BANK);
}
