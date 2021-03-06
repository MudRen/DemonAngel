//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/gift_shop.c
// by bor @DA, 3/5 2003

// 此范例可以提供给你撰写 药水店  等同类型的特殊建筑物

inherit ROOM;

string *gift = ({
	"/d/obj/gift_shop/firework",
	"/d/obj/gift_shop/red_bag",
	"/d/obj/gift_shop/fairy_firework",
	"/obj/potion/potion",
	"/obj/potion/bean"
});

void reset_gift();
object find_gift(string id);

void setup()
{
	seteuid(getuid());
	reset_gift();
	::setup();
}

void init()
{
	add_action("do_list","list");
	add_action("do_buy","buy");
}

int do_list(string arg)
{
	string msg="";

	msg += "目前本礼品店贩卖(buy)的物品如下 :\n";
	for(int i=0;i<sizeof(gift);i++)
		msg += sprintf("    %-35s %5d 枚金币  还有 %3d %s\n",
			gift[i]->short(1), gift[i]->query("value"),
			tmp_dbase["list"][gift[i]], gift[i]->query("unit"));
	this_player()->start_more(msg);
	return 1;
}

int do_buy(string arg)
{
	int count = 1;
	string id, file;
	object ob;

	if(!arg) return notify_fail("你要买什么 ?\n");
	if(sscanf(arg,"%d %s", count, id) != 2) id = arg;

	if( !objectp(ob = find_gift(id)) )
		return notify_fail("你要买什么东西？\n");

	file = base_name(ob);

	for(int i=0; i<count; i++) {
		if(tmp_dbase["list"][file] < 1) return notify_fail("对不起, 这样东西已经卖完了, 请待会再来。\n");
		if( ob->query("base_value") )
			if(!this_player()->can_afford(ob->query("base_value"))) return notify_fail("你的钱不够。\n");
		else 
			if(!this_player()->can_afford(ob->query("value"))) return notify_fail("你的钱不够。\n");
		if(!ob->move(this_player())) {
			destruct(ob);
			return notify_fail("你拿不动了.\n");
		}
		tmp_dbase["list"][file] -= 1;
		if( ob->query("base_value") )
			this_player()->pay_money(ob->query("base_value"));
		else this_player()->pay_money(ob->query("value"));
		message_vision("$N买下了一"+ob->query("unit")+"$n。\n",this_player(), ob);
	}
	return 1;
}

object find_gift(string id)	// 检查你输入要购买的物件是否存在
{
	object ob;

	for(int i=0; i<sizeof(gift); i++) {
		ob = new(gift[i]);
		if( id != ob->query("id") ) {
			destruct(ob);
			continue;
		}
		return ob;
	}
	return ob;
}

void reset_gift()
{
	set_temp("list", ([]));				// 先设定为 [], 方便后来设定
	for(int i=0;i<sizeof(gift);i++)
		tmp_dbase["list"][gift[i]] = 30;	// tmp_dbase 的使用方法请参考 dbase.c
	return;
}

void reset()
{
	reset_gift();
	::reset();
}
