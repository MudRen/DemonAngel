//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/special/relax.c
// by bor @DA, 2/22/2003

inherit ROOM;

void create()
{
	set("short","��Ϣ��");
	set("long",@TEXT
������Ϣ�ĵط����������ǲ�Ҫ�Ҷ��̵�ࡡ�
TEXT
	);
	setup();
	replace_program(ROOM);
}

