//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/saveroom.c
// by bor @DA,

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me)
{
	object env;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fight() ) return notify_fail("������ս���С�\n");
	if(!env = environment(me)) return 0;

if( !wizardp(me) ) {
	if( env->query("kingdom_id")!=me->query("kingdom/id") ) return notify_fail("���Ѿ������ҹ�������!!\n");
}
	if( env->query("no_save") || env->query("no_change") )
		return notify_fail("������������趨�����ܴ浵��������ǡ���������쿴��\n");
	do_saveroom(env);
	refresh_room(env);
	write("���䴢����ϡ�\n");
	return 1;
}

int help(object me) {

	write(@HELP

ָ���ʽ : saveroom

���ǹ����������淿�����ʵ�ָ������޸ķ�������������ʱ�������
���ɴ�ָ��ﵽ���淿���Ŀ�ġ�

���ѶϢ : delete_room, makeroom

HELP
	);
	return 1;
}
