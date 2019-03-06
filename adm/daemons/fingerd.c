//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/fingerd.c
// modify by bor @DA, 3/5 2003

#include <net/dns.h>

void create() { seteuid( getuid() ); }

string age_string(int time)
{
        int year, month, day, hour, minute;

        time /=60;
        minute = time % 60;
        time /= 60;
        hour = time % 24;
        time /= 24;
        day = time % 30;
        time /= 30;
        month = time % 12;
        year = time / 12;
        return (year ? year + " �� " : "") + (month ? month + " �� " : "")
                + (day ? day + " �� " : "") + (hour ? hour + " ʱ " : "")
                + minute + " �֡�";
}

string finger_all()
{
	object *ob;
	string msg="";
	int i;

	ob = sort_array( users(), (: strcmp(query_ip_number($1), query_ip_number($2)) :) );
	write("\n����        ����λ��        ����ʱ��      hostname   port\n");
	write("������������������������������������������������������������������\n");
	for(i=0; i<sizeof(ob); i++) {
		if( this_player() && !this_player()->visible(ob[i]) ) continue;
		msg = sprintf("%s%-12s%-16s%-14s%-11s%d\n",
			msg, ob[i]->query("id"), query_ip_name(ob[i]),
			age_string( (int)ob[i]->query("mud_age")),
			query_host_name(), query_ip_port(ob[i])
		);
	}
	return msg;
/*	object *ob;
	string msg;
	int i;

	ob = users();
	msg = "";
	for(i=0; i<sizeof(ob); i++) {
		if( this_player() && !this_player()->visible(ob[i]) ) continue;
		msg = sprintf("%s%-20s  %-20s  %-10s %s\n",
			msg, ob[i]->query("name"), ob[i]->query("id"),
			age_string( (int)ob[i]->query("mud_age")), query_ip_name(ob[i]) );
	}
	return msg;*/
}

string finger_user(string name)				// modify by bor @DA, 3/9 2003
{
        object ob, body;
        string msg, position="ƽ��";
        int online= 1;

        if(strsrch(name, ".")!=-1) return "û�������ҡ�\n";

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() ) return "û�������ҡ�\n";

	if(!(body = find_player(name))) {
		body = load_player(name);
		online = -1;
	}

	if(!objectp(body)) {
		msg =  sprintf("\nӢ�Ĵ��ţ�%-20s��    ����%s\n",
			ob->query("id"), ob->query("name") );
		return msg;
	} else {
		msg =  sprintf("\nӢ�Ĵ��ţ�%-20s��    ����%s\n",
			ob->query("id"), body->query("name") );
	}

	msg += sprintf("�ԡ�����%-20s��    ż��%s\n",
		body->query("gender"),
		body->query("family/couple") ? body->query("family/couple") : "δ��");

	msg += sprintf("�������ң�%-20sĿǰְ�Σ�%s\n",
		body->query("kingdom/id") ? full_kingdom(body->query("kingdom/id")) : "��",
		body->query("kingdom/king")?(body->query("gender")=="����"?"����":"Ů��"):
			(body->query("kingdom/minister")?"��":position),
		);

	msg += sprintf("Ŀǰְҵ��%-20sĿǰ�ȼ���%d\n",
		body->query("class"),
		body->query("level"),
		);

	msg += sprintf("����ʱ��: %-19s ����λ�� : %s\n\n", age_string(body->query("mud_age")), online>0?query_ip_name(body):"��" );

	msg += sprintf("�ϴ����ߵ�ַ��\t%s( %s )\n",
		ob->query("last_from"),
		ctime(ob->query("last_on"))
                        );

	msg += sprintf("\n״̬: %s\n", online>0?"������":"������" );

        if (online=-1) destruct(ob);
        return msg;
}

varargs string remote_finger_user(string name, int chinese_flag)
{
	object ob, body;
	string msg;

	if(strsrch(name, ".")!=-1) return "û�������ҡ�\n";
	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() )
		return chinese_flag ? "û�������ҡ�\n" : "No such user.\n";
	if( chinese_flag ) msg =  sprintf(
		"\nӢ�Ĵ��ţ�\t%s\n��    ����\t%s\nȨ�޵ȼ���\t%s\n"
		"�����ʼ���ַ��\t%s\n�ϴ����ߵ�ַ��\t%s( %s )\n\n",
		ob->query("id"),
		ob->query("name"),
		SECURITY_D->get_status(name),
		ob->query("email"),
		ob->query("last_from"),
		ctime(ob->query("last_on"))
	);
	else msg =  sprintf(
		"\nName\t: %s\nStatus\t: %s\nEmail\t: %s\nLastOn\t: %s( %s )\n\n",
		capitalize(ob->query("id")),
		SECURITY_D->get_status(name),
		ob->query("email"),
		ob->query("last_from"),
		ctime(ob->query("last_on"))
	);
	if( body = find_player(name) ) {
		if( !this_player() || this_player()->visible(body) )
			msg += chinese_flag ?
				("\n" + ob->query("name") + "Ŀǰ�������ϡ�\n"):
				("\n" + capitalize(name) + " is currently connected.\n");
	}

	destruct(ob);
	return msg;
}

object acquire_login_ob(string id)
{
	object ob;

	if( ob = find_player(id) ) {
		// Check if the player is linkdead
		if( ob->query_temp("link_ob") )
			return ob->query_temp("link_ob");
	}
	ob = new(LOGIN_OB);
	ob->set("id", id);
	return ob->restore() ? ob : 0;
}
