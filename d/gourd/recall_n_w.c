//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_n_w.c

#include <room.h>

inherit SWEAR;

void create()
{
        set("short", "������");
        set("long", @LONG
��«����ר�����˽�������ĵط�

���:
        swear <����>
����:
        adopt <����> as child        ��<����>�����������Ը��
        adopt <����> as parent       ��<����>���Ը�ⱻ��������Ը��

LONG);
        set("exits", ([
                "east" : __DIR__"recall_n_1",
        ]));
        setup();
        replace_program(SWEAR);
}


