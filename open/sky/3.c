//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /open/sky/3.c
// saveroom by pawlo @DA, Mon Jun  9 15:04:36 2003
#include <ansi.h>
inherit ACTIONROOM;

void create()
{
	set("short", "�շ��� - ��ʹ�� set_short ���༭����");
	set("long", @LONG
����һ��ʲôҲû�еĿշ��䣬������ set_long ���༭����������
����һ��ʲô\"Ҳû�еĿշ��䣬������ set_long ���༭����������
����һ��ʲô\\\"Ҳû�еĿշ��䣬������ set_long ���༭����������
����һ��ʲô\\\"\"Ҳû�е�/�շ��䣬������ set_long ���༭����������
LONG
	);
	set("type", "actionroom");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Wed May 14 14:26:06 2003",
  "pawlo",
  "Mon Jun  9 15:04:36 2003"
}));
	set("item_desc", ([
"bb" : @TEXT
pp
sdf
TEXT
,  "aa" : @TEXT
����һ��ʲôҲû�еĿշ��䣬������ set_long ���༭����������
����һ��ʲô\"Ҳû�еĿշ��䣬������ set_long ���༭����������
����һ��ʲô\\\"Ҳû�еĿշ��䣬������ set_long ���༭����������
����һ��ʲô\\\"\"Ҳû�е�/�շ��䣬������ set_long ���༭����������
TEXT
,  
]));
	set("kingdom_id", "sky");
	set("action_move", ([ /* sizeof() == 2 */
  "kill" : ([ /* sizeof() == 3 */
      "file" : __DIR__"21",
      "toward" : "south",
      "dir" : "south",
    ]),
  "lo" : ([ /* sizeof() == 3 */
      "file" : __DIR__"16",
      "toward" : "north",
      "dir" : "north",
    ]),
]));
	set("objects", ([ ]));
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"1",
  "east" : __DIR__"4",
]));

	setup();
	replace_program(ACTIONROOM);
}
