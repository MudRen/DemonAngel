//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_w_2
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
�������˺�«�ǵ�����֡�������ط���������½�ϵĲ�ͬ�����̵�
�����������кܶ�ƽ���������Ķ�����ϲ���Ļ����Կ�һ�²���ѯ�ʿ�����
Ӧ���ܵõ���Ҫ�Ĺ������룬�����Ǻ�«�ǵ������ţ����������߾ͻ�����
�㳡�ˡ�
LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_wdoor",
                "east"  : __DIR__"recall_w_1",
        ]));
        setup();
}
 





