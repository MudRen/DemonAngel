//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/accept.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string *tuned_ch=({});

	seteuid(getuid(me));
	if( !arg ) return notify_fail("ָ���ʽ��accept <ĳ��>\n");
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !( ob = present(arg, environment(me)) ) ) return notify_fail("���˲�������ߡ�\n");
	if( !userp(ob) || !ob->query_temp("join") ) return notify_fail("����û������������� !\n");
	if( ob == me) return notify_fail("���Ѿ���������ҵ������ˡ�\n");
	if( !(ob->query_temp("join")==me) ) return notify_fail("����û���������������� !\n");
	if(!people_data(me->query("kingdom/id"), "add", ob->query("id"))) return notify_fail("���������޷����ˡ�\n");

	if( !arrayp(tuned_ch = ob->query("channels")) ) {
		ob->set("channels", ({"kingdom"}));
	} else {
		if( member_array("kingdom", tuned_ch)==-1 ) {
			tuned_ch += ({ "kingdom" });
			ob->set("channels", tuned_ch);
		}
	}

	ob->delete_temp("join");
	ob->set("kingdom/id", me->query("kingdom/id"));
	ob->save();
	message_vision( "$N������$n������\n", me, ob);
	CHANNEL_D->do_channel(ob, "kingdom",
		sprintf("�� - %s��������ʾЧ��%s��", ob->name_id(1), full_kingdom(ob->query("kingdom/id")) ));
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : accept <ĳ��>

���ָ����������Ƿ���ܶԷ����뱾�������룬����ֻ���ڹ��巽
��ʹ�á�

���ѶϢ : join, kingdom_stat, people

HELP
	);
	return 1;
}
