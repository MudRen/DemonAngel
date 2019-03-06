//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/build.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

private int make_room(object me, string type, string arg);
private int make_base_post_office(string id, string file);

int main(object me, string arg)
{
	string type, dir, *dir_list = ({"east","west","north","south","down","up"});
	int gold, limit_room;

	seteuid(getuid());
	if( !arg ) return notify_fail("ָ���ʽ : build <���⽨��������> <����>\n");
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !me->query("kingdom/id") || !environment(me)->query("kingdom_id")
	|| environment(me)->query("kingdom_id") != me->query("kingdom/id")
	) return notify_fail("���ﲻ�ǹ�������ء�\n");
	if( sscanf(arg, "%s %s", type, dir) != 2 ) return notify_fail("ָ���ʽ : build <���⽨��������> <����>\n");
	if( member_array(dir, dir_list)==-1 ) return notify_fail("û���������\n");
	if( environment(me)->query("exits/"+dir) ) return notify_fail("��������Ѿ��з����ˡ�\n");
	switch( type ) {
		case "shop":
		case "tavern":
		case "herb_shop":
		case "misc_shop":
		case "bank":
		case "post_office":
		case "board":
			gold = 50000;	limit_room = 15;
			break;
		case "smith":
		case "armory":
			gold = 50000;	limit_room = 20;
			break;
		case "barracks":
			gold = 100000;	limit_room = 25;
			break;
		case "trainyard":
		case "gate":
		case "stable":
			gold = 250000;	limit_room = 30;
			break;
		case "magic_tower":
		case "church":
			gold = 250000;	limit_room = 35;
			break;
		case "furnace":
		case "hero_guild":
			gold = 500000;	limit_room = 50;
			break;
		default:
			return notify_fail("Ŀǰ�����Ŵ����⽨���\n");
	}

	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < gold )
		return notify_fail("���������㡣\n");

	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "room") < limit_room )
		return notify_fail("���������δ�ﵽ "+ limit_room +" �޷����á�\n");

	if( !make_room(me, type, dir) ) return 1;

	kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", gold);
	return 1;
}

