//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_s_1

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
�������˺�«�ǵ��ϴ�֡���·�������������������������Ѿ��ǳ�
����ص������ˣ����������Ҫ��ʩ�����ڴˣ���˿����ƺ�ƽ���ޱȣ�
���ϱ߿��Դ��¿������ŵ����ӆ������������߾ͻ�����㳡�ˡ�
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_s_2",
                "north" : __DIR__"gourd_recall",
                "east"  : __DIR__"recall_s_e",
                "west"  : __DIR__"recall_s_w",
        ]));
        setup();
}
 



