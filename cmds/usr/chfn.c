//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/chfn.c
// by bor @DA, 3/17 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int check_legal_name(string name);

int main(object me, string arg)
{
	string *name;
	seteuid(getuid(me));

	if(!arg) return notify_fail("ָ���ʽ : chfn <��������>\n");
	if(!wizardp(me)) {
		if( strlen(arg) > 12) return notify_fail("�������̫������ȡ�����ŵ����ְ� !!\n");
		if(!check_legal_name(arg)) return notify_fail("������ְ������Ϸ����������ڡ�\n");
		if( !me->query("kingdom/king") && !me->query("kingdom/minister") )
		if( me->query("level")<10 ) return notify_fail("��ȼ�̫�ͣ����ܸ�����ȥ��\n");

		if( !me->query("name_time") ) me->set("name_time", 0);
		if( (time()-me->query("name_time")) <= 1200) return notify_fail("�㲻��ǰ�Ÿջ������֣�����ٻ��� !!\n");
	}
	me->set("name", arg);
	me->set("name_time", time());
	write("��ɡ�\n");
	me->save();
	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);

	if( (strlen(name) < 4) || (strlen(name) > 12 ) ) {
		write("�Բ�������������ֱ����� 2 �� 6 �������֡�\n");
		return 0;
	}
	while(i--) {
		if( name[i]<='' ) {
			write("�Բ�������������ֲ����ÿ�����Ԫ��\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("�Բ��������á����ġ�ȡ���֡�\n");
			return 0;
		}
		if( name[i..i+1]=="��" ) {
			write("�Բ����벻Ҫ�ÿհ���Ԫȡ���֡�\n");
			return 0;
		}
	}
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : chfn <��������>
 
���ָ�������������֣��г��������Ҳ�������������

HELP
	);
	return 1;
}
