//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/1.c

#include <room.h>

inherit PRAY;

void create()
{
	set("short", "ʱ����");
	set("long", @LONG
�ҷɰ� ~~~
LONG
	);
	set("exits", ([
		"up" : "/d/gourd/lpc.c",
		"west" : "/d/gourd/ship_port.c"
	]));
	setup();
	load_object("/obj/board/gourd_lpc");
}
