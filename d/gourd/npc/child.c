//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// child.c

inherit NPC;

void create()
{
	set_name("С��Ů", ({ "girl" }) );
	set("int", 3);
	set("dex", 2);
	set("con", 20);
	set("level", 1);

	set_skill("dodge", 3);

	set("long",
		"���ʮ�塢�����С������ǡ��������ˣ���������Ȼ���Ŵֲ�\n"
		"�·�����ȴʮ���Ǹ��������ӣ�һ˫ˮ�����Ĵ��۾���µµ��ת\n"
		"�ţ�����ʱ�����㿴��ʹ�㲻��������Щ������\n");

	setup();
}
