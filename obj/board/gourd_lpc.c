//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// rg_board.c
#include <login.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("程式留言板", ({ "board" }) );
	set("location", "/d/gourd/recall_lpc.c");
	set("board_id", "gourd_lpc_board");
	setup();
	set("capacity", 150);
	replace_program(BULLETIN_BOARD);
}
