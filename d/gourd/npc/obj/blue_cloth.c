//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/gourd/npc/obj/blue_cloth.c

#include <armor.h>
#include <ansi.h>
inherit CLOAK;

void create()
{
	set_name("��������", ({ "blue cloth", "cloth" }) );
	set_weight(200);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 600);
		set("long", "һ���ֲ����ƵĲ��£��������������¹�����·���\n");
		set("wear_as", "cloth");
//		set("apply_armor/cloth", ([
//			"armor": 2,
//		]));
		setup();
	}
	setup();
}
