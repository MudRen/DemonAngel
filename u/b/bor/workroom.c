//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /u/b/bor/workroom.c

#include <ansi.h>
#include <login.h>

inherit ROOM;
void create()
{
	set("short", "[1;36mСˮѼ�ĳ���������[2;37;0m");
	set("long", @LONG
���������ҡ�
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "out" : START_ROOM
]));
	setup();
	load_object("/obj/board/bor_board");
}
