//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/47
// saveroom by pawlo    Fri May 23 17:49:53 2003

#include <ansi.h>
inherit BANK;
void create()
{
	set("short", "银行");
	set("long", @TEXT
你走进了一家银行, 行员们正在柜枱后忙碌着, 几个浑身肌肉的警卫正\n狠狠的盯着你看。一个面带微笑的办事员走了过来, 等着为你服务。这里是
世界闻名的大奸商查克开的银行, 存在这里的钱虽然绝对安全, 但是却没利
息。你可以在这里存(deposit)/提(withdraw)款和转帐(transfer)。
TEXT
);
	set("type", "bank");
	set("refresh_data", ({ "pawlo", "Fri May 23 17:49:53 2003", "pawlo", "Fri May 23 17:49:53 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/40",
]));

	setup();
	replace_program(BANK);
}
