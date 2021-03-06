//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
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
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !arg ) return notify_fail("指令格式：set_short <内容>\n");
	if( !env = environment(me)) return notify_fail("找不到环境。\n");
	if( env->query("no_change") ) return notify_fail("这里不能变更房间的资料。\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("这里不是我国的领土。\n");

	arg = kill_all_bug(arg);
	arg = ansi_color(arg);

	str = explode(arg, "[");
	if( strlen(arg) > 30+sizeof(str)*4 ) return notify_fail("你的参数太长了。\n");

	if( sscanf(arg, "[%*s") || sscanf(arg, "%*s[%*s") ) env->set("short", arg+"[0m");
	else env->set("short", arg);

	do_saveroom(env);
	write("完成。\n");
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : set_short <房间名称>

这是国王与大臣用来开发国土的指令, 这个指令用来改变他所建立的房间的
名称, 就是你用 look 时看到的短描述。这个指令只是改变名称而已, 若房
间的一切都弄好了, 要记得用 saveroom 把房间存起来。

        set_short       : 设定房间的名字, 就是你看到的第一行。
        set_long        : 设定房间的描述, 就是你看到的那堆描述。
        add_mob         : 为这个房间添加一些生物。
        add_desc        : 为这个房间加入一些可以看的描述。
        saveroom        : 当你把房间的一切都设定好了,记得一定要存起来。

当你的房间有上色的话，最后一个字会替你补上颜色还原码 $NOR$，
你可以不用自己补上。

其他相关资讯 :  set_short, set_long, add_mob, add_desc,
		saveroom, ansi

HELP
	);
	return 1;
}
