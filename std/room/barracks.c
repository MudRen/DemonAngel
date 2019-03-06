//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/barracks.c
// by bor @DA, 5/23 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit ROOM;

void destruct_me( string file );

object env = this_object();

void setup()
{
	seteuid(getuid());
	::setup();
}

void init()
{
	if( wizardp(this_player()) || env->query("kingdom_id") == this_player()->query("kingdom/id") ) {
		if( wizardp(this_player()) || this_player()->query("kingdom/minister")
		|| this_player()->query("kingdom/king")) {
			add_action("do_list", "list");
			add_action("do_garrison", "garrison");
			add_action("do_take", "take");
			add_action("do_dismiss", "dismiss");
		}
	}
}

int do_list(string arg)
{
	object me, ob;
	string *list=({}), msg;
	int tmp=-1;

	me = this_player();

	if( !env->query("data") || !arrayp(env->query("data")) )
		return notify_fail("Ŀǰ��Ӫ�յ����������κξ���פ���ڴˡ�\n");

	if( zerop(list = env->query("data")) )
		return notify_fail("Ŀǰ��Ӫ�յ����������κξ���פ���ڴˡ�\n");

	msg = "Ŀǰ��פ���� :\n";
	for(int i=0; i< sizeof(list); i++) {
		if( file_size(list[i]+".c") ==-1 ) continue;
		tmp = -1;
		if( ob = find_object(list[i]) ) { tmp = 1; }
		else ob = new(list[i]);
		msg += sprintf(" %2d : %s �� %2d ��פ�� - %s\n", i,
			tmp==1? "[��Ӫ]":"[��Ӫ]", ob->query("level"), ob->short());
		if( tmp==-1 ) destruct_me(list[i]);
		reset_eval_cost();
	}
	me->start_more(msg);
	return 1;
}

int do_garrison(string arg)
{
	object me, ob;
	mapping room;
	string *list=({});
	int flag = -1;

	me = this_player();

	if( !arg ) return notify_fail("��Ҫ�л���һλ���˻�Ӫ��\n");
	if( !(ob = present(arg, env))) return notify_fail("û��������� !!\n");
	if( ob->query("level") > 45 ) return notify_fail("��Ӫ������ȼ����ֻ�ܵ� 45��\n");
	if( ob->query("type") != "barracks" ) return notify_fail("��Ӫ��ֻ��������˲���פ�ء�\n");
	if(  env->query("data") && arrayp(list = env->query("data")) && sizeof(list) >= 30 )
		return notify_fail("����ľ�Ӫ̫ӵ���ˣ�������פ����Ա��\n");

	if( member_array(base_name(ob), list) != -1 ) {
		write(ob->name_id()+"��Ӫפ���ˡ�\n");
		destruct_me(base_name(ob));
		return 1;
	}

	if( !env->query("objects") || zerop(env->query("objects")) )
		return notify_fail("���ﲻ�����ļң��������פ���ڴ� !!\n");

	room = env->query("objects");
	if( sizeof(keys(room))>0 )
	foreach( string npc, int tmp in room ) {
		if( file_size(npc+".c")==-1 ) continue;
		if( base_name(ob)!=npc ) continue;
		if( member_array(npc, list) == -1 ) {
			flag = 1;
			list += ({ npc });
			map_delete(room, npc);
			write(ob->name_id()+"�ᵽ������פ���ˡ�\n");
			destruct_me(npc);
		}
	}

	if( flag ==1 ) {
		env->set("data", list);
		if( sizeof(room)>0 ) env->set("objects", room);
		else env->delete("objects");
		do_saveroom(env);
		refresh_room(env);
	} else
		write(ob->name_id()+"������������, �޷��ᵽ����פ��!!\n");
	return 1;
}


int do_take(string arg)
{
	int num;
	object me, ob;
	string *list=({});

	me = this_player();

	if( !arg ) return notify_fail("��Ҫ�л���һ֧���� ?\n");
	num = atoi(arg);
	if( num == -1 ) return notify_fail("��Ҫ�л���һ֧���� ?\n");

	if( !env->query("data") || !arrayp(env->query("data")) )
		return notify_fail("����û����֧���ӡ�\n");
	if( zerop(list = env->query("data")) ) return notify_fail("����û����֧���ӡ�\n");
	if( num > (sizeof(list)-1) || num < 0 ) return notify_fail("����û����֧���ӡ�\n");
	if( find_object(list[num]) ) return notify_fail("��֧פ���Ѿ�������Ӫ���ˡ�\n");

	ob = new(list[num]);
	ob->move(env);
	ob->set_temp("barracks", 1);		// ��¼���ǴӾ�Ӫ�г����� [�����޸�, ���ܱ� garrison]
	write("������"+ob->name(1)+"��Ӫ��������\n");
	return 1;
}

int do_dismiss(string arg)
{
	int num;
	object me, ob;
	mapping room;
	string *list;

	me = this_player();

	if( !arg ) return notify_fail("��Ҫ����˭�����Ӫ��\n");
	num = atoi(arg);
	if( num == -1 ) return notify_fail("��Ҫ����˭�����Ӫ��\n");
	if( !(list = env->query("data")) || !arrayp(list) )
		return notify_fail("���ﲢ��פ����Ա��\n");
	if( num > (sizeof(list)-1) || num < 0 ) return notify_fail("û�������ŵ����� !!\n");

	if( !env->query("objects") ) env->set("objects", ([]));
	room = env->query("objects");
	if( sizeof(keys(room)) >= 3 ) return notify_fail("���������̫ӵ���� !!\n");

	room[list[num]] = 1;
	env->set("objects", room);

	if( !(ob = find_object(list[num])) )
		ob = new(list[num]);

	list -= ({ list[num] });
	if(sizeof(list)>0) env->set("data", list);
	else env->delete("data");

	if( ob->query_temp("barracks") ) ob->delete_temp("barracks");

	do_saveroom(env);
	ob->move(env);
	write("����"+ob->name(1)+"�ڴ�פ�ص����\n");

	refresh_room(env);
	return 1;
}

void destruct_me( string file )
{
	object *all;
	all = children(file);
	if( sizeof(all) )
	for(int i=0; i<sizeof(all); i++)
		destruct(all[i]);
	return ;
}
