//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// who.c

#include <net/dns.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
	string str, *option;
	object *list;
	int i, j, ppl_cnt;
	int opt_long, opt_id, opt_wiz, opt_kingdom;

	if( arg ) {
		option = explode(arg, " ");
		i = sizeof(option);
		while( i-- )
			switch(option[i]) {
				case "-l": opt_long = 1;	break;
				case "-i": opt_id = 1;		break;
				case "-w": opt_wiz = 1;		break;
				case "-k": opt_kingdom = 1;	break;
				default:
					if( wizardp(me)
					&&	option[i][0]=='@' ) {
						RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],
							me, opt_long);
						write("��·ѶϢ���ͳ������Ժ�\n");
						return 1;
					}
					return notify_fail("ָ���ʽ��who [-l|-i|-w]\n");
			}
	}

/*	if( opt_long ) {
		if( (int)me->query("sen") < 30 )
			return notify_fail("��ľ���̫���ˣ�û�а취��֪������ҵ���ϸ���ϡ�\n");
		me->receive_damage("sen", 30);
	}*/

	str = "�� " + MUD_NAME + "\n";
	str += "��������������������������������������������������������������������������\n";
	list = users();
//	list = sort_array(users(), "sort_user", this_object());
	if( opt_long || opt_wiz || opt_kingdom ) {
		j = sizeof(list);
		while( j-- ) {
			// Skip those users in login limbo.
			if( !environment(list[j]) ) continue;
			if( !me->visible(list[j]) ) continue;
			if( opt_wiz && !wizardp(list[j]) ) continue;
			if( opt_kingdom && list[j]->query("kingdom/id") != me->query("kingdom/id") ) continue;

			str = sprintf("%s%12s %s\n",
				str,
				list[j]->query("kingdom/id")?
				RANK_D->query_rank(list[j])+" - "+ to_chinese_kingdom(list[j]->query("kingdom/id")):RANK_D->query_rank(list[j]) ,
				list[j]->short(1)
			);
		}
	} else {
		ppl_cnt = 0;
		j = sizeof(list);
		while( j-- ) {
			// Skip those users in login limbo.
			if( !environment(list[j]) ) continue;
			if( me && !me->visible(list[j]) ) continue;
			str = sprintf("%s%-15s%s",
				str,
				opt_id ? capitalize(list[j]->query("id")): list[j]->name(1),
				(ppl_cnt%5==4? "\n": "")
			);
			ppl_cnt++;
		}
		if( ppl_cnt%5 ) str += "\n";
	}
		
	str += "��������������������������������������������������������������������������\n";
	str = sprintf("%s���� %d λʹ���������У�ϵͳ������%s\n", str, sizeof(list),
		query_load_average() + "\n");

	if( remote ) return str;

	me->start_more(str);
	return 1;
}

int sort_user(object ob1, object ob2)
{
	if( wizardp(ob1) && !wizardp(ob2) ) return -1;
	if( wizardp(ob2) && !wizardp(ob1) ) return 1;
	if( wizardp(ob1) && wizardp(ob2) )
		return (int)SECURITY_D->get_wiz_level(ob2) 
			- (int)SECURITY_D->get_wiz_level(ob1);

	return (int)ob1->query("level") - (int)ob2->query("level");
}

int help(object me)
{
write(@HELP
ָ���ʽ : who [-l|-i|-w]

���ָ������г����������ϵ���Ҽ���ȼ���

-l ѡ���г��ϳ���ѶϢ��
-i ֻ�г���ҵ�Ӣ�Ĵ��š�
-w ֻ�г��������е���ʦ��
-k �г�������������ҡ�

���ָ� finger
HELP
    );
    return 1;
}
