//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /std/ship/ship_corpse.c
// by bor @DA, 2/24 2003

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��Ĺ��");
	set("long", @TEXT
����ۼ��˷ǳ���Ĵ�ֻ, �㲻���ȴ�һ��, ��������ֻͨ����, �����̡�
TEXT
	);
	set("no_teleport", 1);
	set("no_cast", 1);
	set("no_summon", 1);
	set("no_fight", 1);

	setup();
}
