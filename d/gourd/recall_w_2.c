//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_w_2
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
你来到了葫芦城的西大街。在这个地方有着许多大陆上的不同部落商店
，所以这里有很多平常看不到的东西，喜欢的话可以看一下并且询问看看，
应该能得到想要的公道价码，西边是葫芦城的西城门，而往东边走就回中央
广场了。
LONG
        );
        set("exits", ([
                "west" : __DIR__"recall_wdoor",
                "east"  : __DIR__"recall_w_1",
        ]));
        setup();
}
 





