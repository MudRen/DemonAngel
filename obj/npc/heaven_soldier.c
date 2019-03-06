//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// heaven_soldier.c

#include <ansi.h>

inherit NPC;

void create()
{
	string *order = ({"��", "��", "��", "��", "��", "��", "��", "��", "��", "��"});

	set_name("��" + (order[random(10)]) + "���", ({ "heaven soldier", "soldier" }) );
	set("long", "����һλ���������ػ���ר�ŵ��λ���֮��\n");
	set("attitude", "friendly");

	set("max_gin", 1000);
	set("max_kee", 1000);
	set("max_sen", 1000);

	set("max_atman", 100);
	set("atman", 100);
	set("max_mana", 100);
	set("mana", 100);

	set("str", 40);
	set("cor", 30);
	set("cps", 25);

	set("combat_exp", 100000);
/*
	set("chat_chance", 15);
	set("chat_msg_combat", ({
		name() + "�ȵ������ϣ����Ҷԣ�\n"
	}) );
*/
	set_skill("sword", 70);
	set_skill("parry", 70);
	set_skill("dodge", 70);

	setup();

	carry_object(__DIR__"obj/golden_armor")->wear();
	carry_object(__DIR__"obj/golden_sword")->wield();
}

int heal_up()
{
	if( environment() && !is_fighting() ) {
		call_out("leave", 1);
		return 1;
	}
	return ::heal_up() + 1;
}

void leave()
{
	message("vision",
		HIY + name() + "˵����ĩ������ٻ��������Ѿ���ɻ������񣬾ʹ˸�ǣ�\n\n"
		+ name() + "����һ����⣬���������ʧ�����ˡ�\n" NOR, environment(),
		this_object() );
	destruct(this_object());
}

void invocation(object who)
{
	int i;
	object *enemy;

	message("vision",
		HIY "һ��������������������߳�һ������ɫս�۵Ľ��١�\n\n"
		+ name() + "˵����ĩ������ٻ�������������\n" NOR,
		environment(), this_object() );
	enemy = who->query_enemy();
	i = sizeof(enemy);
	while(i--) {
		if( enemy[i] && living(enemy[i]) ) {
			kill_ob(enemy[i]);
			if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
			else enemy[i]->kill_ob(this_object());
		}
	}
	set_leader(who);
}
