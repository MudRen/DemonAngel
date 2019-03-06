//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/gourd/recall_shop.c
// by bor @DA

inherit SHOP;

void create()
{
	set("short","�̵�");
	set("long", @TEXT
�߽����װ����, ��һ�۾ͱ���Щ����ǽ�ϵ���������������, һ��
����΢Ц��׳��վ�ڹ�ǰ��ӭ��, һ�涢�������Ͽ�, ������ʱ׼��Ϊ
���������װ��һ�㡣������ʷ�����������ĸ���װ����, �����Դ����
����ħ������������������½, ������, ����԰��ĵ�����(buy/sell)��
�������õ��ı�ƭ, ������ȿ���(list)����, �����ϰ�������(value)
, �������Ҫ���Կ�(try), �ϰ�Ҳ����˵�����ġ�
TEXT
	);
        set("exits", ([
                "west" : __DIR__"recall_n_3",
        ]));
	setup();
//	replace_program(SHOP);		// <--- �ǵ�Ҫ�õ�, ��Ȼ������
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

	if( !arg ) return notify_fail("��Ҫ������һ����Ʒ??\n");
	if( !(ob = present(arg, me)) ) return notify_fail("������û�������Ʒ!!\n");
	if( !ob->query("skill_type") ) return notify_fail("��Ѳ�������!!\n");
	if( !ob->query_temp("broken") || ob->query_temp("broken")<20 ) return notify_fail("���������û��!!\n");
	gold = ob->query("value")*9/10;
	if( !(me->can_afford(gold) ) ) return notify_fail("�������������Ҫ "+gold+" ö��ҡ�\n");
	ob->delete_temp("broken");
	me->pay_money(gold);
	me->save();
	message_vision("$N��$n�������̵��ڵļ���, �������ô����������ֽ�����$N��\n", me, ob);
	return 1;
}
