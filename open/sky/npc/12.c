//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// NPC : /open/sky/npc/12.c
// savenpc by pawlo    Mon May 26 11:49:49 2003

inherit STABLE_NPC;

#include <ansi.h>

void create()
{
	set_name("幼马", ({"horse", "h", "ho"}) );
	set("long", @TEXT
你看见一位第十级的幼马。
TEXT
	);
	set("type", "stable");
	set("level", 10);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 11:49:49 2003",
  "pawlo",
  "Mon May 26 11:49:49 2003"
}));
	set("gender", "雄性");
	set("race", "野兽");
	set("unit", "位");
	set("home", "/open/sky/67");
	set("kingdom", "sky");
	setup_npc();

}
