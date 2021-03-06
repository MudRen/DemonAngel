//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/join.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int do_time(object me);

int main(object me, string arg)
{
	object ob, obj;

	seteuid(getuid(me));
	if( !arg ) return notify_fail("指令格式：join <对象名称>\n");
	if( me->query("kingdom/id") ) return notify_fail("你已经有国籍了，先放弃这个国籍才能加入其他国家！\n");

	if( arg == "cancel" ) {
		if( !objectp(obj = me->query_temp("join")) ) return notify_fail("你现在并没有向任何人申请国籍。\n");
		write("你决定不向" + obj->name_id(1) + "申请国籍了。\n");
		tell_object(obj, me->name_id(1) + "改变主意不想向你申请国籍了。\n");
		me->delete_temp("join");
		return 1;
	}

	if( !(ob = present(arg, environment(me))) || !userp(ob) ) return notify_fail("指令格式：join <对象名称>\n");
	if( ob == me ) return notify_fail("你向自己申请国籍做什么。\n");
	if( !ob->query("kingdom/minister") && !ob->query("kingdom/king"))
		return notify_fail(ob->name_id()+"并非贵族。\n");

	if( !ob->query("kingdom/id") ) return notify_fail("出问题了，请找管理者前来修正。\n");

	if( me->query("arrest") )
	if( member_array(ob->query("kingdom/id"), me->query("arrest") ) != -1 )
		return notify_fail("你正被该国家通缉中，无法入国。\n");

	if( objectp(obj = me->query_temp("join")) ) {
		if( ob = obj ) return notify_fail("对方正在考虑，不用急着加入。\n");
		else {
			write("你改变主意不向" + obj->name_id(1) + "申请国籍了。\n");
			tell_object(obj, me->name_id(1)+ "改变主意不想向你申请国籍了。\n");
		}
	}
	message_vision("$N向$n申请国籍。\n", me, ob);
	me->set_temp("join", ob );
	tell_object(ob, YEL"如果你愿意收" + me->name_id(1) + "入国，请用 accept " + me->query("id") + "。\n" NOR);
	call_out("do_time_check", 10, me);
	return 1;
}

int do_time_check(object me)
{
	if(!me->query_temp("join")) remove_call_out(do_time(me));
	else call_out("do_time", 6, me);
	return 1;
}

int do_time(object me)
{
	if( me->query_temp("join") ) {
		me->delete_temp("join");
		write("看样子对方好像不想理你\n");
	}
	return 1;
}

int help()
{
        write(@HELP

指令格式 : join <对象名称 | cancel>
 
这个指令可以让你向所指定的对象 - 必需是一个国家的国王或大臣
要求加入他所属的国家.

当你中途不想加入，趁对方还没收你入国前赶快取消(cancel)吧。

相关讯息 : kingdom, kingdoms, rebel

HELP
        );
        return 1;
}
