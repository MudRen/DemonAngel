//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/npc/demogorgon.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name( HIW "����" NOR, ({ "ghost king" }) );
	set("long",
		"������������ư���վ������ǰ�����ߴ��������һ��������Ϣ��\n"
		"����ɱ����ѹ���㼸����������������������ƺ���һ�������ڸ�\n"
		"���㣺�� �� �� ������\n");

	set("level", 100);
	setup();
}

void start_shutdown(int min)
{
	if( geteuid(previous_object()) != ROOT_UID ) return;
	message("system", HIY"�� Mud ���� "+min+" ���Ӻ�����������\n"NOR, users() );
	call_out("countdown", 60, 1);
}

private void countdown(int min)
{
	object link_ob;
	min--;

	if( min ) {
		message("system" ,HIY"�� Mud ���� "+min+" ���Ӻ�����������\n"NOR, users() );
		call_out("countdown", 60, min);
	} else {
		message("system" ,"��Ϸ�������������Ժ�һ������ login ��\n", users() );
		foreach(object user in users()) {
			if( !objectp(user) ) continue;
			if( !environment(user) ) continue;
			user->set("startroom", base_name(environment(user)));
			user->set("last_on", time());
			user->save();
			if( objectp(link_ob = user->query_temp("link_ob")) )
				link_ob->save();
			reset_eval_cost();
		}
		shutdown(0);
	}
}
