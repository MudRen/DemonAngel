//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
#include <armor.h>
#include <ansi.h>
inherit LEGGINGS;
void create() {
set_name("�ּ�", ({"leggings"}) );
set_weight(10); 
if( clonep() )
set_default_object(__FILE__);
else {
set("long", @LONG
һ����մ���������ּס�
LONG);
set("type","leggings");
set("level",2);
set("owner","pawlo");
set("kingdom","sky");
set("unit","��");
}
setup();
}
int query_autoload() {
if (query("equipped"))
return 1;
return 0;
}
