//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/defend.c
// by bor @DA, 3/17 2003

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
	object ob;

	if( !arg ) return notify_fail("ָ���ʽ��defend <ĳ��>��\n");

	if( !objectp(ob = present(arg, environment(me))) )
		return notify_fail("����û�� " + arg + "��\n");

	if( !ob->is_character() ) return notify_fail("��û�취��������\n");

	if( ob == me ) return notify_fail("���ñ����Լ� !!\n");

	me->guard_ob(ob);
	message_vision(HIY"$N�ƶ���$nǰ��, ��$n���ܹ�����\n"NOR, me, ob);
	return 1;
}

int help (object me)
{
	write(@HELP

ָ���ʽ : defend <����>

���ָ��������㱣�����ͬ��, �����ж�����ֱ�ӹ�������
����, ���� �Է����ԵĹ���ȴ�ﲻ��æ��. ��������ͬʱ��
���ĸ���, ����, ���� ����Խ���Խ���׷��ġ�����Ա�����
�������(mob) ������Ҫ�ȵ����� Ӣ���Ժ�

���ѶϢ : undefend, kill, party

 
HELP
	);
	return 1;
}
