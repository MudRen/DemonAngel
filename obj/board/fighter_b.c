//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// fighter_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("�������԰�", ({ "board" }) );
	set("location", CLASS_D("fighter") + "/guildhall");
	set("board_id", "fighter_b");
	set("long",	"���ǹ������������Լ��µ����԰塣\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
