//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/party.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object *t;

	if( !arg ) {
		if( !pointerp(t = me->query_team()) )
			return notify_fail("你现在并没有参加任何队伍。\n");
		write("你现在队伍中的成员有：\n  " + implode(t->name(1), "\n  ") + "。\n");
		return 1;
	}
	if( arg=="dismiss" ) {
		if( !pointerp(t = me->query_team()) )
			return notify_fail("你现在并没有参加任何队伍。\n");
		if( me->is_team_leader() ) {
			message("team", me->name(1) + "将队伍解散了。\n", t, me);
			write("你将队伍解散了。\n");
		} else {
			message("team", me->name(1) + "决定脱离队伍。\n", t, me);
			write("你脱离了你的队伍。\n");
		}
		me->dismiss_team();
		return 1;
	}
	if( sscanf(arg, "with %s", arg)==1 ) {
		object ob;

		if( !(ob = present(arg, environment(me)))
		||	!living(ob)
		||	!ob->is_character()
		||	ob==me )
			return notify_fail("你想和谁成为伙伴？\n");

		if( !pointerp(me->query_team()) || me->is_team_leader() ) {
			if( me==(object)ob->query_temp("pending/team") ) {
				if( !pointerp(me->query_team()) ) {
					ob->add_team_member(me);
					message_vision("$N决定加入$n的队伍。\n", me, ob);
				} else {
					me->add_team_member(ob);
					message_vision("$N决定让$n加入队伍。\n", me, ob);
				}
				ob->dellete_temp("pending/team");
				return 1;
			} else {
				message_vision("$N邀请$n加入$P的队伍。\n", me, ob);
				tell_object(ob, YEL "如果你愿意加入，请用 team with " + me->query("id") + "。\n" NOR);
				me->set_temp("pending/team", ob);
				return 1;
			}
		} else
			return notify_fail("只有队伍领袖可以邀请别人加入。\n");
	}
	if( sscanf(arg, "talk %s", arg)==1 ) {
		if( !pointerp(t=me->query_team()) )
			return notify_fail("你现在并没有和别人组成队伍。\n");
		message("team", HIW "【队伍】" + me->name(1) + "：" + arg + "\n" NOR, t);
		return 1;
	}
	if( sscanf(arg, "form %s", arg)==1 ) {
		if( !pointerp(t=me->query_team()) || !me->is_team_leader() )
			return notify_fail("你必须是一个队伍的领袖才能组织阵形。\n");
		if( !me->query_skill(arg, 1) )
			return notify_fail("这种阵形你没学过。\n");
		return SKILL_D(arg)->form_array(me);
	}
}

int help(object me)
{
	write(@HELP
队伍指令使用方法:

party form - 组成一个冒险队伍, 自己当领队. 
party invite <对象> - 邀请某人加入队伍. 只有领队才能使用. 
party join <领袖> - 答应加入某领队的邀请, 加入他的队伍. 
party talk <讯息> - 使用队伍专用的频道与队友聊天, 可以用 tt <讯息> 替代。 
party disband - 领队使用时, 会解散整个冒险队伍. 队员使用时, 会脱离 脱离冒险队伍. 
party disband <队员> - 领队专用, 可将指定的队员从队伍中除名.

直接下 party 指令时则会显示你目前是否有加入队伍及队员名单。

HELP
	);
	return 1;
}
