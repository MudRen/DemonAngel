//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// rg_board.c
#include <login.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("���԰�", ({ "board" }) );
	set("location", START_ROOM);
	set("board_id", "rg_board");
	setup();
	set("capacity", 150);
	replace_program(BULLETIN_BOARD);
}
