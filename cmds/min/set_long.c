//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/set_long.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>

int main(object me, string arg)
{
	object env;
	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !env = environment(me)) return notify_fail("�Ҳ���������\n");
	if( env->query("no_change") ) return notify_fail("���ﲻ�ܱ����������ϡ�\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id")!=me->query("kingdom/id") ) return notify_fail("���ﲻ���ҹ��������\n");

	me->edit( (: call_other, __FILE__, "do_change", me :) );
	return 1;
}

void do_change(object me, string str)
{
	string *str_arg;

	str = ansi_color( str );

	if( strlen(str) > 8000 ) {
		write("��Ĳ���̫���ˡ�\n");
		return;
	}
	str_arg = explode(str, "\n");

	if( sizeof(str_arg) > 10 ) {
		write("�������ʮ�����ڡ�\n");
		return;
	}
	str = kill_all_bug(str);
	environment(me)->set("long", str);
	write("ok!\n");

	do_saveroom(environment(me));
	return ;
}

int help()
{
	write(@HELP

ָ���ʽ��set_long

���ǹ����������η���������ָ�

HELP
        );
        return 1;
}
