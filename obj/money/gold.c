//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// gold.c

inherit MONEY;

void create()
{
	set_name("�ƽ�", ({"gold"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("money_id", "gold");
		set("long", "�ƳγεĽ��ӣ��˼��˰��Ľ��ӣ����������ӣ�\n");
		set("unit", "Щ");
		set("base_value", 1 );
		set("base_unit", "��");
		set("base_weight", 1);
	}
	set_amount(1);
}

