//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/wiz/jobroom.c

inherit ROOM;

void create()
{
	set("short", "�������ȼ���");
	set("long", @LONG
��������ʦ�Ǳ����Լ��������ȵļ��ң�ͬʱҲ�Ǵ���ʦץ����
�ĸ��ݣ�������й���������ó��������������Ĺ������ȣ����̫
��û�п�����Ĺ������ȱ��棬����ʦ�ǻ���Ϊ��û������ָ�ɹ�����
��Ҫ������Ȼ����Ҳ�п��ܻᱻ������Ѿ�������ʦ�Ĺ�����������
����֡�
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "south" : "/d/wiz/hall1",
]));
	set("no_clean_up", 0);

	setup();
	call_other("/obj/board/wizard_j", "???");
	replace_program(ROOM);
}
