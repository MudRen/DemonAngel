//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/potion/heal.c
// ����һ�� potion �̳г�ʽ

#pragma optimize
#pragma save_binary

inherit COMBINED_ITEM;

void init()
{
	add_action("do_drink", "drink");
}

int do_drink(string arg)
{
	if( !id(arg) ) return notify_fail("��Ҫ��ʲô��\n");
	if(query("eat_msg")) message_vision(query("eat_msg")+"\n", this_player(), this_object());
	else message_vision("$N�๾��غ���һ" + query("unit") + query("name") + "��\n", this_player() );
	this_player()->receive_heal(query("kind"), query("cure"));
	add_amount(-1);
	return 1;
}

int is_potion() { return 1; }
