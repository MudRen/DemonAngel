//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : KINGDOM_DIR+id+/data/sky15
// saveroom by pawlo    Wed May 14 21:43:59 2003

#include <ansi.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("���԰�", ({ "board" }) );
	set("location", "/open/sky/15");
	set("board_id", "sky15");
	setup();
	set("capacity", 70);
	replace_program(BULLETIN_BOARD);
}