//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/npc/cast.c
// modify bor @DA

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string spells, spl, trg;
	object target;
	
	seteuid(getuid());

	if( me->is_busy() ) return notify_fail("( 你上一个动作还没有完成，不能施法。)\n");
	if( environment(me)->query("no_cast") ) return notify_fail("这里不准施法。\n");

	if( !arg ) return notify_fail("指令格式：cast <法术> [on <目标>]\n");
	if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
		if( spl == " " ) return notify_fail("指令格式：cast <法术> [on <目标>]\n");
		target = present(trg, environment(me));
		if( !target ) target = present(trg, me);
		if( !target ) return notify_fail("这里没有 " + trg + "。\n");
	} else {
		spl = arg;
		target = 0;
	}

	if( !me->query_spell(spl, 1) ) return notify_fail("你没学习这样的法术。\n");
	return (int)SPELL_D(spl)->cast_spell(me, target);
}

int help (object me)
{
        write(@HELP
指令格式 : cast <法术> on <对象>
 
这个指令让你施法在某人身上. 不指定对象时, 若施防御性法术, 则会
施在自己身上, 若在战斗中施攻击性法术, 会自动施在敌人身上。

其他相关指令: magic, learn, spells
 
HELP
	);
        return 1;
}
