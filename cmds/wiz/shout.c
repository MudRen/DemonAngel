//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/shout.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !wizardp(me) ) return notify_fail("Ŀǰ�ݲ�������� shout��\n");

	if (!arg) return notify_fail("ָ���ʽ��shout <ѶϢ>\n");
	shout(HIY"��"HIR"��Ҫ�㲥"NOR+HIY"��" + me->name(1) + WHT"(" + capitalize(me->query("id")) + ")��"HIM + arg + "\n"NOR);
	write(HIY"��"HIR"��Ҫ�㲥"NOR+HIY"��" + me->name(1) + WHT"(" + capitalize(me->query("id")) + ")��"HIM + arg + "\n"NOR);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��shout <ѶϢ>

���ָ�����㽫 <ѶϢ> ���ͳ�ȥ������������Ϸ�е��˶���������Ļ���

HELP
	);
	return 1;
}

