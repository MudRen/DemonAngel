//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���2") ;
	set ("long",
	"    �����Ǻ�«��������н�֮һ����㳡��������������Ͷ�\n");
	set ("exits", ([
	"east" : "/d/grid/rooms/11,4.grid",
	"west" : "/d/grid/rooms/11,2.grid",
	]) ) ;
}
