//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/herb_shop/potion.c
// by bor @DA, 3/11 2003

inherit "/std/potion/heal.c";

void create()
{
	set_name("��ͨҩˮ",({"hp potion","hp","potion"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","����һƿ��ͨҩˮ, ���������ָ�����, ����Ժ�(drink)���� !\n");
		set("base_value", 500);
		set("base_unit", "��");
		set("base_weight", 50);
		set("unit","��");
		set("item", "potion");
		set("kind","hp");
		set("cure",100);
	}
	setup();
}
