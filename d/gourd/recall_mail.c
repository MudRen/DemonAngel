//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/mail.c

#include <room.h>

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
	set("exits", ([
		"north"	: __DIR__"recall_w_1.c"
	]));
	setup();
}
