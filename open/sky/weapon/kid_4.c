//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
#include <weapon.h>
inherit AXE;
void create() {
	set_name( "��ͷ", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10); 
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������ĸ�ͷ��
LONG );
		set("unit","��");
		set("type","axe");
		set("level",200);
		set("skill",400);
		set("owner","kid");
		set("kingdom","sky");
	init_axe(200);
	}
	setup();
}