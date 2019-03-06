//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// zombie.c

#include <ansi.h>

inherit NPC;

void do_bite();

void create()
{
	set_name("��ʬ", ({ "zombie" }) );
	set("long",
		"����һ�߱����÷�����ƵĽ�ʬ�������԰׵����Ͽ������κ�ϲŭ���֡�\n");
	set("max_gin", 400);
	set("max_kee", 400);
	set("max_sen", 60);
	set("max_atman", 100);
	set("atman", 100);
	set("max_mana", 100);
	set("mana", 100);
	set("str", 60);
	set("cor", 40);
	set("chat_chance", 15);
	set("chat_msg_combat", ({
		"��ʬ���з����ɺɵĽ�����\n",
		"��ʬ�����Ͽ�ʼ���Σ�һ��鴤�������Ƶش�С�\n",
		"��ʬ��ָ���ţ�ҧ���гݣ�¶��������Ц�ݡ�\n",
		(: do_bite :),
	}) );
	set_skill("unarmed", 30);
	set_skill("dodge", 30);

	set_temp("apply/damage", 15);

	setup();
}

int is_zombie() { return 1; }

void animate(object who, int time)
{
	set("possessed", who);
	set_leader(who);
}

void dispell()
{
	object corpse;

	if( environment() ) {
		say( name() + "�����ص�����������Ϊһ̲Ѫˮ��\n");
	}

	destruct(this_object());
}

int heal_up()
{
	object master;

	if( objectp(master = query("possessed")) 
	&&	(int)master->query("atman") > 10 ) {
		message("tell",
			HIR + name() + "�����㣺��...��...Ҫ...��...��...��...��...\n" NOR,
			master );
		master->add("atman", -10);
		master->receive_damage("gin", 1);
		::heal_up();
		return 1;		// Always acquire power from master.
	} else {
		call_out("dispell", 1);
		return ::heal_up();
	} 
}

void do_bite()
{
	object *enemy;

	say( name() + "�������һ��������Ż�ĳ�����ʹ�����ͷ�����͡�\n" );
	enemy = query_enemy();
	for(int i=0; i<sizeof(enemy); i++) {
		if( !enemy[i] ) continue;
		enemy[i]->receive_damage("gin", 20);
		COMBAT_D->report_status(enemy[i], "gin");
	}
}
