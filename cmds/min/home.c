//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/home.c
// by bor @RG
// modify by bor @DA, 3/9 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if(!me->query("home")) return notify_fail("���ұ������, �޷���ȥ�ˡ�\n");

	if(!arg) {
		if(environment(me)->query("no_recall"))
			return notify_fail("��ͻȻ������ļ������\n");
		message_vision("$N�Ȳ������Ļص��Լ����ڡ�\n", me);
		if( !me->query("home") || file_size(me->query("home")) == -1 ) {	// ������ home �ĵ�����������
			if( file_size(KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c")==-1 ) 
				return notify_fail("���ұ������, �޷���ȥ�ˡ�\n");
			write("��ļ��Ѿ��������ˣ���ʱ�趨����������\n");
			me->set("home", KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c" );
		}
		me->move(me->query("home"));
		me->start_busy(2);
		return 1;
	}
	if(arg=="here") {
		if( !environment(me)->query("kingdom_id")
		|| environment(me)->query("kingdom_id") != me->query("kingdom/id") )
			return notify_fail("���ﲻ����Ĺ��ҡ�\n");
		me->set("home", base_name(environment(me))+".c" );
		write("������ﵱ�����ˣ��Ժ��� home ��ص����\n");
	}
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : home <here>

���ǹ�������õ�˲�䴫��ָ��, ���Դ��ͻ��Լ��ļҡ��������
home here ���趨�Լ��ļң����û���趨������㴫��������

HELP
	);
	return 1;
}
