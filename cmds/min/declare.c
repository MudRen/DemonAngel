//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/declare.c
// by smallpen
// modify by bor @DA, 3/6 2003 for war, peace

#pragma optimize
#pragma save_binary

#include <ansi.h>

//inherit F_CLEAN_UP;			// ���� war �Ĺ�ϵ, ȡ���˼̳�, ������ɼ�����û�취�ͷ�, �Լ���һ����ô�İ�

string show_declare(object me,string id);
void do_wait_war_end(string id, string enemy_id);

int main(object me, string arg)
{
        object ob;
        string id, action,country;

        seteuid(getuid());
        if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
        if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");

	id = me->query("kingdom/id");
        if( !arg ) {
                show_declare(me, id);
                return 1;       
        }
        
        if( sscanf(arg, "%s with %s", action, country)!=2 ) {
                if( sscanf(arg, "%s",country)!=1) {
                        return notify_fail("ָ���ʽ : declare <war/peace/hate/forgive/war> with ĳ�� \n");}
                if(!check_kingdom(country)) {
                        return notify_fail("û���������\n");}
                else {
                        show_declare(me,country);
                        return 1;
                }
	}
        if( action=="hate") {
                if(country==id) return notify_fail("�㲻�ܵ����Լ�");
                if(!check_kingdom(country)) return notify_fail("û���������\n");
                if(kingdom_data(id, "declare","check","hate",country)) return notify_fail("�˹��Ѿ�����������ˡ�\n");
                if(!kingdom_data(id, "declare", "add", "hate",country)) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                if(!kingdom_data(country,"declare","add","hated", id)) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                write(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "���������������" +to_chinese_kingdom(country) + "��\n");
                shout(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "���������������"+to_chinese_kingdom(country)  + "��\n");
	} else if(action=="forgive") {
                if(country==id) notify_fail("�㲻�ܽ�����ӡ�\n");
                if(!check_kingdom(country)) return notify_fail("û��������ҡ�\n");
                if(!kingdom_data(id, "declare", "check", "hate", country)) return notify_fail("���û�е��Ӵ˹���\n");
                if(!kingdom_data(id, "declare", "sub", "hate", country)) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                if(!kingdom_data(country,"declare", "sub", "hated", id)) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                write(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "������������ֹͣ����" +to_chinese_kingdom(country) + "��\n");
                shout(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "������������ֹͣ����"+to_chinese_kingdom(country)  + "��\n");
        } else if(action == "war") {	// by bor @DA, 3/6 2003
        	// Ŀǰ war, peace ��ʱ���ж��Է��Ƿ��д�... �Ǻ�, ͵�� @@
                if(country==id) return notify_fail("�㲻�ܸ��Լ�ս����\n");
                if(!check_kingdom(country)) return notify_fail("û��������ҡ�\n");
        	if(kingdom_data(id, "ally","check",country)) return notify_fail("����������ǽ�����, ����ֱ����ս��\n");
                if(kingdom_data(id, "war", "check", country, 1)) return notify_fail("������ù�������ս���С�\n");
		kingdom_data(id, "war", "set", country);
		kingdom_data(country, "war", "set", id);
		call_out( "do_wait_war_end", kingdom_data(id, "war", "query_par", country, "time"), id, country);
                write(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "������" +to_chinese_kingdom(country) + "������ս, ����ս����\n");
                shout(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "������" +to_chinese_kingdom(country)  + "������ս, ����ս����\n");
	} else if(action == "peace") {	// by bor @DA, 3/6 2003
                if(country==id) return notify_fail("�㲻�ܶ��Լ������ͳ���ƽ��\n");
                if(!check_kingdom(country)) return notify_fail("û��������ҡ�\n");
                if(!kingdom_data(id, "war", "check", country, 1)) return notify_fail("���û�к͸ù���ս����\n");
		call_out( "do_wait_war_end", 0, id, country);
                write(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "��" +to_chinese_kingdom(country) + "�ͳ���ƽ��, �����Ӵ˺����ദ��\n");
                shout(HIY"�� - " + NOR+me->short(1)+"����"+to_chinese_kingdom(id) + "��" +to_chinese_kingdom(country)  + "�ͳ���ƽ��, �����Ӵ˺����ദ��\n");
	}
	return 1;
}

