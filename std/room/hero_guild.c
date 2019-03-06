//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/hero_guild.c
// Ӣ�ۻ��

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
	add_action("do_list", "list");		// �������ķ�չ���
	add_action("do_drill", "drill");
}

int do_list(string arg)
{
	string msg = "";
	object me = this_player();

	if( !check_class(me) ) return notify_fail("�����������, ��������ѧϰ���׼��ܡ�\n");
	if( !mapp(check_class(me)) || (mapp(check_class(me)) && zerop(keys(check_class(me))) ) )
		return notify_fail("Ŀǰ��ְҵ, ���׼��������з��׶�, �����ڴ���\n");

	msg += "�����������ѧ���Ľ��׼����� :\n";
	foreach(string can_drill_list, int tmp in check_class(me))
		msg += sprintf("    %-32s Ŀǰѧ��  %d %% �´�������Ҫ  %d %s\n",
			to_chinese(can_drill_list)+"("+can_drill_list+")",
			me->query_skill(can_drill_list, 1),
			skill_next_exp(me->query_skill(can_drill_list)+1), "�㾭��" );
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

	if( !check_class(me) ) return notify_fail("�����������, ��������ѧϰ���׼��ܡ�\n");
	if( !arg ) return notify_fail("����ѧʲô���ܣ�\n");

	can_drill = check_class(me);
	skill = keys(can_drill);
	if( sscanf(arg, "%d %s", num, learn_sk) != 2 ) {
		num = 1;
		learn_sk = arg;
	}
	if( num<1 ) num = 1;
	if( member_array(learn_sk, skill) == -1 )
		return notify_fail("���ְҵ��û�д���ܿ�ѧ��\n");

	dbase = me->query_entire_dbase();

	for(int i=0; i<num; i++) {
		my_skill = me->query_skill(learn_sk, 1);
		if( my_skill >= can_drill[learn_sk] )
			return notify_fail("��������Ѿ���Ŀǰ����ѧ�����ֵ�ˡ�\n");
		// ��ʹ�� test_lv ����������������ޡ�
		// ����˵������ level �� 40 ��ʱ�����ܾͿ���������ְҵ��ȫ����
		test_lv = dbase["max_lv"]*0.8;

		if( dbase["level"] <= test_lv )
		if( my_skill > dbase["level"]*2 )
			return notify_fail("�����, ��Ŀǰֻ��ѧ������̶ȡ�\n");

		if( !SKILL_D(learn_sk)->valid_learn(me) ) return 0;

		if( !me->check_exp(skill_next_exp(my_skill+1)) )
			return notify_fail("��ľ���ֵ������\n");

		printf("���%s�������������� %d �ˡ�\n", to_chinese(learn_sk), my_skill+1);
		me->set_skill(learn_sk, my_skill+1);
		me->pay_exp( skill_next_exp(my_skill+1) );
	}
	return 1;
}

// ���Ե�����ѧϰ������ְҵ�Լ�����
mixed check_class(object me)
{
	mapping adv_spell;

	switch( me->query("class") ) {
		case "ħ��ʦ":
			if( me->query_skill("magic", 1) < 75 ) {
				return 0;
			} else if( me->query_skill("magic", 1) >= 75 ) {
				adv_spell = ADV_MAGE_1;
			} else return 0;
			break;
		case "��ʦ":
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
