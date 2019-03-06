//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/makeroom.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#define ROOM_MONEY	500

int main(object me,string arg)
{
	object env;
	int num;
	string new_file, new_arg, str;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !arg ) return notify_fail("ָ���ʽ��makeroom <����>\n");
	if( !env = environment(me)) return notify_fail("�Ҳ���������\n");
	if( !me->query("kingdom/id") || !env->query("kingdom_id")
	|| env->query("kingdom_id") != me->query("kingdom/id")
	) return notify_fail("���ﲻ�ǹ�������ء�\n");
	if( arg != "north" && arg != "south" && arg != "east" && arg != "west" && arg != "down" && arg != "up" ) return notify_fail("û���������\n");
	if( env->query("exits/"+arg) ) return notify_fail("��������Ѿ������ӷ����ˡ�\n");
	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "room") >= kingdom_data(me->query("kingdom/id"), "data", "query_par", "max_room") ) return notify_fail("������������Ѷ�������ɾ������Ҫ�ķ����ٽ���\n");
	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < ROOM_MONEY ) return notify_fail("���������㡣\n");

	// ����ʵ�ʷ������ͷ�����ˮ�ŵ��ܺ���Ϊ��һ�䷿�䵵��������
	num = kingdom_data(me->query("kingdom/id"), "data", "query_par", "room")
		+ kingdom_data(me->query("kingdom/id"), "data", "query_par", "room_num");

	new_file = KINGDOM_DIR+me->query("kingdom/id")+"/"+(string)num;

	if( file_size(new_file+".c")!=-1) return notify_fail("��������Ѿ����ˣ����ҹ������޸ġ�\n");

	new_arg = inverse_dir(arg);

	str = "// room : " + new_file + ".c\n";
	str += "// saveroom by "+ me->query("id")+"    "+ctime(time())+"\n\n";
	str += @ROOM
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�շ��� - ��ʹ�� set_short ���༭����");
	set("long", "����һ��ʲôҲû�еĿշ��䣬������ set_long ���༭����������\n");
	set("type", "normal");
ROOM
	;

	// refresh_data ��ʽ��({ ������, ����ʱ��, ��������, ������ʱ�� })
	str += sprintf("\tset(\"refresh_data\", ({ %O, %O, %O, %O }));\n",
		me->query("id"), ctime(time()), me->query("id"), ctime(time()) );

	str += sprintf("\tset(\"kingdom_id\", %O);\n", me->query("kingdom/id"));
	str += sprintf("\tset(\"exits\", %O);\n", ([ new_arg: base_name(env) ]) );

	str += "\n\tsetup();\n";
	str += "\treplace_program(ROOM);\n}\n";

	if( !write_file(new_file+".c", str, 1) )
		return notify_fail("��û�н��췿���Ȩ������֪ͨ�����ߡ�\n");

	message_vision("$N����һ�ѹ������� "+capitalize(arg)+" ���ô��ģ�����һ�䷿�䡣\n", me);

	// ԭ����Ҫ��������
	env->add("exits",([ arg: new_file ]));
	do_saveroom(env);

	kingdom_data(me->query("kingdom/id"), "data", "add", "room", 1);
	kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", ROOM_MONEY);

	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : makeroom <����>

���ǹ��������������������������ص�ָ��, �����˿��������ϱ�
�������������е���һ����û�г��ڵķ���������, ��ʱ�Ǹ�����ͻ�
���һ�䷿��, ��������Ҳ���Զ��߹�ȥ,������������ָ���趨�·���
������ :

        set_short       : �趨���������, �����㿴���ĵ�һ�С�
        set_long        : �趨���������, �����㿴�����Ƕ�������
        add_mob         : Ϊ����������һЩ���
        add_desc        : Ϊ����������һЩ���Կ���������
        saveroom        : ����ѷ����һ�ж��趨����,�ǵ�һ��Ҫ��������
        delete_room     : ɾ������ķ��䡣
        linkroom        : �����������䡣

���������Ѷ :  set_short, set_long, add_mob, add_desc, saveroom,
		delete_room

HELP
	);
	return 1;
}
