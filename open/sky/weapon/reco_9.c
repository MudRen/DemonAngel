//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
#include <weapon.h>
#include <ansi.h>
inherit AXE;
void create() {
	set_name("��ͷ", ({"axe"}) );
	set_weight(10); 
	set("new", 1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������ĸ�ͷ��
LONG );
		set("unit","��");
		set("weapon_prop/wl",4);
		set("weapon_prop/Mh",4);
		set("type","axe");
		set("level",40);
		set("skill",80);
		set("owner","reco");
		set("kingdom","sky");
	}
	init_axe(13);
	setup();
}
