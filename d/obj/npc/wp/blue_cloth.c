//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// blue_cloth.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("��������", ({ "blue cloth", "cloth" }) );
	set_weight(2000);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "��");
		set("value", 600);
		set("long", "һ���ֲ����ƵĲ��£��������������¹�����·���\n");
		set("wear_as", "cloth");
		set("apply_armor/cloth", ([
			"armor": 2,
		]));
	}

	setup();
}
