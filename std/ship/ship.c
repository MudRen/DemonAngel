//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/ship/ship.c
// by bor @DA, 2/24 2003
/*
	��ֻ������, ���˴˷�( item ) ��, ���в��ٵķ�ʽ( NPC, ....)ȥ��, �˿���λ���ȥ׫д��
*/

#pragma optimize
#pragma save_binary

inherit ITEM;
#include <ansi.h>

void init()
{
	// �����������������Ļ�, ��ǵ��Լ��ж�
	add_action("do_board", "board");
	add_action("do_out", "out");
}

int do_board(string arg)
{
	object me = this_player(), ob, *all;

	if( environment(me) == this_object() ) return 0;	// �����ϴ��Ļ��Ͳ�������������
	if( !arg ) return notify_fail("��Ҫ����һ�Ҵ���\n");
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	arg = lower_case(arg);
	ob = present(arg, environment(me));
	if( !ob ) return notify_fail("��ȷ������һ�Ҵ���\n");
	if( ob->query("type")!="ship" ) return 0;
	tell_room(environment(me), sprintf(YEL"%s������%s��\n"NOR, me->name_id(1), ob->short(1) ), ({me}));
	me->direct_move(ob);
	tell_room(environment(me), sprintf(HIB"%s����%s��\n"NOR, me->name_id(1), ob->short(1) ), ({me}));
	return 1;
}

int do_out(string arg)
{
	object me = this_player(), ob;

	if( environment(me)!= this_object() ) return 0;
	if( this_object()->query("shiping") ) return notify_fail("�����н��У���Ҫ�������ȥ��\n");

	tell_room(environment(me), sprintf(HIB"%s�뿪%s���ߵ�����ȥ��\n"NOR, me->name_id(1), this_object()->name(1) ) , ({me}));

	if( !ob = find_object(this_object()->query("exits/out")) ) {
		call_other(this_object()->query("exits/out"), "???");
		ob = find_object(this_object()->query("exits/out"));
	}
	me->direct_move(ob);
	tell_room(environment(me), sprintf(HIB"%s��%s������\n"NOR, me->name_id(1), this_object()->name(1) ) , ({me}));
	return 1;
}
