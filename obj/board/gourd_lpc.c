//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// rg_board.c
#include <login.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("��ʽ���԰�", ({ "board" }) );
	set("location", "/d/gourd/recall_lpc.c");
	set("board_id", "gourd_lpc_board");
	setup();
	set("capacity", 150);
	replace_program(BULLETIN_BOARD);
}
