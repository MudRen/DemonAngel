//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/potion/bean_eat.c
// ����һ�� �� �̳г�ʽ

#pragma optimize
#pragma save_binary

inherit COMBINED_ITEM;

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	if(userp(this_player())) return 0;		// ������ҳ�����
	if( !id(arg) ) return notify_fail("��Ҫ��ʲô��\n");
	if(query("eat_msg")) message_vision(query("eat_msg")+"\n", this_player(), this_object());
	else message_vision("$N��ڴ�ڵ�ҧ��һ" + query("unit") + query("name") + "��\n", this_player() );
	this_player()->feed_heal(query("kind"), query("cure"));
	add_amount(-1);
	return 1;
}

int is_bean() { return 1; }

int feed_heal(string type, int heal)
{
	int val;

	if( heal < 0 ) error("F_DAMAGE: �ָ�ֵΪ��ֵ��\n");
	if( type!="kee" )
		error("F_DAMAGE: �ָ��������( ֻ���� kee ����֮һ )��\n");

	val = (int)query_temp("apply/"+type) + heal;

	if( val > (int)query_temp("pet/" + type) ) set_temp("apply/" + type, (int)query_temp("pet/" + type));
	else set_temp("apply/" + type, val );

	return heal;
}
