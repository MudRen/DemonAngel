//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/adm/delete_kingdom.c
// by bor @RG

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string name, *channeld_ch;
	object *list;
	int i;

	if(!wizardp(me)) return notify_fail("��û��Ȩ��ʹ�����ָ�\n");
	if( !arg || arg =="") return notify_fail("ָ���ʽ��delete_kingdom <��������>\n");
	seteuid(getuid());
	if( !check_kingdom(arg) ) return notify_fail("ָ���ʽ��delete_kingdom <��������>\n");

	name = full_kingdom(arg);

	list = users();
	i = sizeof(list);
	while( i-- ) {
		if( list[i]->query("kingdom/id")==arg ) {
			list[i]->delete("cwd");
			list[i]->delete("home");
			list[i]->delete("kingdom");
			list[i]->delete("title"); 
			channeld_ch = list[i]->query("channels");
			if( pointerp(channeld_ch) && member_array("kingdom", channeld_ch)!=-1 ) {
                                channeld_ch -= ({ "kingdom" });
				list[i]->set("channels", channeld_ch);
			}
			tell_object(list[i], sprintf("�����û�й�����ð�����ˡ�\n"));
			list[i]->save();
		}
	}

	CHINESE_D->remove_kingdom_name( arg);

	if( !rename(KINGDOM_DIR+arg+"/", DATA_DIR+"nuke/kingdom/"+arg+"/") )
		write( name+ "������ɾ����\n");
	else write( name+ "�����Ƴ�ʧ�ܡ�\n");

	log_file("kingdom_destory", sprintf("[%s] %s destroy kingdom - %s.\n",
		ctime(time())[0..15], geteuid(this_player(1)), arg));

	write("\n"+HIW+"һֻ����ͻȻ������"+HIR+name+HIW+"�����ƻ�...."+HIR+name+HIW+"�ʹ�������\n"NOR);
	shout("\n"+HIW+"һֻ����ͻȻ������"+HIR+name+HIW+"�����ƻ�...."+HIR+name+HIW+"�ʹ�������\n"NOR);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ��delete_kingdom <��������>

���ǹ������������Υ����ҵ��ռ�������

HELP
	);
	return 1;
}
