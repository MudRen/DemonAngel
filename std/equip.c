//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/equip.c

inherit ITEM;
inherit F_EQUIP;

/*
void setup()
{
	if( !query("armor_prop/dodge") && (weight() >= 3000) )
		set("armor_prop/dodge", - weight() / 3000 );
	if( !query("weapon_prop/dodge") && (weight() >= 3000) )
		set("weapon_prop/dodge", - weight() / 3000 );
}
*/
int query_autoload()
{
	if(this_object()->query("equipped")) return 1;
	return 0;
}