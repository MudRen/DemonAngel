//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/special/recall_shop.c
// by bor @DA,

inherit ROOM;

void create()
{
	set("short","商店的储藏室");
	set("long",@TEXT	
不少货品都堆放于此地, 请不要乱拿走喔 !!
TEXT
	);
	set("no_clean_up", 1);
	setup();
	replace_program(ROOM);
}
