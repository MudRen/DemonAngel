//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/bug_board.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "BUG�ر���");
	set("long", @LONG
�� MUDLIB �� BUG, ���ڴ˷��� ~~
LONG
	);
	set("exits", ([
		"west" : __DIR__"recall_lpc.c",
	]));
	setup();
	load_object("/obj/board/gourd_bug");
}
