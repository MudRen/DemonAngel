//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// score.c
//modify by amgbell@DA

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        string line, tmp, *list;
        int i;

        if(!arg) ob = me;
        else {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("��Ҫ�쿴˭��״̬��\n");
                if (!wizardp(me) && !ob->accept_info(me, "score") )
                        return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");
        }

        seteuid(getuid(ob));

        line = sprintf( BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(ob), ob->short(1) );

        line = sprintf("%s ����һ%s��%s����%s%s��\n\n", line,
                (tmp = ob->query("unit")) ? tmp : "��",
                chinese_number(ob->query("level")),
                to_chinese(ob->query("race")),
                (tmp = ob->query("gender")) ? to_chinese(tmp) : "" );

        line = sprintf(
                "%s ���� [%2d/%2d]  �ǻ� [%2d/%2d]  ���� [%2d/%2d]\n"
                  " ���� [%2d/%2d]  ���� [%2d/%2d]  ���� [%2d/%2d]\n\n", line,
                ob->query_str(), ob->query("str"),
                ob->query_int(), ob->query("int"),
                ob->query_dex(), ob->query("dex"),
                ob->query_sta(), ob->query("sta"),
                ob->query_con(), ob->query("con"),
                ob->query_kar(), ob->query("kar"));

// ����״̬         
	if( sizeof(ob->all_condition()) > 0 ) {
		tmp = "";
		for(i=0; i<sizeof(ob->all_condition()); i++) {
			tmp += to_chinese(keys(ob->all_condition())[i]) + ", ";
		}
		line += sprintf(" ����״�� : %s\n\n", tmp);
		reset_eval_cost();
	}

// ͨ��
	if( sizeof(list = ob->query("arrest"))>0 ) {
		tmp = "";
		for(i=0; i<sizeof(list); i++)
			tmp += list[i] + ", ";
		line += sprintf(" ͨ��״�� : %s\n\n", tmp);
		reset_eval_cost();
	}

        line += sprintf(" <����> %3d/%3d (%3d%%)      " , 
                ob->query_hp(),ob->query_base_hp(),
                ob->query_hp()*100/ob->query_base_hp());

        line += sprintf("<����> %3d/%3d (%3d%%)\n\n\n" , 
                ob->query_mp(),ob->query_base_mp(),
                ob->query_mp()*100/ob->query_base_mp());

// ����
	line += sprintf(" ���������ȼ� %4d    ����˺��� %4d    ��С�˺��� %4d\n\n",
		ob->query_wl(), ob->query_Mh(), ob->query_mh());

// ����
	line += sprintf(" ���������ȼ� %4d    ��������� %4d    ս������ %10d\n\n",
		ob->query_ac(), ob->query_db(), ob->query("exp") );

        line += sprintf(" ���ϴ��� %d ö���, �������� %d ö���",
                 ob->query("gold"), ob->query("bank_gold") );

        write(line+"\n");
        return 1;
}


int help(object me)
{
        write(@HELP
ָ���ʽ : score
           score <��������>                   (��ʦר��)
 
���ָ�������ʾ��(��)��ָ������(������)�Ļ������ϡ�
�������ϵ��趨����� 'help setup'��
 
�������ָ�hp
HELP
    );
    return 1;
}
