//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/ship/ship.c
// by bor @DA, 2/24 2003

#include <ansi.h>
inherit SHIP;

void create()
{
	set("short", "���Ǵ�(Iron Ship)" );
	set_name("���Ǵ�", ({ "Iron Ship", "Iron", "Ship" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @TEXT
�㿴��һ���ƾɵ����ƵĴ�ֻ�������˿�����������ҡͷ����
��ˣ�������Զ·��˱�Ĵ�ֻ��Ҳ��Ը�⿿�������������Ĵ�ֻ
�ڰ�·�ϴ�������û��
TEXT
	);
		set("type", "ship");
		set("port1", "/d/gourd/ship_port.c");	// ϵͳ�ۿ�
		set("port2", "/open/test/1.c");		// ���Ҹۿ�
		set("max_load", 15);			// Ԥ��һ��
		set("value", 1);
		set("unit","��");
		set("no_kill", 1);
		set("no_get", 1);
		set("kingdom_id", "test");		// ��һ���ҵĴ�ֻ
	}
	setup();
}
