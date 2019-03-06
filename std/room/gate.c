//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/gate.c
// by amgbell @DA, 

inherit ROOM;
#include <ansi.h>

object env = this_object();

void setup()
{
	seteuid(getuid());
	::setup();
}

void init() {

	int change=0;

	add_action("do_limit","limit");


	if (!query("long") || query("long")=="0\n" || query("long")=="0\n\n") {
		set("long",@LONG
������һ���ؿ���·���Ը�����һ������ڣ�·���뻹���ž�������
��ǹִ��������������վ�Լ�����ˣ������������չ�·˰��
LONG);
	change=1;
}

	if (!query("short")) {
		set("short","�ؿ�");
		change=1;
	}

	if (!query("limit/pass"))  set("limit/pass","all");

}

int do_limit(string arg){

	string *exits,*limits;
	object me;

	me=this_player();
	exits=(keys(environment(me)->query("exits")));
	limits=({"king_only","minister_only","civil_only","ally_only","all"});
        

	if (!me->query("kingdom/king")) return notify_fail("What��\n");
	if (query("kingdom_id")!=me->query("kingdom/id")) return notify_fail("What��\n");

	if (!arg) {
		write("Ŀǰ���ؿ������� : "+query("limit/pass")+"\n" );
		write("���Ƶķ��� : "+query("limit/exit")+"\n");
		return 1;
	}

	if (member_array(arg,exits)!=-1) {
		environment(me)->set("limit/exit",arg);
		do_saveroom(environment(me));
		write("ok!\n");
		return 1;
	}

	if (member_array(arg,limits)!=-1) {
		environment(me)->set("limit/pass",arg);
		do_saveroom(environment(me));
		write("ok!\n");
		return 1;
	}


	return notify_fail(@TEXT
	limit ��ָ���ʽ���� :

	limit               ����Ŀǰ���վ���޶�״̬
	limit <����>        �趨���ĸ��������Ҫ���
	limit <��������>    �趨���������Ŀ���
TEXT);
}

int valid_leave(object me, string dir)	// by bor @DA
{
	if( wizardp(me) ) {
		printf(HIC"[�ؿ�]-> ����: %s, ����: %s\n"NOR, env->query("limit/pass"), env->query("limit/exit") );
		return 1;
	}

	if( !env->query("limit/exit")
	|| dir != env->query("limit/exit")
	) return ::valid_leave(me, dir);

	if( env->query("limit/pass")=="all" ) {	// û�����ƵĹؿ�, ������˰
		int gold;
		gold = kingdom_data(env->query("kingdom_id"), "data", "query_par", "tax");
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") ) {
			if(!me->can_afford(gold) ) return notify_fail("���Ǯ��������˰��\n");
			message_vision("$N���� "+gold+" ö��Һ�ͨ������ڡ�\n", me);
			me->pay_money(gold);
			kingdom_data(env->query("kingdom_id"), "data", "add", "gold", gold);
		}
	} else if( env->query("limit/pass")=="king_only" ) {
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") )
			return notify_fail("����ֻ׼��������ͨ����\n");
		else {
			if( !me->query("kingdom/king") ) return notify_fail("����ֻ׼��������ͨ����\n");
		}
	} else if( env->query("limit/pass")=="minister_only" ) {
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") )
			return notify_fail("����ֻ׼������ͨ����\n");
		else {
			if( !me->query("kingdom/minister") && !me->query("kingdom/king") )
				return notify_fail("����ֻ׼������ͨ����\n");
		}
	} else if( env->query("limit/pass")=="ally_only" ) {
		if( !me->query("kingdom/id") ) return notify_fail("����ֻ׼ͬ�˹�ͨ����\n");
		if( me->query("kingdom/id")!=env->query("kingdom_id") ) {
			if(!kingdom_data(env->query("kingdom_id"), "ally","check", me->query("kingdom/id")))
				return notify_fail("����ֻ׼ͬ�˹�ͨ����\n");
		}
	} else if( env->query("limit/pass")=="civil_only" ) {
		if( !me->query("kingdom/id") || me->query("kingdom/id")!=env->query("kingdom_id") )
			return notify_fail("����ֻ׼��������ͨ����\n");
	}
	return ::valid_leave(me, dir);
}
