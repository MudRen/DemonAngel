//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/obj/npc/guard_1.c

inherit NPC;

void create()
{
	set_name("��������", ({ "guard" }) );
	set("dex", 5);
	set("str", 30);
	set("level", 4);

	set_skill("dodge", 3);

	set("long", "�װ˰˵Ļ���������\n");

	setup();
	carry_object("/d/obj/npc/wp/thin_sword")->wield();
}
