//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
//npc : /open/test/npc/0.c
//create by testlife     Mon Mar 10 20:24:47 2003

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("����",({ "tavern", "taver", "tave", "tav", "ta", "t" }));
	set("long","����һ�������ľ���
");
	set("int",2);
	set("dex",2);
	set("con",2);
	set("level",2);
	set("type","tavern");
	set("owner","testlife");
	set("kingdom","test");
	set("gender","����");
	set("unit","��");
	set("chasing",0);
	set("reward",0);
	set("no_corpse",0);
	set("wimpy",0);
	set("die_msg",0);

	setup();}
