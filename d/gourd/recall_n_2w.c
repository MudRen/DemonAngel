//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_n_2w.c

#include <room.h>

inherit PET_SHOP;

void create()
{
        set("short", "����ר�ŵ�");
        set("long", @LONG
�ö�����ṩ���㹺����������� list ��һ����ʲô������Թ���(buy),
Ҳ�������� take ���Լ��ĳ��������...
LONG
        );
        set("exits", ([
                "east" : __DIR__"recall_n_2",
        ]));
        setup();
        replace_program(PET_SHOP);
}

