//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/shop.c
// by bor @DA

inherit ROOM;

#define SHOP_ROOM		"/d/special/recall_shop.c"
static object shop;

int do_sell_object(object me, object ob);
int is_shop() { return 1; }

void setup()
{
	::setup();
	seteuid(getuid());
	if( !shop = find_object(SHOP_ROOM) ) {
		call_other( SHOP_ROOM, "???" );
		shop = find_object(SHOP_ROOM);
	}
	if( !shop ) shop = new(SHOP_ROOM);
}

void init()
{
	add_action("do_sell", "sell");
	add_action("do_list", "list");
	add_action("do_buy", "buy");
	add_action("do_try", "try");
	add_action("do_value", "value");
}

int do_list(string arg)
{
	object *all;
	string msg;

	if( !shop ) return notify_fail("�̵�Ŀǰû���κ���Ʒ��\n");
	if( zerop(all = all_inventory(shop)) ) return notify_fail("�̵�Ŀǰû���κ���Ʒ��\n");

	msg = "�̵�Ŀǰ���۵���Ʒ�����£�\n";
	msg += implode( map_array(all, (: sprintf("%-50s%s", $1->short(), "�۸� "+(string)$1->query("value")+" ö��ҡ�" ) :)), "\n  ");
	msg += "\n";
	reset_eval_cost();
	this_player()->start_more(msg);
	return 1;
}

int do_sell(string arg)
{
	object me = this_player(), ob;
	int value, gold;

	if( !arg ) return notify_fail("��Ҫ����ʲô��Ʒ��\n");
	if( arg=="all" ) {
		object *inv;
		inv = all_inventory(me);
		if( sizeof(inv) )
		foreach(ob in inv) {
			if(!objectp(ob)) continue;
			if(ob->query("equipped")) continue;
			do_sell_object(me, ob);
		}
		write("Ok��\n");
		return 1;
	}
	if( !(ob = present(arg, me)) ) return notify_fail("��Ҫ����ʲô��Ʒ��\n");
	do_sell_object(me, ob);
	write("Ok��\n");
	return 1;
}

int do_sell_object(object me, object ob)
{
	int value, gold;

	if(ob->query("equipped")) {
		write("�����Ʒ��װ���ţ��޷����ۡ�\n");
		return 0;
	}
	if( ob->query("money_id") ) return 0;

	value = ob->query("value");
	if( !value ) return notify_fail("����������ֵǮ��\n");

	gold = value*4/5;

	if( ob->is_corpse() ) gold = 1;

	message_vision("$N�����ϵ�$n����, �õ� "+gold+" ö��ҡ�\n", me, ob);

	if( ob->is_corpse() ) destruct(ob);
	if( !userp(me) ) gold = gold/10;
	me->got_money(gold);
	if( objectp(ob) ) ob->direct_move(SHOP_ROOM);
	return 1;
}

int do_buy(string arg)
{
	object *all;
	int flag = -1, value;

	if( !shop ) return notify_fail("��Ҫ��ʲô��Ʒ��\n");
	if( zerop(all = all_inventory(shop)) ) return notify_fail("�̵�Ŀǰû������Ҫ����Ʒ��\n");
	for(int i=0; i<sizeof(all); i++) {
		if( !all[i]->id(arg) ) continue;
		flag = i;
		break;
	}
	if( flag == -1 ) return notify_fail("����û������Ҫ����Ʒ��\n");
	else {
		value = all[flag]->query("value");
		// �ǵ�Ԥ�� mob �������̵깺����Ʒ
		if( userp(this_player()) )
		if( !(this_player()->can_afford(value) ) ) return notify_fail("�����ϵ�Ǯ������\n");
		if( !all[flag]->move(this_player()) ) return notify_fail("�����帺�ɲ��ˣ�û�취��������\n");
		if(userp(this_player())) {
			this_player()->pay_money(value);
			this_player()->save();
		}
		message_vision("$N������һ"+all[flag]->query("unit")+"$n��\n", this_player(), all[flag]);
		reset_eval_cost();
	}
	return 1;
}

int do_try(string arg)
{
	object *all, me = this_player();
	int flag=-1;

	if(!arg) return notify_fail("��Ҫ��ʲô ?\n");
	if( zerop(all = all_inventory(shop)) ) return notify_fail("����û�����ֶ��� !\n");
	for(int i=0; i<sizeof(all); i++) {
		if( !all[i]->id(arg) ) continue;
		flag = i;
		break;
	}
	if( flag == -1 ) return notify_fail("����û�����ֶ��� !\n");
	if( all[flag]->query("skill_type") ) {
		if( all[flag]->query("skill") && all[flag]->query("skill")> me->query_skill(all[flag]->query("skill_type"),1) )
			tell_object(me, "������"+all[flag]->query("name")+"����һ����������"+
				to_chinese(all[flag]->query("skill_type"))+"�ļ��ܻ�������ʹ������������\n");
		return 1;
	} else if( all[flag]->query("armor_type") ) {
		if( all[flag]->query("level")> me->query("level") )
			tell_object(me, "������"+all[flag]->query("name")+"����һ����������ĵȼ���������ʹ�����ַ��ߡ�\n");
		return 1;
	}
	tell_object(me, "������"+all[flag]->query("name")+"����һ��������ĵ��ͷ��\n");
	return 1;
}

int do_value(string arg)
{
	object me = this_player(), ob;

	if( !arg || !(ob = present(arg, me)) ) return notify_fail("��Ҫ��ʲô��Ʒ���ϰ���ۣ�\n");
	tell_object( me, ob->name_id()+"��ֵ "+ob->query("value")+" ö��ҡ����Ҫ��(sell)�������õ� "+ob->query("value")*4/5+" ö��ҡ�\n");
	return 1;
}
