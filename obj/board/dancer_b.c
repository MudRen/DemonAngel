//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// dancer_b.c

inherit BULLETIN_BOARD;

void create()
{
	set("board_id", "dancer_b");
	set("location", "/d/latemoon/latemoon1" );
	setup();
	set_name("�廨����", ({ "mirror" }) );
	set("long",
		"����һ����һ���˸ߵľ��������Ź��ٲ����ŵĺ�ľ�������滹׺��\n"
		"һЩ�ղ������ʻ����㿴�ž��е��Լ�������վ�ڻ���֮�У�����ׯ��\n"
		"Ů��ϲ�����Լ�������д��ֽ�����ھ����ϡ�\n");
	set("capacity", 30);
	replace_program(BULLETIN_BOARD);
}
