//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/develop.c
// by bor @DA 2/23, 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#define MAX_DEVELOP	70			// 自己定义最高发展上限,建议不要写 100, 以免未来就已经定死了

int main(object me, string arg)
{
	string id, dev, *list;
	int cost;
	mapping DEVELOP = ([	// 如果你想增加其他项目的话, 直接在此补就好了,不用翻山越岭到处补
				//	by bor @DA 2/23, 2003
		"tavern" :		"旅馆",			// 休息与招收一般 mob
		"smith" :		"铁铺",			// 制造更好的武器
		"armory" :		"防具铺",		// 制造更好的装备
		"barracks" :		"军营",			// 招收更高级的部队, 发展英雄厅
		"trainyard" :		"训练场",		// 发展新的职业与技能
		"gate" :		"关卡",			// 建筑物与设施防御力增强
		"stable" :		"马厩\",		// 可以生产更强壮的马匹或座骑
		"magic_tower" :		"魔法塔",		// 发展新法术, 发展魔法阵
		"church" :		"教堂",			// 发展新法术, 发展圣殿
		"furnace" :		"魔力炉",		// 增强武器防具的威力
		"hero_guild" :		"英雄会馆",		// 召唤强力自然生物，须研发配合
	]);


	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");

	id = me->query("kingdom/id");

	if(!arg) {
		write(full_kingdom(id)+"的建筑物发展资金状况 :\n");
		foreach( dev, string tmp in DEVELOP )
			printf("    %-32s目前进度 %3d / 剩余资金 %d\n", tmp+"("+dev+")",
			develop_data(id, "query_par", dev, "dev"),
			develop_data(id, "query_par", dev, "gold") );
		reset_eval_cost();
		return 1;
	}

	if( sscanf(arg, "%s %d", dev, cost) != 2 )
		return notify_fail("指令格式 : develop <特殊建筑物类型> <投入金币数>\n");

	if(!kingdom_data(id, "special_room", "check", dev))
		return notify_fail("贵国没有 "+dev+" 这类型的特殊建筑物, 无法进行发展。\n");

	dev = lower_case(dev);
	list = keys(DEVELOP);
	if( member_array(dev, list) == -1 ) return notify_fail("没有这样的特殊建筑物类型。\n");

	if( cost > 0) {
		if( develop_data(id, "query_par", dev ) )
		if( develop_data(id, "query_par", dev, "dev") >= MAX_DEVELOP )
			return notify_fail("投资发展已经全满，不需要再投资。\n");

		if( kingdom_data(id, "data", "query_par", "gold") < cost )
			return notify_fail("国库目前没有这么多钱可供投资。\n");
		if( cost < 50000 ) return notify_fail("投资至少一次要 50000 金币。\n");
		if( cost > 2000000 ) return notify_fail("投资不要超过 200 万金币。\n");
		CHANNEL_D->do_channel(me, "kingdom", sprintf("本国又投入了 "+cost+" 枚金币进行"+DEVELOP[dev]+"及其相关事业的发展。"));
		log_file("kingdom/develop", sprintf("%s:%s[%s] 投资 "+ cost +" gold on %s\n",
			ctime(time())[0..15], geteuid(me), query_ip_name(me), id ));
	} else {
		if( develop_data(id, "query_par", dev, "gold") < -cost )
			return notify_fail("本投资事业，并没有投资那么多，无法回收。\n");
		if( 5000000+cost < 0 ) return notify_fail("回收资金，请控制在 500 万以下。\n");
		CHANNEL_D->do_channel(me, "kingdom", sprintf("本国从"+DEVELOP[dev]+"及其相关事业的发展资金中收回 "+(-cost)+" 枚金币。"));
		log_file("kingdom/develop", sprintf("%s:%s[%s] 回收 "+ -cost +" gold on %s\n",
			ctime(time())[0..15], geteuid(me), query_ip_name(me), id ));
	}
	develop_data(id, "add", dev, "gold", cost);
	kingdom_data(id, "data", "add", "gold", -cost);
	return 1;
}

int help(object me)
{
write(@HELP

指令格式 : develop <特殊建筑物类型> <投入金币数>

这是国王与大臣用来发展特殊建筑物的指令。在特殊建筑物落成的时候, 他们
的功能尚未完全, 这个时候使用 develop 指令来发展他们, 使他们的功能更能
发挥到极致。适当的搭配发展与研发会使得两者的进行相辅相成, 同时, 某些
特殊建筑只在发展到一定程度时才会出现。当投入的金币数是负的时，会将已
投入的金币收回国库。

目前需要发展的特殊建筑如下 :

        名称    中文名称        发展后
----------------------------------------------------------------------
     tavern     酒吧、旅馆      休息与招收一般 mob
     smith      铁铺		制造更好的武器
     armory	防具铺		制造更好的装备
     barracks   军营            招收更高级的部队, 发展英雄厅
     trainyard  训练场          发展新的职业与技能
     gate       关卡            建筑物与设施防御力增强
     stable	马厩		可以生产更强壮的马匹或座骑
   magic_tower  魔法塔          发展新法术, 发展魔法阵
     church     教堂		发展新法术, 发展圣殿
     furnace	魔力炉		增强武器防具的威力 
   hero_guild   英雄会馆        召唤强力自然生物，须研发配合

如果不加任何参数，将会看到建筑物发展基金状况的列表。

其他相关资讯 : build, research

HELP
	);
	return 1;
}

/*

> develop
天空(sky)的建筑物发展资金状况 :
    魔法塔(magic_tower)             目前进度  14 / 剩余资金 252050
    魔力炉(furnace)                 目前进度   3 / 剩余资金 387600
    铁铺(smith)                     目前进度  13 / 剩余资金 244450
    防具铺(armory)                  目前进度  14 / 剩余资金 239325
    马厩(stable)                    目前进度   0 / 剩余资金 389000
    关卡(gate)                      目前进度  13 / 剩余资金 157925
    旅馆(tavern)                    目前进度   3 / 剩余资金 189650
    英雄会馆(hero_guild)            目前进度   0 / 剩余资金 589000
    训练场(trainyard)               目前进度   0 / 剩余资金 291000
    教堂(church)                    目前进度   3 / 剩余资金 189425
    军营(barracks)                  目前进度   0 / 剩余资金 191000

*/