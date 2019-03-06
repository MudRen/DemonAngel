//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/set_action.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;
int show_action(object me);
int check_verb(object env, string type, string verb);
int move_set(object env, string type, string verb, string par, string set);

string *action_type = ({"move"});
string *move_type = ({"check_ob", "toward", "pre_msg", "msg", "post_msg"});

int main(object me, string arg)
{
	object env;
	string type, verb, par, set;

	seteuid(getuid());
	if(!env = environment(me)) return 0;

	if( !env->query("kingdom_id")
	|| env->query("kingdom_id")!=me->query("kingdom/id")
	) return 0;

	if(!arg) {
		show_action(me);
		return 1;
	}

	if(sscanf(arg,"%s %s %s %s", type, verb, par, set)!=4 )
		return notify_fail("ָ���ʽ��set_action <��������> <������> <����> <��������ֵ>\n");

	switch(type) {
		case "move":
			if(!check_verb(env, type, verb)) return notify_fail("���ﲢû�����������!!\n");
			if( member_array(par, move_type) == -1 ) return notify_fail("û�������Ĳ�����̬��\n");
			move_set(env, type, verb, par, set);
		break;
		default:
			return notify_fail("Ŀǰ������ "+type+" ��̬�Ķ������͡�\n");
	}
	return 1;
}

int show_action(object me)
{
	object env;
	string str, _action, __action, tmp;

	env = environment(me);
	if(env->query("type")!="actionroom") {
		write("�������û�ж����ʡ�\n");
		return 1;
	}
	str = "��������еĶ������У�\n\n";
	if(env->query("action_move")&&sizeof(keys(env->query("action_move")))>0) {
		str += sprintf("action_move �Ķ����ʰ�����\n");
		foreach(_action, tmp in env->query("action_move")) {
			str += sprintf(_action+"\n");
			foreach(__action, tmp in env->query("action_move/"+_action)) {
				if(__action=="file") continue;
				if(__action=="dir" ) str += sprintf("\tʵ�ʷ���   : "+tmp+"\n");
				else if(__action=="check_ob") str += sprintf("\t"+__action+"   : ��\n");
				else str += sprintf("\t"+__action+"   : "+tmp+"\n");
			}
			str += "\n";
		}
	}
	me->start_more(str);
	return 1;
}

// �ȼ�黷���Ƿ��иö�����
int check_verb(object env, string type, string verb)
{
	if(!env->query("action_"+type)&&!env->query("action_"+type+"/verb") ) return 0;
	return 1;
}

int move_set(object env, string type, string verb, string par, string set)
{
	object me = this_player(), ob;
	if(par!="check_ob") env->set("action_"+type+"/"+verb+"/"+par, set);
	else {
		ob = present(set, me);
		if(!ob) return notify_fail("������û�����������\n");
		// ���ж��Ƿ�Ϊ�Լ����ҵ���Ʒ
		env->set("action_"+type+"/"+verb+"/"+par, base_name(ob)+".c" );
	}
	tell_object(me, "�㽫 "+par+ " �趨Ϊ "+set+"\n");
	do_saveroom(env);
	refresh_room(env);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : �Է��� set_action <��������> <������> <����> <��������ֵ>

������̬��Ŀǰ��Ϊ move��

���磺����Ҫ��һ��ָ����� jump tree �����Դ�һ�������ƶ�����һ�����䣬�ﵽ������
	Ч����������´� add_action move jump north��

	��˵��
		1. move ������ѡ���Ķ�����̬����ΪĿǰֻ���� move�����Ԇ� @@
		2. jump ������ѡ�Ķ����ʡ�
		3. ����Ϊ north��Ϊʲô��ֱд�� tree ??����ʵ���ϵĲ���Ӧ���� tree
		   ��û��ģ�����ʵ���ϣ����Ǳ���ָ�������򡱲�֪�������������δ���
		   �����Ҫ���������� tree�����Ҫ�� set_action ������ˡ�
		4. ������set_action move jump toward tree����ʱ�Ὣ north ��Ϊ
		   tree���Ժ�Ϳ���ֱ�� jump tree ���ﵽ�Լ���Ҫ��ָ���ˡ�

���ѶϢ : add_action

HELP
	);
	return 1;
}
