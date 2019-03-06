//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/arrest.c
// by sbada @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#include <ansi.h>

#define ARR_COST	5000

int main(object me, string arg)
{
	string *list, msg ="", tar;
	object ob;

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fight() ) return notify_fail("��������ս���С�\n");
	if( !arg ) {
		if( !arrayp(list = kingdom_data(me->query("kingdom/id"), "arrest", "query_all")) ) return notify_fail("\n���Ŀǰ��û��ͨ���ˡ�\n");
		msg += "���������ͨ���� :\n";
		for( int i=0; i<sizeof(list); i++ ) {
			msg += sprintf("\t%-16s  ͨ��ʱ�� %s\n", list[i],
				kingdom_data(me->query("kingdom/id"), "arrest", "query_par", list[i])
			);
		}
		msg += "\n";
		me->start_more(msg);
		return 1;
	}

	// ȡ��ͨ��
	if(sscanf( arg, "%s cancel", tar ) == 1) {
		if( !(ob = find_player(tar)) ) ob = load_player(tar);
		if( !ob ) return notify_fail("������Ѿ������ڡ�\n");
		if( !kingdom_data(me->query("kingdom/id"), "arrest", "sub", tar) ) return notify_fail("\n���Ŀǰ��û��ͨ���ˡ�\n");
		if( arrayp(list = ob->query("arrest")) ) {
			if( member_array(me->query("kingdom/id"), list)!=-1 )
				ob->set("arrest", list - ({me->query("kingdom/id")}) );
			if( zerop(ob->query("arrest"))) ob->delete("arrest");
			ob->save();
		}
		write(HIY"�� -- " + to_chinese_kingdom(me->query("kingdom/id")) + (me->query("kingdom/king")?"����":"��")+ NOR + me->short() + "Ϊ" + ob->short(1) + "�������������\n"
		"�������ˡ��������һ�����У���ȡ��������ͨ���\n" );
		shout(HIY"�� -- " + to_chinese_kingdom(me->query("kingdom/id")) + (me->query("kingdom/king")?"����":"��")+ NOR + me->short() + "Ϊ" + ob->short(1) + "�������������\n"
		"�������ˡ��������һ�����У���ȡ��������ͨ���\n" );
		if(!find_player(tar)) destruct(ob);
		return 1;
	}
	// ͨ��
	if( !ob = find_player(arg) ) return notify_fail("û������˻������������� !\n");
	if( !userp(ob) ) return notify_fail("������һλ��ҡ�\n");
	if( me == ob ) return notify_fail("�㲻��ͨ���Լ���\n");
	if( ob->query("kingdom/king") && ob->query("kingdom/id")==me->query("kingdom/id") ) return notify_fail("�������ܱ�ͨ����\n");
	if( !me->can_afford(ARR_COST*ob->query("level")) ) return notify_fail("������û���㹻��Ǯ��ͨ����\n");
	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < ARR_COST * ob->query("level") * 2 ) return notify_fail("������û���㹻��Ǯ��\n");
	if( kingdom_data(me->query("kingdom/id"), "arrest", "check", arg) ) return notify_fail("������ѱ����ͨ���ˡ�\n");
	if( sizeof(kingdom_data(me->query("kingdom/id"), "arrest", "query_all"))>=3 ) return notify_fail("���ֻ��ͬʱͨ�����ˡ�\n");
	if(!kingdom_data(me->query("kingdom/id"), "arrest", "add", arg)) return notify_fail("������ϴ����޷�д�롣\n");

	if( arrayp(list = ob->query("arrest")) ) {
		if( member_array(me->query("kingdom/id"), list)==-1 )
			ob->set("arrest", list + ({me->query("kingdom/id")}) );
	} else ob->set("arrest", ({me->query("kingdom/id")}) );
	ob->save();
	me->pay_money(ARR_COST * ob->query("level") );
	me->save();
	kingdom_data(me->query("kingdom/id"), "data", "gold", "sub", ARR_COST * ob->query("level")* 2 );

	write(HIY + "�� - "+to_chinese_kingdom(me->query("kingdom/id")) + "��" + (me->query("kingdom/king")?"����":"��") +" -- " + me->short() + "������" + ob->short() + "��ͨ�������\n"NOR
	"������ȫ��׷��" + ob->short() + "����ۡ�\n" );
	shout(HIY + "�� - "+to_chinese_kingdom(me->query("kingdom/id")) + "��" + (me->query("kingdom/king")?"����":"��") +" -- " + me->short() + "������" + ob->short() + "��ͨ�������\n"NOR
	"������ȫ��׷��" + ob->short() + "����ۡ�\n" );
        return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : arrest <ĳ��> <cancel>

���ǹ�����ʹȨ��һ���ַ�����������ò�Ҫ����ͨ����Ȩ����
������ܻ�����

���ѶϢ : die, 

HELP
	);
	return 1;
}

