//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/3.c

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
		"south" : "/d/gourd/2.c",
		"east" : "/d/gourd/gourd-gift_shop.c",
		"west"	: "/d/gourd/pet.c",
		"north" : "/d/gourd/4.c"
	]));
	set("objects", ([
		__DIR__"npc/mob1" : 1,
	]) );

	setup();
	replace_program(ROOM);
}
