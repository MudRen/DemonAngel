//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
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
这个函数是用来判定一个物件 (this_object()) 是否付得起 amount 这个价钱.
若传回 0 表示这个物件并没有这么多钱, 传回 1 表示物件有这么多钱, 而且
有正确的钱币种类. 传回 2 则表示此物件虽然有足够的钱, 却没有正确的钱币
种类. */
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

// 付钱
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
	if( amount > 0 ) error("F_FINANCE：金钱不足。\n");
}

// 存多少钱去银行内
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

// 从银行内领钱
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

// 拿钱
int got_money(int amount)
{
	object me;

	me = this_player();
	if( amount<=0 ) return 0;
	me->add("gold", amount);
	amount = 0;
	return 1;
}

// 检查玩家的 exp
int check_exp(int exp)
{
	int my_exp;

	my_exp = query("exp");
	if( !exp ) return 0;
	if( my_exp < exp )
		return 0;
	return 1;
}

// 付 exp
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

	if( query("list/pet") ) {	// 1. 若有宠物
		// 2. 若有骑上来
//		log_file("pet_exp", sprintf("%s has pet\n", query("list/pet/file") ) );
		if( query_temp("riding_pet")==1 ) {
			// 3. 按照 pet, player 的 Level 去依比例分经验直
			if( objectp(ob = find_object( query("list/pet/file") )) ) {
				pet_exp = ob->query("level") * exp / ( ob->query("level") + query("level") );
				add("list/pet/exp", pet_exp);	// 写入到玩家身上
				tell_object(this_object(), sprintf("( %s 分得 %d 点经验值。)\n", ob->query("name"), pet_exp ) );
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

	// 1. 依照 ob Level 来计算何时升级
	Max_exp = ob->query("level") * ob->query("level") * 30000 + exp/10;
//	Max_exp = ob->query("level") * ob->query("level") * 500 + exp/10;

	if( exp <= Max_exp ) return ;
	attr = list[random(6)];

	if(attr !="level") add("list/pet/attr/"+attr, 1);
	else add("list/pet/"+attr, 1);

	ob->add(attr, 1);
	CHAR_D->setup_char( ob );

	set("list/pet/exp", exp-Max_exp);

	tell_object(this_object(), sprintf("( %s 获得 %s 一级的提升。)\n", ob->query("name"), attr ) );
	return ;
}

