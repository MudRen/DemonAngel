//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/wiz/set_title.c
// by bor @DA, 2/23 2003

#include <ansi.h>
inherit F_CLEAN_UP;
 
int main(object me, string str)
{
	string id, title;
	object ob;

	if( !str ) return notify_fail("��Ҫ��˭ȡʲô�������� ?\n"); 
	if( sscanf(str, "%s %s", id, title)!=2 ) return notify_fail("set_title <���> <ͷ��>\n");
	ob = present(id, environment(me));
	if(!ob) ob = me;
	if(!userp(ob)) return notify_fail("��ֻ�����������ͷ�Ρ�\n");

	title = ansi_color(title);
	ob->set("title", title + NOR);
	write("Ok.\n"); 
	return 1; 
}
 
int help(object me)
{
	write(@HELP
ָ���ʽ: set_title <���> <ͷ��>
 
�������һ��������ͷ�Ρ�

HELP
	);
}