//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/npc/wolf.c

inherit NPC;

void create()
{
	set_name("ħ��", ({ "magic wolf", "magic", "wolf"}) );
	set("race", "Ұ��");
	set("long", @TEXT
�㿴��һֻ������ɫƤë�ͼ���Ȯ�ݵĴ���, ������ħ��ʦ��ħ��
����Ļ���, ֻΪ�����������˶�ս��
TEXT
	);
	set("level", 5+random(2));

	add_temp("apply/damage", query("level"));

	setup();
}

void die()
{
	object ob;
	if( objectp( ob = query_temp("owner")) ) {
		this_object()->remove_guard(ob);
		this_object()->set_leader(0);
	}
	::die();
}
