//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/recall.c
// by bor @RG,

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <login.h>

inherit F_CLEAN_UP;  

int main(object me, string arg)
{
	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
	if(me->is_fighting()) return notify_fail("����ս���У��޷��ƶ���\n");
	if(!wizardp(me)&&environment(me)->query("no_recall")) {
		message_vision("$N����Ѽ�Ӱ�$N����һ�и�Դ֮�أ�����\n"
		"����Ѽ��װ����������\n",me);
		return 1;
	}
	message_vision(HIC"$N��ͷ��Ѽ�������$N����һ�и�Դ֮��\n"
		HIW"ͻȻ��Ӱ����һ���׹�, $P����������С�\n"NOR, me);
	me->move(START_ROOM);
	if(!wizardp(me)) me->start_busy(3);
	message_vision(HIC"һ���׹����մ��Ƽž�, $N��Ӱ�������֡�\n"NOR,me);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : recall

���㱻��סʱ, �����ʹ�����ָ��ʹ�����̻ص�ð����֮�ҡ�
���ָ��ֻ�ڷ�ս��״̬����Ч��

���ѶϢ :

HELP
	);
	return 1;
}
