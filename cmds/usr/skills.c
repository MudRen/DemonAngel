//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/skills.c
// by bor @DA

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mapping sk;
	string *sk_name, msg="";

	seteuid(getuid());
	if( !arg ) ob = me;
	else {
		if( wizardp(me) ) {	// ���������ʦ������Բ쿴��ҵļ���
			arg = lower_case(arg);
			if( !ob = present(arg, environment(me)) )
				ob = find_player(arg);
			if( !ob ) ob = load_player(arg);
			if( !ob ) return notify_fail("û����λ������ϡ�\n");
		} else ob = me;
	}

	if( zerop(sk = ob->query_skills()) )
		return notify_fail( (ob==me?"��":ob->name_id())+"Ŀǰ��û��ѧ���κμ��ܡ�\n");

	sk_name  = keys(sk);

	if( ob == me ) msg += "��Ŀǰ��ѧ���ļ��ܣ�\n\n";
	else msg += ob->name_id()+"Ŀǰ��ѧ���ļ��ܣ�\n\n";

	for(int i=0; i<sizeof(sk_name); i++) {
		msg += sprintf("%-40s%3d\n",to_chinese(sk_name[i])+"("+sk_name[i]+")",
			sk[sk_name[i]] );
	}

	if( userp(ob) && !find_player(ob->query("id")) ) destruct(ob);
	reset_eval_cost();
	me->start_more(msg);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : skills

���ָ���������(��)��ѯ��ѧ���ļ��ܡ�

���ѶϢ : attribute, list, cost, kingdom, die

HELP
	);
	return 1;
}
