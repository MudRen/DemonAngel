//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// buy.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string item, targ;
	object ob, owner;
	int price, afford;

	if( !arg || sscanf(arg, "%s from %s", item, targ)!=2 )
		return notify_fail("ָ���ʽ��buy <ĳ��> from <ĳ��>\n");

	if( !objectp(owner = present(targ, environment(me))) )
		return notify_fail("��Ҫ��˭������\n");

	if( userp(owner) ) {
		message_vision("$N����$n����" + item + "����\n", me, owner);
		return 1;
	}

	notify_fail("�Է�����Ը����㽻�ס�\n");
	if( (price = owner->buy_object(me, item)) < 1 ) return 0;

	if( afford = me->can_afford(price) ) {
		if( afford==2 ) 
			return notify_fail("��û���㹻����Ǯ�����Է�Ҳ�Ҳ���...��\n");
		me->pay_money(price, 0);
		owner->compelete_trade(me, item);
		return 1;
	} else
		return notify_fail("���Ǯ������\n");
}

int help(object me)
{
   write( @HELP
ָ���ʽ: buy <something> from <someone>

��һָ��������Դ�ĳЩ����������Ʒ��
HELP
   );
   return 1;
}
