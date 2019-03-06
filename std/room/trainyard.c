//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
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
		case "ð����":		MY_ALL_SKILL = ADVENTURER_SKILLS;	break;
		case "սʿ":		MY_ALL_SKILL = WARRIOR_SKILLS;		break;
		case "ħ��ʦ":		MY_ALL_SKILL = MAGE_SKILLS;		break;
		case "��ʦ":		MY_ALL_SKILL = CLERIC_SKILLS;		break;
		default:
			write("Ŀǰ�����ְҵ��û���ڹ滭�ڣ��޷�ѧϰ�κμ��ܡ�\n");
			return 1;
	}
	if( !mapp(MY_ALL_SKILL) || (mapp(MY_ALL_SKILL) && zerop(keys(MY_ALL_SKILL))))
		return notify_fail("Ŀǰ���ְҵ����û�滭�ü��ܣ��޷�ѧϰ��\n");

	msg = "����������ѵ���ļ�����:\n";
	foreach(string skill, int tmp in MY_ALL_SKILL ) {
		msg += sprintf("    %-38s ���� = %d\n", to_chinese(skill)+"("+skill+")", tmp);
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
		msg = "�㻹��Ҫ "+level_next_exp(dbase["level"]+1)+" �㾭�����������\n";
	else msg = "��ľ���ֵ�Ѿ��ﵽ������׼�ˡ�\n";

	msg += "�������� "+dbase["exp"]+" �㾭������������������뼼�ܡ�\n";
	msg += "�������� :";

	foreach( list, int tmp in ATTR_LIMIT ) {
		msg += sprintf("\n    %-30s -> %2d    %d �㾭�顣",
			to_chinese(list)+"("+list+")", (me->query(list)+1), attr_next_exp(me->query(list)+1) );
	}

	switch( dbase["class"] ) {
		case "ð����":		MY_ALL_SKILL = ADVENTURER_SKILLS;	break;
		case "սʿ":		MY_ALL_SKILL = WARRIOR_SKILLS;		break;
		case "ħ��ʦ":		MY_ALL_SKILL = MAGE_SKILLS;		break;
		case "��ʦ":		MY_ALL_SKILL = CLERIC_SKILLS;		break;
	}

	if( !me->query_skills() ) my_sk = ([]);
	else my_sk = me->query_skills();

	msg += "\nѵ������ :";
	if( sizeof(MY_ALL_SKILL) )
	foreach( list, int tmp in MY_ALL_SKILL ) {
		if( my_sk[list]>=100 ) continue;
		msg += sprintf("\n    %-30s -> %2d    %d �㾭�顣",
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

	if( !arg ) return notify_fail("�﷨ : train [����] <��������>\n\n���� list ָ��쿴���������ṩ��ѵ�����ݡ�\n");

	dbase = me->query_entire_dbase();

	switch( dbase["class"] ) {
		case "ð����":		MY_ALL_SKILL = ADVENTURER_SKILLS;	break;
		case "սʿ":		MY_ALL_SKILL = WARRIOR_SKILLS;		break;
		case "ħ��ʦ":		MY_ALL_SKILL = MAGE_SKILLS;		break;
		case "��ʦ":		MY_ALL_SKILL = CLERIC_SKILLS;		break;
		default:		return 0;
	}
	skill = keys(MY_ALL_SKILL);

	if( sscanf(arg, "%d %s", num, learn_sk) != 2 ) {
		num = 1;
		learn_sk = arg;
	}
	if( num<1) num = 1;

	if( member_array(learn_sk, skill) == -1 )
		return notify_fail("���ﲻ�ṩ����ѵ�� !\n");

	for(int i=0; i<num; i++) {
		my_skill = me->query_skill(learn_sk, 1);

		if( my_skill >= MY_ALL_SKILL[learn_sk] )
			return notify_fail("�ܱ�Ǹ�����ְҵֻ��ѵ����Ŀǰ���ֵز���\n");

		test_lv = dbase["max_lv"]*6/7;	// ���� 30 ��ʱ, ����ѧ�����м���

		if( dbase["level"] <= test_lv )
			if( my_skill > dbase["level"]*3 )
				return notify_fail("�ܱ�Ǹ����ĵȼ�ֻ��ѵ����Ŀǰ���ֵز���\n");

		if( !SKILL_D(learn_sk)->valid_learn(me) )
			return notify_fail("�ܱ�Ǹ, �������û�취����ѵ���ķ�ʽ������\n");

		if( !me->check_exp(sk_next_exp(my_skill+1)) )
			return notify_fail("��ľ���ֵ������\n");

		printf("���%s�������������� %d �ˡ�\n", to_chinese(learn_sk), my_skill+1);
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

	if( !arg || arg == "") return notify_fail("��Ҫ����ʲô���ȼ�(level)�������ԣ�\n");
	arg = lower_case(arg);
	dbase = me->query_entire_dbase();

// �����ȼ�
	if( arg == "level") {
		if( dbase["level"] >= me->query("max_lv") ) return notify_fail("���Ѿ�������߼��ˡ�\n");
		if( dbase["level"] >= 35 ) return notify_fail("���Ѿ�������߼��ˡ�\n");
		if( !me->check_exp(exp = level_next_exp(dbase["level"]+1)) ) return notify_fail("��ľ���ֵ������\n");
		me->add("level", 1);
		me->pay_exp(exp);
		me->setup();
		me->save();
		message_vision("$N�ĵȼ����������� "+dbase["level"]+"��\n", me);
		return 1;
	}
// ��������
	if( member_array(arg, attr_list) == -1 ) return notify_fail("ָ���ʽ : advance < ���� || level >\n");
	if( dbase[arg] >= dbase["level"]+1 ) return notify_fail("���"+to_chinese(arg)+"�Ѿ��ﵽĿǰ�ȼ������ֵ�ˡ�\n");
	if( !me->check_exp(exp = attr_next_exp(dbase["level"]+1)) ) return notify_fail("��ľ���ֵ������\n");
	me->add(arg, 1);
	me->pay_exp(exp);
	me->setup();
	me->save();
	write("���"+to_chinese(arg)+"���������� "+dbase[arg]+"��\n");
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
���Ѿ�������߼��ˡ�
�������� 212533885 �㾭������������������뼼�ܡ�
�������� :
    ����(kar)                      -> 31    891607 �㾭�顣
ѵ������ :
    ħ�����(recharge)             -> 91    89788 �㾭�顣
    ����(wizard_magic)             -> 81    55125 �㾭�顣
    ħ��֪ʶ(magic)                -> 96    114591 �㾭�顣
    ��������(staff)                ->  1    236 �㾭�顣
    ʩ��(cast)                     -> 91    89788 �㾭�顣
    ����(dodge)                    -> 71    28795 �㾭�顣
    ����ʹ��(invoke)               -> 91    89788 �㾭�顣
    ڤ˼(meditate)                 -> 44    4476 �㾭�顣
    ذ��������(dagger)             ->  1    236 �㾭�顣

> list
����������ѵ���ļ�����:
    ħ�����(recharge)              ���� = 100
    ����(wizard_magic)              ���� = 100
    ħ��֪ʶ(magic)                 ���� = 100
    ��������(staff)                 ���� = 100
    ʩ��(cast)                      ���� = 100
    ����(dodge)                     ���� = 100
    ����ʹ��(invoke)                ���� = 100
    ڤ˼(meditate)                  ���� = 100
    ħ��������(wand)                ���� = 100
    ذ��������(dagger)              ���� = 100

> train

�﷨ : train [����] <��������> 

���� list ָ��쿴���������ṩ��ѵ�����ݡ�

> train cost
���ﲻ�ṩ����ѵ�� !
> train cast
�ܱ�Ǹ�����ְҵֻ��ѵ����Ŀǰ���ֵز���

*/
