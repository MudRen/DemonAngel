//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create() {
	set_name("��", ({"sword"}) );
	set_weight(10); 
	set("new", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ľ���
LONG );
		set("unit","��");
		set("weapon_prop/wl",3);
		set("weapon_prop/Mh",3);
		set("type","sword");
		set("level",30);
		set("skill",60);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_sword(10);
	setup();
}
