//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���6") ;
	set ("long",
	"    ���������«������������ؽֵ��ϣ������������ƺ�æ��׬Ǯ\n") ;
	set ("exits", ([
	"north" : "/d/grid/rooms/5,10.grid",
	"east" : "/d/grid/rooms/6,11.grid",
	"west" : "/d/grid/rooms/6,9.grid",
	"south" : "/d/grid/rooms/7,10.grid",
	]) ) ;
}
