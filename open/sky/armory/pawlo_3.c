//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
#include <armor.h>
#include <ansi.h>
inherit BOOTS;
void create() {
set_name("����", ({"boots"}) );
set_weight(10); 
if( clonep() )
set_default_object(__FILE__);
else {
set("long", @LONG
һ����մ�������Ļ��ߡ�
LONG);
set("type","boots");
set("level",10);
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
