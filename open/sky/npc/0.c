//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
//npc : /open/sky/npc/0.c
//create by pawlo     Mon Mar 10 20:59:54 2003

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("����",({ "tavern", "taver", "tave", "tav", "ta", "t" }));
	set("long","����һ��һ���ľ���
");
	set("int",1);
	set("dex",1);
	set("con",1);
	set("level",1);
	set("type","tavern");
	set("owner","pawlo");
	set("kingdom","sky");
	set("gender","����");
	set("unit","��");
	set("chasing",0);
	set("reward",0);
	set("no_corpse",0);
	set("wimpy",0);
	set("die_msg",0);

	setup();}
