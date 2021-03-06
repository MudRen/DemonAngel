//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
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
        return (year ? year + " 年 " : "") + (month ? month + " 月 " : "")
                + (day ? day + " 天 " : "") + (hour ? hour + " 时 " : "")
                + minute + " 分。";
}

string finger_all()
{
	object *ob;
	string msg="";
	int i;

	ob = sort_array( users(), (: strcmp(query_ip_number($1), query_ip_number($2)) :) );
	write("\n代号        连线位置        连线时数      hostname   port\n");
	write("─────────────────────────────────\n");
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
        string msg, position="平民";
        int online= 1;

        if(strsrch(name, ".")!=-1) return "没有这个玩家。\n";

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() ) return "没有这个玩家。\n";

	if(!(body = find_player(name))) {
		body = load_player(name);
		online = -1;
	}

	if(!objectp(body)) {
		msg =  sprintf("\n英文代号：%-20s姓    名：%s\n",
			ob->query("id"), ob->query("name") );
		return msg;
	} else {
		msg =  sprintf("\n英文代号：%-20s姓    名：%s\n",
			ob->query("id"), body->query("name") );
	}

	msg += sprintf("性　　别：%-20s配    偶：%s\n",
		body->query("gender"),
		body->query("family/couple") ? body->query("family/couple") : "未婚");

	msg += sprintf("所属国家：%-20s目前职衔：%s\n",
		body->query("kingdom/id") ? full_kingdom(body->query("kingdom/id")) : "无",
		body->query("kingdom/king")?(body->query("gender")=="男性"?"国王":"女王"):
			(body->query("kingdom/minister")?"大臣":position),
		);

	msg += sprintf("目前职业：%-20s目前等级：%d\n",
		body->query("class"),
		body->query("level"),
		);

	msg += sprintf("上线时数: %-19s 连线位置 : %s\n\n", age_string(body->query("mud_age")), online>0?query_ip_name(body):"无" );

	msg += sprintf("上次连线地址：\t%s( %s )\n",
		ob->query("last_from"),
		ctime(ob->query("last_on"))
                        );

	msg += sprintf("\n状态: %s\n", online>0?"上线中":"离线中" );

        if (online=-1) destruct(ob);
        return msg;
}

varargs string remote_finger_user(string name, int chinese_flag)
{
	object ob, body;
	string msg;

	if(strsrch(name, ".")!=-1) return "没有这个玩家。\n";
	ob = new(LOGIN_OB);
	ob->set("id", name);
	if( !ob->restore() )
		return chinese_flag ? "没有这个玩家。\n" : "No such user.\n";
	if( chinese_flag ) msg =  sprintf(
		"\n英文代号：\t%s\n姓    名：\t%s\n权限等级：\t%s\n"
		"电子邮件地址：\t%s\n上次连线地址：\t%s( %s )\n\n",
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
				("\n" + ob->query("name") + "目前正在线上。\n"):
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
