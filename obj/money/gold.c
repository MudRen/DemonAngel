//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// gold.c

inherit MONEY;

void create()
{
	set_name("黄金", ({"gold"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("money_id", "gold");
		set("long", "黄澄澄的金子，人见人爱的金子，啊～～金子！\n");
		set("unit", "些");
		set("base_value", 1 );
		set("base_unit", "两");
		set("base_weight", 1);
	}
	set_amount(1);
}

