//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_n_e

#include <room.h>

inherit WEDDING;

void create()
{
        set("short", "����");
        set("long", @LONG
��«����ר�����������õ����½�Ϊ���޵ĵط�

ָ����: marry <�з�> with <Ů��>
�ش����� answer yes

LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_n_1",
        ]));
        setup();
        replace_program(WEDDING);
}



