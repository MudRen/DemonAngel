//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/city/gourd_recall.c

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "����㳡");
        set("long", @LONG
����һ����«�ǵ�����㳡��������������Ϣһ��(check_in)��Ŀǰ
�ṩ����ѵķ��񣬶����ϱ�������һ��ͨ���ĸ����ŵĵ�·������пղ�
��ȥ��䣬���������Ÿ��ص����»���������˳�������˵��ð���ߵ���
�á�
LONG
        );
        set("exits", ([
                "south" : __DIR__"recall_s_1",
                "east"  : __DIR__"recall_e_1",
                "west"  : __DIR__"recall_w_1",
                "north" : __DIR__"recall_n_1",
                "down"  : __DIR__"recall_lpc",
//		"up" : "/d/grid/rooms/3,2.grid",
        ]));
        set("objects", ([
                __DIR__"npc/child" : 1,
        ]) );
        setup();
        load_object("/obj/board/gourd_recall");
}

void init()
{
        add_action("do_relax", "check_in");
}

private int do_relax(string arg)
{
        object me = this_player(), ob;

        seteuid(getuid(me));
        if( !userp(me) ) return 0;
        // �ж������ϵ�Ǯ����ʱ����
//      if(!me->can_afford(50)) return notify_fail("�����ϵ�Ǯ���㣬û�취������Ϣ��\n");
        ob = new("/d/special/relax.c");
        ob->set("exits/out", "/d/gourd/gourd_recall.c");
	message_vision("QKŮ�д�Ա����$N�������ڡ�\n", me);
        me->move(ob);
        return 1;
}
