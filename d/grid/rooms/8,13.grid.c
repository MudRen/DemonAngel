//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间10") ;
	set ("long",
	"果你是一个精明的商人，喊价是一个重要的磨练。\n") ;
	set ("exits", ([
	"east" : "/d/grid/rooms/8,14.grid",
	"south" : "/d/grid/rooms/9,13.grid",
	"west" : "/d/grid/rooms/8,12.grid",
	"north" : "/d/grid/rooms/7,13.grid",
	]) ) ;
}
