//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/banish.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string *tuned_ch=({});

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ : banish <ĳ��>\n");

	// ��������û�������϶���ȡ����
	if( !(ob = find_player(arg)) ) ob = load_player(arg);
	if( !ob ) return notify_fail("������Ѿ������ڡ�\n");

	if( ob == me ) return notify_fail("���ܽ��Լ�������\n");
	if( !ob->query("kingdom") ) return notify_fail("����������Ĺ��� !\n");
	if( ob->query("kingdom/minister") || ob->query("kingdom/king") ) return notify_fail("����Ϊ���壬���ò��ʿ������� !!\n");
	if( !people_data(me->query("kingdom/id"), "sub", ob->query("id")) ) return notify_fail("����������Ĺ��� !\n");

	CHANNEL_D->do_channel(me, "kingdom", sprintf("��֣����������%s�Ĺ��塣", ob->name_id(1) ) );

	if( arrayp(tuned_ch = ob->query("channels")) ) {
		if( member_array("kingdom", tuned_ch)!=-1 ) {
			tuned_ch -= ({ "kingdom" });
			ob->set("channels", tuned_ch);
		}
	}
	ob->delete("kingdom");
	ob->save();
	if(find_player(arg)) tell_object( ob, "�����û�й����������ˡ�\n");
	if(!find_player(arg)) destruct(ob);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : banish <ĳ��>

���ǹ�������˿ڵ�ָ��, ��ĳ�˴������г����������ʹ󳼶���ʹ�ã���ֻ��
�������ܿ����󳼡�

���ѶϢ : join, kingdom

HELP
	);
	return 1;
}
