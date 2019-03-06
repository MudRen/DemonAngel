//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/delete_mob.c
// by bor @DA, 5/23 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me,string arg)
{
	object env, ob;
	mapping room;
	int flag = -1;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ��delete_mob <NPC>\n");
	if( !env = environment(me)) return notify_fail("�Ҳ���������\n");
 
	if( !me->query("kingdom/id") || !env->query("kingdom_id")
	|| env->query("kingdom_id") != me->query("kingdom/id")
	) return notify_fail("���ﲻ�ǹ�������ء�\n");

	if( !objectp(ob = present(arg, env)) ) return notify_fail("û���������!\n");
	if( ob->query_temp("barracks") ) return notify_fail("���Ƚ������Ӫ��״̬, �������������!!\n");
       
	if( env->query("objects") && mapp(room = env->query("objects"))  ) {
		foreach(string npc, int tmp in room) {
			if( file_size(npc+".c")==-1 ) continue;
			if( npc != base_name(ob) ) continue;
			flag = 1;
			break;
		}
	}
	message_vision("$N˫��һ��, ��$n��������С�\n", me, ob);
	if( flag == 1) {
		map_delete(room, base_name(ob));
		env->set("objects", room);
		rm( full_name(ob) );
		do_saveroom(env);
		refresh_room(env);
	} else {	// ��� NPC �� home ���ڱ��񷿼�, ��ô������ NPC ���ϵ�"home" ȥ׷��ԭ�ȵ� env
		object new_env;
		if( !(new_env = find_object( ob->query("home") )) ) {
			call_other(ob->query("home"), "create_room");
			new_env = find_object( ob->query("home") );
		}
		if( new_env->query("objects") && mapp(room = new_env->query("objects"))  ) {
			foreach(string npc, int tmp in room) {
				if( file_size(npc+".c")==-1 ) continue;
				if( npc != base_name(ob) ) continue;
				flag = 1;
				break;
			}
		}
		if( flag == 1) {
			map_delete(room, base_name(ob));
			new_env->set("objects", room);
			rm( full_name(ob) );
			do_saveroom(new_env);
			refresh_room(new_env);
		}
	}
	if( flag==1) {
		kingdom_data(me->query("kingdom/id"), "data", "sub", "npc", 1);
		kingdom_data(me->query("kingdom/id"), "data", "add", "npc_num", 1);
	}
	destruct(ob);
        return 1;       
}

int help(object me)
{
        write(@HELP
ָ���ʽ��delete_mob <who>
���ǹ�������������ɾ����ָ��

HELP
        );
        return 1;
}
