//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/obj/gift/firework.c
// by bor @DA, 3/5 2003

#include <ansi.h>

inherit ITEM;

string *color = ({
		RED"", YEL"", GRN"", BLU"", MAG"", CYN"", WHT"",
		HIR"", HIG"", HIY"", HIB"", HIM"", HIC"", HIW""
		});
string *msg = ({
		"����ͷ׵Ļ���������ɢ������������\n",
		"ɲ����ձ��߲ʹ�â�����������ۻ����ҡ�\n",
		"�ٺ�ɫ�Ļ�������ֱ�䣬�ֱ���������ɫ�Ĵ�״�𻨡�\n",
		"����Ļ������̸��Ա������������������ĵ�ϸ�鱬����\n",
		"ɢ�ų�ǧ�����棬���Ĵ��׷ɶ�ȥ������Ŀ��Ͼ����\n",
		"��һƬ�ٲ��������߲ʵĻ𻨣������ش��춥����������\n"
		});
void create()
{
	set_name("�̻�", ({ "firework","firework" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������ף���̻�����Ե�ȼ��(light firework)��\n");
		set("value", 1000);
	}
	setup();
}

void init()
{
	if(userp(this_player())) add_action("do_light","light");
}

int do_light(string arg)
{
	string reason="";
	object me;
	int colornum, msgnum;

	me = this_player();

	if(!arg) return notify_fail("�����ȼʲô��?\n");
	else if(arg=="firework") {
		msgnum = random(sizeof(msg));
		reason = msg[msgnum];
	} else if(sscanf(arg, "firework %s", reason)==1) 
		reason = "�𻨺ͱ����ڿ����ų���"+reason+"��\n";
	else return notify_fail("�����ȼʲô��?\n");

	colornum = random(sizeof(color));        

	write(color[colornum]+me->short()+"ȼ�����,\n"+"һ�����⻮����ʣ�һ���̻�������һ���ڿ��б��� ...\n"+reason+NOR);
	shout(color[colornum]+me->short()+"ȼ�����,\n"+"һ�����⻮����ʣ�һ���̻�������һ���ڿ��б��� ...\n"+reason+NOR);
	destruct(this_object());
	return 1;
}