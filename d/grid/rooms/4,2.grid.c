//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/grid/rooms/4,2.grid.c
// by bor @DA, 3/11 2003

inherit ROOM ;

void create () {
	set ("short", "����") ;
	set ("long", @LONG
�ö๷���ڴ�˯���ĵط���
LONG
	);
	set ("exits", ([
		"north" : "/d/grid/rooms/3,2.grid",		// ����������
		"east" : "/d/grid/rooms/4,3.grid",		// ����������
		"west" : "/d/grid/rooms/4,1.grid",		// ����������
		"south" : "/d/grid/rooms/5,2.grid",		// ����������
	]) ) ;
}
