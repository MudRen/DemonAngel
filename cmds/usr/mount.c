//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/mount.c

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

int do_ride(object me, object ob);

int main(object me,string arg)
{
	return do_ride(me, ob);
}

int do_ride(object me, object ob)
{
	message_vision("$N��"+ob->query("name")+"������һ����˳��������"+ob->query("name")+"��\n", me);
        return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : mount <Ŀ��>

���ָ����������������������� -- ��ȻҪ��Ը�������

���ѶϢ : dismount, charge


HELP
	);
	return 1;
}
