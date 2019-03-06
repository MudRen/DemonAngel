//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/bank.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit ROOM;

void init()
{
	add_action("do_deposit", "deposit");
	add_action("do_withdraw", "withdraw");
	add_action("do_transfer", "transfer");
}

int do_deposit(string arg)
{
	int amount;
	object me = this_player();

	seteuid(getuid());
	if( me->is_busy()) return notify_fail("��������æ�š�\n");
	if( !arg || sscanf(arg, "%d", amount)!=1 ) return notify_fail("��ʽ : deposit <����Ǯ>\n");
	if( amount < 0 ) return notify_fail("��ǸĿǰû�п��Ž�������ˡ�\n");
	if( amount == 0 ) return notify_fail("��� "+amount+" ö��Ҵ�����С�\n");
	if( !me->deposit_bank(amount) ) return notify_fail("������û����ô��Ǯ��\n");

        write("��� "+amount+" ö��Ҵ�����С�\n");
	if(amount>100000) log_file("bank",sprintf("[%s] %s[%s] deposit %d ö��� <%s>��\n",
		ctime(time())[0..15], geteuid(me), me->query("kingdom/id"), amount,
		query_ip_name(me)));
	me->save();
        return 1;
}

int do_withdraw(string arg)
{
	int amount;
	object me=this_player();

	seteuid(getuid());
	if( !arg || sscanf(arg, "%d", amount)!=1 ) return notify_fail("��ʽ : withdraw <����Ǯ>\n");
	if( amount < 0) return notify_fail("��ǸĿǰû�п��Ž�������ˡ�\n");
	if( amount == 0 ) return notify_fail("���������� "+amount+" ö��ҡ�\n");
        if( !me->withdraw_bank(amount) ) return notify_fail("��������û����ô��Ǯ��\n");

	write("���������� "+amount+" ö��ҡ�\n");
	if(amount>100000) log_file("bank",sprintf("[%s] %s[%s] withdraw %d ö��� <%s>��\n",
		ctime(time())[0..15], geteuid(me), me->query("kingdom/id"), amount,
		query_ip_name(me)));
	me->save();
	return 1;
}

int do_transfer(string arg)
{
	object me = this_player(), ob;
	string id;
	int flag =1, amount;

	if(!arg) return notify_fail("��ʽ: transfer <���> <����Ǯ>\n");
	if( sscanf(arg, "%s %d", id, amount)!=2 ) return notify_fail("��ʽ: transfer <���> <����Ǯ>\n");
	if( !(ob = find_player(id))) {
		ob = load_player(id);
		flag = -1;
	}
	if(!ob) return notify_fail("�Ҳ��������ҡ�\n");
	if( amount < 1 ) return notify_fail("��ǸĿǰû�п��Ž�������ˡ�\n");
	if( me->query("bank_gold")<amount ) return notify_fail("��������û����ô��Ǯ��\n");
	ob->add("bank_gold", amount);
	ob->save();
	me->add("bank_gold", -amount);
	me->save();
	message_vision("$N������ת�� "+amount+" ö��Ҹ�$n��\n", me, ob);
	if(flag ==-1) destruct(ob);
	return 1;
}
