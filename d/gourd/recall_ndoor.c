//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_ndoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǻ�«�ǵı����š��������Ǵ�����Ϣ����Ⱥ���ƶ������Ҹ�����
�弸�����ܼ���������е���Ϊ��Ȥ��Ӧ��Ҳֻ���ڴ˵��ܼ������ʢ����
���Ƕ����޸��ң���Ҳ������ѵ�����صĳ������������㲻���зǷ�֮�롣
LONG
        );
        set("exits", ([
                "south"  : __DIR__"recall_n_3",
        ]));
        setup();
}
 








