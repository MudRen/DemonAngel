//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/obj/gift/red_bag.c
// by bor @DA, 3/5 2003

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR"�����"NOR, ({"red bag","red","bag"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","��������Ŵ�(open bag)�����ߴ��(put xxx)��ҵ�����ڡ�\n");
		set("value", 50);
		set("unit", "��");
		set("new", 1);
	}
	setup();
}

void init()
{
	if(userp(this_player())) {
		add_action("do_open","open");
		add_action("do_put","put");
	}
}

int do_open(string str)
{
	object me = this_player();

	if( !query("gold") ) return notify_fail("����һ���յĺ������\n");

	message_vision("$N���������, ���������� "+query("gold")+" ö��ҡ�\n", me, this_object() );

	me->got_money(query("gold"));
	destruct(this_object());
	return 1;
}

int do_put(string str)
{
	int num;
	object me = this_player();

	num = atoi(str);
	if(num==-1) return notify_fail("Ŀǰֻ�ܴ�Ž�ҡ�\n");
	if( !this_object()->query("new") ) return notify_fail("�����Ѿ����ý���ˡ�\n");
	if(num<100) return notify_fail("����Ҫ���һ��ö��ҲŹ����ɡ�\n");
	if(num>200000) return notify_fail("�������ֻ�ܰ�����ʮ�򣬷�����ֽ����ơ�\n");
	if(!me->can_afford(num)) return notify_fail("������û��ô��Ǯ���ԷŽ�������ڡ�\n");

	this_object()->set("gold", num);
	this_object()->delete("new");

	me->pay_money(num);

	message_vision("$N���������, ���ֽ� "+num+" ö��ҷ������ڡ�\n", me, this_object() );

	return 1;
}