//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// wizard_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("��ʦ���԰�", ({ "board" }) );
	set("location", "/d/wiz/hall1");
	set("board_id", "wizard_b");
	set("long",
		"����һ���������Լ��µ����԰塣\n" );
	setup();
	set("capacity", 50);
	replace_program(BULLETIN_BOARD);
}
