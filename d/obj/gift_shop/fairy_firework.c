//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /d/obj/gift/fairy_firework.c
// by bor @DA, 3/5 2003

#include <ansi.h>

inherit ITEM;

string *color = ({
		RED"", YEL"", GRN"", BLU"", MAG"", CYN"", WHT"",
		HIR"", HIG"", HIY"", HIB"", HIM"", HIC"", HIW""
		});
string *msg = ({
		"����ͷ׵Ļ�������ܺ�����������˸���ѡ�\n",
		"ɲ����Χ���߲��������䣬�����ۻ����ҡ�\n",
		});
void create()
{
	set_name(HIW"��Ů��"NOR, ({ "fairy firework","firework","fairy" }) );
	set_weight(30);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "��һ����С�����������Ů�������(light firework)��ȥ�ͻ��кܶ�𻨡�\n");
		set("value", 200);
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

	if(!arg || !id(arg) ) return notify_fail("�����ȼʲô��?\n");

	msgnum = random(sizeof(msg));
	reason = msg[msgnum];

	colornum = random(sizeof(color));        

	message_vision(color[colornum]+"$N��ȼ$n, "+color[random(sizeof(color))]+reason+NOR, me, this_object());
	destruct(this_object());
	return 1;
}
