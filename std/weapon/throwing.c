//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// throwing.c

#include <weapon.h>
#include <weapon_price.h>

inherit COMBINED_ITEM;
inherit F_EQUIP;

varargs void init_throwing(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", flag);
}

void setup()
{
	// ::setup();
	seteuid(getuid());

	if( clonep(this_object()) ) return;

	set("skill_type", "throwing");
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "throw" }) );
	}
	set("value", wp_price(this_object()));

	if(!query("weapon_prop/wl")) set("weapon_prop/wl", query("skill")/10+2 );
	if(!query("weapon_prop/Mh")) set("weapon_prop/Mh", damage+query_weight()/20+1 );
}
