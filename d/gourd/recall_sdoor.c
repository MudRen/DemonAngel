//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/recall_sdoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ϳ���");
        set("long", @LONG
�����Ǻ�«�ǵ��ϳ��š��Ӹ�����ͬ�ط������˼�ֱ�����ﲻ��������
���̾Ϊ��ֹ�����ﷱ�������ӿɼ�һ�࣬���ҵ����ɼ���װ���õ�������
Ѳ�ߣ���Ҫ���ҵ���ͷ���ܶ�Ҫ���������˸е���Ϊ��ȫ��
LONG
        );
        set("exits", ([
                "north"  : __DIR__"recall_s_2",
        ]));
        setup();
}


