//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
/*  /feature/finance.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#pragma optimize
#pragma save_binary

#include <dbase.h>

void check_pet_exp(object ob, int exp);

/*
��������������ж�һ����� (this_object()) �Ƿ񸶵��� amount �����Ǯ.
������ 0 ��ʾ��������û����ô��Ǯ, ���� 1 ��ʾ�������ô��Ǯ, ����
����ȷ��Ǯ������. ���� 2 ���ʾ�������Ȼ���㹻��Ǯ, ȴû����ȷ��Ǯ��
����. */
int can_afford(int amount)
{
	int total;
	int gold;
	object me;

	me = this_player();
	gold = me->query("gold");
	total = 0;

	if( gold ) total += gold;
	if( total < amount ) return 0;
	return 1;
}

// ��Ǯ
int pay_money(int amount)
{
	int total;
	int gold;
	object me;

	me = this_player();
	gold = me->query("gold");
	total = 0;

	if( !gold ) return 0; 
	total = gold;
	if( total < amount ) return 0;
	if( total >= amount ) {
		me->add("gold",-amount);
		amount = 0;
	}
	if( amount > 0 ) error("F_FINANCE����Ǯ���㡣\n");
}

// �����Ǯȥ������
int deposit_bank(int amount)
{
	object me;

	me = this_player();
	if(amount <= 0 ) return 0;
	if( me->query("gold")<amount ) return 0;
	me->add("gold", -amount);
	me->add("bank_gold", amount);
	me->save();
	return 1;
}

// ����������Ǯ
int withdraw_bank(int amount)
{
	object me;

	me = this_player();
	if(amount <= 0 ) return 0;
	if( me->query("bank_gold")<amount ) return 0;
	me->add("bank_gold", -amount);
	me->add("gold", amount);
	me->save();
	return 1;
}

// ��Ǯ
int got_money(int amount)
{
	object me;

	me = this_player();
	if( amount<=0 ) return 0;
	me->add("gold", amount);
	amount = 0;
	return 1;
}

// �����ҵ� exp
int check_exp(int exp)
{
	int my_exp;

	my_exp = query("exp");
	if( !exp ) return 0;
	if( my_exp < exp )
		return 0;
	return 1;
}

// �� exp
int pay_exp(int exp)
{
	int my_exp;

	my_exp = query("exp");
	if( !exp ) return 0;
	if( my_exp < exp )
		return 0;
	add("exp", -exp); 
	return 1;
}

int got_exp(int exp)
{
	int pet_exp =0;
	object ob;

	if( query("list/pet") ) {	// 1. ���г���
		// 2. ����������
//		log_file("pet_exp", sprintf("%s has pet\n", query("list/pet/file") ) );
		if( query_temp("riding_pet")==1 ) {
			// 3. ���� pet, player �� Level ȥ�������־���ֱ
			if( objectp(ob = find_object( query("list/pet/file") )) ) {
				pet_exp = ob->query("level") * exp / ( ob->query("level") + query("level") );
				add("list/pet/exp", pet_exp);	// д�뵽�������
				tell_object(this_object(), sprintf("( %s �ֵ� %d �㾭��ֵ��)\n", ob->query("name"), pet_exp ) );
				check_pet_exp( ob, query("list/pet/exp") );
//				log_file("pet_exp", sprintf("%s, %s got exp: %d\n", query("id"), query("list/pet/file"), pet_exp ) );
			}
		}
	}
	add("exp", (exp - pet_exp)  );
	return 1;
}

void check_pet_exp(object ob, int exp)
{
	int Max_exp;
	string *list = ({ "str", "con", "dex", "sta", "int", "str", "level"  }), attr;

	// 1. ���� ob Level �������ʱ����
	Max_exp = ob->query("level") * ob->query("level") * 30000 + exp/10;
//	Max_exp = ob->query("level") * ob->query("level") * 500 + exp/10;

	if( exp <= Max_exp ) return ;
	attr = list[random(6)];

	if(attr !="level") add("list/pet/attr/"+attr, 1);
	else add("list/pet/"+attr, 1);

	ob->add(attr, 1);
	CHAR_D->setup_char( ob );

	set("list/pet/exp", exp-Max_exp);

	tell_object(this_object(), sprintf("( %s ��� %s һ����������)\n", ob->query("name"), attr ) );
	return ;
}

