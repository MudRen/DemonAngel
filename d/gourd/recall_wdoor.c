//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_wdoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǻ�«�ǵ������š����ſڿ��Կ�������ȫ�׿��׵�ʿ����Ѳ�ӣ�
���������Ҫ����������Ҫ��˼���У�����������������ʮ��æµ���о�
������Ϊ���٣������ſ�����ʮ�ֵĸߴ���ΰ������������η��
LONG
        );
        set("exits", ([
                "east"  : __DIR__"recall_w_2",
        ]));
        setup();
}
 






