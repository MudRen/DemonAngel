//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/mail.c

#include <room.h>

inherit POST_OFFICE;

void create()
{
	set("short", "邮局");
	set("long", @LONG
收信用的。
LONG
	);
	set("exits", ([
		"east"	: "/d/gourd/gourd_recall.c"
	]));
	setup();
}
