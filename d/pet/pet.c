//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/pet/pet.c
// by bor @DA, 3/11 2003

inherit NPC;

#include <ansi.h>
#include <pet.h>

void create()
{
	set_name("����", ({"bad dragon", "dragon", "bad"}));
	set("race", "Ұ��");
	set("level", 3);
	set("limbs", ({ "ͷ��", "����", "ǰצ", "����", "β��" }) );
	set("verbs", ({ "bite"}));
	set("unit", "ֻ");
	set("value", (: query("level")*query("level")*3000 :));

//	set("owner", "bor");

	set_temp("pet/damage", 2);
	set_temp("pet/armor", 2);

	set_temp("pet/file", base_name(this_object()) );

	set_temp("pet/kee", query("level")*10+random(30) );	// �趨"��", �������� charge ��, Ԥ��һ��
	set_temp("apply/kee", query_temp("pet/kee") );

	setup();
}

void init()
{
	add_action("do_mount", "mount");
	add_action("do_feed", "feed");
}

int is_pet() { return 1; }