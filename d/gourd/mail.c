//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/mail.c

#include <room.h>

inherit POST_OFFICE;

void create()
{
	set("short", "�ʾ�");
	set("long", @LONG
�����õġ�
LONG
	);
	set("exits", ([
		"east"	: "/d/gourd/gourd_recall.c"
	]));
	setup();
}
