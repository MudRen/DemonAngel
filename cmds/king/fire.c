//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/king/fire.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	int flag = 1;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ��fire <��>\n");
	arg = lower_case(arg);
	if( !ob = find_player(arg) ) {
		flag = -1;
		ob = load_player(arg);
	}
	if( !objectp(ob) ) return notify_fail("û����λ���\n");
	if( !userp(ob) ) return notify_fail(ob->name() + "��������ҡ�\n");
	if( ob == me ) return notify_fail("�㲻�ܿ����Լ���\n");
	if( !kingdom_data(me->query("kingdom/id"), "power", "sub", "minister", arg) ) return notify_fail("�Ҳ����ô����ϡ�\n");

        ob->delete("home");
	ob->delete("kingdom/minister");
	if(flag == 1) ob->sub_path( ({"/cmds/min/"}) );
	ob->save();

	CHANNEL_D->do_channel(me, "kingdom", sprintf("��֣���������"+ob->name_id(1)+"Ϊ�����󳼵�ְ��"));
	if( flag == -1) destruct(ob);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : fire <ĳ��>

���ָ����Խ������е�һλ�����󳼱��Ӣ�ۡ������󳼵�����Ȩ�����͹���
�൱������ʮ����Ҫ�ĵ�λ����������ĸ�������Ϊʧ�������п��ܼ�����䡣
һ���������������λ�����󳼡�

���ѶϢ : appoint, kingdom_stat

HELP
	);
	return 1;
}
