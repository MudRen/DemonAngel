//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// rg_board.c
#include <login.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("BUG���԰�", ({ "bug board","board","bug" }) );
	set("location", "/d/gourd/bug_board.c");
	set("board_id", "gourd_bug_board");
	setup();
	set("capacity", 150);
	replace_program(BULLETIN_BOARD);
}
