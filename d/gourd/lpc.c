//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/lpc.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��ʽ���¡������");
	set("long", @LONG
�����ʽ�������������ɡ�
LONG
	);
	set("exits", ([
		"up" : "/d/gourd/gourd_recall.c",
		"down": "/d/gourd/1.c"
	]));
	setup();
	load_object("/obj/board/gourd_lpc");
}
