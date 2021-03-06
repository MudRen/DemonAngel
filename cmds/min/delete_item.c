//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/delete_item.c
// by amgbell@hoe

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	object ob,*all_ob;
	int i;

	if (!arg) return notify_fail("指令格式 : delete_item <item>\n");
	ob=present(arg,me);

	if (!ob) return notify_fail("你身上没有这样东西。\n");

	if (ob->query("kingdom") != me->query("kingdom/id"))
		return notify_fail("这件不是贵国的物品。\n");

	if( !me->query("kingdom/king") && ob->query("owner")!=me->query("id") )
		return notify_fail("这件拥有者不是你!!\n");
	if( ob->query("equipped") ) return notify_fail("你正装备这武器．\n");
	// 如果 wp 有 coating 效果, 暂时不销毁
	if( ob->query_temp("coating") ) return notify_fail("这把武器还布满魔法力场中, 不能销毁武器!!\n");

	message_vision("$N派人把$n送去回收。\n",me,ob);

	all_ob=children(full_name(ob));

	rm(full_name(ob));

	if( ob->query("skill_type") ) {
		kingdom_data(me->query("kingdom/id"), "data", "sub", "weapon", 1);
		kingdom_data(me->query("kingdom/id"), "data", "add", "weapon_num", 1);
	} else if( ob->query("armor_type") ) {
		kingdom_data(me->query("kingdom/id"), "data", "sub", "armory", 1);
		kingdom_data(me->query("kingdom/id"), "data", "add", "armory_num", 1);
	}

	for (i=0;i<sizeof(all_ob) ;i++ ) {
		if(!objectp(all_ob[i])) continue;
		if(!environment(all_ob[i])) continue;
		if( !environment(all_ob[i])->is_character() ) continue;
		all_ob[i]->unequip();
		destruct(all_ob[i]);
	}
        return 1;
}

int help()
{
        write(@HELP

指令格式 : delete_item <item>

这是国王与大臣用来回收一些没用的武器防具的指令, 把已经用不到的次级
货回收, 可以得到制造新物品的材料, 对于发展太过而资源缺乏的国家而言,
这是促进进步的方法之一。

请注意 : 如果你把一件物品回收了, 拥有这件物品的人在下次上线后会发现
他的东西不翼而飞 ... 虽然很可怜, 可是为了国家的进步 ...

其他相关资讯 :  make_weapon, set_item, give

HELP
        );
        return 1;
}
