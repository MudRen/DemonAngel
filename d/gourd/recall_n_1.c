//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_n_1

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����һ����«�ǵı���֡���·�������������ÿͣ��������ǳ���
����ҵ���ģ���������һ��С���ڽ���������пղ���������䣬�����߿�
�Դ��¿������ŵ���ΰ���������ϱ��߾�������㳡�ˡ�
LONG
        );
        set("exits", ([
                "south" : __DIR__"gourd_recall",
                "north" : __DIR__"recall_n_2",
                "east"  : __DIR__"recall_n_e",
                "west"  : __DIR__"recall_n_w",
        ]));
        setup();
}
 


