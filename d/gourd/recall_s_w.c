//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
  // Room: /d/city/recall_s_w.c

#include <ansi.h>

inherit ROOM;

int check_legal_id(string id);
int check_legal_name(string name);

void create()
{
	set("short", "Բ������");
	set("long", @LONG
���У�ר������ҵġ�

	ʹ�ø�ʽ��buy_kingdom <����> <Ӣ��>

LONG
	);
	set("exits", ([
        "east": __DIR__"recall_s_1"
	]));
	set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_buy", "buy_kingdom");
}

int do_buy(string arg)
{
	object me = this_player();
	string name, id;

        seteuid(getuid());
	if(!me->query_temp("kingdom_build")) return notify_fail("��ʱ�����Ž�����...��Ȼ���˶��ǹ��� .. �е���졣\n");
	if( !arg ) return notify_fail("ָ���ʽ��buy_kingdom <����> <Ӣ��>\n");
	if( me->query("kingdom") ) return notify_fail("��������ƽ����С�\n");
	if( sscanf(arg, "%s %s", name, id)!=2 )
		return notify_fail("ָ���ʽ��buy_kingdom <����> <Ӣ��>\n");
//	if( !(me->can_afford(300000)) )
//		return notify_fail("�����ϲ��� 30 ���ң��޷����� !!\n");
	if(!check_legal_name(name)||!check_legal_id(id)) return 1;
	if( check_kingdom(id) ) return notify_fail("�˹����Ѿ��й�������ʹ�ã��뻻��Ӣ�� !!\n");
	if( file_size(DATA_DIR+"nuke/kingdom/"+id) == -2 )
		return notify_fail("�˹���������������ʷ�ϣ��뻻��Ӣ�ġ�\n");
	mkdir(KINGDOM_DIR+id);
	mkdir(DATA_DIR+"nuke/kingdom/"+id);
	mkdir(DATA_DIR+"kingdom/"+id);
	KINGDOM_D->creat_kingdom_data(id, name, me);
	create_kingdom(me, id, name);

	shout(HIM"��������Ѷ��"+HIY+"��"+me->name_id(1)+HIY+"���쵼�Ĺ��� -- "+name+"("+id+")��ʽ������\n"+NOR);
	write(HIM"��������Ѷ��"+HIY+"��"+me->name_id(1)+HIY+"���쵼�Ĺ��� -- "+name+"("+id+")��ʽ������\n"+NOR);

//	me->pay_money(300000);
	me->save();

        return 1;
}

int check_legal_name(string name)
{
	int i;

	if(name=="") return 0;

	i = strlen(name);
        
	if( (strlen(name) < 4) || (strlen(name) > 12 ) ) {
		write("�����������ֱ����� 2 �� 6 �������֡�\n");
		return 0;
	}
	while(i--) {
		if( name[i]<='' ) {
			write("�����������ֲ����ÿ�����Ԫ��\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("�����á����ġ�ȡ�������֡�\n");
			return 0;
		}
	}
	return 1;
}

int check_legal_id(string id)
{
	int i;

	if(id=="") return 0;
	i = strlen(id);

	if( i < 3 || i > 15 ) {
		write("����Ӣ�����ֱ����� 3 �� 15 ��Ӣ����ĸ��\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z')
		if( id[i] != '_') {
			write("��ֻ��ʹ��Ӣ�Ļ��� _ �ķ������������ҵ�Ӣ�ġ�\n");
			return 0;
		}

	return 1;
}
