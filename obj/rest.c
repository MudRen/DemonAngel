//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/rest.c

inherit ROOM;

void create()
{
	set("short", "�ͷ�");
	set("long", @TEXT
����һ���徻�Ŀͷ�, ���ھ�ֻ��һ��һ��, ������һ��С��, ϸϸ��
����͵����Ļ��㲻ʱƮ����������������ר���ĸ��˿ռ�, �����������
���ĵ�ЪϢ, �����Ҫ�뿪, ��ǵð��Լ��Ķ�������, ��Ȼ������������
����ʱ������Ǽ��е������ҡ�
TEXT);

	set("type","normal");
	set("no_fight", 1);
	set("no_quit", 1);
	set("no_recall", 1);
	set("no_teleport", 1);
	setup();
	replace_program(ROOM);
}
