//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_w_1
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
�������˺�«�ǵ�����֡������������źܶ��������ĵ�ң����Ժ�
�మ������˶��������ˣ������Ҳ����������İ����ߣ������ڴ˵ض��
�Σ�˵�������ҵ���Ŀ�еĺö�������������һ�����ţ����������߾ͻ���
��㳡�ˡ�
LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_w_2",
                "east"  : __DIR__"gourd_recall",
        ]));
        setup();
}
 






