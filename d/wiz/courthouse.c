//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/wiz/courthouse.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
�����Ƕ������µ���ʦ���ʻ����˵ķ�Ժ����һ���Ǳ��˼�ٻ���
��Ϊ̫������ˣ��Ż�������������𲻳����йٵ��������⣬��
�����ϼǺţ��������ε��˽��ᱻ���Լ��̣��úûش�ɡ�
LONG
	);
	set("no_fight", 1);
	set("no_magic", 1);
	set("no_spells", 1);
	set("objects", ([
		__DIR__"npc/judge":1 ]) );

	setup();
}

void test_me(object me)
{
	me->set_temp("old_startroom", me->query("startroom"));
	me->set("startroom", __FILE__);
	me->set_temp("last_location", base_name(environment(me)));
	message_vision("��Ȼһ��������ס��$N��\n", me);
	me->move(this_object());
}
