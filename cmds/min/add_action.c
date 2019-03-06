//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/add_action.c
// by bor @DA

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int check_verb(object env, string type, string verb);
varargs void cancel_verb(object env, string type, string verb);
void add_move_verb(object env, string type, string verb, string par);

int main(object me, string arg)
{
	object env;
	string type, verb, par;

	seteuid(getuid());
	if(!arg) return notify_fail("ָ���ʽ : add_action <������̬> <������> <����>\n");
	if(!env = environment(me)) return 0;
	if(!env->query("kingdom_id")||!me->query("kingdom/id")||env->query("kingdom_id")!=me->query("kingdom/id")) return notify_fail("���ﲻ�ǹ���Ĺ�����\n");
	if( env->query("type")!="normal"&&env->query("type")!="actionroom") return notify_fail("���������⽨������ܼ��붯����!!\n");
	if(sscanf(arg,"%s %s %s", type, verb, par)!=3 ) return notify_fail("ָ���ʽ : add_action <������̬> <������> <����>\n");

	switch(type) {
		case "-d":	// verb �༴ type, par ���� verb
			if(!check_verb(env, verb, par)) return notify_fail("���ﲢû�����������!!\n");
			cancel_verb(env, verb, par);
		break;
		case "move":
			if(check_verb(env, type, verb)) return notify_fail("�����Ѿ��иö�������!!\n");
			if( !env->query("exits/"+par) ) return notify_fail("û��������򣬲�������\n");
			add_move_verb(env, type, verb, par);
		break;
		default:
			return notify_fail("Ŀǰ������ "+type+" �Ķ������͡�\n");
	}
	refresh_room( env );
	return 1;
}

// �ȼ�黷���Ƿ��иö�����
int check_verb(object env, string type, string verb)
{
	if( env->query("action_"+type) && env->query("action_"+type+"/"+verb) ) return 1;
	else return 0;
}

// ȡ��ĳ�������ʣ�Ŀǰֻ�ܿ� action_move
varargs void cancel_verb(object env, string type, string verb)
{
	if(env->query("action_"+type+"/"+verb+"/dir")) env->add("exits/"+env->query("action_"+type+"/"+verb+"/dir"), env->query("action_"+type+"/"+verb+"/file"));
	if(env->query("action_"+type+"/"+verb)) map_delete(env->query("action_"+type), verb);
	if(zerop(env->query("action_"+type))) env->delete("action_"+type);

	printf("��ȡ�� " + verb + " ��������ʡ�\n");
	if(!env->query("action_move")) env->set("type", "normal");
	do_saveroom(env);
	return ;
}

// ���� action_move �Ķ�����̬
void add_move_verb(object env, string type, string verb, string par)
{
	verb = kill_all_bug(verb);
	env->set("action_"+type+"/"+verb+"/dir", par);
	env->set("action_"+type+"/"+verb+"/toward", par);
	env->set("action_"+type+"/"+verb+"/file", env->query("exits/"+par));
	map_delete( env->query("exits"), par);
	if(env->query("type")!="actionroom") env->set("type", "actionroom");
	do_saveroom(env);
	printf("������ "+verb+" ��������ʡ�\n");
	return ;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : add_action <������̬> <������> <����>	: ���Ӷ�����
           add_action -d <������̬> <����>		: ɾ��ĳ������, ��ԭ����

������̬��Ŀǰ��Ϊ: move

���磺����Ҫ��һ��ָ����� jump tree �����Դ�һ�������ƶ�����һ�����䣬�ﵽ������
	Ч����������´� add_action move jump north��

	��˵��
		1. move ������ѡ���Ķ�����̬����ΪĿǰֻ���� move�����Ԇ� @@
		2. jump ������ѡ�Ķ����ʡ�
		3. ����Ϊ north��Ϊʲô��ֱд�� tree ??����ʵ���ϵĲ���Ӧ���� tree
		   ��û��ģ�����ʵ���ϣ����Ǳ���ָ�������򡱲�֪�������������δ���
		   �����Ҫ���������� tree�����Ҫ�� set_action ������ˡ�

	�����ոյ� action �������´� add_action -d move jump��

���ѶϢ : set_action

HELP
	);
	return 1;
}
