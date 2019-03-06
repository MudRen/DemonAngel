//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/go.c

inherit F_CLEAN_UP;

mapping default_dirs = ([
	"north":		"��",
	"south":		"��",
	"east":			"��",
	"west":			"��",
	"up":			"��",
	"down":			"��",
	"out":			"��",
]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string dest, mout, min, dir;
	object env, obj;
	mapping exit;

	if( !arg ) return notify_fail("��Ҫ���ĸ������ߣ�\n");

	if( me->over_encumbranced() )
		return notify_fail("��ĸ��ɹ��أ��������á�\n");

	if( me->is_busy() )
		return notify_fail("��Ķ�����û����ɣ������ƶ���\n");

	env = environment(me);
	if(!env) return notify_fail("������Ҳȥ���ˡ�\n");

	if( !mapp(exit = env->query("exits")) || undefinedp(exit[arg]) ) {
		if( query_verb()=="go")
			return notify_fail("�������û�г�·��\n");
		else
			return 0;
	}

	dest = exit[arg];

	// Ϊ��ȷ�� ���ʱ, ���ϸù��ҵ����, ���ܵ����߶�, ���趨���ж�, ҲΪ�������ʽ�������
	//							by bor @DA, 3/10 2003
	if( !sscanf(dest, "%*s.c") ) {
		if( !sscanf(dest, "%*s.grid") ) {
			dest += ".c";
			if( file_size(dest)==-1) return notify_fail("�������ķ�����˵�����, �޷��߹�ȥ !!\n");
		}
	}

	if( !(obj = find_object(dest)) )
		call_other(dest, "???");
	if( !(obj = find_object(dest)) )
		return notify_fail("�޷��ƶ���\n");

	if( !env->valid_leave(me, arg) ) return 0;

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;

	if( me->is_fighting() ) {
		mout = "��" + dir + "��Ķ����ˡ�\n";
		min = "����ײײ�����˹�����ģ����Щ�Ǳ���\n";
	} else {
		mout = "��" + dir + "�뿪��\n";
		min = "���˹�����\n";
	}

	message( "vision", me->name() + mout, environment(me), ({me}) );
	if( me->move(obj) ) {
//		me->remove_all_enemy();
		message( "vision", me->name() + min, environment(me), ({me}) );
		me->set_temp("pending", 0);
		all_inventory(env)->follow_me(me, arg);
		return 1;
	}

	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;

	if( !environment(me) || !living(me) ) return;
	exits = environment(me)->query("exits");
	if( !mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	tell_object(me, "�������һ���������...\n");
	main(me, directions[random(sizeof(directions))]);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : go <����>
 
������ָ���ķ����ƶ���
 
HELP
    );
    return 1;
}
