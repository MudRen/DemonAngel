//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/potion/bean.c
// by bor @DA, 3/11 2003

inherit "/std/potion/bean_eat.c";

void create()
{
	set_name("��",({"bean"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","����һ�Ѹ�����Ե�����������ǿ�������� !\n");
		set("base_value", 300);
		set("base_unit", "��");
		set("base_weight", 30);
		set("unit","��");
		set("item", "potion");
		set("kind","kee");
		set("cure", 60);
	}
	setup();
}
