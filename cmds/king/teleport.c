//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/king/teleport.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, obj_env;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("��Ҫ�ɱ����ģ�\n");

	obj = find_player(arg);
	if( !obj ) return notify_fail("û�������һ������ϡ�\n");
	if( obj==me ) return notify_fail("ָ���ʽ��teleport <����>\n");
	if(!me->query("kingdom/id") ) return 0;

	if( !obj->query("kingdom/id")
	|| obj->query("kingdom/id") != me->query("kingdom/id") )
		return notify_fail("�����Ǳ�������\n");

	if(!obj_env = environment(obj)) return notify_fail("���Ļ����Ѿ���ʧ���޷���ȥ��\n");
	if( obj_env->query("no_teleport") ) return notify_fail("�Է����ڵĵط���׼ teleport��\n");

	message_vision("ֻ��һ���������$N����Ӱ�Ѿ������ˡ�\n", me);
	me->move(obj_env);
	message("vision","һ�������"+me->name_id(1)+"����Ӱ����������ǰ��\n", environment(me), ({me}) );
	return 1;
}

int help()
{
	write(@HELP

ָ���ʽ��teleport <����>

���ǹ���ר�õ�˲�䴫��ָ��, ���Դ��͵������κ�һ����������ڣ�ֻҪ��
�Ļ���û���趨 no_teleport ����������ǰ����

HELP
	);
	return 1;
}
