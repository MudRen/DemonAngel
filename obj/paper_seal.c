//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// paper_seal.c

inherit COMBINED_ITEM;

void create()
{
	set_name("桃符纸", ({"paper seal", "seal", "paper"}));
	set("long",
		"这是道士们用来画符的符纸，具有封存法力的功\用。\n");
	set("unit", "叠");
	set("base_unit", "张");
	set("base_weight", 5);
	set_amount(1);
}

