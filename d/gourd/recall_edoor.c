//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_edoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǻ�«�ǵĶ����š������ų��Ų������������ΰ�ĳ���Ҫ������
ʱ�����Ǻã���Χ���ż��಻ͬ���ҵ���������ǣ�������½����֮�ǵ���
��Ӧ�ò��������������Ÿ���������װ�õ�ʿ����Ѳ�ӣ�ʹ�˲����������
��
LONG
        );
        set("exits", ([
                "west"  : __DIR__"recall_e_2",
        ]));
        setup();
}


