//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/king/appoint.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ : appoint <ĳ��> \n");
	if( !me->query("kingdom/id") ) return 0;
	if( !(ob = present(arg, environment(me)) )) return notify_fail("��������˭Ϊ�󳼣�\n");
	if( !userp(ob) ) return notify_fail(ob->name() + "���������ݡ�\n");

	if( ob == me ) return notify_fail("�㲻�������Լ�Ϊ�󳼡�\n");
	if( !ob->query("kingdom/id")
	|| ob->query("kingdom/id") != me->query("kingdom/id") )
		return notify_fail("�������������Ϊ�󳼣�\n");

	if( ob->query("kingdom/minister") ) return notify_fail("���������Ǵ� !!\n");
//	if( ob->query("level")<25 ) return notify_fail("���ĵȼ�����Ҫ���� 25 ������������Ϊ�󳼡�\n");

	if( sizeof(kingdom_data(me->query("kingdom/id"), "power", "minister", "query_all"))>=6 ) return notify_fail("ÿ���������ֻ������λ������ !!\n");
	if( !kingdom_data(me->query("kingdom/id"), "power", "add", "minister", ob->query("id")) ) return notify_fail("������������û�취���Է�д�������ڡ�\n");

	ob->set("kingdom/minister", ob->query("id"));
	ob->set("home",KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c");
	// �趨�󳼻���Ȩ��
	ob->add_path( ({"/cmds/min/"}) );
	ob->save();
	CHANNEL_D->do_channel(me, "kingdom", sprintf("��֣����������"+ob->name_id(1)+"Ϊ�����󳼡�"));
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : appoint <ĳ��>

���ָ�����ָ�������е�һλӢ�۳��θ����󳼡������󳼵�����Ȩ�����͹���
�൱������ʮ����Ҫ�ĵ�λ����������ĸ�������Ϊʧ�������п��ܼ�����䡣
һ���������������λ�����󳼡�

���ѶϢ : fire, kingdom_stat

HELP
	);
	return 1;
}
