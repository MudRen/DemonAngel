//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
//npc : /open/test/npc/1.c
//create by testlife     Mon Mar 10 23:07:24 2003

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("居民",({ "tavern", "taver", "tave", "tav", "ta", "t" }));
	set("long","他是一名二级的居民
");
	set("int",2);
	set("dex",2);
	set("con",2);
	set("level",2);
	set("type","tavern");
	set("owner","testlife");
	set("kingdom","test");
	set("gender","男性");
	set("unit","无");
	set("chasing",0);
	set("reward",0);
	set("no_corpse",0);
	set("wimpy",0);
	set("die_msg",0);

	setup();}
