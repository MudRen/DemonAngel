//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// Room: /d/gourd/choice_class.c
// by bor @DA

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "ְҵ������");
	set("long", @LONG
������ѡ�����ְҵ�ĵط�.... ��ʹ�� list ���ο�
LONG
	);
	set("exits", ([
		"east" : __DIR__"recall_n_3",
	]));

	setup();
//	replace_program(ROOM);
}

void init()
{
	add_action("do_list", "list");
	add_action("do_advance","advance");
}

int do_list(string arg)
{
	object me = this_player();
	string msg ="";

	if( me->query("class")!="ð����" ) return notify_fail("���Ѿ�ѡ��ְҵ��!!\n");
	msg += "Ŀǰ����ѡ���ְҵ��:\n";
	msg += "ħ��ʦ\n";
	msg += "սʿ\n";
	msg += "��ʦ\n\n";
	msg += "ת���ɻ�����ְҵ, ������ advance <����ְҵ����>\n";

	write(msg+"\n");
	return 1;
}

int do_advance(string arg)
{
	object me = this_player();
	string *list = ({"ħ��ʦ","սʿ","��ʦ"});

	seteuid(getuid());
//	if( !wizardp(me) && me->query("class")!="ð����" ) return notify_fail("���Ѿ�ѡ��ְҵ��!!\n");
	if(!arg) return notify_fail("ת���ɻ�����ְҵ, ������ advance <����ְҵ����>\n");
	if( member_array(arg, list) == -1 ) return notify_fail("û�����������ְҵ����ת��!!\n");
	me->set("class", arg);
	me->set("max_lv", 25);		// ��¼��ְҵ��ߵȼ�
	write(HIC"���ְҵת�����!!\n"NOR);
	return 1;
}
