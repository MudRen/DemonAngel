//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间7") ;
	set ("long",
	"服驱车奔向结婚礼堂。往南边可以到达全镇最著名的飞马广场，西边\n") ;
	set ("exits", ([
	"east" : "/d/grid/rooms/6,3.grid",
	"south" : "/d/grid/rooms/7,2.grid",
	]) ) ;
}
