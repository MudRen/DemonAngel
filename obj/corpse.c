//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/corpse.c

inherit ITEM;

void create()
{
	set_name("ʬ��", ({ "corpse" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
//		set("long", "����һ��һ������ʬ�塣\n");
		set("unit", "��" );
	}
	setup();
}

int is_corpse() { return 1; }
string short() { return name()+"("+capitalize(query("id"))+")"; }

int receive_object(object oob, int from_inventory) { return 1; }
