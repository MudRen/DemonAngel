//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/actionroom.c
// by bor @RG, 3/5, 2001

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

void move_room(object me, string pre_msg, string post_msg, string file);
int check_ob(object me, mapping action);

object env;

void setup()
{
	seteuid(getuid());
	env = this_object();
	::setup();
}

void init()
{
	mapping act_move;
	string *a_move;

	if( mapp(act_move = env->query("action_move")) && sizeof(act_move)>0 ) {
		a_move = keys(act_move);
		if( sizeof(a_move)>0 ) add_action("action_move", a_move);
	}
}

int action_move(string arg)
{
	mapping action;
	object me = this_player();
	string verb;

	if(!verb = query_verb()) return 0;
	if(!mapp(action = env->query("action_move/"+verb))) return 0;
	// ����ƶ���Ŀ�겻��ȷ
	if(!arg||arg!=action["toward"]) return 0;
	if(action["check_ob"]&&check_ob(me, action)==-1) return 0;
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if(undefinedp(action["msg"])) tell_object(me, "��ͻȻ����һ����ѣ��\n");
	else tell_object(me, action["msg"]+"\n");
	move_room(me, action["pre_msg"], action["post_msg"], action["file"]);
	return 1;
}

// �ƶ����÷���
void move_room(object me, string pre_msg, string post_msg, string file)
{
	if(!me) return ;
	if(undefinedp(pre_msg)) message_vision("$N����ӰͻȻ����һ��, ��ʧ�ˡ�\n", me);
	else message_vision(pre_msg+"\n", me);
	me->start_busy(2);
	call_out("move_to", 2, me, post_msg, file);
	return ;
}

void move_to(object me, string post_msg, string file)
{
	if(!me) return ;
	me->move(file);
	if(undefinedp(post_msg)) message_vision("$N����ӰͻȻ�����ˡ�\n", me);
	else message_vision(post_msg+"\n", me);
	return ;
}

int check_ob(object me, mapping action) // ����������Ƿ�������Ʒ������������
{
	object ob;
	int flag = -1;

	// flag == -1 �����������û�и� ob �Ļ�����Ӧ -1
	foreach(ob in all_inventory(me)) {
		if(base_name(ob)+".c"!=action["check_ob"]) continue;
		flag = 1;
		break;
	}
	return flag;
}
