//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_n_2

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "�����");
        set("long", @LONG
����һ����«�ǵı���֡����Կ����и��ֲ�ͬ��������������˸�
����һ�ֶ�Ŀһ�µĸо�����Χ���˶�ʮ�����磬�������Դ˵طǳ���Ϥ��
���Ҫ���˽�˵���ʷ�������ʣ������ǳ���ı����ϱ�ͨ�������롣
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_n_1",
                "north"  : __DIR__"recall_n_3",
                "west" : __DIR__"recall_n_2w",
                "east" : __DIR__"recall_n_2e",
        ]));
        set("objects", ([
                __DIR__"npc/mob1" : 1,
        ]) );
        setup();
}
 


