//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// file : /open/test/ship/ship.c
// save ship by bor @DA, Sat Mar 08 22:54:49 2003
#include <ansi.h>
inherit SHIP;

void create()
{
	set("short", "���Ǵ�(Iron Ship)");
	set_name( "���Ǵ�(Iron Ship)", ({ /* sizeof() == 3 */
  "iron ship",
  "iron",
  "ship"
}) );
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
		set("port1", "/d/gourd/ship_port.c");
		set("port2", "/open/test/1.c");
		set("max_load", 15);
		set("value", 1);
		set("unit", "��");
		set("no_kill", 1);
		set("no_get", 1);
		set("kingdom_id", "test");
	}
	setup();
}
