//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/set_short
// by bor @RG

#pragma optimize
#pragma save_binary

//#include <ansi.h>

int main(object me,string arg)
{
	string *str;
	object env;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ��set_short <����>\n");
	if( !env = environment(me)) return notify_fail("�Ҳ���������\n");
	if( env->query("no_change") ) return notify_fail("���ﲻ�ܱ����������ϡ�\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("���ﲻ���ҹ���������\n");

	arg = kill_all_bug(arg);
	arg = ansi_color(arg);

	str = explode(arg, "[");
	if( strlen(arg) > 30+sizeof(str)*4 ) return notify_fail("��Ĳ���̫���ˡ�\n");

	if( sscanf(arg, "[%*s") || sscanf(arg, "%*s[%*s") ) env->set("short", arg+"[0m");
	else env->set("short", arg);

	do_saveroom(env);
	write("��ɡ�\n");
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : set_short <��������>

���ǹ��������������������ָ��, ���ָ�������ı����������ķ����
����, �������� look ʱ�����Ķ����������ָ��ֻ�Ǹı����ƶ���, ����
���һ�ж�Ū����, Ҫ�ǵ��� saveroom �ѷ����������

        set_short       : �趨���������, �����㿴���ĵ�һ�С�
        set_long        : �趨���������, �����㿴�����Ƕ�������
        add_mob         : Ϊ����������һЩ���
        add_desc        : Ϊ����������һЩ���Կ���������
        saveroom        : ����ѷ����һ�ж��趨����,�ǵ�һ��Ҫ��������

����ķ�������ɫ�Ļ������һ���ֻ����㲹����ɫ��ԭ�� $NOR$��
����Բ����Լ����ϡ�

���������Ѷ :  set_short, set_long, add_mob, add_desc,
		saveroom, ansi

HELP
	);
	return 1;
}
