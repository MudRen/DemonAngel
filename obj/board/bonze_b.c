//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// bonze_b.c

inherit BULLETIN_BOARD;

void create()
{
	set_name("Ե����", ({ "wheel" }) );
	set("location", "/d/sanyen/temple" );
	set("board_id", "bonze_b");
	set("long",
		"����һ����ͭ���ɵķ��֣���������߲���ͭ�̺ۼ����Կ�����������Ѿ�\n"
		"�൱��Զ�ˣ�Ե�����Ա߷���һ�����ӹ�����ɮ�˻�������ԡ�\n" );
	setup();
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
