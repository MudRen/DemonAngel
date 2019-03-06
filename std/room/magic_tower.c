//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/magic_tower.c
// by bor @DA, 

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

private int spell_next_exp(int level);
private mapping got_list( object me );

mapping MAGE_1 = ([
	"magefire"	:	95,
	"magic_shield"	:	95,
	"wolf"		:	95,
	"coating"	:	95,
	"arc_fire"	:	95,
]);

mapping MAGE_2 = ([
	"fireball"	:	90,
	"magic_missile"	:	90,
	"stun"		:	85,
	"stone"		:	85,
	"storm"		:	85,
	"ogre_power"	:	85,
]);

mapping MAGE_3 = ([
	"mind_blast"	:	80,
]);

mapping CLERIC_1 = ([
	"firefly"	:	95,
	"strong"	:	95,
	"first_aid"	:	95,
	"fist"		:	95,
	"cure"		:	95,
	"heal"		:	95,
]);

mapping CLERIC_2 = ([
]);

mapping CLERIC_3 = ([]);

void init()
{
	add_action("do_list","list");
	add_action("do_study","study");
}

private int do_list(string arg)
{
	string msg="";
	object me = this_player();
	mapping spell=([]);

	spell = got_list(me);

	if( !mapp(spell) || zerop(spell) ) return notify_fail("���ְҵû�취ѧϰ�κη�����\n");

	msg += "��Ŀǰ����ѧϰ���ķ����У�";
	foreach(string list, int tmp in spell) {
		msg += sprintf("\n%-30s Ŀǰ���� %2d%%, �´����� %6d �㾭��ֵ��������",
			list, me->query_spell(list,1), spell_next_exp(me->query_spell(list,1)+1) );
	}
	me->start_more(msg+"\n");
	return 1;
}

private mapping got_list( object me )
{
	int learn;
	mapping base_spell=([]);

	switch( me->query("class") ) {
		case "ħ��ʦ" :
			learn = me->query_skill("magic", 1);
			if( learn <= 50 ) base_spell = MAGE_1;
			else if( learn >50 && learn <= 70 )
				base_spell = MAGE_1 + MAGE_2;
			else
				base_spell = MAGE_1 + MAGE_2 + MAGE_3;
			return base_spell;
			break;
		case "��ʦ" :
			learn = me->query_skill("magic", 1);
			if( learn <= 50 ) base_spell = CLERIC_1;
			else if( learn >50 && learn <= 70 )
				base_spell = CLERIC_1 + CLERIC_2;
			else
				base_spell = CLERIC_1 + CLERIC_2 + CLERIC_3;
			return base_spell;
			break;
		default:
			return 0;
	}
	return 0;
}

private int do_study(string arg)
{
	object me = this_player();
	mapping spell=([]);
	string *list=({}), learn_spell;
	int num, my_spell, exp;

	if( !arg || arg == "") return notify_fail("ָ���ʽ��study <��������>\n");
	arg = lower_case(arg);

	spell = got_list(me);
	if( !mapp(spell) || zerop(spell) ) return notify_fail("���ְҵû�취ѧϰ�κη�����\n");
	list = keys(spell);
	if( zerop(list) ) return notify_fail("���ְҵû�취ѧϰ�κη�����\n");

	if( sscanf(arg, "%d %s", num, learn_spell) != 2 ) {
		num = 1;
		learn_spell = arg;
	}
	if( num<1) num = 1;

	if( member_array(learn_spell, list) == -1 ) return notify_fail("Ŀǰ�����Ŵ˷�����\n");

	for(int i=0; i<num; i++) {
		my_spell = me->query_spell(learn_spell, 1);
		if( my_spell >= spell[learn_spell] )
			return notify_fail("�ܱ�Ǹ�����ְҵֻ��ѵ����Ŀǰ���ֵز���\n");
		if( my_spell>=65 && my_spell >= develop_data(environment(me)->query("kingdom_id"), "query_par", "magic_tower", "dev") )
			return notify_fail("�������﷢չ���㡣\n");
		if( my_spell >= me->query_skill("magic",1)*3/2 )
			return notify_fail("������ħ��֪ʶ��������������ķ����ˡ�\n");
		if( !me->check_exp(exp = spell_next_exp(my_spell+1)) ) return notify_fail("��ľ���ֵ������\n");
		me->set_spell(learn_spell, my_spell+1);
		me->pay_exp(exp);
		write("���"+to_chinese(learn_spell)+"�Ѿ�ѧ�� "+me->query_spell(learn_spell, 1)+" %%�ˡ�\n");
	}
	me->save();
	return 1;
}

