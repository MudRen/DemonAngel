//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// swordsman_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("��ʿ���԰�", ({ "board" }) );
	set("location", "/d/snow/schoolhall");
	set("board_id", "swordsman_b");
	set("long",	"���ǹ���ʿ�����Լ��µ����԰塣\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
