//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/2.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�ֵ�");
	set("long", @LONG
һ��Ľֵ� ...
LONG
	);
	set("exits", ([
		"south" : "/d/gourd/gourd_recall.c",
		"west" : "/d/gourd/swear.c",
		"east" : "/d/gourd/wedding.c",
		"north" : "/d/gourd/3.c",
	]));
	setup();
	replace_program(ROOM);
}
