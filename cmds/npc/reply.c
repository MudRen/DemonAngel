//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// reply.c

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string target, mud;
	object obj;

	if( !arg || arg=="" )
		return notify_fail("��Ҫ�ش�ʲô��\n");

	if( !stringp(target = me->query_temp("reply")) )
		return notify_fail("�ղ�û���˺���˵������\n");

	if( sscanf(target, "%s@%s", target, mud)==2 ) {
		GTELL->send_gtell(lower_case(mud), lower_case(target), me, arg);
		write("��·ѶϢ���ͳ�������Ҫ�Ժ���ܵõ���Ӧ��\n");
		return 1;
	}

	obj = find_player(target);
	if( !obj )
		return notify_fail("�ղź���˵�����������޷������㣬�����Ѿ��뿪��Ϸ�ˡ�\n");
	write(GRN "��ش�" + obj->name(1) + "��" + arg + "\n" NOR);
	tell_object(obj, sprintf(GRN"%s�ش��㣺%s\n"NOR,
		me->name(1), arg ));

	obj->set_temp("reply", me->query("id"));
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��reply <ѶϢ>

����������ָ��͸ղ��� tell ����˵����ʹ����˵����

see also : tell
HELP
	);
	return 1;
}
