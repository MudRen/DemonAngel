//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// child.c

inherit NPC;

void create()
{
	set_name("小美女", ({ "girl" }) );
	set("int", 3);
	set("dex", 2);
	set("con", 20);
	set("level", 1);

	set_skill("dodge", 3);

	set("long",
		"这个十五、六岁的小姑娘就是“阿宝”了，她身上虽然穿着粗布\n"
		"衣服，但却十足是个美人胚子，一双水汪汪的大眼睛骨碌碌地转\n"
		"着，还不时盯着你看，使你不禁觉得有些发窘。\n");

	setup();
}