private int spell_next_exp(int level)
{
	int exp;
	exp = level*level*15 + level* 3 + 30;
	return exp;
}

/*

mage_magic:

�� ��ʦ֮��(magefire) 
���һ��ħ������, Ư����ħ��ʦ��ǰ��, ���������ܡ� 

�� ����ָ(arc_fire) 
��ָ�ⷢ��һ�����ȵ绡, �Ե�����ɵ���˺��� 

�� ħ����Ĥ(coating) 
�������϶���һ��ħ���������������������˺����� 

�� Ʈ��(float) 
ʹʩ����Ʈ������������Ʈ���ض���һЩΣ�յ����塣 

�� ħ����(magic_missle) 
����һ��ħ������������ˣ��Ե������ħ���˺��� 

�� �ǲ���֮��(magic_shield) 
������Χ�Ŀ������γ�һ�����εĶ��ơ� 

�� ������(wolf) 
�ٻ���һֻ��õ��ǣ�����ķ�����Чǰ�����ᾡȫ��
�����㡣 

�� ������(fireball) 
�������澫����������Գ��ȵĻ��򹥻����ˡ� 

�� ������(identify) 
���üž���ڤ˼�Լ�������Ʒ����ϸ���ʡ� 

�� ��ħ������(anti_magic) 
����һƬ��������ħ������������������������������
��ʩ���ķ����� 

�� �����(stun) 
����һ���糡����������ڵ糡�еĵ��ˣ����˵����
�˺����⣬���� �ĵ��˻������һ��ʱ�䡣 

�� ��ʯ��(stone) 
�����˱��ʯͷ���������ĵ��˻���һ��ʱ�䲻�ܶ���
��������Եģ� ����ƤҲ���ñȽ�Ӳ�� 

�� ����(poison) 
��թ��ħ��ʦ��ϲ���ķ�������а����������������
���ڣ������� �����ٶ���һ�����͵��˶������������ӡ� 

�� ��ѩ�籩(storm) 
�ٻ���ѩ����������������һ�����͵ı�ѩ�籩���õ�
�˱��ܴ̹Ǻ� ������Ϯ�� 

�� ��ħ֮��(ogre_power) 
���Լ�������ħ��񱩣���ʹս������������� 

�� �������(dragon) 
���Լ�ת����һֻ���������ҹ������ˣ��ڶ��ݵı�����
�������п��� ��ɵ����޷����Ƶ��˺���־塣 

�� ������(invisible) 
���Ǿ������е��ܷ������԰��Լ����͸�����Է�������
���ж������� ���������һ��ȱ�㣬���ƶ���ʱ���������
���Შ�������Ի���ʱ ʧȥЧ���� 

�� ������(lightning) 
�ٻ���ǿ���׵磬��������ڳ��ĵ��ˡ�����Ŀǰ��ǿ��
�׵�ϵ������ ����ֻ���ڻ���ʹ�á� 

�� ���ں���(flare) 
�ô�����ħ�������С�͵ĺڶ������úڶ����ĺ��ں�
�����������˺� ���ˡ���Ŀǰ��֪������ǿ�ķ�����ֻ��ϧ
���ں����Կ��ƣ�һ��ʩ�� ʧ�ܣ����е������ᱬ����ʩ��
�����ϡ� 

�� ��λ��(location) 
ʩ�������ô���ħ������ѡ���ĵط������Լ��ġ����
ֻҪ�ûɢ ȥ��ʩ���߱������ʱ׷Ѱ���Լ������
�����Լ�ѡ���ĵط��� 

�� ��������(gravity) 
����Ŀǰ����Ψһһ����ȫ�޷����ܻ�����˺��ķ�����
ʩ�����ڵ��� ���ܽ�����磬ʹ���������еĵ��˸��ܵ�����
���Ӻü���������ʹ�� ���������������ģ�ͬʱҲʹ���˸���
�ױ����С���������Ӵ�ĵ��ˣ� ����ϵ�����������г�
�������Ч����

cleric_magic:

�� ө����(firefly)
���֮����, ʹ�Լ����ϲ���һ��ө��, ���������ܵ�
��������û�й�Դ�� ��ˮ��, һ�����������, ө�������ɵ�
���ó��ˡ� 

�� ������(make_rope) 
��ͨ���ض��ȵط�ʱ, ���û�д�����, �������������
������ӡ���Ȼ���� ����������, ����û�а׳Ե����, �㻹
��Ҫ��Ǯ�ġ� 

�� ������(first_aid) 
��Ȱ���������������, ʹ�������˻ָ������ hp�� 
����ֻ��Ҫ��������� ����, �ʺϽϵ͵ȼ�����ʦ�� 

�� ��ȭ��(fist) 
����ս������һ��ȭ��֮���Դ������, �������ħ��
�˺��� 

�� Ʈ��(float) 
��ʹʩ���Ķ���Ʈ������, �Աܿ������ϵ�����, ��Ʈ��
�ض�, ������������ 

�� ף��(bless) 
����֮����, ������֮����ǿʩ�������ս����
�������� 

�� ������(cure) 
�ȼ������ߵ�һ��������÷���, ���Զ�ָ�һЩ hp �� 

�� �ָ���(heal) 
�����������߼��������÷���, ���Իָ� 20 �����ϵ� hp�� 

�� ����֮��(spirit_hammer) 
����ս���Э������ս����״�������˵����顣 

�� ǿ׳(strong) 
���������ߵ�����������ս������ͬʱҲ���԰����
�Ķ����� 

�� ӲƤ��(stone_skin) 
ʹ�����ߵ�Ƥ��Ӳ��(ʯ��), �����ӷ������� 

�� �ƶ���(cure_poison) 
����ʥ����������ʩ����������ϣ��԰������ų�а
�����������š� 

�� ʥˮ��(holy_water) 
ʩ����������ʥ����������ʥˮ����ָ����ŵ�����
��������ڳ������е��������ʥ�������˺������ǻ���
����ħ������������ħ�м�ǿ���˺�Ч���� 

�� ������(freeze) 
ʩ����������֮���ڳ������е��˶��ᡣ�����
���˺�����ǿ������ȴ��ǣ����ˣ�ʹ���ǵĻ������
�����������׻��С� 

�� ������(identify) 
���üž���ڤ˼�Լ�������Ʒ����ϸ���ʡ� 

�� ǿ���ָ�(restore) 
���״����ķ����������Խ����k�ľ�ˡ�����ǿ����
�ָ��Է�����Ч��Ҳ�ܺá� 

�� �־���(fear) 
����ս��ս���Ĳ��ҺͿ־崵����˵����У�ʹ����
�µ���֫������������ �ղ��Ρ� 

�� ����֮��(spectre_touch) 
ʩ���߰��Լ�ת�������壬�����������˵Ļ���������
��������������֮ת�����Լ���������������һ�ּ������
������������������ߵĵ��ˣ������п����� �����ķ����� 

�� ������(hazy) 
ʩ����ʹ�Լ�����������ʵ�һƬ�����˱㲻���׻���
�������൱��Ч�ķ����� ������ 

�� �¹���(moon_light) 
����һ���ڹ����������涼�ܼ�˵ķ�����ʩ��������
��������ŵİ�����ʹ��͵��¹����ڵ�����ʩ�������ϣ�
�������������ȡ���˵�������ת��Ϊҽ��ħ��ҽ��ʩ���ߡ�
���������ҽ��Ч��������ǿ���ָ��Ψһ��ȱ����ֻ����
�¹��յõ��ĵط�ʹ�á� 

�� ��ħ(demon_bane) 
�����߼�����ħ��������ʥˮ����ǿ�󣬲���ֻ�����
һ�����ˡ� 

�� ����ָ֮(death_touch) 
����һ�����Ѷȵ�ȴ�����Ч�ʵķ�����ʩ����������
���٣����ߵ��˵���ꡣ��������Ӧ�����Ҫ�󣬾���
����ǿ��ĵ���Ҳ�����̵�����ȥ�� 

�� ������(regeneration) 
��������������Ѷȵ���Ҳ�����ܳ�ݵķ�����ʩ����
���״����ķ��������񣬽��Ի�ȡһ����ʧ����ꡣ�����
���Ӧ����Ҫ����ô�Ѿ���ȥ���˾ͻ�õ� һ��ȫ�µ���
�壬����������һ���� 

�� ʥ����(holy_word) 
������ǿ������а����������ħ���˺�������ʤ������
һ����֪�ķ�����ʩ����������ʥ��������һ��а��ĵ�
�ˣ����ʩ���߱�������ǿ����������ʹ����û�����Ӵ�
��ֱ����Ϊֹ��

*/