//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// A basic grid room, with non-grid exits.
// The shrubbery for the shrub quest is here.
// Mobydick@TMI-2, 11-12-92

#include <mudlib.h>

inherit ROOM ;

void create () {

	object shrubbery ;

	seteuid(getuid()) ;
	shrubbery = clone_object ("/d/grid/thin_sword") ;
	shrubbery->move(this_object()) ;
	set ("short", "���Է���9") ;
	set ("long",
	"��Զ������һ��ص������죬�����ڶ��������г��������ﲻ������\n") ;
	set ("exits", ([
	"south" : "/d/grid/rooms/8,3.grid",
	"north" : "/d/grid/rooms/6,3.grid",
	"east" : "/d/grid/rooms/7,4.grid",
	"west" : "/d/grid/rooms/7,2.grid",
	]) ) ;
}

void init() {
	add_action ("show_view", "view") ;
}

int show_view() {
	write (
"To the south you can see the city of Footown spread out along the north\n"+
"shore of the Bay of Wetness. A long sandy beach runs along the bay shore.\n"+
"This road leads north from Footown, and a second road leads west from\n"+
"Footown to the village of Smallville. The Flowing River runs into the\n"+
"bay from the northeast, flowing more or less parallel to this road. A\n"+
"small brook passes under the road to the north, and flows into the river\n"+
"soon thereafter. The brook comes down from some high mountains off to the\n"+
"west; you can see that there is a small valley between two spines of the\n"+
"mountains. To the east is a smaller hill, and on the near slope, east and\n"+
"a little south of here is a tall, dark tower. North of here you can see\n"+
"a small forest of oak and pine trees: the road detours around it to the\n"+
"east.\n") ;
	return 1 ;
}