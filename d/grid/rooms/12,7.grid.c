//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���4") ;
	set ("long",
	"ȺӢ��ݣ��Ǳ߾ۼ����൱������������ʿ���ڶ����߲�Զ����ʽ��\n") ;
	set ("exits", ([
	"east" : "/d/grid/rooms/12,8.grid",
	"west" : "/d/grid/rooms/12,6.grid",
	]) ) ;
}
