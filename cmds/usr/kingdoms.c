//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/kingdoms.c
// by bor @DA

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *str, msg, king;
	int flag;

	seteuid(getuid());
	str = get_dir(KINGDOM_DIR);
	msg = "Ŀǰ���� "+sizeof(str)+" �����ң�\n";
	msg += "��������                     ����       �˿�  ʯ�� ��� ���ӳ���λ��\n";
	for(int i=0;i<sizeof(str);i++) {
		king = kingdom_data(str[i], "power", "query_all", "king")[0];
		if(kingdom_data(str[i], "open", "check")) flag += 1;

		msg += sprintf("%-29s%-13s%-5d%-8s%4s%17s\n"NOR,
			to_chinese_kingdom(str[i])+"("+capitalize(str[i])+")",
			king!=""?capitalize(king):"����",
			kingdom_data(str[i], "data", "query_par", "people"),
			(kingdom_data(str[i], "other", "query_par", "time_gate")?HIW"����"NOR:""),
			(kingdom_data(str[i], "other", "query_par", "story")?"��":""),
			(kingdom_data(str[i], "open", "check")? HIW"����"NOR:"")
		);
	}
	msg += "\n���� "+flag+" �����Ҿ�����������Ȩ��\n";
	me->start_more(msg);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ: kingdoms

��ѯ���й�����Ѷ��ָ�

HELP
	);
	return 1;
}