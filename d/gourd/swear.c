//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/swear.c

#include <room.h>

inherit SWEAR;

void create()
{
	set("short", "�����");
	set("long", @LONG
���, �����ĵĵط�...
���:
	swear <����>
����:
	adopt <����> as child        ��<����>�����������Ը��
	adopt <����> as parent       ��<����>���Ը�ⱻ��������Ը��

LONG
	);
	set("exits", ([
		"east" : "/d/gourd/2.c",
	]));
	setup();
	replace_program(SWEAR);
}
