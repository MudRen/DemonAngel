//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/pet.c

#include <room.h>

inherit PET_SHOP;

void create()
{
	set("short", "����ר�ŵ�");
	set("long", @LONG
�ö�����ṩ���㹺��
LONG
	);
	set("exits", ([
		"east" : "/d/gourd/3.c",
	]));
	setup();
	replace_program(PET_SHOP);
}
