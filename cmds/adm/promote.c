//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/adm/promote.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string old_status, new_status;
	int my_level, ob_level, level;

	if( me!=this_player(1) ) return 0;

	if( !arg || sscanf(arg, "%s %s", arg, new_status)!=2 )
		return notify_fail("指令格式：promote <使用者> <等级>\n");

	if( wiz_level(new_status) < 0 ) return notify_fail("没有这种等级。\n");

	if( !objectp(ob = present(arg, environment(me))) 
	||	!userp(ob) )
		return notify_fail("你只能改变使用者的权限。\n");

	if( wiz_level(me) < wiz_level(new_status) )
		return notify_fail("你没有这种权力。\n");

	old_status = wizhood(ob);

	seteuid(getuid());
	if( !(SECURITY_D->set_status(ob, new_status)) )
		return notify_fail("修改失败。\n");

	message_vision("$N将$n的权限从 " + old_status + " 改为 " + new_status + " 。\n", me, ob);
	seteuid(getuid());
	ob->setup();

	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : promote <某人> (权限等级)

只有 admin 才能提升玩家的权限, (player), (wizard)

HELP
	);
	return 1;
}
