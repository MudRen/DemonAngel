//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

// /d/grid/rooms/10,13.grid

inherit ROOM ;

void create () {
	set ("short", "���Է���") ;
	set ("long", @LONG
������������, û�¶��ᷢ����
LONG
	);
	set ("exits", ([
	"north" : "/d/grid/rooms/9,13.grid",		// ����������
	"east" : "/d/grid/rooms/10,14.grid",		// ����������
	"west" : "/d/grid/rooms/10,12.grid",		// ����������
	"south" : "/d/grid/rooms/11,13.grid",		// ����������
	"down" : "/d/gourd/gourd_recall"		// ��ʵ����
	]) ) ;
}
