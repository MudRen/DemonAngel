//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���7") ;
	set ("long",
	"���������������á����ϱ߿��Ե���ȫ���������ķ���㳡������\n") ;
	set ("exits", ([
	"east" : "/d/grid/rooms/6,3.grid",
	"south" : "/d/grid/rooms/7,2.grid",
	]) ) ;
}
