//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "���Է���12") ;
	set ("long",
	"�¿�Ļ�����ſڻ��м������ʵĻ���������ȥ���̼Һ��۵�������\n") ;
	set ("exits", ([
	"north" : "/d/grid/rooms/8,14.grid",
	"west" : "/d/grid/rooms/9,13.grid",
	]) ) ;
}