int make_room(object me, string type, string arg)
{
	int num;
	string new_arg, new_file, str, short, long;
	object env;

	env = environment(me);

	// ����ʵ�ʷ������ͷ�����ˮ�ŵ��ܺ���Ϊ��һ�䷿�䵵��������
	num = kingdom_data(me->query("kingdom/id"), "data", "query_par", "room") +
		kingdom_data(me->query("kingdom/id"), "data", "query_par", "room_num");

	new_file = KINGDOM_DIR+me->query("kingdom/id")+"/"+(string)num;

	if( file_size(new_file+".c")!=-1 ) {
		write("��������Ѿ����ڣ���ǡ������ǰ���쿴��������\n");
		return 1;
	}

	new_arg = inverse_dir(arg);

	str = "// room : " + new_file + "\n";
	str += "// saveroom by "+ me->query("id")+"    "+ctime(time())+"\n\n";
	str += "#include <ansi.h>\n";
	if( type !="normal" )
		str += "inherit " + upper_case(type) +";\n";
	else str += "inherit ROOM;\n";

	str += "void create()\n{\n";

	switch( type ) {
		case "bank":
			short = "����";
			long = "���߽���һ������, ��Ա�����ڹ񖟺�æµ��, ����������ľ�����\n";
			long +="�ݺݵĶ����㿴��һ�����΢Ц�İ���Ա���˹���, ����Ϊ�����������\n";
			long +="���������Ĵ���̲�˿�������, ���������Ǯ��Ȼ���԰�ȫ, ����ȴû��\n";
			long +="Ϣ��������������(deposit)/��(withdraw)���ת��(transfer)��";
			break;
		case "board":
			short = "���԰�";
			long = "����һ���������Լ��µ����԰塣";
			break;
		case "shop":
			short = "�̵�";
			long ="�߽����װ����, ��һ�۾ͱ���Щ����ǽ�ϵ���������������, һ��\n";
			long +="����΢Ц��׳��վ�ڹ�ǰ��ӭ��, һ�涢�������Ͽ�, ������ʱ׼��Ϊ\n";
			long +="���������װ��һ�㡣������ʷ�����������ĸ���װ����, �����Դ����\n";
			long +="����ħ������������������½, ������, ����԰��ĵ�����(buy/sell)��\n";
			long +="�������õ��ı�ƭ, ������ȿ���(list)����, �����ϰ�������(value)\n";
			long +=", �������Ҫ���Կ�(try), �ϰ�Ҳ����˵�����ġ�";
			break;
		case "post_office":
			short = "�ʾ�";
			long ="���߽�һ��С�ʾ�, �����ʲ�������һ�������Ա������ż�, ���Ǳ���\n";
			long +="��߰��ż����벻ͬ�������С������������Ӧ��Ҳ����İ�, ������뿴\n";
			long +="����û�������, ��������ҿ���û���������(search mailbox)��";
			break;
		case "trainyard":
			short = "ѵ����";
			long ="������һ������ź�ˮ���������ѵ����, ���Ĵ�������һ������\n";
			long +="�Ĺ㳡, ����\�������ڳ��������ض�����, �������뵶��ײ�������ϴ���\n";
			long +=", �㳡�߶�����һЩѵ�����ߺ�����װ��, �������������ǽ���ģ������\n";
			long +="��վ�ڳ��߶��ų��ϵ���ָָ��㡣�����������ѵ��(train)���ܡ���\n";
			long +="��(advance)�ȼ����鿴(list)���������ѵ���������(cost)��";
			break;
		case "magic_tower":
			short = "������ϰӪ";
			long ="������һ��������������ϰ��, ��ϰ�ҵ�������һ�ų�����, ��������\n";
			long +="ֱ���ݶ������, ���ϰ��˻�����ʽ��ַ��ŵ��鼮, �󲿷����й�ħ����,\n";
			long +="������, ����Է�����(list)��ʲô�ʺ���Ŀǰ�̶ȵķ�����ѧ, Ҳ���Ծ�\n";
			long +="��������ϰ(study)������";
			break;
		case "smith":
			short = "����";
			long = "���߽�һ�����̣����ȵ��ȷ����������������������Ĺ�����������\n";
			long += "�������е��������䣬�е����������������������ø���ͣ����ߵĵ��ϣ�\n";
			long += "���м�����������Χ��һ�����ԣ���̯�����ϵ�һ�Ŵ����ͼ�����š�";
			break;
		case "armory":
			short = "������";
			long = "���߽�һ�ҹ���Ƥ������Ͳ��ϵĵ��̣��÷��������ڹ�̨�����һ��\n";
			long += "�����߱�����߽�һ�����Ŀ��׷�������������м�λ������������һ����\n";
			long += "����֦���ƺ����������ơ�";
			break;
		case "furnace":
			short = "ħ��¯";
			long = "���߽�һ���Ӵ��¯����¯���м�Ʈ����һ����ֵ����壬�Ǹ�������\n";
			long +="�㣬���������Ĵ���Ķ�������ħ��¯(furnace)��ħ��¯�Ĵ����¯��\n";
			long +="����ش��������ϣ�����ֻ������һ�㡣�ߵ��������һ��������ħ��¯\n";
			long +="�Ǳ����ݵĸо�����Ȼ��ǿ�ң�����ȴ���˺����ܡ���ħ��¯�������쳣��\n";
			long +="�ྻ������һ��ҳ�Ҳû�У�������������Ҳ�ƺ�ֹͣ�ˡ�";
			break;
		case "tavern":
			short = "�ù�";
			long ="������һ��С�ùݣ�ר�Ź�����·���ÿ���ЪЪ���õģ�����ķ���װ\n";
			long +="�εķǳ����ʣ����������˶����˺���������;���ۣ��㶼���������ﰲ\n";
			long +="�ĵ������������������±��˴��ţ�������һ��������������صķ����\n";
			long +="һ�Ե���һλ�൱�ɰ���Ů�̣����ڵ��Ÿ�λ����Ҫ���˽�����Ϣ��";
			break;
		case "herb_shop":
			short = "ҩ��";
			long ="���߽�һ�ҳ���ҩ��ζ��ҩ��, ��������Ÿ���ƿƿ�޹�, ���������\n";
			long +="���򵽸�����ҩ������������, �������øò�һ����, ������ list ��\n";
			long +="����ʲô��ɫ, �ٿ���Ҫ��Ҫ��(buy)��";
			break;
		case "misc_shop":
			short = "�ӻ���";
			long ="�������ӻ��꣬��������Ÿ�ʽ����ð���õ��ӻ���Ʒ��������Ŭ������\n";
			long +="�ҿ����Ƿ������Լ���Ҫ����������Ҫ�ĵĶ������� list ��������Ҫ�Ķ���\n";
			long +="�ɡ�";
			break;
		case "gate":
			short = "�ؿ�";
			long ="������һ���ؿ���·���Ը�����һ������ڣ�·���뻹���ž�������\n";
			long +="��ǹִ��������������վ�Լ�����ˣ������������չ�·˰��";
			break;
		case "hero_guild":
			short = "Ӣ�ۻ��";
			long = "�����ǹ���·Ӣ�۾ۼ��ĵط�, ��������ѵ�ס����, ͬʱ�ֿ��Ը�\n";
			long += "�����ķ���Ӣ���Ǿۻ�ͽ�����Ϣ, ���Ի���г��������˸��ص�Ӣ�ۺ�\n";
			long += "�鱨����, ͬʱ, Ҳ�����Ӣ�������ﻥ�����(drill)���ڸ��ֽ���\n";
			long += "�ļ���, ��Щ����������һ��Ӣ������һ�����ж�����, �������ʸ�\n";
			long += "��, ����Ҳ��������Ӣ��Ը�����, ������������ѧ��һЩ��һ���ļ�\n";
			long += "�ܡ���������������(drill)���鿴(list)�ܻ�õĽ��׼��������ѯ��\n";
			long += "��������Ĵ���(cost)��";
			break;
		case "barracks":
			short = "��Ӫ";
			long = "���߽�һ����Ӫ�Ĵ���, ������ì��ʿ������ľկΧ�ɵľ���ǰվ��,\n";
			long += "��������, ����Կ���һƬ�ٳ�, �����ž��͵ľ������ڲٳ���Ʈ���š�\n";
			long += "�ٳ���Ե��һ����Ӫ��, ���ʿ�����ڿ�Ӫ���Ĳٳ��߻������";
			break;
		case "stable":
			short = "��";
			long = "���߽�һ������˲�����ζ�����\���������Կ���һЩ׳˶�ߴ�ǿ׳��\n";
			long += "���������\��һ���ߵ��ֿ����ߵ����Ա��ֳ�һ���ģ��е���������\n";
			long += "�Ļ����š��м������������Ŷ��Ų��ϵĳ��ӣ��Ѳ��ϲ�������ǰ��ʳ����\n";
			long += "�������������˻����������䣬����������������Զ��������������ǿ\n";
			long += "�������֣���Ҫ����Щ��������Ʊ�����Ҫ���Լ�ȥѱ�����ǣ����������\n";
			long += "����������Ǡ������˵ġ�";
			break;
		case "church":
			short = "����";
			long = "���߽�һ���ľ��Ľ��ã����ݶ��ϵ��߲�������͸��Ĺ�â�У�����Լ\n";
			long += "������Щ��ʦ������⻷�Ƶļ�̳ǰ��������ר�������г�ݵ����}��ͨ��\n";
			long += "��Ȼ������ĵ�����";
			break;
		default:
			write("Ŀǰ���ṩ "+type+" �����⽨���\n");
			return 1;
	}
	str += sprintf("\tset(\"short\", %O);\n", short );
	str += sprintf("\tset(\"long\", @TEXT\n%s\nTEXT\n);\n", long );
	str += sprintf("\tset(\"type\", %O);\n", type);

	// refresh_data ��ʽ��({ ������, ����ʱ��, ��������, ������ʱ�� })
	str += sprintf("\tset(\"refresh_data\", ({ %O, %O, %O, %O }));\n",
		me->query("id"), ctime(time()), me->query("id"), ctime(time()) );

	str += sprintf("\tset(\"kingdom_id\", %O);\n", me->query("kingdom/id"));
	str += sprintf("\tset(\"exits\", %O);\n", ([ new_arg: base_name(env) ]));

	str += "\n\tsetup();\n";
	str += "\treplace_program("+upper_case(type)+");\n";
	str += "}\n";

	if( !write_file(new_file+".c", str, 1) ) {
		write("��û�н��췿���Ȩ������֪ͨ�����ߡ�\n");
		return 1;
	}

	message_vision("$N����һ�ѹ������� "+capitalize(arg)+" ���ô��ģ�����һ�䷿�䡣\n", me);

	// ԭ����ҲҪ��������
	env->add("exits",([ arg: new_file ]));
	if( !do_saveroom(env) ) {
		write("������û�д浵��Ȩ������֪ͨ�����ߡ�\n");
		return 1;
	}

	if( type=="board" ) {
		make_base_post_office(me->query("kingdom/id"), (string)num);
	}

	kingdom_data(me->query("kingdom/id"), "special_room", "add", type, new_file+".c");
	return 1;
}

