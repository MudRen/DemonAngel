//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/special/death.c

#include <login.h>
inherit ROOM;

void create()
{
	set("short", "�ظ�");
	set("long", @LONG
���������߾ۼ�֮�أ��ж��������أ���....��ô�࣬���˰� ~~~
LONG
	);
	set("exits", ([
		"out" : START_ROOM
	]) );
	setup();
	replace_program(ROOM);
}
