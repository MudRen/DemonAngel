//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/develop.c
// by bor @DA 2/23, 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#define MAX_DEVELOP	70			// �Լ�������߷�չ����,���鲻Ҫд 100, ����δ�����Ѿ�������

int main(object me, string arg)
{
	string id, dev, *list;
	int cost;
	mapping DEVELOP = ([	// �����������������Ŀ�Ļ�, ֱ���ڴ˲��ͺ���,���÷�ɽԽ�뵽����
				//	by bor @DA 2/23, 2003
		"tavern" :		"�ù�",			// ��Ϣ������һ�� mob
		"smith" :		"����",			// ������õ�����
		"armory" :		"������",		// ������õ�װ��
		"barracks" :		"��Ӫ",			// ���ո��߼��Ĳ���, ��չӢ����
		"trainyard" :		"ѵ����",		// ��չ�µ�ְҵ�뼼��
		"gate" :		"�ؿ�",			// ����������ʩ��������ǿ
		"stable" :		"���\",		// ����������ǿ׳����ƥ������
		"magic_tower" :		"ħ����",		// ��չ�·���, ��չħ����
		"church" :		"����",			// ��չ�·���, ��չʥ��
		"furnace" :		"ħ��¯",		// ��ǿ�������ߵ�����
		"hero_guild" :		"Ӣ�ۻ��",		// �ٻ�ǿ����Ȼ������з����
	]);


	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");

	id = me->query("kingdom/id");

	if(!arg) {
		write(full_kingdom(id)+"�Ľ����﷢չ�ʽ�״�� :\n");
		foreach( dev, string tmp in DEVELOP )
			printf("    %-32sĿǰ���� %3d / ʣ���ʽ� %d\n", tmp+"("+dev+")",
			develop_data(id, "query_par", dev, "dev"),
			develop_data(id, "query_par", dev, "gold") );
		reset_eval_cost();
		return 1;
	}

	if( sscanf(arg, "%s %d", dev, cost) != 2 )
		return notify_fail("ָ���ʽ : develop <���⽨��������> <Ͷ������>\n");

	if(!kingdom_data(id, "special_room", "check", dev))
		return notify_fail("���û�� "+dev+" �����͵����⽨����, �޷����з�չ��\n");

	dev = lower_case(dev);
	list = keys(DEVELOP);
	if( member_array(dev, list) == -1 ) return notify_fail("û�����������⽨�������͡�\n");

	if( cost > 0) {
		if( develop_data(id, "query_par", dev ) )
		if( develop_data(id, "query_par", dev, "dev") >= MAX_DEVELOP )
			return notify_fail("Ͷ�ʷ�չ�Ѿ�ȫ��������Ҫ��Ͷ�ʡ�\n");

		if( kingdom_data(id, "data", "query_par", "gold") < cost )
			return notify_fail("����Ŀǰû����ô��Ǯ�ɹ�Ͷ�ʡ�\n");
		if( cost < 50000 ) return notify_fail("Ͷ������һ��Ҫ 50000 ��ҡ�\n");
		if( cost > 2000000 ) return notify_fail("Ͷ�ʲ�Ҫ���� 200 ���ҡ�\n");
		CHANNEL_D->do_channel(me, "kingdom", sprintf("������Ͷ���� "+cost+" ö��ҽ���"+DEVELOP[dev]+"���������ҵ�ķ�չ��"));
		log_file("kingdom/develop", sprintf("%s:%s[%s] Ͷ�� "+ cost +" gold on %s\n",
			ctime(time())[0..15], geteuid(me), query_ip_name(me), id ));
	} else {
		if( develop_data(id, "query_par", dev, "gold") < -cost )
			return notify_fail("��Ͷ����ҵ����û��Ͷ����ô�࣬�޷����ա�\n");
		if( 5000000+cost < 0 ) return notify_fail("�����ʽ�������� 500 �����¡�\n");
		CHANNEL_D->do_channel(me, "kingdom", sprintf("������"+DEVELOP[dev]+"���������ҵ�ķ�չ�ʽ����ջ� "+(-cost)+" ö��ҡ�"));
		log_file("kingdom/develop", sprintf("%s:%s[%s] ���� "+ -cost +" gold on %s\n",
			ctime(time())[0..15], geteuid(me), query_ip_name(me), id ));
	}
	develop_data(id, "add", dev, "gold", cost);
	kingdom_data(id, "data", "add", "gold", -cost);
	return 1;
}

int help(object me)
{
write(@HELP

ָ���ʽ : develop <���⽨��������> <Ͷ������>

���ǹ������������չ���⽨�����ָ������⽨������ɵ�ʱ��, ����
�Ĺ�����δ��ȫ, ���ʱ��ʹ�� develop ָ������չ����, ʹ���ǵĹ��ܸ���
���ӵ����¡��ʵ��Ĵ��䷢չ���з���ʹ�����ߵĽ����ศ���, ͬʱ, ĳЩ
���⽨��ֻ�ڷ�չ��һ���̶�ʱ�Ż���֡���Ͷ��Ľ�����Ǹ���ʱ���Ὣ��
Ͷ��Ľ���ջع��⡣

Ŀǰ��Ҫ��չ�����⽨������ :

        ����    ��������        ��չ��
----------------------------------------------------------------------
     tavern     �ưɡ��ù�      ��Ϣ������һ�� mob
     smith      ����		������õ�����
     armory	������		������õ�װ��
     barracks   ��Ӫ            ���ո��߼��Ĳ���, ��չӢ����
     trainyard  ѵ����          ��չ�µ�ְҵ�뼼��
     gate       �ؿ�            ����������ʩ��������ǿ
     stable	���		����������ǿ׳����ƥ������
   magic_tower  ħ����          ��չ�·���, ��չħ����
     church     ����		��չ�·���, ��չʥ��
     furnace	ħ��¯		��ǿ�������ߵ����� 
   hero_guild   Ӣ�ۻ��        �ٻ�ǿ����Ȼ������з����

��������κβ��������ῴ�������﷢չ����״�����б�

���������Ѷ : build, research

HELP
	);
	return 1;
}

/*

> develop
���(sky)�Ľ����﷢չ�ʽ�״�� :
    ħ����(magic_tower)             Ŀǰ����  14 / ʣ���ʽ� 252050
    ħ��¯(furnace)                 Ŀǰ����   3 / ʣ���ʽ� 387600
    ����(smith)                     Ŀǰ����  13 / ʣ���ʽ� 244450
    ������(armory)                  Ŀǰ����  14 / ʣ���ʽ� 239325
    ���(stable)                    Ŀǰ����   0 / ʣ���ʽ� 389000
    �ؿ�(gate)                      Ŀǰ����  13 / ʣ���ʽ� 157925
    �ù�(tavern)                    Ŀǰ����   3 / ʣ���ʽ� 189650
    Ӣ�ۻ��(hero_guild)            Ŀǰ����   0 / ʣ���ʽ� 589000
    ѵ����(trainyard)               Ŀǰ����   0 / ʣ���ʽ� 291000
    ����(church)                    Ŀǰ����   3 / ʣ���ʽ� 189425
    ��Ӫ(barracks)                  Ŀǰ����   0 / ʣ���ʽ� 191000

*/