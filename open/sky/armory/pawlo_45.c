//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
#include <armor.h>
#include <ansi.h>
inherit RING;
void create() {
	set_name("��ָ", ({"ring"}) );
	set_weight(10); 
	set("new", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ľ�ָ��
LONG);
		set("armor_prop/ac",3);
		set("armor_prop/db",3);
		set("type","ring");
		set("level",30);
		set("owner","pawlo");
		set("kingdom","sky");
		set("unit","��");
	}
	setup();
}
