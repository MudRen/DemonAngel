//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���3") ;
	set ("long",
	"�����������ϱ����ŷǳ������ĺ�«��ķ���㳡���Լ�������\n");
	set ("exits", ([
	"north" : "/d/grid/rooms/10,7.grid",
	"east" : "/d/grid/rooms/11,8.grid",
	"west" : "/d/grid/rooms/11,6.grid",
	]) ) ;
}
