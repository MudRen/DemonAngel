//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// home.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string msg, to;

	if( !arg ) {
		if( file_size(to = user_path(geteuid(me)) + "workroom.c") <= 0 )
			return notify_fail("��û���Լ��Ĺ����ҡ�\n");
//		to = user_path(geteuid(me)) + "workroom";
	} else if( arg == "wiz") {
		to = "/d/wiz/hall1";
	} else return notify_fail("��Ҫ���ģ�\n");

	if( stringp(msg = me->query("env/msg_home")) ) message_vision(msg + "\n", me);

	me->move(to);
	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : home

���ô�һָ���ֱ�ӻص��Լ��Ĺ����ҡ�
������� 'msg_home' ����趨, ���ڳ����˶��ῴ���Ǹ�ѶϢ.
home wiz ���Իص�������  wiz board���벻Ҫ summon �� wiz��ȥ��
HELP
    );
    return 1;
}
