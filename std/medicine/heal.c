//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/medicine/heal.c
// by bor @RG, DA

inherit COMBINED_ITEM;

void init()
{
	add_action("do_drink", "drink");
}

int do_drink(string arg)
{
	object ob;
	if( !id(arg) ) return notify_fail("��Ҫ��ʲô��\n");
	if( !ob = present(arg, this_player()) ) return notify_fail("��Ҫ��ʲô��\n");
	this_player()->receive_heal(query("type"), query("heal"));
	message_vision("$N���๾��غ���һ"+query("unit") + "$n��\n", this_player(), ob);
	add_amount(-1);
	return 1;
}
