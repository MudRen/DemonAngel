//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/obj/npc/guard_1.c

inherit NPC;

void create()
{
	set_name("王座守卫", ({ "guard" }) );
	set("dex", 5);
	set("str", 30);
	set("level", 4);

	set_skill("dodge", 3);

	set("long", "凶八八的坏蛋守卫。\n");

	setup();
	carry_object("/d/obj/npc/wp/thin_sword")->wield();
}
