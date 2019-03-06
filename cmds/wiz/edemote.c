//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/wiz/edemote.c
// modify by bor @ RG,

#pragma optimize
#pragma save_binary

/*
        ����һЩ����Ĺ��ܣ�����ʾ��ʽ
        1. $T �ڶ������ļ��롣
        2. emote ��������˼�Ķ���(chinese)
        3. Ŀǰ es2 �е��趨�벿�ݽ�˵��
                ʹ�� emote ����ҿ����ģ�
                a. myself               ��ָ������ʹ����� emote ʱ�����Լ�������ѶϢ
                b. myself_self          ���Լ�ʹ����� emote ʱ���Լ�������ѶϢ
                c. myself_target        �Ա���ʹ����� emote ʱ���Լ�������ѶϢ
                d. myself_rest          ����ָ���������еڶ�����ʱ���Լ���������ѶϢ

                �Է�������ѶϢ��
                e. target               �Ա���ʹ����� emote ʱ��ʹ�ö��󿴵���ѶϢ
                f. target_self          ��ָ���ض��������еڶ�����ʱ��ʹ�ö�����������ѶϢ
                g. target_rest          ����ָ���������еڶ�����ʱ��ʹ�ö�����������ѶϢ


                �����˿�����ѶϢ��
                h. other                ��ָ������ʹ����� emote ʱ�������˿�����ѶϢ
                i. others_target        �Ա���ʹ����� emote ʱ�������Լ���ʹ�ö����⣬�����˿�����ѶϢ
                j. others_self          ���Լ�ʹ����� emote ʱ�������˿�����ѶϢ
                k. others_rest          ��û��ָ���������еڶ�����ʱ��������˿�����ѶϢ

*/

inherit F_CLEAN_UP;

string tmp;     // ��¼һ��֮ǰд�ģ�����Ҫ���������������� tmp ȡ��

int main(object me, string arg)
{
        mapping emote;

        if( !arg ) return notify_fail("��Ҫ�༭ʲô emote��\n");
        if( sscanf(arg, "-d %s", arg) ) {
                write("ɾ�� emote��" + arg + "\n");
                EMOTE_D->delete_emote(arg);
                return 1;
        }

        // ��ʾĳ�� emote �ĸ����趨
        if( sscanf(arg, "-p %s", arg) ) {
                emote = EMOTE_D->query_emote(arg);
                printf("�ϴ��޸��ߣ�%-25s���ƣ�%s,%s\n", emote["updated"], arg, emote["chinese"] );
                printf("����������������������������������������������������������������������\n"
                "myself :\t%s\nmyself_self :\t%s\nmyself_target :\t%s\nmyself_rest :\t%s\n"
                "target :\t%s\ntarget_self :\t%s\ntarget_rest :\t%s\nothers :\t%s\n"
                "others_target :\t%s\nothers_self :\t%s\nothers_rest :\t%s\n",
                emote["myself"], emote["myself_self"], emote["myself_target"], emote["myself_rest"],
                emote["target"], emote["target_self"], emote["target_rest"],
                emote["others"], emote["others_target"], emote["others_self"], emote["others_rest"]
                );
                return 1;
        }

        emote = EMOTE_D->query_emote(arg);
        emote["updated"] = geteuid(me);

        write("�༭ emote��" + arg + "\n");

        write("ѶϢ�����кü��У��� . ��ʾ�������� ~q ���Ա���ԭ���趨��������һ���趨ȥ��\n");
        write("ѶϢ�п�ʹ�õĲ��������¼��֣�\n");
        write("  $N  �Լ������֡�\n");
        write("  $n  ʹ�ö�������֡�\n");
        write("  $P  �Լ����˳ƴ����ʣ����㡢�㡢����������������\n");
        write("  $p  ʹ�ö�����˳ƴ����ʣ����㡢�㡢����������������\n");
        write("  $T  �ڶ�������ʹ�á�\n");
        write("����������������������������������������������������������������������\n");
        log_file("emote", sprintf("[%s]%s edemote %s\n", ctime(time()), geteuid(me), arg ) );
        printf("��Ŀ��chinese����������� emote �������������ĸ�������Ϊ�ޣ�\n\t��ԭ���趨����%s\n->", undefinedp(emote["chinese"])?"":emote["chinese"] );
        tmp = emote["chinese"];         // ��ȡ�����ϣ����ⱻ����
        input_to("input_chinese", emote, arg);
        return 1;
}

