//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/special/recall_shop.c
// by bor @DA,

inherit ROOM;

void create()
{
	set("short","�̵�Ĵ�����");
	set("long",@TEXT	
���ٻ�Ʒ���ѷ��ڴ˵�, �벻Ҫ������� !!
TEXT
	);
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}
