//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/recall_lpc.c

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
		"up" : __DIR__"gourd_recall.c",
		"down": __DIR__"recall_pray.c",
		"east": __DIR__"bug_board.c"
	]));
	setup();
	load_object("/obj/board/gourd_lpc");
}
