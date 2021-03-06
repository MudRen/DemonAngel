//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/trainyard.c
// by bor @DA

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

mapping ADVENTURER_SKILLS = ([
	"parry"			:	80,
	"dodge"			:	60,
]);

mapping WARRIOR_SKILLS = ([
	"sword"			:	100,
	"axe"			:	100,
	"hammer"		:	100,
	"spear"			:	100,
	"parry"			:	100,
	"dodge"			:	70,
	"defend"		:	80,
	"enhance_damage"	:	100,
	"weapon_master"		:	100,
]);

mapping MAGE_SKILLS = ([
	"magic"			:	80,
	"cast"			:	80,
	"recharge"		:	80,
	"invoke"		:	80,
	"dagger"		:	100,
	"wand"			:	100,
	"parry"			:	100,
	"dodge"			:	70,
	"enhance_damage"	:	100,
	"weapon_master"		:	100,
]);

mapping CLERIC_SKILLS = ([
	"magic"			:	80,
	"cast"			:	80,
	"recharge"		:	80,
	"invoke"		:	80,
	"dagger"		:	100,
	"staff"			:	100,
	"parry"			:	100,
	"dodge"			:	70,
	"enhance_damage"	:	100,
	"weapon_master"		:	100,
]);

mapping ATTR_LIMIT = ([
	"str"			:	35,
	"dex"			:	35,
	"int"			:	35,
	"con"			:	35,
	"sta"			:	35,
	"kar"			:	35,
]);

private int level_next_exp(int level);
private int attr_next_exp(int level);
private int sk_next_exp(int level);

void init()
{
	add_action("do_advance","advance");
	add_action("do_train", "train");
	add_action("do_cost", "cost");
	add_action("do_list", "list");
}

int do_list()
{
	object me = this_player();
	mapping MY_ALL_SKILL;
	string msg;

	switch( me->query("class") ) {
		case "冒险者":		MY_ALL_SKILL = ADVENTURER_SKILLS;	break;
		case "战士":		MY_ALL_SKILL = WARRIOR_SKILLS;		break;
		case "魔法师":		MY_ALL_SKILL = MAGE_SKILLS;		break;
		case "牧师":		MY_ALL_SKILL = CLERIC_SKILLS;		break;
		default:
			write("目前你这个职业，没有在规画内，无法学习任何技能。\n");
			return 1;
	}
	if( !mapp(MY_ALL_SKILL) || (mapp(MY_ALL_SKILL) && zerop(keys(MY_ALL_SKILL))))
		return notify_fail("目前你的职业，还没规画好技能，无法学习。\n");

	msg = "在这里所能训练的技能有:\n";
	foreach(string skill, int tmp in MY_ALL_SKILL ) {
		msg += sprintf("    %-38s 上限 = %d\n", to_chinese(skill)+"("+skill+")", tmp);
	}

	me->start_more(msg);
	return 1;
}

int do_cost()
{
	object me = this_player();
	mapping MY_ALL_SKILL, my_sk;
	string list, msg="";
	mapping dbase;

	dbase = me->query_entire_dbase();

	if( !me->check_exp(level_next_exp(dbase["level"]+1)) )
		msg = "你还需要 "+level_next_exp(dbase["level"]+1)+" 点经验才能升级。\n";
	else msg = "你的经验值已经达到升级标准了。\n";

	msg += "并且你有 "+dbase["exp"]+" 点经验可以用来提升属性与技能。\n";
	msg += "提升属性 :";

	foreach( list, int tmp in ATTR_LIMIT ) {
		msg += sprintf("\n    %-30s -> %2d    %d 点经验。",
			to_chinese(list)+"("+list+")", (me->query(list)+1), attr_next_exp(me->query(list)+1) );
	}

	switch( dbase["class"] ) {
		case "冒险者":		MY_ALL_SKILL = ADVENTURER_SKILLS;	break;
		case "战士":		MY_ALL_SKILL = WARRIOR_SKILLS;		break;
		case "魔法师":		MY_ALL_SKILL = MAGE_SKILLS;		break;
		case "牧师":		MY_ALL_SKILL = CLERIC_SKILLS;		break;
	}

	if( !me->query_skills() ) my_sk = ([]);
	else my_sk = me->query_skills();

	msg += "\n训练技能 :";
	if( sizeof(MY_ALL_SKILL) )
	foreach( list, int tmp in MY_ALL_SKILL ) {
		if( my_sk[list]>=100 ) continue;
		msg += sprintf("\n    %-30s -> %2d    %d 点经验。",
			to_chinese(list)+"("+list+")", my_sk[list]+1, sk_next_exp(my_sk[list]+1) );
	}
	me->start_more(msg);
	return 1;
}

