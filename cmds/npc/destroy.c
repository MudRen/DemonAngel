//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/destroy.c
// by bor @DA, 3/7 2003
// actionroom �ڱ��ƻ�����ô�� action ? �п������
// 

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
inherit "/cmds/min/declare";			// ����������ʹ��

#include <ansi.h>

int main(object me, string arg)
{
	string id, enemy_id;
	object env, ob, *inv;
	int money;

	seteuid(getuid());
	if(arg) return notify_fail("�㲻���ƻ��Ǹ�����!!\n");
	if(!(id= me->query("kingdom/id"))) return notify_fail("�޹����������ƻ���\n");
	if(!objectp(env = environment(me))) return notify_fail("����Ļ������ڿ��顣\n");
	if( !(enemy_id = env->query("kingdom_id")) ) return notify_fail("������ϵͳ������ !!");
	if( enemy_id == id ) return notify_fail("�����ѹ��� ?\n");
	if(!kingdom_data(id, "war", "check")) return notify_fail("���Ŀǰû���κ�һ��ս������!!\n");
	if(!kingdom_data(id, "war", "check", enemy_id, 1)) return notify_fail("���û�к͸ù���ս����\n");
	if(env->query_temp("destroy")) return notify_fail("�����Ѿ����ƻ�һ�ա�\n");

	if( env->query("type")=="normal"&&env->query("no_delete")==1 ) { // ����÷���Ϊ����
		if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
		if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");

		// ��������� guard , ��ô�����Ƶ��˲����ƻ��Ļ�
		inv = all_inventory(env);
		for(int i=0; i<sizeof(inv); i++) { // ���÷����Ƿ��е��˵� mob�����������ƻ�
			if( inv[i]->query("kingdom")&& kingdom_data(id, "war", "check", inv[i]->query("kingdom"), 1) )
				return notify_fail("���ﻹ�е��˴���, �޷����ս�����!!\n");
		}

		message_vision("[1;30m$N�����ѽ�������մ�����[m\n", me);
		money = 1300 + random(500);
		message_vision("[1;30m$N����ĵ����ѹ�, �ѳ� "+money+" ö��ҡ�[m\n", me);
		env->add_temp("destroy_normal", 1); // ÿ������һ��ֱ�� 5���ͱ���ͣս
		me->got_money(money);
		me->add("war_score/gold", money);

		kingdom_data(id, "war", "add", enemy_id, ({"gold", money}));
		kingdom_data(enemy_id, "war", "add", id, ({"gold_", money}));

		kingdom_data(enemy_id, "data", "sub", "gold", money);

		for(int i=0;i<2;i++) {
			// ���ݻ�������������, ˳�㿴Ҫ��ɶ��Ѷ... ����, ��������ո����ҵ�ĳ��չ�������� npc �� level
			// �������ڴ˲���ȥ
			ob = new("/d/obj/npc/guard_1.c");
			ob->set("kingdom", enemy_id);
			ob->move(env);
		}
		message_vision("$N�������ڳ�������������ķ��ߡ�\n", ob);
		if( env->query_temp("destroy_normal")>=5 ) {
			env->set_temp("destroy", 1);
			me->add("war_score/building", 1);
			kingdom_data(id, "war", "add", enemy_id, ({"building",1}) );
			kingdom_data(enemy_id, "war", "add", id, ({"building_",1}) );

			shout(HIR+full_kingdom(id)+"ǿ�й���"+full_kingdom(enemy_id)+"������"+NOR+"\n\n");
			write(HIR+full_kingdom(id)+"ǿ�й���"+full_kingdom(enemy_id)+"������"+NOR+"\n\n");
			call_out("do_wait_war_end", 0, id, enemy_id);
		}
//	} else if() {	// ���⽨������ж�, Ŀǰ���ṩ, ���п��Լ�����ȥ
	} else {	// ������һ�㷿��
		env->set_temp("destroy", 1);
		message_vision("[1;30m$N�����ѽ�������մ�����[m\n", me);
		kingdom_data(id, "war", "add", enemy_id, ({"room",1}) );
		kingdom_data(enemy_id, "war", "add", id, ({"room_",1}) );
		me->add("war_score/room", 1);
	}
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : destroy

���Ǵݻٽ�ս���������ָ������������ָ��Է��Ľ�����������
���̶Ƚ��з��������������и���������������㡣������ֻҪ���ܿ˷�һ
���ϰ�����Ϳ��ԶԷ��Ľ������𻵣������ѹε�һ���Ǯ���ݻٽ������
����Ĺ��Ҵ�������սʤ����������ʹ�з��Ĺ���������ʧ����Ȼ�����ս
����ս��Ҳ����ļ���һ�ʡ�

���⣬���������췿��Ҳ���������ָ�������ֻ��û��ս��Ҳ�Ѳ���Ǯ��
��Щ�ǽ�����ķ��䱻�ݻٺ����޸�������һ�� reboot ��ͻ�ָ�������

����նɱ���˻�ݻٵз��������, ����������ս������, ��Щ�������
������������������������������ڹ��ڵ�Ӣ�ۻ������ show ����ѯ��
���ۻ���ս�����顣

�����Ľ�����ս���б��ݻ٣�������� set_room �е� repair �Ĳ�����
�����޺á�

���ѶϢ : kill, kingdoms, declare, set_room

HELP
	);
	return 1;
}
