//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/add_mob.c
// by bor @DA

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

#define NPC_COST	5000

int main(object me,string arg)
{
	int num, lv;
	string file, type, NPC_CODE, name, id;
	object env, ob;

	seteuid(getuid());
	if( !(env = environment(me)) ) return 0;
	if( env->query("kingdom_id")!=me->query("kingdom/id") ) return notify_fail("�ⲻ�ǹ��������!!\n");
	if( !arg || !sscanf(arg, "%d %s", lv, type) ) return notify_fail("ָ���ʽ��add_mob <�ȼ�> <�Ӻδ���>\n");
	if( lv>45 || lv<1 ) return notify_fail("Ŀǰ��������Щ�ȼ���mob��\n");

	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < NPC_COST * lv )
		return notify_fail("���������㡣\n");

	num = kingdom_data(me->query("kingdom/id"), "data", "query_par", "npc")
		+ kingdom_data(me->query("kingdom/id"), "data", "query_par", "npc_num");

	file = KINGDOM_DIR+me->query("kingdom/id")+"/npc/"+(string)num;

	if(!kingdom_data(me->query("kingdom/id"), "special_room", "check", type))
		return notify_fail("���û�� "+type+" �����͵����⽨����, �޷��������\n");

	if( lv>15 ) {
		if( type=="stable" ) {
			if( lv>20 ) return notify_fail("��ƥ�ĵȼ�, ���ó��� 20��\n");
			if( lv > develop_data(me->query("kingdom/id"), "query_par", "stable", "dev") )
				return notify_fail("�����չ����, û�취����ߵȼ����\n");
		} else
			if( lv > develop_data(me->query("kingdom/id"), "query_par", type, "dev") )
				return notify_fail("�����չ����, û�취����ߵȼ����\n");
	}

// ��ʼ�趨
	switch(type) {
		case "tavern":
			if ( lv<=5 ) { name = "С��";id = "child"; }
			else { name = "����";id = "man"; }
			break;
		case "barracks":
			if ( lv<=15 ) { name = "����";id = "guard"; }
			else { name = "����";id = "guard"; }
			break;
		case "misc_shop":
			if ( lv<=10 ) { name = "ʵϰ����";id = "merchant"; }
			else { name = "����";id = "merchant"; }
			break;
		case "magic_tower":
			if ( lv<=10 ) { name = "Сħ��ʦ";id = "mage"; }
			else { name = "��ʦ";id = "mage"; }
			break;
		case "church":
			if ( lv<=10 ) { name = "С��ʦ";id = "cleric"; }
			else { name = "��ʦ";id = "cleric"; }
			break;
		case "stable":
			if ( lv<=10 ) { name = "����";id = "horse"; }
			else { name = "Ұ��";id = "horse"; }
			break;
		default:	// ���� ���� type �� default
			write("ע�� : ��"+type+"����û�ж���� !!\n");
			return 1;
	}


// NPC ������̬
	NPC_CODE = "// NPC : " +file+".c\n";
	NPC_CODE += "// savenpc by "+ me->query("id")+"    "+ctime(time())+"\n\n";

	NPC_CODE += "inherit "+upper_case(type)+"_NPC;\n\n";

	NPC_CODE += "#include <ansi.h>\n\n";
	NPC_CODE += "void create()\n{\n";
	NPC_CODE += "\tset_name(\""+name+"\", ({\""+id+"\", \""+id[0..0]+"\", \""+id[0..1]+"\"}) );\n";
	NPC_CODE += sprintf("\tset(\"long\", @TEXT\n%s\nTEXT\n\t);\n", "�㿴��һֻ��"+chinese_number(lv)+"����"+name+"��" );
	NPC_CODE += sprintf("\tset(\"type\", %O);\n", type );
	NPC_CODE += sprintf("\tset(\"level\", %O);\n", lv );
	NPC_CODE += sprintf("\tset(\"refresh_data\", %O);\n", ({ this_player()->query("id"), ctime(time()), this_player()->query("id"), ctime(time()) }) );
	NPC_CODE += sprintf("\tset(\"home\", %O);\n", base_name(env) );
	NPC_CODE += sprintf("\tset(\"kingdom\", %O);\n", me->query("kingdom/id") );
	if( type=="stable") {
		NPC_CODE += sprintf("\tset(\"ridable\", 1);\n");
	}
	NPC_CODE += "\tsetup_npc();\n\n";
	NPC_CODE += "}\n";
    
	write_file(file+".c", NPC_CODE, 1);

	if( !(ob = call_other( file, "???" )))
		ob = new(file);

	if(!objectp(ob)) return notify_fail("�д�����, ��֪ͨ�����ߡ�\n");

	ob->move(env);
	message_vision("$N˫��һ��, �ٻ���$n\n", me, ob);

	env->add("objects/",([ file:1 ]));
	do_saveroom(env);
	refresh_room(env);

	kingdom_data(me->query("kingdom/id"), "data", "add", "npc", 1);
	kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", NPC_COST * lv );
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ��add_mob <�ȼ�> <�Ӻδ���>

����������ô�ָ��ɴ���mob��

���磺 add_mob 20 tavern

Ŀǰ�������յ��У�

  tavern        : �����������������һ��İ��գ����ǰ��ú�ƽ��ֻ��վ�ű�
                  ��Ȼ�������
  misc_shop     : �������е�һЩ����, ���ǿ��Է���һЩ����������ð����, ͬ
                  ʱ�����׬Ǯ��
  barracks      : �Ӿ�Ӫ���г����ľ��� -- �����ķ����������������뽻ս��
                  ���Ǳ�ͨ�������ı�������Ⱥ׷ɱ��
  church	: �ӽ����ٳ�������ͨ��������ʥ����������Ȼս����ǿ�����ǵ�
  		  ��Խ�ߣ��ͻ�Խ�а�����
  magic_tower   : ��ħ�����ٳ������ﶼ��һЩħ��ʦ���ó�ʩ����ħ��������ս
		  ����Ҳ���
  stable	: Ұ��

HELP
	);
	return 1;
}
