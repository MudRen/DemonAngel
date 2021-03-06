//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/hero_guild.c
// 英雄会馆

#pragma optimize
#pragma save_binary

inherit ROOM;

mixed check_class(object me);

mapping ADV_MAGE_1 = ([
	"advance_wand"		:	100,
]);

mapping ADV_CLERIC_1 = ([
	"advance_staff"		:	100,
]);

private int skill_next_exp(int level);

void setup()
{
	seteuid(getuid());
	::setup();
}

void init()
{
	add_action("do_list", "list");		// 检查这里的发展如何
	add_action("do_drill", "drill");
}

int do_list(string arg)
{
	string msg = "";
	object me = this_player();

	if( !check_class(me) ) return notify_fail("你的能力不足, 不能来此学习进阶技能。\n");
	if( !mapp(check_class(me)) || (mapp(check_class(me)) && zerop(keys(check_class(me))) ) )
		return notify_fail("目前该职业, 进阶技能尚在研发阶段, 敬请期待。\n");

	msg += "你在这里可以学到的进阶技能有 :\n";
	foreach(string can_drill_list, int tmp in check_class(me))
		msg += sprintf("    %-32s 目前学成  %d %% 下次提升需要  %d %s\n",
			to_chinese(can_drill_list)+"("+can_drill_list+")",
			me->query_skill(can_drill_list, 1),
			skill_next_exp(me->query_skill(can_drill_list)+1), "点经验" );
	me->start_more(msg);
	return 1;
}

private int skill_next_exp(int level)
{
	int exp;
	exp = level*level*13 + level* 3 + 30;
	return exp;
}

int do_drill(string arg)
{
	object me;
	string *skill, learn_sk;
	int my_skill, num, test_lv;
	mapping can_drill, dbase;

	me = this_player();

	if( !check_class(me) ) return notify_fail("你的能力不足, 不能来此学习进阶技能。\n");
	if( !arg ) return notify_fail("你想学什么技能？\n");

	can_drill = check_class(me);
	skill = keys(can_drill);
	if( sscanf(arg, "%d %s", num, learn_sk) != 2 ) {
		num = 1;
		learn_sk = arg;
	}
	if( num<1 ) num = 1;
	if( member_array(learn_sk, skill) == -1 )
		return notify_fail("你的职业并没有此项技能可学。\n");

	dbase = me->query_entire_dbase();

	for(int i=0; i<num; i++) {
		my_skill = me->query_skill(learn_sk, 1);
		if( my_skill >= can_drill[learn_sk] )
			return notify_fail("这项技能你已经到目前所能学的最大值了。\n");
		// 我使用 test_lv 来当作技能最高上限。
		// 比如说当我们 level 到 40 级时，技能就可以练到该职业的全满。
		test_lv = dbase["max_lv"]*0.8;

		if( dbase["level"] <= test_lv )
		if( my_skill > dbase["level"]*2 )
			return notify_fail("这项技能, 你目前只能学到这个程度。\n");

		if( !SKILL_D(learn_sk)->valid_learn(me) ) return 0;

		if( !me->check_exp(skill_next_exp(my_skill+1)) )
			return notify_fail("你的经验值不够。\n");

		printf("你的%s技能现在提升到 %d 了。\n", to_chinese(learn_sk), my_skill+1);
		me->set_skill(learn_sk, my_skill+1);
		me->pay_exp( skill_next_exp(my_skill+1) );
	}
	return 1;
}

// 可以到进阶学习东西的职业以及限制
mixed check_class(object me)
{
	mapping adv_spell;

	switch( me->query("class") ) {
		case "魔法师":
			if( me->query_skill("magic", 1) < 75 ) {
				return 0;
			} else if( me->query_skill("magic", 1) >= 75 ) {
				adv_spell = ADV_MAGE_1;
			} else return 0;
			break;
		case "牧师":
			if( me->query_skill("magic", 1) < 75 ) {
				return 0;
			} else if( me->query_skill("magic", 1) >= 75 ) {
				adv_spell = ADV_CLERIC_1;
			} else return 0;
			break;
		default :
			return 0;

	}
	return adv_spell;
}