string show_declare(object me,string id)
{
        string *list,*list1,str="";
        int i;
        str += sprintf("Ŀǰ%s�Ľ�ս���У�\n\n",to_chinese_kingdom(id) );
                if(!list = kingdom_data(id,"declare","query_all","hate"))
                        str += "������޽�ս����\n\n";
                else {
                        for(i=0; i<sizeof(list);i++) {
                                str += sprintf("%s\n",full_kingdom(list[i]));
                        }
                        str += sprintf("\n�� %d ����\n\n",sizeof(list));
                }
                str += sprintf("Ŀǰ����%s�Ĺ����У�\n\n",to_chinese_kingdom(id) );
                if(!list1 = kingdom_data(id,"declare","query_all","hated"))
                        
                        str += "�޹��ҵ��ӹ����\n\n";
                else {
                        for(i=0; i<sizeof(list1);i++) {
                                str += sprintf("%s\n",full_kingdom(list1[i]));
                        }
                        str += sprintf("\n�� %d ����\n\n",sizeof(list1));
                }
                return me->start_more(str);
                
}


// ��λ���Դ������д��, �������쵽 logind.c ��, ���ǹ̶�ʱ�� reboot ...
int query_war_end() { return find_call_out("do_wait_war_end"); }

// war ��ʽ�� ~~ һСʱΪ����, ʱ�䵽�ͽ���
void do_wait_war_end(string id, string enemy_id)	// by bor @DA, 3/6 2003
{
	mapping war;
	int score, score_, gold;

	war = kingdom_data(id, "war", "query", enemy_id);

	shout("���ⳡս����, "+full_kingdom(id)+"һ����"+full_kingdom(enemy_id)+"�Ӷ��� "+war["gold"]+" ö��ҡ�\n");
	write("���ⳡս����, "+full_kingdom(id)+"һ����"+full_kingdom(enemy_id)+"�Ӷ��� "+war["gold"]+" ö��ҡ�\n");
	shout("�����˶Է� "+war["npc"]+" ֻ����, �ݻ��� "+war["room"]+" �䷿�䡣\n");
	write("�����˶Է� "+war["npc"]+" ֻ����, �ݻ��� "+war["room"]+" �䷿�䡣\n");
	shout("��ɱ�˶Է� "+war["enemy"]+" �����, �ݻ��� "+war["building"]+" �������\n\n");
	write("��ɱ�˶Է� "+war["enemy"]+" �����, �ݻ��� "+war["building"]+" �������\n\n");
	shout("���ⳡս����, "+full_kingdom(enemy_id)+"һ����"+full_kingdom(id)+"�Ӷ��� "+war["gold_"]+" ö��ҡ�\n");
	write("���ⳡս����, "+full_kingdom(enemy_id)+"һ����"+full_kingdom(id)+"�Ӷ��� "+war["gold_"]+" ö��ҡ�\n");
	shout("�����˶Է� "+war["npc_"]+" ֻ����, �ݻ��� "+war["room_"]+" �䷿�䡣\n");
	write("�����˶Է� "+war["npc_"]+" ֻ����, �ݻ��� "+war["room_"]+" �䷿�䡣\n");

	shout("��ɱ�˶Է� "+war["enemy_"]+" �����, �ݻ��� "+war["building_"]+" �������\n\n");
	write("��ɱ�˶Է� "+war["enemy_"]+" �����, �ݻ��� "+war["building_"]+" �������\n\n");

	score  = war["building"]  * 10 + war["enemy"]  * 5 + war["npc"] *1 + war["room"] /10;
	score_ = war["building_"] * 10 + war["enemy_"] * 5 + war["npc_"]*1 + war["room_"]/10;

	if( score > score_ ) {
		shout("����ж�"+full_kingdom(id)+"Ӯ�����ⳡս����\n");
		write("����ж�"+full_kingdom(id)+"Ӯ�����ⳡս����\n");
		gold = (score - score_) * 1000;
		shout(full_kingdom(enemy_id)+"�����⳥"+full_kingdom(id)+" "+gold+" ö��ҡ�\n\n");
		write(full_kingdom(enemy_id)+"�����⳥"+full_kingdom(id)+" "+gold+" ö��ҡ�\n\n");
		kingdom_data(id, "data", "add", "gold", gold);
		kingdom_data(enemy_id, "data", "sub", "gold", gold);
	} else if( score < score_ ) {
		shout("����ж�"+full_kingdom(enemy_id)+"Ӯ�����ⳡս����\n");
		write("����ж�"+full_kingdom(enemy_id)+"Ӯ�����ⳡս����\n");
		gold = (score_ - score) * 1000;
		shout(full_kingdom(id)+"�����⳥"+full_kingdom(enemy_id)+" "+gold+" ö��ҡ�\n\n");
		write(full_kingdom(id)+"�����⳥"+full_kingdom(enemy_id)+" "+gold+" ö��ҡ�\n\n");
		kingdom_data(id, "data", "sub", "gold", gold);
		kingdom_data(enemy_id, "data", "add", "gold", gold);
	} else {
		shout("����ж�"+full_kingdom(id)+"��"+full_kingdom(enemy_id)+"����ʤ����\n");
		write("����ж�"+full_kingdom(id)+"��"+full_kingdom(enemy_id)+"����ʤ����\n");
	}

	kingdom_data(id, "war", "del", enemy_id);
	kingdom_data(enemy_id, "war", "del", id);

	return ;
}

