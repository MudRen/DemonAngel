//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/wiz/hall1.c

inherit ROOM;

void create()
{
	set("short", "��ʦ������");
	set("long", @LONG
��������ʦ�������۵ĵط��������ʦ��Ҫ����Ļ���Ҳ����ѡ����
����У���������ʦ����ҡ�
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "north" : "/d/wiz/jobroom",
  "east" : "/d/wiz/entrance",
]));
	set("no_clean_up", 0);

	setup();
	call_other("/obj/board/wizard_b", "???");
	replace_program(ROOM);
}
