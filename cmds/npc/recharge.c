//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/recharge.c
// by bor @DA, 5/25 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
	object ob;
	int cost;

	seteuid(getuid());
	if( !me->query_skill("recharge") ) return notify_fail("�㲻����ӡ�ļ��ܡ�\n");
	if( me->is_busy() ) return notify_fail("����һ��������û��ɡ�\n");
	if( !arg ) return notify_fail("��Ҫ��ħ����ӡ���ģ�\n");
	ob = present(arg, me);
	if( !ob ) return notify_fail("������û������������\n");
	if( ob->query_temp("invoke_times")>=10 )
		return notify_fail(ob->name()+"�Ѿ���������, �����ټ�ǿ�ˡ�\n");

	if( me->query_mp()< 100 ) return notify_fail("��ķ��������Լ�ǿ��ӡ��������\n");

	cost = 45+random(4);
	if( me->query_mp()<cost ) return notify_fail("��ķ��������Լ�ǿ��ӡ��������\n");

	me->add("mp", -cost);
	message_vision(HIY"$N�ķ����������������" + ob->name() + "֮�С�\n"NOR, me);
	me->start_busy(2);
	call_out("recharge", 0, me, ob);
	return 1;
}

int recharge(object me, object ob)
{
	if( ob->query("skill")/23+random(30) > me->query_skill("recharge", 1)*2/3 + me->query_kar()/2 ) {
		ob->add_temp("broken", 20);
		me->add("broken", 20);
		if( ob->query_temp("broken") >= 100 ) {
			message_vision(HIG"$N���е�$n���һ����Ƭ...\n"NOR, me, ob);
			me->delete("broken");
			destruct(ob);
			return 1;
		}
		tell_object(me, ""+ob->name()+"��ž����һ��, ������һ���Ѻ�, ������ӡʧ���ˡ�\n");
		return 1;
	}
	if( ob->query_temp("invoke_times")>=10 ) {
		write(ob->name()+"�Ѿ���������, �����ټ�ǿ�ˡ�\n");
		return 1;
	}
	ob->add_temp("invoke_times", 1);
	me->add("invoke_times", 1);
	message_vision("$N�������˵Ĺ�����, Ȼ�󻺻��ذ���ķ������ս�ȥ��\n"NOR, ob);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : recharge             Ϊ���ϵķ������䷨����
	   recharge <��������>  Ϊ�������䷨����
	   recharge <��������>  ħ��ʿר�ã���ħ��������ͨ�������С�

������� -

    һ��ʩ���߿��������ʵ��ķ��������Լ�����ķ����������У�ʹ����ת��
��ĳ���ض��ķ�����̬�����ڷ����С��Է������ļ����൱��Ҫ�����û�м�
�ܣ��������˷ѷ�����ͬʱҲ���𻵷�������

    ����ħ��ʿ���ڽ����������������У�ʹ�������ܹ�����İ��Լ�֪���ķ�
�����Լ��Ľ���ϣ���������һ��ǿ�����Գ���ħ�������Ľ���ʱ��ɿ��µ�ħ
�����������Ľ����̬��һ��״���ȶ����ڷ��������������ʱ�̣�������ʧ��
Ҳ����ʹ�����𻵣����Ҳֻ�Ǵ���ķ�����ʧ���ѡ�

���ѶϢ : invoke, spells


HELP
	);
	return 1;
}
