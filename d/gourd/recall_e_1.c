//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_e_1

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
�������˺�«�ǵĶ���֡�������������ð���߾ۼ��������Ҫ��Щ
��ĵط����������£����������ٴ�פ����һЩ��ʱ�䣬Ӧ�ÿ����кܴ��
�ջ�������ԶԶ����ȥ���ǳ���Ķ��ņ������������߾ͻ�����㳡�ˡ�
LONG
        );
        set("exits", ([
                "west" : __DIR__"gourd_recall",
                "east"  : __DIR__"recall_e_2",
        ]));
        setup();
}
 




