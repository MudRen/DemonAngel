//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/join.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int do_time(object me);

int main(object me, string arg)
{
	object ob, obj;

	seteuid(getuid(me));
	if( !arg ) return notify_fail("ָ���ʽ��join <��������>\n");
	if( me->query("kingdom/id") ) return notify_fail("���Ѿ��й����ˣ��ȷ�������������ܼ����������ң�\n");

	if( arg == "cancel" ) {
		if( !objectp(obj = me->query_temp("join")) ) return notify_fail("�����ڲ�û�����κ������������\n");
		write("���������" + obj->name_id(1) + "��������ˡ�\n");
		tell_object(obj, me->name_id(1) + "�ı����ⲻ��������������ˡ�\n");
		me->delete_temp("join");
		return 1;
	}

	if( !(ob = present(arg, environment(me))) || !userp(ob) ) return notify_fail("ָ���ʽ��join <��������>\n");
	if( ob == me ) return notify_fail("�����Լ����������ʲô��\n");
	if( !ob->query("kingdom/minister") && !ob->query("kingdom/king"))
		return notify_fail(ob->name_id()+"���ǹ��塣\n");

	if( !ob->query("kingdom/id") ) return notify_fail("�������ˣ����ҹ�����ǰ��������\n");

	if( me->query("arrest") )
	if( member_array(ob->query("kingdom/id"), me->query("arrest") ) != -1 )
		return notify_fail("�������ù���ͨ���У��޷������\n");

	if( objectp(obj = me->query_temp("join")) ) {
		if( ob = obj ) return notify_fail("�Է����ڿ��ǣ����ü��ż��롣\n");
		else {
			write("��ı����ⲻ��" + obj->name_id(1) + "��������ˡ�\n");
			tell_object(obj, me->name_id(1)+ "�ı����ⲻ��������������ˡ�\n");
		}
	}
	message_vision("$N��$n���������\n", me, ob);
	me->set_temp("join", ob );
	tell_object(ob, YEL"�����Ը����" + me->name_id(1) + "��������� accept " + me->query("id") + "��\n" NOR);
	call_out("do_time_check", 10, me);
	return 1;
}

int do_time_check(object me)
{
	if(!me->query_temp("join")) remove_call_out(do_time(me));
	else call_out("do_time", 6, me);
	return 1;
}

int do_time(object me)
{
	if( me->query_temp("join") ) {
		me->delete_temp("join");
		write("�����ӶԷ�����������\n");
	}
	return 1;
}

int help()
{
        write(@HELP

ָ���ʽ : join <�������� | cancel>
 
���ָ�������������ָ���Ķ��� - ������һ�����ҵĹ������
Ҫ������������Ĺ���.

������;������룬�öԷ���û�������ǰ�Ͽ�ȡ��(cancel)�ɡ�

���ѶϢ : kingdom, kingdoms, rebel

HELP
        );
        return 1;
}
