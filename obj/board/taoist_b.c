//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// taoist_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("éɽ�����԰�", ({ "board" }) );
	set("location", "/d/temple/temple1");
	set("board_id", "taoist_b");
	set("long",
		"���ǹ�éɽ�ɵ������Լ��µ����԰塣\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