private int
input_chinese(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["chinese"] = tmp;
                if( strlen(msg)>8 ) {
                        write("emote �������������ĸ�������Ϊ�ޣ�\n");
                        input_to("input_chinese", emote, pattern);
                        return 1;
                }
                printf("��Ŀ��myself������ָ������ʹ����� emote ʱ�����Լ�������ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["myself"])?"":emote["myself"] );
                tmp = emote["myself"];
                input_to("get_msg_myself", emote, pattern);
                return 1;
        }
//      if( !undefinedp(emote["chinese"]) )
//              emote["chinese"] += msg + "\n";
//      else emote["chinese"] = msg;
        emote["chinese"] = msg +"\n";
        write("->");
        input_to("input_chinese", emote, pattern);
        return 1;
}

private int
get_msg_myself(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself"] = tmp;
                printf("��Ŀ��others������ָ������ʹ����� emote ʱ�������˿�����ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["others"])?"":emote["others"] );
                tmp = emote["others"];
                input_to("get_msg_others", emote, pattern);
                return 1;
        }

        emote["myself"] = msg +"\n";
        write("->");
        input_to("get_msg_myself", emote, pattern);
        return 1;
}

private int
get_msg_others(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["others"] = tmp;
                printf("��Ŀ��myself_self�������Լ�ʹ����� emote ʱ���Լ�������ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["myself_self"])?"":emote["myself_self"] );
                tmp = emote["myself_self"];
                input_to("get_msg_myself_self", emote, pattern);
                return 1;
        }
        emote["others"] = msg +"\n";
        write("->");
        input_to("get_msg_others", emote, pattern);
        return 1;
}

private int

get_msg_myself_self(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself_self"] = tmp;
                printf("��Ŀ��others_self�������Լ�ʹ����� emote ʱ�������˿�����ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["others_self"])?"":emote["others_self"] );
                tmp = emote["others_self"];
                input_to("get_msg_others_self", emote, pattern);
                return 1;
        }
        emote["myself_self"] = msg +"\n";
        write("->");
        input_to("get_msg_myself_self", emote, pattern);
        return 1;
}

private int
get_msg_others_self(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["others_self"] = tmp;
                printf("��Ŀ��myself_target�����Ա���ʹ����� emote ʱ���Լ�������ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["myself_target"])?"":emote["myself_target"] );
                tmp = emote["myself_target"];
                input_to("get_msg_myself_target", emote, pattern);

                return 1;
        }
        emote["others_self"] = msg +"\n";
        write("->");
        input_to("get_msg_others_self", emote, pattern);
        return 1;
}

private int
get_msg_myself_target(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself_target"] = tmp;
                printf("��Ŀ��target�����Ա���ʹ����� emote ʱ��ʹ�ö��󿴵���ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["target"])?"":emote["target"] );
                tmp = emote["target"];
                input_to("get_msg_target", emote, pattern);
                return 1;
        }
        emote["myself_target"] = msg +"\n";
        write("->");
        input_to("get_msg_myself_target", emote, pattern);
        return 1;
}

private int
get_msg_target(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["target"] = tmp;
                printf("��Ŀ��others_target�����Ա���ʹ����� emote ʱ�������Լ���ʹ�ö����⣬�����˿�����ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["others_target"])?"":emote["others_target"] );
                tmp = emote["others_target"];
                input_to("get_msg_others_target", emote, pattern);
                return 1;
        }
        emote["target"] = msg +"\n";
        write("->");
        input_to("get_msg_target", emote, pattern);
        return 1;
}

