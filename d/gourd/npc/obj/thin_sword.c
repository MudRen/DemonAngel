//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/gourd/npc/obj/thin_sword.c

#include <weapon.h>

inherit SWORD;

void create()
{
	set_name("ϸ��", ({ "thin sword", "sword" }) );
	set_weight(14);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("type", "sword");
		set("skill", 20);
		set("level", 10);
		set("material", "steel");
		set("long", "����һ����ϸ�ֳ��Ľ�����ƮƮ������Ů���Ӽҵ����⡣\n");
		set("wield_msg", "$N���һ�ѽ���ϸ���Ľ����������С�\n");
		set("unequip_msg", "$N�������е�$n��\n");
	}
	init_sword(16);
	setup();
}
