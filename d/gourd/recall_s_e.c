//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_s_e

#include <room.h>

inherit POST_OFFICE;

void create()
{
        set("short", "�ʾ�");
        set("long", @LONG
���߽�һ��С�ʾ�, �����ʲ�������һ�������Ա������ż�, ���Ǳ���
��߰��ż����벻ͬ�������С������������Ӧ��Ҳ����İ�, ������뿴
����û�������, ��������ҿ���û���������(search mailbox)��
LONG
        );
        set("exits", ([
                "west"  : __DIR__"recall_s_1"
        ]));
        setup();
}

