//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /d/gourd/gourd-gift_shop.c

#include <ansi.h>
#include <room.h>

inherit GIFT_SHOP;

void create()
{
	set("short", "����Ʒ�꡿");
	set("long", @TEXT
����һ�߽����Ϳ������ٵ���Ʒ�����ڴ�, ��ؽ���, ����������
���๺��, ס�ں�«���ڵĵ����˶�֪������һ�ҷǳ��������ϵ�, ��
���Ϻÿڱ�������, �ϰ�����һλ����򼫾��׺���, ������������
��ð���߲�඼������������������Ҫѡ��(buy)��Ʒ, ��������
��(list)һ����
TEXT
	);
	set("outdoors", 1);
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/d/gourd/3.c",
]));
	setup();
}
