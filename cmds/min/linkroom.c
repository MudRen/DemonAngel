//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/linkroom.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_CLEAN_UP;

void show_linkroom(object env);
int del_link(object me, string dir);
int check_link(object env);
int connect_link(object env, string dir, string file);

int main(object me, string arg)
{
	object env;
	string list, tmp, new_arg;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if(!env = environment(me)) return 0;
	if(!env->query("kingdom_id") || !me->query("kingdom/id")
	|| env->query("kingdom_id") != me->query("kingdom/id") )
		return notify_fail("���ﲻ���ҹ������� !!\n");
	if(!arg) {
		show_linkroom(me);
		return 1;
	}
	arg = lower_case(arg);
	if( arg == "cancel") {	// ȡ����ǰ linkkroom �Ķ���
		if(!me->query_temp("linkdir")) return notify_fail("��Ŀǰ��δ�趨�κ�·�ꡣ\n");
		me->delete_temp("linkdir");
		me->delete_temp("linkroom");
		write("�����ǰ��·��γ��ˡ�\n");
		return 1;
	}
	if( sscanf(arg, "cancel %s", arg) == 1 ) {
		if( !env->query("link") || !mapp(env->query("link")) )
			return notify_fail("����û���� linkroom ����ķ��䡣\n");
		if( !env->query("exits/"+arg) ) return notify_fail("�Ҳ����������\n");
		foreach( list, tmp in env->query("link") ) {
			if( list!=arg ) continue;
			if(del_link(me, arg)) return 1;
		}
		return notify_fail( capitalize(arg) + " �ķ������� linkroom ��������ġ�\n");
	}
	if( env->query("type")!="normal" ) return notify_fail("���ﲻ��һ��ķ��䣬�������ᡣ\n");
	if( arg!="north" && arg!="south" && arg!="east" && arg!="west" && arg!="down" && arg!="up" )
		return notify_fail("û���������\n");
	if( env->query("exits/"+arg) ) return notify_fail(arg + " ��������Ѿ��г����ˣ�����������·�ˡ�\n");

	if( me->query_temp("linkdir") && me->query_temp("linkroom") ) { // �������¹� ����ָ���ʾ׼������ room
		new_arg = inverse_dir(me->query_temp("linkdir"));
		if( arg != new_arg ) return notify_fail("�����᷽����� !!\n");
		if( connect_link(env, new_arg, me->query_temp("linkroom") ) ) return 1;
	}
	me->set_temp("linkdir", arg);			// �趨���᷽��
	me->set_temp("linkroom", base_name(env));	// �趨��������
	write("����������������������һ��·�� -- ��·ʩ���С�\n");
	return 1;
}

void show_linkroom(object me)
{
	object env;
	string str="";
	env = environment(me);

	if( !env->query("link") ) {
		write("�������û���κ����ӡ�\n");
		return;
	}
	str += "��������� linkroom ��������ӷ����� :\n";
	foreach( string list, string tmp in env->query("link") ) {
		str += "\t"+list+"\t: "+tmp+",\n";
	}
	me->start_more(str);
	return ;
}

int del_link(object me, string dir)
{
	object env, link_env;
	string new_dir;
	mapping env_link, link_link;

	env = environment(me);

	if( !link_env = find_object(env->query("exits/"+dir)) ) {
		call_other( env->query("exits/"+dir), "create_env" );
		link_env = find_object(env->query("exits/"+dir));
	}
	if( check_link(link_env) ) {
		write("���淿�������⶯���ʴ��� !!\n");
		return 1;
	}

	// ������ link
	env->delete("exits/"+dir);
	env_link = env->query("link");
	map_delete( env_link, dir );
	if( zerop( env->query("link") ) ) env->delete("link");
	do_saveroom(env);

	// ����һ�������
	new_dir = inverse_dir(dir);
	link_env->delete("exits/"+new_dir);
	link_link = link_env->query("link");
	map_delete( link_link, new_dir );
	if( zerop( link_env->query("link") ) ) link_env->delete("link");
	do_saveroom(link_env);

	write("�������������Ѿ�����ˡ�\n");
	return 1;
}

// ��� env �Ƿ�Ϊ actionroom
int check_link(object env)
{
	if(env->query("type")=="actionroom" || !env->query("link") ) return 1;
	return 0;
}

// env ���᷽��Ϊ dir�������� file �ĵط�
int connect_link(object env, string dir, string file)
{
	object link_env;
	string new_dir;

	// �����ȴ���
	env->add("exits/"+dir, file);
	if(!env->query("link")) env->set("link", ([ dir:ctime(time()) ]) );
	else env->add("link/"+dir, ctime(time()) );
	do_saveroom(env);

	// ���᷿�䴦��
	if( !link_env = find_object(file) ) {
		call_other( file, "create_env" );
		link_env = find_object(file);
	}
	new_dir = inverse_dir(dir);
	link_env->add("exits/"+new_dir, base_name(env));
	if(!link_env->query("link")) link_env->set("link", ([ new_dir:ctime(time()) ]) );
	else link_env->add("link/"+new_dir, ctime(time()) );
	do_saveroom(link_env);

	message_vision("$N����һȺ��·���ˣ��̳���һ����·��\n", this_player());
	this_player()->delete_temp("linkdir");
	this_player()->delete_temp("linkroom");
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : linkroom <����>              ��ĳ�������ӳ���
           linkroom <cancel>            ȡ��δ��ɵ����Ӷ���
           linkroom                     ����Ŀǰ���е����ӳ���
           linkroom <cancel ����>       ȡ������ɵ�����
 
���ǹ������������·��ָ������������������Ѵ��ڵķ��䡣������
makeroom �ѷ��������ˣ������һ�������ͷβ����������ʱ����ͻ���
�����ָ�

���ָ����÷��� : ����ѡ��Ҫ���ӵ��������䣬�������е�һ���� 
linkroom <����> �Զ������ӵķ���Ȼ���ڵ���һ���� linkroom <������>
������������������ӣ���·�ͻῪ�����ˡ�������� link cancel ȡ����
һ������ָ�

���㷢��������Ӳ��ʵ�ʱ, ��������� linkroom cancel <����> ���ָ��
�������Ѿ����õ����ӡ�

���������Ѷ : makeroom, delete_room


HELP
	);
	return 1;
}
