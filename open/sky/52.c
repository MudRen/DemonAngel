//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/52
// saveroom by pawlo    Sun May 25 20:59:06 2003

#include <ansi.h>
inherit POST_OFFICE;
void create()
{
	set("short", "邮局");
	set("long", @TEXT
你走进一家小邮局, 几个邮差正坐在一堆信箱旁边整理信件, 他们边聊
天边把信件塞入不同的信箱中。在这堆信箱中应该也有你的吧, 如果你想看
看有没有你的信, 你可以找找看有没有你的信箱(search mailbox)。
TEXT
);
	set("type", "post_office");
	set("refresh_data", ({ "pawlo", "Sun May 25 20:59:06 2003", "pawlo", "Sun May 25 20:59:06 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/40",
]));

	setup();
	replace_program(POST_OFFICE);
}
