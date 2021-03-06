//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/set_room.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	object env;
	mapping dbase;
	string *data, str;
	string *set_only = ({"no_teleport", "no_summon", "no_cast", "no_fight", "no_mob",
		"no_recall", "no_quit", "dark", "outdoors"});

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !env = environment(me)) return notify_fail("找不到环境。\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("这里不是我国的领土。\n");

	dbase = env->query_entire_dbase();
	data = dbase["refresh_data"];

	if(!arg) {
		str = "这个房间的基本性质如下 :\n";
		str += "\ttype            : "+dbase["type"]+"\n";
		str += "\tmake_owner      : "+data[0]+"\n";
		str += "\tmake_time       : "+data[1]+"\n";
		str += "\tlast_owner      : "+data[2]+"\n";
		str += "\tlast_update     : "+data[3]+"\n";
		str += "\tno_summon       : "+dbase["no_summon"]+"\n";
		str += "\tno_teleport     : "+dbase["no_teleport"]+"\n";
		str += "\tdark            : "+dbase["dark"]+"\n";
		str += "\tno_mob          : "+dbase["no_mob"]+"\n";
		str += "\tno_cast         : "+dbase["no_cast"]+"\n";
		str += "\tno_fight        : "+dbase["no_fight"]+"\n";
		str += "\tno_recall       : "+dbase["no_recall"]+"\n";
		str += "\tno_quit         : "+dbase["no_quit"]+"\n";
		str += "\toutdoors        : "+dbase["outdoors"]+"\n";

		me->start_more(str);
		return 1;
	}

	if( dbase["no_change"] ) return notify_fail("这里有特殊的设定，无法变更。有事请恰管理者来察看。\n");

	if(member_array(arg, set_only) != -1) {
		if( dbase[arg]==1 ) {
			dbase[arg] = 0;
			env->delete(arg);
		} else {
			dbase[arg] = 1;
			env->set(arg, 1);
		}

		write("你将 "+arg+ " 设定为 "+ dbase[arg] + "\n");
		do_saveroom(env);
		return 1;
	} else return notify_fail("指令格式 : set_room <房间性质>\n");
	return 1;
}

int help()
{
	write(@HELP

指令格式 : set_room <房间性质>

这是国土开发时的指令之一, 这个指令用来设定一些比较琐碎的房间性质,
目前可以设定的性质有 : <以下是设定值为 1 的状况, 0 则解除状况。>
如果不加任何参数，会看见目前房间的状态。

 1. outdoors    : 把这个房间设成户外, 这样你可以在这里看到天气讯息。
 2. no_quit     : 不能在这个房间 quit。
 3. no_recall   : 不能在这个房间用 recall 指令。
 4. no_fight    : 此处禁止战斗。
 5. no_cast     : 此处禁止施法。
 6. no_mob      : 此处 mob 不得通行。
 7. no_summon   : 此处禁止 summon .
 8. type        : 变换普通房间的基本型态。目前的允许变换的基本型态有 :
                  normal        :       把特殊房间变成普通房间
                  board         :       留言广场
                  gate          :       关卡
                  例如你可以使用 set_room type gate 把一般房间转成 gate
                  你只能变换普通房间的型态。
 9. add_room    : 向某方向增加一个普通房间。
                  例如 : set_room add_room west : 向西增加一个房间。
11. repair here : 修理被摧毁的建筑物。由于要清理重建, 代价跟盖新的差不多。
11. dark        : 将房间设定为黑暗的，1 为黑暗, 0 则恢复光亮。

如果还想到要补充的, 请跟管理者联络。
PS. 2-7 项请勿乱设, 否则 ....

相关讯息 : makeroom, set_short, set_long, saveroom

HELP
	);
	return 1;
}