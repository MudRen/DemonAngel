//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/wedding.c

#include <room.h>

inherit WEDDING;

void create()
{
	set("short", "����");
	set("long", @LONG
���ĵط�� ~~~

ָ����: marry <�з�> with <Ů��>
�ش����� answer yes

LONG
	);
	set("exits", ([
		"west" : "/d/gourd/2.c",
	]));
	setup();
	replace_program(WEDDING);
}
