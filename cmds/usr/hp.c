//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/hp.c
 
inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
	object ob;
 
	seteuid(getuid(me));
	if(!arg) ob = me;
	else if (wizardp(me)) {
		ob = present(arg, environment(me));
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
		if (!ob) ob = me;
	} else ob = me;
 
	printf("���� : %4d/%4d (%3d%%)\n" , ob->query_hp(),ob->query_base_hp(),ob->query_hp()*100/ob->query_base_hp());
	printf("���� : %4d/%4d (%3d%%)\n" , ob->query_mp(),ob->query_base_mp(),ob->query_mp()*100/ob->query_base_mp());
	printf("���� : %d\n", ob->query("exp"));

	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : hp
 
���ָ�������ʾ��(��)Ŀǰ�ĸ���״����
 
���ѶϢ : score, die

HELP
	);
	return 1;
}
