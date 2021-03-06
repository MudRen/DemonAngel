//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/gourd_recall.c

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "中央广场");
        set("long", @LONG
这是一个葫芦城的中央广场。你可以在这边休息一下(check_in)，目前
提供着免费的服务，东西南北各都有一条通往四个城门的道路，如果有空不
妨去逛逛，在这里有着各地的最新货物和最多的人潮，可以说是冒险者的天
堂。
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
        // 判定你身上的钱，暂时不用
//      if(!me->can_afford(50)) return notify_fail("你身上的钱不足，没办法让你休息。\n");
        ob = new("/d/special/relax.c");
        ob->set("exits/out", "/d/gourd/gourd_recall.c");
	message_vision("QK女招待员引领$N到房间内。\n", me);
        me->move(ob);
        return 1;
}
