//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/gourd/recall_shop.c
// by bor @DA

inherit SHOP;

void create()
{
	set("short","商店");
	set("long", @TEXT
走进这家装备店, 你一眼就被那些挂在墙上的武器防具所吸引, 一个
带着微笑的壮汉站在柜枱前欢迎你, 一面盯着你身上看, 像是随时准备为
你量身打造装备一般。这里是史坎布雷有名的盖兹装备店, 主人以打造高
级的魔法武器闻名于整个大陆, 在这里, 你可以安心的买卖(buy/sell)东
西而不用担心被骗, 你可以先看看(list)货物, 或请老板帮你估价(value)
, 如果你想要试试看(try), 老板也不会说怎样的。
TEXT
	);
        set("exits", ([
                "west" : __DIR__"recall_n_3",
        ]));
	setup();
//	replace_program(SHOP);		// <--- 记得要拿掉, 不然不能用
}

void init()
{
	::init();
	add_action("do_repair", "repair");
}

int do_repair(string arg)
{
	object me = this_player(), ob;
	int gold;

	if( !arg ) return notify_fail("你要修理哪一件物品??\n");
	if( !(ob = present(arg, me)) ) return notify_fail("你身上没有这件物品!!\n");
	if( !ob->query("skill_type") ) return notify_fail("这把不是武器!!\n");
	if( !ob->query_temp("broken") || ob->query_temp("broken")<20 ) return notify_fail("这把武器还没损坏!!\n");
	gold = ob->query("value")*9/10;
	if( !(me->can_afford(gold) ) ) return notify_fail("修理这把武器需要 "+gold+" 枚金币。\n");
	ob->delete_temp("broken");
	me->pay_money(gold);
	me->save();
	message_vision("$N把$n交给了商店内的技工, 技工敲敲打打修理完毕又交还给$N。\n", me, ob);
	return 1;
}
