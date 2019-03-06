//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/gift_shop.c
// by bor @DA, 3/5 2003

// �˷��������ṩ����׫д ҩˮ��  ��ͬ���͵����⽨����

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

	msg += "Ŀǰ����Ʒ�귷��(buy)����Ʒ���� :\n";
	for(int i=0;i<sizeof(gift);i++)
		msg += sprintf("    %-35s %5d ö���  ���� %3d %s\n",
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

	if(!arg) return notify_fail("��Ҫ��ʲô ?\n");
	if(sscanf(arg,"%d %s", count, id) != 2) id = arg;

	if( !objectp(ob = find_gift(id)) )
		return notify_fail("��Ҫ��ʲô������\n");

	file = base_name(ob);

	for(int i=0; i<count; i++) {
		if(tmp_dbase["list"][file] < 1) return notify_fail("�Բ���, ���������Ѿ�������, �����������\n");
		if( ob->query("base_value") )
			if(!this_player()->can_afford(ob->query("base_value"))) return notify_fail("���Ǯ������\n");
		else 
			if(!this_player()->can_afford(ob->query("value"))) return notify_fail("���Ǯ������\n");
		if(!ob->move(this_player())) {
			destruct(ob);
			return notify_fail("���ò�����.\n");
		}
		tmp_dbase["list"][file] -= 1;
		if( ob->query("base_value") )
			this_player()->pay_money(ob->query("base_value"));
		else this_player()->pay_money(ob->query("value"));
		message_vision("$N������һ"+ob->query("unit")+"$n��\n",this_player(), ob);
	}
	return 1;
}

object find_gift(string id)	// ���������Ҫ���������Ƿ����
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
	set_temp("list", ([]));				// ���趨Ϊ [], ��������趨
	for(int i=0;i<sizeof(gift);i++)
		tmp_dbase["list"][gift[i]] = 30;	// tmp_dbase ��ʹ�÷�����ο� dbase.c
	return;
}

void reset()
{
	reset_gift();
	::reset();
}
