//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/city/recall_ndoor
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "北城门");
        set("long", @LONG
这里是葫芦城的北城门。到处都是川流不息的人群在移动，而且各种种
族几乎都能见到，令你感到极为有趣，应该也只有在此地能见到如此盛况，
人们都毫无隔阂，你也见到了训练有素的城门守卫，让你不敢有非法之想。
LONG
        );
        set("exits", ([
                "south"  : __DIR__"recall_n_3",
        ]));
        setup();
}
 








