//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/charge.c
// by bor @DA, 3/17 2003

// Ŀǰ�ṩ�������ö��ѣ������ְҵ��Ҫ��ָ�������д...
// һʱ���ǣ��ҵ���д�����ǰ����Ƶ����ȥ, ��ô��ָ��Ͳ�������

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object guard, ob;

	if( !me->query("list/pet/file") ) return 0;
	if( !me->query_temp("riding_pet") ) return 0;

	if( !objectp( guard = find_object(me->query("list/pet/file")) ) ) {
		call_other(me->query("list/pet/file"), "???");
		guard = find_object(me->query("list/pet/file"));
	}
	if( !arg || arg=="" ) return notify_fail("��û��ѡ������Ŀ�ꡣ\n");

	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("����û������ˡ�\n");

	if( !me->is_fighting(ob) )
		return notify_fail("��Ŀǰû�к�" + ob->name() + "ս����\n");

	guard->charge_ob(ob);

	return 1;
}

int help(object me)
{
	write(@TEXT

ָ���ʽ : charge <Ŀ��>

������ʿ������ָ������������Ļ������Կ��ٵĳ���
���ˣ�ʹ���� �ܵ����ص�ײ���������ˡ����������������
�ϻ����κ������ϣ��������ܵ������׹����ϡ�

�������ָ��: kill, advance_class, warrior_adv


TEXT
	);
	return 1;
}
