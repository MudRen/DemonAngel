//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// entrance.c

#include <login.h>
#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��ʦ�����");
	set("long",
		"��������ʦ���������ĵط����������ʲô���Ҫ����ʦ��֪����������\n"
	"����������;������������Ƕ�����Ϸ�е����⣬������ȷ�������ṩ��˵��\n"
	"�ļ���û��˵������������ʣ���ʦ����Ҫְ�𲢲��ǽ��������档\n"
	"    Ϊ�˶ž������ˣ���������������(accuse)ĳ����ң�������һᱻץȥ\n"
	"��һЩСС�Ĳ��飬Ŀǰ���\����δ���κ����ƣ�����������ɧ�ű��ˡ�\n");
	set("exits", ([
		"west" : "/d/wiz/hall1",
		"southeast": "/d/snow/inn" ]) );
	set("no_fight", 1);
	set("no_magic", 1);
	create_door("southeast", "ľ��", "northwest", DOOR_CLOSED);

	setup();
	call_other( "/obj/board/query_b", "???" );
}

int valid_leave(object me, string dir)
{
	if( dir=="west" && !wizardp(me) )
		return notify_fail("����ֻ����ʦ���ܽ�ȥ��\n");
	return ::valid_leave(me, dir);
}

void init()
{
	add_action("do_accuse", "accuse");
}

int do_accuse(string arg)
{
	object ob;
	string s;

	if( (int)this_player()->query("age") < 15 )
		return notify_fail("�����̫С�ˣ�û�м�ٱ��˵�Ȩ����\n");

	if( !arg ) return notify_fail("��Ҫ���˭��\n");
	if( ob = find_player(arg) ) {
		if( ob==this_player() )
			return notify_fail("��Ҫ����Լ���\n");
		if( ob->is_ghost() )
			return notify_fail( ob->name(1) + "�Ѿ����ˣ�����һ��ɡ�\n");
		if( wizardp(ob) )
			return notify_fail("�㲻�ܼ����ʦ��\n");
		tell_object(ob, HIW + this_player()->name(1) + "������Ǹ������ˣ��������һ��СС�Ĳ��顣\n" NOR);
		ROBOT_CHECK->test_me(ob);
		write("Ok. �Ѿ������ٵĶ�����ȥ�����顣\n");
		write("Ϊ�˱��������û������Ҽ��ɧ�ű��ˣ�����Ҳ������ͬ�Ĳ��顣\n");
		ROBOT_CHECK->test_me(this_player());
		log_file("robot_accuse",
			sprintf("%s accused %s on %s.\n", this_player()->query("id"), ob->query("id"), ctime(time())));
		return 1;
	}
	return notify_fail("Ŀǰ���ϲ�û����λ��ҡ�\n");
}