int do_train(string arg)
{
	object me = this_player();
	string *skill, learn_sk;
	int my_skill, num, test_lv;
	mapping MY_ALL_SKILL, dbase;

	if( !arg ) return notify_fail("语法 : train [多少] <技能名字>\n\n请用 list 指令察看这里所能提供的训练内容。\n");

	dbase = me->query_entire_dbase();

	switch( dbase["class"] ) {
		case "冒险者":		MY_ALL_SKILL = ADVENTURER_SKILLS;	break;
		case "战士":		MY_ALL_SKILL = WARRIOR_SKILLS;		break;
		case "魔法师":		MY_ALL_SKILL = MAGE_SKILLS;		break;
		case "牧师":		MY_ALL_SKILL = CLERIC_SKILLS;		break;
		default:		return 0;
	}
	skill = keys(MY_ALL_SKILL);

	if( sscanf(arg, "%d %s", num, learn_sk) != 2 ) {
		num = 1;
		learn_sk = arg;
	}
	if( num<1) num = 1;

	if( member_array(learn_sk, skill) == -1 )
		return notify_fail("这里不提供这种训练 !\n");

	for(int i=0; i<num; i++) {
		my_skill = me->query_skill(learn_sk, 1);

		if( my_skill >= MY_ALL_SKILL[learn_sk] )
			return notify_fail("很抱歉，你的职业只能训练到目前这种地步。\n");

		test_lv = dbase["max_lv"]*6/7;	// 假设 30 级时, 可以学到所有技能

		if( dbase["level"] <= test_lv )
			if( my_skill > dbase["level"]*3 )
				return notify_fail("很抱歉，你的等级只能训练到目前这种地步。\n");

		if( !SKILL_D(learn_sk)->valid_learn(me) )
			return notify_fail("很抱歉, 这个技能没办法经由训练的方式提升。\n");

		if( !me->check_exp(sk_next_exp(my_skill+1)) )
			return notify_fail("你的经验值不够。\n");

		printf("你的%s技能现在提升到 %d 了。\n", to_chinese(learn_sk), my_skill+1);
		me->set_skill(learn_sk, my_skill+1);
		me->pay_exp( sk_next_exp(my_skill+1) );
	}
	me->save();
	log_file("train", sprintf("[%s]%s train %s to %d\n", ctime(time())[0..19], me->query("id"), learn_sk, me->query_skill(learn_sk, 1) ));
	return 1;
}

int do_advance(string arg)
{
	object me = this_player();
	string *attr_list = ({"str","dex","int","kar","sta","con"});
	mapping dbase;
	int exp;

	if( !arg || arg == "") return notify_fail("你要提升什么？等级(level)还是属性？\n");
	arg = lower_case(arg);
	dbase = me->query_entire_dbase();

// 提升等级
	if( arg == "level") {
		if( dbase["level"] >= me->query("max_lv") ) return notify_fail("你已经升到最高级了。\n");
		if( dbase["level"] >= 35 ) return notify_fail("你已经升到最高级了。\n");
		if( !me->check_exp(exp = level_next_exp(dbase["level"]+1)) ) return notify_fail("你的经验值不够。\n");
		me->add("level", 1);
		me->pay_exp(exp);
		me->setup();
		me->save();
		message_vision("$N的等级现在提升到 "+dbase["level"]+"。\n", me);
		return 1;
	}
// 提升属性
	if( member_array(arg, attr_list) == -1 ) return notify_fail("指令格式 : advance < 属性 || level >\n");
	if( dbase[arg] >= dbase["level"]+1 ) return notify_fail("你的"+to_chinese(arg)+"已经达到目前等级的最大值了。\n");
	if( !me->check_exp(exp = attr_next_exp(dbase["level"]+1)) ) return notify_fail("你的经验值不够。\n");
	me->add(arg, 1);
	me->pay_exp(exp);
	me->setup();
	me->save();
	write("你的"+to_chinese(arg)+"现在提升到 "+dbase[arg]+"。\n");
	return 1;
}

private int level_next_exp(int level)
{
	int exp;
	exp = level*level*level*35 + 30;
	return exp;
}

private int attr_next_exp(int level)
{
	int exp;
	exp = level*level*level*30 + 30;
	return exp;
}

private int sk_next_exp(int level)
{
	int exp;
	exp = level*4 + level*level*10 + 30;
	return exp;
}

/*
> cost
你已经升到最高级了。
并且你有 212533885 点经验可以用来提升属性与技能。
提升属性 :
    运气(kar)                      -> 31    891607 点经验。
训练技能 :
    魔法充电(recharge)             -> 91    89788 点经验。
    巫术(wizard_magic)             -> 81    55125 点经验。
    魔法知识(magic)                -> 96    114591 点经验。
    杖类武器(staff)                ->  1    236 点经验。
    施法(cast)                     -> 91    89788 点经验。
    闪躲(dodge)                    -> 71    28795 点经验。
    法器使用(invoke)               -> 91    89788 点经验。
    冥思(meditate)                 -> 44    4476 点经验。
    匕首类武器(dagger)             ->  1    236 点经验。

> list
在这里所能训练的技能有:
    魔法充电(recharge)              上限 = 100
    巫术(wizard_magic)              上限 = 100
    魔法知识(magic)                 上限 = 100
    杖类武器(staff)                 上限 = 100
    施法(cast)                      上限 = 100
    闪躲(dodge)                     上限 = 100
    法器使用(invoke)                上限 = 100
    冥思(meditate)                  上限 = 100
    魔杖类武器(wand)                上限 = 100
    匕首类武器(dagger)              上限 = 100

> train

语法 : train [多少] <技能名字> 

请用 list 指令察看这里所能提供的训练内容。

> train cost
这里不提供这种训练 !
> train cast
很抱歉，你的职业只能训练到目前这种地步。

*/
