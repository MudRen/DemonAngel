//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/spells.c
// by bor @DA

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mapping spell;
	string *sk_name, msg;

	seteuid(getuid());
	if( !arg ) ob = me;
	else {
		if( wizardp(me) ) {	// ���������ʦ������Բ쿴��ҵļ���
			arg = lower_case(arg);
			if( !ob = present(arg, environment(me)) )
				ob = find_player(arg);
			if( !ob ) ob = load_player(arg);
			if( !ob ) return notify_fail("û����λ������ϡ�\n");
		} else ob = me;
	}

	if( zerop(spell = ob->query_spells()) )
		return notify_fail( (ob==me?"��":ob->name_id())+"Ŀǰ��û��ѧ���κη�����\n");

	sk_name  = keys(spell);

	if( ob == me ) msg = "��Ŀǰ��ѧ���ķ�����\n\n";
	else msg = ob->name_id()+"Ŀǰ��ѧ���ķ�����\n\n";

	for(int i=0 ;i < sizeof(sk_name);i++) {
		msg += sprintf("%-43s%3d\n",to_chinese(sk_name[i])+"("+sk_name[i]+")",
			spell[sk_name[i]] );
	}

	if( !find_player(ob->query("id")) ) destruct(ob);
	reset_eval_cost();
	me->start_more(msg);
	return 1;
}

int help(object me)
{
	write(@HELP
���ܲ�ѯ

ָ���ʽ : spells

���ָ���������(��)��ѯ��ѧ���ķ�����

���ѶϢ : study, list, cost, skills

HELP
	);
	return 1;
}

/*
��Ŀǰ��ѧ���ķ����У�

ף�� (bless)                                90/ 90
���� (calm)                               80/ 80
������ (cure)                               90/ 90
�ƶ��� (cure_poison)                        90/ 90
����ָ֮ (death_touch)                      90/ 90
��ħ (demon_bane)                           90/ 90
������� (detect_invi)                      90/ 90
��ʹ�� (divine_dust)                        80/ 80
˫��ҽ�� (double_heal)                      80/ 80
�޴��� (enlarge)                            80/ 80
�־��� (fear)                               90/ 90
ө���� (firefly)                            90/ 90
������ (first_aid)                          90/ 90
��ȭ�� (fist)                               90/ 90
Ʈ�� (float)                                90/ 90
������ (freeze)                             90/ 90
Ѹ���� (haste)                              80/ 80
������ (hazy)                               90/ 90
�ָ��� (heal)                               90/ 90
��ʥ���� (holy_blast)                       80/ 80
��ʥ֮�� (holy_power)                       80/ 80
��ʥ���� (holy_spirit)                      80/ 80
ʥˮ�� (holy_water)                         90/ 90
ʥ���� (holy_word)                          90/ 90
������ (identify)                           90/ 90
������ (make_rope)                          90/ 90
�¹��� (moon_light)                         90/ 90
����֮�� (pure_shield)                      80/ 80
������ (regeneration)                       90/ 90
ǿ���ָ� (restore)                          90/ 90
ʥ���� (sanctuary)                          80/ 80
���� (silence)                            80/ 80
����֮�� (spectre_touch)                    90/ 90
���ٶ� (speedup)                            80/ 80
����֮�� (spirit_hammer)                    90/ 90
ӲƤ�� (stone_skin)                         90/ 90
ǿ׳ (strong)                               90/ 90

��Ŀǰ��ѧ���ķ�����

��ҹ��(moon_light)                         7
��Ȼ֮��(nature_music)                       7

*/