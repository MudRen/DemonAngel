//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h> 

inherit ROOM ;

void create () {
	set ("short", "���Է���5") ;
	set ("long",
	"������Ʒ���ϱ�������г����Ǳ�Ӧ�ÿ����ҵ�����Ҫ�Ķ�����\n") ;
	set ("exits", ([
	"north" : "/d/grid/rooms/11,8.grid",
	"east" : "/d/grid/rooms/12,9.grid",
	"west" : "/d/grid/rooms/12,7.grid",
	"south" : "/d/grid/rooms/13,8.grid"
	]) ) ;
}
