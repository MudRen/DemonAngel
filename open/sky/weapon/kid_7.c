//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/kid_7.c
// saveitem by system @ Sun May 18 22:43:47 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "��ͷ", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������ĸ�ͷ��
LONG );
		set("unit","��");
		set("type","axe");
		set("level",80);
		set("skill",160);
		set("add_attr","con");
		set("weapon_prop/con", 1);
		set("owner","kid");
		set("kingdom","sky");
	}
	init_axe(2613);
	setup();
}
