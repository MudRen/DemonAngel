//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_e_1

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
你来到了葫芦城的东大街。这里有着许多的冒险者聚集，如果想要听些
别的地方的奇闻逸事，不妨可以再此驻留久一些的时间，应该可以有很大的
收获，往东边远远望过去就是城里的东门啰，而往西边走就回中央广场了。
LONG
        );
        set("exits", ([
                "west" : __DIR__"gourd_recall",
                "east"  : __DIR__"recall_e_2",
        ]));
        setup();
}
 




