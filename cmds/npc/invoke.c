//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/invoke.c
// by bor @DA, 5/24 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;
int check_wp_type(string type);

int main(object me, string arg)
{
	object wp_ob, tar;
	string wp, ppl, magic;

	seteuid(getuid());
	if( !me->query_skill("invoke", 1) ) return notify_fail("�㲻������ܣ�\n");
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɣ�����������ӡ��\n");
	if( !arg ) return notify_fail("�﷨ : invoke <����> on <����>\n");
	if( sscanf(arg, "%s on %s", wp, ppl) == 2 ) {
		tar = present( ppl, environment(me) );
		wp_ob = present( wp, me );
		if( !tar ) return notify_fail("����û������ˣ�\n");
	} else {
		tar = me;
		wp_ob = present( arg, me );
	}

	if( !wp_ob ) return notify_fail("������û�����������\n");
	if( !wp_ob->query("equipped") ) return notify_fail("�㲢��װ����������\n");
	if( !check_wp_type(wp_ob->query("type")) ) return notify_fail("������������ܾ���invoke���⿪��ӡ��\n");
	if( !(magic = wp_ob->query("invoke_magic")) ) return notify_fail("�������û���κη�ӡ��\n");
	if( wp_ob->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	if( environment(me)->query_temp("no_cast") || environment(me)->query("no_cast") )
		return notify_fail("���ﲻ��ʩ����\n");

	if( file_size(SPELL_D(magic)+".c")==-1 ) return notify_fail("û�������ķ�ӡ !!\n");

	SPELL_D(magic)->invoke(me, tar, wp_ob);
	return 1;
}

int check_wp_type(string type)
{
	switch(type) {
		case "wand":
		case "staff":
			return 1;
			break;
		default:
			return 0;
	}
	return 0;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : invoke <��������> on <����>

����ʹ�� -

    ����������ϣ���ʦ�ǳ�����Ͼʱ������ķ��������ض��ķ����У��Ա���ʱ
֮�衣�� invoke ���ǿ��԰���Щ��ӡ�������ͷų����ļ��ܺ�ָ��⿪��ӡ��
������Ҫ�ķ�һ��������һ����ȫ��������ʹ�ü��ɵ��˻����л������������ӡ
�����������ǲ���Ҫ�����ĺܶ෨����ͬʱ���кܴ�Ļ�����ɷ������𻵣�����
�����ò������ú󣬷�����������������֮��ȥ�ˡ�

���ѶϢ : recharge, skills, spells

HELP
	);
	return 1;
}
