//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/dismount.c
// by bor @DA, 3/11 2003
 
inherit F_CLEAN_UP;

int do_dismount(object me, string arg);
 
int main(object me, string arg)
{
	seteuid(getuid(me));
	if(!me->query("list/pet")) return 0;
	if(!arg = me->query("list/pet/file")) return 0;
	do_dismount(me, arg);
	return 1;
}

int do_dismount(object me, string arg)
{
        object ob;

	if( me->query_temp("apply/damage") ) me->add_temp("apply/damage", -me->query("list/pet/damage"));
	if( me->query_temp("apply/armor") ) me->add_temp("apply/armor", -me->query("list/pet/armor"));
	ob = find_object(arg);
	if(!ob) return notify_fail("��Ŀǰû�����κε����\n");

	ob->set_temp("apply/kee", me->query_temp("apply/kee"));

	message_vision("$N����һԾ, �뿪��$n��\n", me, ob );
	ob->move(environment(me));
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : dismount <����>
 
����ůů��, ��Ҫ���ǿ������ˡ�
 
���ѶϢ : mount, pet

HELP
	);
	return 1;
}
