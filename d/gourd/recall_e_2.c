//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_e_2
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
�������˺�«�ǵĶ���֡��о��������������ʮ�����֣����źܶ��
�����������лν�̸���ܶ�ĵ�һ�����Ϻ����Ŷ��������������������Գ�
��������������ţ������߹�ȥ���Ǻ�«�ǵĶ��ţ����������߾ͻ������
���ˡ�
LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_e_1",
                "east"  : __DIR__"recall_edoor",
        ]));
        setup();
}
 




