//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/potion/bean_eat.c
// 这是一个 马豆 继承程式

#pragma optimize
#pragma save_binary

inherit COMBINED_ITEM;

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	if(userp(this_player())) return 0;		// 限制玩家吃起来
	if( !id(arg) ) return notify_fail("你要吃什么？\n");
	if(query("eat_msg")) message_vision(query("eat_msg")+"\n", this_player(), this_object());
	else message_vision("$N大口大口的咬了一" + query("unit") + query("name") + "。\n", this_player() );
	this_player()->feed_heal(query("kind"), query("cure"));
	add_amount(-1);
	return 1;
}

int is_bean() { return 1; }

int feed_heal(string type, int heal)
{
	int val;

	if( heal < 0 ) error("F_DAMAGE: 恢复值为负值。\n");
	if( type!="kee" )
		error("F_DAMAGE: 恢复种类错误( 只能是 kee 其中之一 )。\n");

	val = (int)query_temp("apply/"+type) + heal;

	if( val > (int)query_temp("pet/" + type) ) set_temp("apply/" + type, (int)query_temp("pet/" + type));
	else set_temp("apply/" + type, val );

	return heal;
}
