//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/order.c from es2 1.2b
// modify by bor @DA, 3/17 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int res;
	object ob;
	string who, cmd, verb, path;

	seteuid(getuid(me));
	if( me != this_player(1) ) return 0;

	if( !arg || arg=="" || sscanf(arg, "%s to %s", who, cmd)!=2 )
		return notify_fail("��Ҫ����˭��ʲô�£�\n");

	ob = present(who, environment(me));
	if( !ob || !ob->is_character()) return notify_fail("����û������ˡ�\n");

	if( sscanf(cmd, "%s %*s", verb) != 2 ) verb = cmd;

	if( !ob->query("kingdom/id") ) return notify_fail("�㲻����������ˡ�\n");

	if( me->query("kingdom/id") != ob->query("kingdom/id") )
		return notify_fail("�㲻��ָ������ˡ�\n");

	write("������" + ob->name() + ": " + cmd + "\n");

	if( stringp(path = ob->find_command(verb))
	&&    path != "/cmds/npc/" + verb && path != "/cmds/usr/" + verb  )
		return notify_fail("�㲻����������������¡�\n");

	if( !ob->accept_order(me, verb) ) return notify_fail("What !?\n");

	seteuid(getuid());
	res = ob->force_me(cmd);
	return res;
}

int help(object me)
{
	write(@TEXT

ָ���ʽ��order <target> to <command>

�����ù����ʹ��������ָ����ǿ����������Ĺ�������
���ֵ��£� ��Ȼ��Щ���Ǳ���ֹ�ġ�������������������
���˷��еġ�

�������������������������� mob ����(drop)�����ϵ�װ
�������� ���������ĵȼ��ľ����� mob ����ͱ����㣬��
��Ҳֻ���ڴ��ˡ�ֻ �й���������������е����� mob��ע��
�������� mob ������ȥ����ҪС�ĵİ������������������
�����˸����ˣ�������ʧ�ˡ�

�����Ĺ���ܳ��������ù���Ƶ������, ���������������
(quiet)ʮ ����, �����𺦹������󡣲�����������ǲ��ܳ���
��, ֻ�е�ʱ����˲Ż�ȡ��, ����ǧ��Ҫ��������Ц��

Ŀǰ����ʹ�õ������� : nick, chfn, wear, remove, wield, unwield, 


TEXT
	);
	return 1;
}
