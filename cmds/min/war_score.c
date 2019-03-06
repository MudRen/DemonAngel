//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/war_score.c
// by bor @DA, 3/6 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

string age_string(int time);

int main(object me, string arg)
{
	string id, msg="", *war_list;
	mapping war;

	if(!(id= me->query("kingdom/id"))) return notify_fail("��û�й�������ʹ�á�\n");
	if(!kingdom_data(id, "war", "check")) return notify_fail("���Ŀǰû���κ�һ��ս����\n");

	war_list = kingdom_data(id, "war", "query_all");
	for(int i=0; i<sizeof(war_list); i++) {
		if( !mapp( war = kingdom_data(id, "war", "query", war_list[i] ) )) continue;
		msg += full_kingdom(id)+"��"+full_kingdom(war_list[i])+"��ս����ʣ�� "+age_string(find_object("/cmds/min/declare.c")->query_war_end())+"\n";
		msg += "��ĿǰΪֹս��������£�\n\n";
		msg += "����� ���Ӷ� " + war["gold"]      + " ö / ���Ӷ� "+war["gold_"]   +" ö\n";
		msg += "ɱ���� ��ɱ�� " + war["npc"]       + " ֻ / ��ɱ " + war["npc_"]    +" ֻ\n";
		msg += "ɱ���� ��ɱ�� " + war["enemy"]     + " �� / ��ɱ " + war["enemy_"]  +" ��\n";
		msg += "������ ��ռ�� " + war["room"]      + " �� / ��ռ " + war["room_"]   +" ��\n";
		msg += "������ ���ݻ� " + war["building"]  + " �� / ���� "+ war["building_"]+" ��\n\n";
	}

	me->start_more(msg);
	return 1;
}

string age_string(int time)
{
	int day, hour, minute, sec;

	sec = time % 60;
	time /=60;
	minute = time % 60;
	time /= 60;
	hour = time % 24;
	time /= 24;
	day = time;
	return (day?day+" �� ":"")+(hour?hour+" Сʱ ":"")+minute+" �� " + sec + " ��";
}

int help(object me)
{
	write(@HELP

ָ���ʽ : war_score

���ǹ�������õ�ָ��, �鿴ս���Ľ���ʱ���ʤ��״����

HELP
	);
	return 1;
}
