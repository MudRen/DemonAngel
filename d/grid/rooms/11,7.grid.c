//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间3") ;
	set ("long",
	"讨生活。在你的南边有着非常著名的葫芦镇的飞马广场，以及著名的\n");
	set ("exits", ([
	"north" : "/d/grid/rooms/10,7.grid",
	"east" : "/d/grid/rooms/11,8.grid",
	"west" : "/d/grid/rooms/11,6.grid",
	]) ) ;
}
