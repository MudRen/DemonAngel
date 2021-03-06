//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/choice_class.c
// by bor @DA

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "职业介绍所");
	set("long", @LONG
这里是选择基本职业的地方.... 请使用 list 来参考
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

	if( me->query("class")!="冒险者" ) return notify_fail("你已经选过职业了!!\n");
	msg += "目前可以选择的职业有:\n";
	msg += "魔法师\n";
	msg += "战士\n";
	msg += "牧师\n\n";
	msg += "转换成基本的职业, 请输入 advance <中文职业名称>\n";

	write(msg+"\n");
	return 1;
}

int do_advance(string arg)
{
	object me = this_player();
	string *list = ({"魔法师","战士","牧师"});

	seteuid(getuid());
//	if( !wizardp(me) && me->query("class")!="冒险者" ) return notify_fail("你已经选过职业了!!\n");
	if(!arg) return notify_fail("转换成基本的职业, 请输入 advance <中文职业名称>\n");
	if( member_array(arg, list) == -1 ) return notify_fail("没有这个基本的职业可以转换!!\n");
	me->set("class", arg);
	me->set("max_lv", 25);		// 纪录该职业最高等级
	write(HIC"你的职业转换完毕!!\n"NOR);
	return 1;
}
