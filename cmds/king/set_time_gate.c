//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/king/set_time_gate.c
// by bor @DA, 2/22 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env;
	string file;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ��set_time_gate <here | cancel>\n");
	if( arg!="here" && arg!="cancel" ) return notify_fail("ָ���ʽ��set_time_gate <here | cancel>\n");

	switch(arg) {
		case "cancel":
			if( !kingdom_data(me->query("kingdom/id"), "other", "del", "time_gate") )
				return notify_fail("�����û���趨ʱ���š�\n");
			message_vision("$Nȡ����ʱ���š�\n", me);
			break;
		case "here":
			if( !objectp(env = environment(me)) ) return notify_fail("������������֮�أ�û�취�趨ʱ���š�\n");
			if( file_size(file = base_name(env)+".c") == -1) return notify_fail("��Ҫ�趨������Ϊ�����ʱ���ţ�\n");
			// �ҽ����λ Admin ���Խ��ж��Ƿ�Ϊ������䣬д��һ���������̶��ж��ã��������Ա���д�ܶ��
			if( !me->query("kingdom/id") || !env->query("kingdom_id")
			|| env->query("kingdom_id") != me->query("kingdom/id")
			) return notify_fail("���ﲻ�ǹ�������ء�\n");
			kingdom_data(me->query("kingdom/id"), "other", "set", "time_gate", file);
			message_vision("$N���˵�������ʱ���š�\n", me);
			break;
		default:
	}
	return 1;
}

int help()
{
	write(@HELP

ָ���ʽ��set_time_gate <here | cancel>

�趨�÷�����Ϊ���ӹ�����ϵͳ�ĵص㣬��֮Ϊ[ʱ����]���Ժ���˿���͸��ʱ���Ž��ٹ��
���۹⡣
	<cancel>	ȡ��ʱ����

HELP
	);
	return 1;
}