private int
get_msg_others_target(string msg, mapping emote, string pattern)
{
	if(msg=="." || msg=="~q") {
		if(msg=="~q") emote["others_target"] = tmp;
		else if( emote["others_target"] ) emote["others_target"] += "\n";
		printf("��Ŀ��myself_rest��������ָ���������еڶ�����ʱ���Լ���������ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["myself_rest"])?"":emote["myself_rest"] );
		tmp = emote["myself_rest"];
		input_to("get_msg_myself_rest", emote, pattern);
		return 1;
	}
	if( !undefinedp(emote["others_target"]) )
		emote["others_target"] += msg + "\n";
	else emote["others_target"] = msg;
	write("->");
	input_to("get_msg_others_target", emote, pattern);
	return 1;
}

private int
get_msg_myself_rest(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["myself_rest"] = tmp;
                printf("��Ŀ��target_self������ָ���ض��������еڶ�����ʱ��ʹ�ö�����������ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["target_self"])?"":emote["target_self"] );
                tmp = emote["target_self"];
                input_to("get_msg_target_self", emote, pattern);
                return 1;
        }
        emote["myself_rest"] = msg +"\n";
        write("->");
        input_to("get_msg_myself_rest", emote, pattern);
        return 1;
}

private int
get_msg_target_self(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["target_self"] = tmp;
                printf("��Ŀ��target_rest��������ָ���������еڶ�����ʱ����ָ��������������ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["target_rest"])?"":emote["target_rest"] );
                tmp = emote["target_rest"];
                input_to("get_msg_target_rest", emote, pattern);
                return 1;
        }
        emote["target_self"] = msg +"\n";
        write("->");
        input_to("get_msg_target_self", emote, pattern);
        return 1;
}

private int
get_msg_target_rest(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {

                if(msg=="~q") emote["target_rest"] = tmp;
                printf("��Ŀ��others_rest������û��ָ���������еڶ�����ʱ�����е��˿�����ѶϢ��\n\t��ԭ���趨����%s\n->", undefinedp(emote["others_rest"])?"":emote["others_rest"] );
                tmp = emote["others_rest"];
                input_to("get_msg_others_rest", emote, pattern);
                return 1;
        }
        emote["target_rest"] = msg +"\n";
        write("->");
        input_to("get_msg_target_rest", emote, pattern);
        return 1;
}

private int
get_msg_others_rest(string msg, mapping emote, string pattern)
{
        if(msg=="." || msg=="~q") {
                if(msg=="~q") emote["others_rest"] = tmp;
                EMOTE_D->set_emote(pattern, emote);
                write("Emote "+pattern+" �༭������\n");
                return 1;
        }
        emote["others_rest"] = msg +"\n";
        write("->");
        input_to("get_msg_others_rest", emote, pattern);
        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��edemote [-d|-p] <emote>
 
���ָ������޸�, ɾ�� emote ���г�������. ���� -d ������ɾ��
ָ���� emote, -p ��������г�ָ�� emote ������. �г���˳�����
�� emote ʱ��ͬ.
 
���� emote ѶϢʱ��������Ŀ: û��Ŀ��, ָ��Ŀ����Ƕ��Լ�. ��
������ĳ��ѶϢ, ��ֱ���ڿհ������� '.' ����.
 
һ�� emote ѶϢ�����кܶ���, �ڿհ������� '.' ����������� emote.
 
�༭ emote ʱ���������µķ�������ʾ:
 
$N : �Լ�������.
$n : Ŀ�������.
$P : �Լ����˳ƴ�����.
$p : Ŀ����˳ƴ�����.
$T : �ڶ�������


��Ӣ�Ĵ���Ľ�˵��

                ʹ�� emote ����ҿ����ģ�
                a. myself               ��ָ������ʹ����� emote ʱ�����Լ�������ѶϢ
                b. myself_self          ���Լ�ʹ����� emote ʱ���Լ�������ѶϢ
                c. myself_target        �Ա���ʹ����� emote ʱ���Լ�������ѶϢ
                d. myself_rest          ����ָ���������еڶ�����ʱ���Լ���������ѶϢ

                �Է�������ѶϢ��
                e. target               �Ա���ʹ����� emote ʱ��ʹ�ö��󿴵���ѶϢ
                f. target_self          ��ָ���ض��������еڶ�����ʱ��ʹ�ö�����������ѶϢ
                g. target_rest          ����ָ���������еڶ�����ʱ��ʹ�ö�����������ѶϢ

                �����˿�����ѶϢ��
                h. other                ��ָ������ʹ����� emote ʱ�������˿�����ѶϢ
                i. others_target        �Ա���ʹ����� emote ʱ�������Լ���ʹ�ö����⣬�����˿�����ѶϢ
                j. others_self          ���Լ�ʹ����� emote ʱ�������˿�����ѶϢ
                k. others_rest          ��û��ָ���������еڶ�����ʱ��������˿�����ѶϢ


HELP
        );
        return 1;
}
