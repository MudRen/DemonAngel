//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/weapon/whip.c

#include <weapon.h>
#include <weapon_price.h>

inherit EQUIP;

varargs void init_whip(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", flag );
	set("skill_type", "whip");
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "whip" }) );
	}
	set("value", wp_price(this_object()));

	if(!query("weapon_prop/wl")) set("weapon_prop/wl", query("skill")/10+2 );
	if(!query("weapon_prop/Mh")) set("weapon_prop/Mh", damage+query_weight()/18+1 );
}

