//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/grid/rooms/1,2.grid.c
// by bor @DA, 3/11 2003

inherit ROOM;

void create ()
{
	object ob;

	seteuid(getuid()) ;
	ob = clone_object ("/d/grid/thin_sword") ;
	ob->move(this_object()) ;
	set ("short", "������") ;
	set ("long", @TEXT
���һ�������
TEXT
);
	set ("exits", ([
	"south" : "/d/grid/rooms/2,2.grid",
	"north" : "/d/grid/rooms/0,2.grid",
	"east" : "/d/grid/rooms/1,3.grid",
	"west" : "/d/grid/rooms/1,1.grid",
	]) ) ;
}
