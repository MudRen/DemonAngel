//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/summon.c
// by bor @ RG,

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( !arg ) return notify_fail("ָ���ʽ��summon <ĳ��>\n");
	arg = lower_case(arg);
	if( !ob = find_player(arg) ) return notify_fail("û������ˡ�\n");
	if( ob == me ) return notify_fail("�㲻���л��Լ���\n");

	if( !ob->query("kingdom/id")
	|| ob->query("kingdom/id") != me->query("kingdom/id") )
		return notify_fail("�����ǹ��� !!\n");
	if( ob->query("kingdom/king") ) return notify_fail("�㲻���ٻ����� !!\n");
	if( environment(me)->query("no_summon") ) return notify_fail("��һ�����ٻ����˹�����\n");
	if( ob->is_fighting() ) return notify_fail("������ս���С�\n");

	tell_room(environment(ob), ob->query("name")+"ͻȻ�ӵ�"+me->name_id(1)+"���ٻ���, ����ææ�����ˡ�\n", ob);
	ob->move(environment(me));
	write("���"+ob->query("name")+"�ٵ������ǰ��\n");
	tell_object(ob, me->name_id(1)+"ͻȻ�������ٻ���, ���㲻��صı������ˡ�\n");
	tell_room(environment(ob), ob->query("name")+"ͻȻ����������ǰ��\n",({me,ob}));
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ��summon <ĳ��>

��ָ�����������ٵĽ������Ƶ�����ǰ��

���ѶϢ : teleport, prison

HELP
	);
	return 1;
}