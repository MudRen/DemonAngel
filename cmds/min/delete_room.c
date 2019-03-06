//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/delete_room.c
// by sbada @ RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	string *dir_list = ({"east","west","north","south","down","up"});
	string id, del_file, type, file;
	object new_env;
	int flag=0;

	seteuid(getuid());
	if(!arg) return notify_fail("ָ���ʽ : delete_room <����>\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !id = me->query("kingdom/id") ) return 0;
	if( !environment(me)->query("kingdom_id")
	|| environment(me)->query("kingdom_id") != id
	) return notify_fail("���ﲻ�ǹ�������ء�\n");
	arg = lower_case(arg);
	if( member_array(arg, dir_list)==-1 ) return notify_fail("û���������\n");
	if( !del_file = environment(me)->query("exits/"+arg) ) return notify_fail("�������û�з��䡣\n");
	if( !sscanf(del_file, "%*s.c") ) del_file += ".c";

	if( !new_env = find_object(del_file) ) {
		call_other(del_file, "create_room");
		new_env = find_object(del_file);
	}
	if( new_env->query("no_delete") || new_env->query("no_save") || new_env->query("no_change") )
		return notify_fail("���淿���޷��Ƴ�!!\n");

	if( !type = new_env->query("type") ) type = "normal";

	switch( type ) {
		case "normal":
			// 1. �����н��� room �� npc ��ͳ��Ȼ����¹�����Ѷ
			// 2. �Ƴ� room
			kingdom_data(id, "data", "add", "room_num", 1);
			kingdom_data(id, "data", "sub", "room", 1);
			break;
		case "port":	// by bor @DA, 3/4 2003
			return notify_fail("���Ҹۿڲ����������\n");
			break;
		default:
			// ���⽨����
			kingdom_data(id, "special_room", "sub", type, del_file);
			// ��ʼ���� board data
			if( type == "board") {
				del_file = replace_string(del_file, ".c", "");
				file = explode(del_file, "/")[2];
				file = id+file;
				rm(DATA_DIR+"board/"+file+".o");
				rm(KINGDOM_DIR+id+"/data/"+file+".c");
			}
	}

	if( new_env->query("objects") && sizeof(new_env->query("objects"))>0 ) {
		// �������и÷���� NPC ��¼
		foreach( file, int tmp in new_env->query("objects") ) {
			if(file_size(file+".c")==-1) continue;
			flag += 1;
			if( find_object(file) ) destruct(find_object(file));
		}
	}
	// ����Ǿ�Ӫ������?
	if( new_env->query("data") && sizeof(new_env->query("data"))>0 ) {
		string *list;
		list = new_env->query("data");
		// �������и÷���� NPC ��¼
		for(int i=0; i<sizeof(list); i++) {
			if(file_size(list[i]+".c")==-1) continue;
			flag += 1;
			// ����Ѿ���Ӫ, �Ǿ����� NPC
			if( find_object(list[i]) ) destruct(find_object(list[i]));
		}
	}
	kingdom_data(id, "data", "sub", "npc", flag);
	kingdom_data(id, "data", "add", "npc_num", flag);

	if( !sscanf(del_file, "%*s.c") ) del_file += ".c";
	rm(del_file);
	destruct(new_env);

	environment(me)->delete("exits/"+arg);
	
	message_vision("$N����һ�ѹ������� "+capitalize(arg)+" �����וּģ�������䷿�䡣\n", me);
	do_saveroom(environment(me));
	return 1;
}

int help(object me)
{
write(@HELP

ָ���ʽ : delete_room <����>

���ǹ�����󳼿�������ʱ����������෿���ָ����������ɾ��ֻ
ʣһ�����ڻ���һ��ֱֱͨ���ķ���(���ַ��������������)���������
�ڵķ��������վ��λ�á����ָ�������ɾ��������

���������Ѷ :  set_short, set_long, add_mob, add_desc, rooms, areas
		special_rooms, saveroom

HELP
	);
	return 1;
}
