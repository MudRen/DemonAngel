//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/undefend.c
// by bor @DA,

inherit F_CLEAN_UP;

#include <ansi.h>

int main(object me, string arg)
{
	object ob;

	seteuid(getuid());
	if(!arg) return notify_fail("ָ���ʽ : undefend <����>\n");
	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("����û������ˡ�\n");
	if( member_array(ob, me->query_guarding()) == -1 )
		return notify_fail("�����ڲ�û�б����κ��ˡ�\n");

	me->sub_guard(ob);
	message_vision(HIY"$Nֹͣ����$n��\n"NOR, me, ob);
	return 1;
}

int help (object me)
{
	write(@HELP

ָ���ʽ : undefend <����>

������Ѿ����뱣��ĳ����, ����������ָ��ֹͣ������.

���ѶϢ : defend, party, kill. 

 
HELP
	);
	return 1;
}
