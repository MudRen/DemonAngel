//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_s_2
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
�������˺�«�ǵ��ϴ�֡���·�������źܶ�����⽨��������е�ʮ
�ֵ����棬����Ҳ�������˺��񲻶��ˣ������Ų������ο���ˣ�ĺõط�
�����ϱ߿��������«�ǵ����ŵ�ģ�������������߾ͻ�����㳡�ˡ�
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_sdoor",
                "north"  : __DIR__"recall_s_1",
        ]));
        setup();
}
 




