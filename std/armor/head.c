//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/armor/head.c

#include <armor.h>
#include <armor_price.h>

inherit EQUIP;

void setup()
{
	if( clonep(this_object()) ) return;
	set("armor_type", TYPE_HEAD);
	if( !query("armor_apply/dodge")
	&&	weight() > 3000 )
		set("armor_prop/dodge", - weight() / 3000 );

	set("value", eq_price(this_object()));

	if(!query("armor_prop/ac")) set("armor_prop/ac", query("level")/6+2 );
	if(!query("armor_prop/db")) set("armor_prop/db", query("level")/6+1 );

}