int help(object me)
{
        write(@HELP

ָ���ʽ : declare <war/peace/hate/forgive> with <����> - ������ר��
           declare              ���Լ����ҵ�ս��״����
           declare <kingdom>    ��ĳ�����ҵ�ս��״����
                                                                                
���ָ����Ժ�����������ս/̸��/����/������ӡ�
��������κβ������Ϳ��Կ������ҵ�ս��״����
                                                                                
���������ҷ���Ħ��ʱ, �����ȶԶԷ����������Ա�ﲻ��, �� A ����ʼ��
�� B ��ʱ, AB �����Ĺؿ���ȫ��ԶԷ���������, �� A ����ս���������
������ B ������, �� B �������ﱻ A �������� B ����������ʱ, ս���ȡ
�߸�����Ļ��ǡ��ڵ���״̬��, A �����ù��� B ���Ĺؿ��ͽ����
                                                                                
����״̬������ declare forgive with <����> �����
                                                                                
��������ϵ���ӵ����뷢��ȫ����ս��ʱ, ��������뻥����ս�Խ���ս��
״̬��
                                                                                
�����������, ��ս�Ĺ��ʷ�ʽ�� : �ȵ���ս����Է��Ĺ������, ��
�ȴ��Է��Ļ���, ����Է�һֱ����Ӧ, ��ô���޷�����ս��״̬��ֻҪ��
�뽻ս״̬, ս���Ϳ�����ʱ������һ��������������ս����, ˫��������
�Ĺؿ��������������ȫ������˴˵Ĳ���, ����һ������Ա�򲿶ӽ����
������, �����⵽�Է����²��ӵ���������, ˫�����Կ�������Է�������
��ݻٽ�����õ�ʤ������, �ڶ�������(��ʵʱ��Լ 2-3 Сʱ)��ս������
��, ϵͳ��ͳ��˫��ʤ������������ʤ����һ���������ս���У�ս��˫��
�˴�����ս��һ�Σ���ս���ĳ���ʱ�������ӳ�����(��ʵʱ��Ϊ����Сʱ)��
                                                                                
δ���ϴ�½�Ĺ��Ҳ��ܶ�����������ս����ӡ�
                                                                                
ս��״̬������˫�� declare peace with <����> ��������ս��״̬ʱ��
���Ҫ��������ս�ܷ�����ϵͳ�Խ���ͳ��ս�������ս�ܵ�һ������Ҫ
�⳥����Ҫ��ͣս��һ����սʤ������ͳ��ս����
                                                                                
ע�� : ��ս�����������˽�ֱ��ͨ��ս���ս������ս���߳ͷ�,
������������ô���ơ������һ�� mob ս��, ������꽫�ᱻ���, ����
�� reboot ǰ�������ٻص�ԭλ����ʵ��, ֻҪ mob ̤������, �������
����ս�������ˡ�

HELP
        );
        return 1;
}       