private int make_base_post_office(string id, string file)
{
	string str;
	str = "// room : KINGDOM_DIR+id+/data/"+id+file + "\n";
	str += "// saveroom by "+ this_player()->query("id")+"    "+ctime(time())+"\n\n";
	str += @ROOM
#include <ansi.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("���԰�", ({ "board" }) );
ROOM
	;
	str += sprintf("\tset(\"location\", %O);\n", KINGDOM_DIR+id+"/"+file);
	str += sprintf("\tset(\"board_id\", %O);\n", id+file);

	str += "\tsetup();\n";
	str += "\tset(\"capacity\", 70);\n";
	str += "\treplace_program(BULLETIN_BOARD);\n}";

	write_file( KINGDOM_DIR+id+"/data/"+id+file+".c", str , 1);
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : build <���⽨��������> <����>

���ǹ�����������������⽨�����ָ������˿��������ϱ�
�������������е���һ����û�г��ڵķ���������, ��ʱ�Ǹ�����ͻ�
�����ָ���Ľ���, ��������Ҳ���Զ��߹�ȥ, ������������ָ���趨�·���
������ :

        set_short       : �趨���������, �����㿴���ĵ�һ�С�
        set_long        : �趨���������, �����㿴�����Ƕ�������
        add_mob         : Ϊ����������һЩ���
        add_desc        : Ϊ����������һЩ���Կ���������
        saveroom        : ����ѷ����һ�ж��趨����,�ǵ�һ��Ҫ��������
        delete_room     : ɾ������ķ��䡣

Ŀǰ���Ž��������⽨������ :
        ����    ��������        ��Ҫ������/���� ����
*     tavern    �ù�            15/50000        ��������һ��mob, ס��
*     shop      �̵�            15/50000        ������Ʒ����˰
*   herb_shop   ҩ��            15/50000        ��ҩ����˰
*     bank      ����            15/50000        ��Ǯ -- ������
*   post_office �ʾ�            15/50000        �շ��ż� -- ������
*     board     ���԰�          15/50000        ���Ժ���������, һ���������
      vote      ͶƱ��          15/50000        ���й�Ͷ, һ���������
*    smith      ����		20/50000	������õ�����
*    armory	������		20/50000	������õ�װ��
      baker     �����          20/80000        ����������ʳ��
?     stable    ���            20/80000        �ṩ���
*     barracks  ��Ӫ            25/100000       ���վ��ӣ���������
*     prison    ����            25/100000       ר�Źط����õ�
*    trainyard  ѵ����          30/250000       �з����м����뿪���¼���
*    gate       �ؿ�            30/250000       ��ϸ������ help gate
*    prairie    ������          35/300000       ������������׬Ǯ
?  equipment    �з���          35/300000        �з�������װ��
*  magic_tower  ������ϰӪ      35/300000       �з�ħ�������뿪���·���
?    altar      ��̳            50/500000       ��ǿ�������ߵ�����
   magic_circle ħ����          50/500000       �ٻ�ǿ��ħ��������з����
?  hero_guild   Ӣ�ۻ��        50/500000       �ٻ�ǿ����Ȼ������з����

* : �����      ? : �ɽ�����������δ��ȫ����
���������Ѷ :  set_short, set_long, add_mob, add_desc, rooms, areas
                special_rooms, saveroom, delete_room, linkroom

HELP
	);
	return 1;
}
