//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/special/no_reborn_room.c
// by bor @DA, 3/11 2003

inherit ROOM;

void create()
{
	set("short","������ʧ������");
	set("long",@TEXT	
����ס��һ�Ʋ��������Ŀ��� .... ��ࡺ�� ~~~~
TEXT
	);
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}
