//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���10") ;
	set ("long",
	"������һ�����������ˣ�������һ����Ҫ��ĥ����\n") ;
	set ("exits", ([
	"east" : "/d/grid/rooms/8,14.grid",
	"south" : "/d/grid/rooms/9,13.grid",
	"west" : "/d/grid/rooms/8,12.grid",
	"north" : "/d/grid/rooms/7,13.grid",
	]) ) ;
}
