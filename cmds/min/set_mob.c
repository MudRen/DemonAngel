//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/set_mob.c
// by bor @DA, 4/25 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

void show_npc( object mob );
private int check_legal_name(string name);
private int check_legal_id(string id);

int main(object me, string arg)
{
	object env, ob;
	string arg1, arg2, type, set, *list=({}), mob_file;
string *set_type = ({ "name", "id", "long", "nickname", "level", "unit",
	"gender", "aggressive", "no_corpse", "die_msg", "home", "chasing",
	"polite", "reward"
});
	int value, npc_cost;
	mapping dbase;

	seteuid(getuid());
	if( !arg ) return notify_fail("ָ���ʽ : set_mob <��������> <��������> <�趨ֵ>\n");
	env = environment(me);
	if( ob = present(arg, env) ) {	// ��ѯ�� npc ����
		if( !ob->query("kingdom") || ob->query("kingdom")!=me->query("kingdom/id") )
			return notify_fail("What?");
		show_npc(ob);
		return 1;
	}
	if( sscanf(arg, "%s %s", arg1, arg2) != 2 )
		return notify_fail("ָ���ʽ : set_mob <��������> <��������> <�趨ֵ>\n");
	if( !(ob = present(arg1, env)) ) {
		// �����û�¹� home change �Ļ�����ֻ��һ��� mob �޸Ķ���
		if( !( ob = me->query_temp("change_mob") ) ) return notify_fail("û����� MOB !!\n");
	}
	if( file_size(full_name(ob)) == -1) return notify_fail("û����� MOB !!\n");
	if( ob->is_character() && userp(ob) ) return notify_fail("�ⲻ��һֻ���\n");
	if( ob->query("kingdom") != me->query("kingdom/id") )
		return notify_fail("�ⲻ�ǹ�������\n");

	if( sscanf(arg2, "%s %s", type, set) != 2 ) {
		return notify_fail("ָ���ʽ : set_mob <��������> <��������> <�趨ֵ>\n");
	}
	if( !mapp(dbase = ob->query_entire_dbase()) ) return 0;

	if( !arrayp(list = ob->query("refresh_data")) && sizeof(list)==4)
		return notify_fail("��������������, �޷��ж�Ȩ�ޡ�\n");

	// �ж�����û��Ȩ���� NPC
	if( list[0]!=me->query("id") && !me->query("kingdom/king") )
		return notify_fail("��Ȩ�޲���, û�취�޸ĸ����\n");

	if( ob->query_temp("barracks") )
		return notify_fail("������Ӫ״̬, �������޸ġ�\n");

//	if( file_size(ob->query("home")+".c") == -1 )
//		return notify_fail("���ļ��Ѿ������٣��޷�������ȥ�� !!\n");

	if( member_array(type, set_type) == -1) return notify_fail("û�������Ĳ������͡�\n");

	switch(type) {
		case "name":
		case "nickname":
			if( type == "nickname" && set =="-d") {
				if( !dbase["nickname"] ) return notify_fail("OK !\n");
				ob->delete("nickname");
			} else {
				if(strlen(set)>30) return notify_fail("��Ĳ���̫���ˡ�\n");
				set = ansi_color(set);
				if( !check_legal_name(set) ) return notify_fail("������˼����ȡ�� name �����Ϲ涨 !!\n");
				if( sscanf(set, "[%*s") || sscanf(set, "%*s[%*s") ) dbase[type]=set+"[0m";
				else dbase[type]=set;
			}
			break;
		case "id":
			if(strlen(set)>30) return notify_fail("��Ĳ���̫���ˡ�\n");

			if(type=="id") {
				if( !check_legal_id(set) ) return notify_fail("Ӣ���ڰ������Ϸ��ĵ��ֻ򲻵�ʹ�á�\n");
			}
			dbase[type] = set;
			break;
		case "long":
			if( !sscanf(set, "%d", value) ) value = 0;
			switch( value ) {
				case 0:	// �����Զ��Ű�
				case 1:	// �Զ��Ű�
					me->edit( (: call_other, __FILE__, "do_changelong", ob, value :) );
					return 1;
					break;
				default:
					return notify_fail("û�������Ĳ�����\n");
			}
			break;
		case "polite":
		case "no_corpse":
		case "aggressive":
		case "chasing":
			value = atoi(set);
			if( value<0 ) return notify_fail("�����趨�����Ĳ�����\n");
			if( value != 0 && value != 1 ) return notify_fail("�����趨�����Ĳ�����\n");
			if(type =="polite") {
				if( dbase["type"]!="barracks" ) return notify_fail("����ֻ�о������ͣ������趨�˲�����\n");
			}
			dbase[type] = value;
			write(dbase["name"]+"("+dbase["id"]+")�� "+ type +" �趨Ϊ " + value +"\n");
			break;
		case "level":
			if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
			if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");

			value = atoi(set);
			if( value==-1 ) return notify_fail("�����趨�����Ĳ�����\n");
			if( value == dbase["level"] ) return notify_fail("MOB �ĵȼ�������������ȼ� !!\n");
			if( value > 50 ) return notify_fail("MOB �ȼ����ܳ��� 50��\n");
			if( value < 1 ) return notify_fail("MOB �ĵȼ�������ô�� !!\n");
			if( value > dbase["level"] ) {
				npc_cost = ( value - dbase["level"] ) * 5000;
				if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < npc_cost )
					return notify_fail("���������㡣\n");
				dbase["level"] = value;
				write(dbase["name"]+"�ĵȼ��趨Ϊ "+ value +"\n");
				kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", npc_cost );
			} else {
				dbase["level"] = value;
				write(dbase["name"]+"�ĵȼ��趨Ϊ "+ value +"\n");
			}
			break;
		case "die_msg":
			if( set == "-d") {
				ob->delete("die_msg");
				break;
			}
			set = ansi_color( set );
			set = kill_all_bug(set);
			dbase[type] = set+"\n";
			break;
		default:
			write("Ŀǰ��ʱ�����Ŵ˲������͡�\n");
			return 1;
	}

	if( !save_npc(ob) ) return notify_fail("���� MOB ����ʧ��, ��ر��������� !!\n");
	write("OK !\n");

	mob_file = base_name(ob);

	if(objectp(ob)) destruct(ob);
	if(find_object(mob_file)) destruct(find_object(mob_file));
	ob = new(mob_file);
	ob->move(env);			// ��һ��� mob �Ͱ� mob �Ƶ��ø�Ϳ�

	refresh_room(env);
        return 1;
}

void show_npc( object mob )
{
	string str;
	object me = this_player();
	mapping dbase;

	dbase = mob->query_entire_dbase();

	str = sprintf("[1;30m"+dbase["name"]+"("+dbase["id"]+")"+"���������� :\n\n[m");

	str += sprintf("name : %s\t\tid : %s\tlevel : %d\n", dbase["name"], dbase["id"], dbase["level"] );
	str += sprintf("nickname : %s\n", dbase["nickname"]?dbase["nickname"]:"��");
	str += sprintf("race : %s\t\tgender : %s\t\tunit : %s\n", dbase["race"], dbase["gender"], dbase["unit"] );
	str += sprintf("aggressive : %d\t\tchasing : %d\t\treward : %s\n", dbase["aggressive"], dbase["chasing"], dbase["reward"]?dbase["reward"]:"��" );
	str += sprintf("no_corpse : %d\t\twimpy : %d\t\tpolite : %d\n", dbase["no_corpse"], dbase["wimpy"], dbase["polite"] );
	str += sprintf("die_msg : %s\n", dbase["die_msg"]?dbase["die_msg"]:"��" );
	str += "long :\n";
	str += sprintf("%s\n", dbase["long"] );

	me->start_more(str);
	return ;
}

private int check_legal_id(string id)
{
	int i;
	string *banned_id = ({"bor","zethus","fuck","sbada"});

	i = strlen(id);
        
	if( (strlen(id) < 2) || (strlen(id) > 20 ) ) return 0;
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) return 0;
	for(i=0;i<sizeof(banned_id);i++) {
		if(strsrch(id, banned_id[i]) != -1) {
			write("�Բ�����������в������ֽ�����ɱ������š�\n");
			return 0;
		}
	}
	return 1;
}

private int check_legal_name(string name)
{
        int i;
string *banned_name = ({
	"��", "��", "��", "��", "��", "��", "��", "�k", "��", "��", "��",
	"�����", "����", "Ѽ", "ҡƨƨСˮѼ","ҹ��","��ɵ�Ѽ��","����һϢ"
});
	i = strlen(name);
        
	if( (strlen(name) < 4) || (strlen(name) > 30 ) ) return 0;
	while(i--) {
		if( name[i]<=' ' ) return 0;
		if( i%2==0 && !is_chinese(name[i..<0]) ) return 0;
	}
	for(i=0;i<sizeof(banned_name);i++) {
		if(strsrch(name, banned_name[i]) != -1) return 0;
	}
	return 1;
}

void do_changelong(object ob, int flag, string str)  // �趨 mob long
{
	string *str_arg;

	str = ansi_color( str );

	if( strlen(str) > 8192 ) {
		write("��Ĳ���̫���ˡ�\n");
		return;
	}
	str_arg = explode(str, "\n");

	if( sizeof(str_arg) > 11 ) {
		write("�������ʮ�����ڡ�\n");
		return;
	}
	str = kill_all_bug(str);

	if( flag==0 || flag ==1) ob->set("long", str);

	if( save_npc(ob) ) write("OK !\n");
	else write("[1;30m�޸�ʧ�ܡ�\n[m");
        return ;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : set_mob <��������> <��������> <�趨ֵ>

���ǹ������������ mob ���趨��ָ������ָ�������Ըı�һЩ mob
�Ĳ�����ʹ�����������ʺϻ�����
������Ŀǰ�����趨�Ĳ������� :
 name   :       �趨������������֡�
 id     :       �趨�����Ӣ�����֡�
 nickname:      �趨����Ĵºš����� set_mob ruby nickname ��ħ��
                ��Ϳ��Կ��� ����ħ�������(Ruby)��
                ������� nickname -d ��ԭ�ȵ� nickname ������
                nickname ��ɫ���÷���ο� help nick
 long   :       �趨���������, �����㿴�����Ƕ�������
 race   :       �趨���壬Ŀǰ�� : ���ࡢҰ�ޡ���ħ������ ...
 unit   :       �趨��λ������ : λ��ֻ��ͷ���� ...
 gender :       ���Ի�Ů�ԡ����Ի���ԡ�
 aggressive :   ����������ֵΪ 1����ֻ����ͻ�ץ���� ...
 chasing :      �� mob ������׷�����ˣ����������ս�������ܣ����ᾡ����
                ׷ɱ���ܵĵ��ˣ�ֱ��׷����Ϊֹ���� 0 �ͻ���׷ɱ��
                  ���� : set_mob <mob> chasing <1/0>

 ask    :       �趨�����ĳЩ����Ĵ𸲣����� :
                set_mob soldier ask ruby����ʱ��ش����ڱ༭��������
                ��ѶϢ�����ʲô��ûд��������������Ͳ���ش�
                ������� set_mob <id> ask what ����ѯ�������Ŀǰ��ش�
                ���������⡣
 ask -d  :      ��ĳ������Ĵ�ȡ��

 chat_msg :     �趨�����һֱ��˵��ĳЩѶϢ, ���� :
                set_mob bagger chat_msg ��ؤ������� : ��ү !! ����С�İ� !!
                ������� set_mob <id> chat_msg what ����ѯ�������Ŀǰ��
                �лὲ��ѶϢ
 chat_msg -d <ѶϢ���> : ɾ����ֻ�����ĳЩ�ὲ��ѶϢ��
 chat_msg_combat : �趨������ս��ʱ�ὲ�Ļ�, �÷��� chat_msg ��ͬ
                  set_mob beggar chat_msg_combat ��ؤ���� : ����� !! ���˰� !!

 reward :       �� mob ����������������һ����������������ֻ��������
                ר����Ʒ������ : set_mob dragon reward gem����Ȼ����Ҫ�� gem
                ��������ÿ�θɵ� dragon����ͻ��һ�鱦ʯ
                �����Ҫȡ�� rewared, ������ set_mob <mob> reward none

 no_corpse :    ��� 1 ʱ���� mob ������������������ʬ�壬���ϵ�װ��Ҳ������
                ��������� 0 �Ϳ��Խ������״����

 die_msg :      �� mob ������ʱ��������µ�ѶϢ������ :
                ��ħ����¶���������ŵı��飬����$N��� : ��ô���� ?? ���ǲ�
                �ᱻ��ܵ� !!
                ����Ҫ����ץס$N���������ڻ���һ��ʯͷ��
                ����� $N �Ǳ�ʾ��������˵����֡�
 die_msg -d :   ɾ�� die_msg

 home   :       Ҫ mob ��ҡ����� :
                  ���ҵ�Ҫ��ҵ� mob���� set_mob dog home change ָ�Ȼ��
                  �ߵ������¼ң����� set_mob dog home here�����������ͻ�ᵽ
                  �¼��ˡ������������ң��� set_mob dog home cancel��

 owner  :       �� mob ��������, �����˱���Ҳ�Ǵ󳼡�ֻ��ԭ���˺͹������á�

 level  :       �� mob ����ȼ�����Ȼ�û���Ǯ���ǻỨ�ġ�

 sp_attack :    �� mob �趨���⹥������̬��ѶϢ������ :
                  �����ع� : set_mob <mob> sp_attack <�ع���̬> <�ع�ѶϢ>
                  ȡ���ع� : set_mob <mob> sp_attack -d <�ع���̬>
                �ع�ѶϢ��д�� : $N�ݺݵ���$n�Ľ���ҧ��һ�ڡ�
                        $N ��ʾ����ʹ���ع�����������
                        $n��ʾ�������Ķ��������
                ���⹥������̬��ο� help special_attack

 path   :       �� mob �����ض���·�������߶������� :
                 �趨·��  set_mob <mob> path east, east, west, west
                 ȡ��·��  set_mob <mob> path -d
                mob �߶���·�߱�����һ����·�����������ܶ���ʼ��һֱ�߶�,
                ·�ߵ�ÿ�����򶼱��������������ö�����������е������У�
                ֻ�о��������������߶�ʱͬʱ��Ѱ���ˡ�·�ߵ��趨������
                ��ֻ���� mob �ļҲ��ܽ��У����Ҳ��������߳�������

 wimpy :        �� mob �������������趨����ֵʱ���ͻᵽ�����ӡ�
                set_mob <mob> wimpy <��ֵ>

 polite :       ����Ӫ������Ĳ���������趨�����ͻ��Ӣ�����ϵ��˾���
                �� : set_mob soldier polite <1 or 0>

������� set_mob ����ֱ�Ӽ� mob �� id, �ǾͿ��Կ����� mob �������趨ֵ��

�� : set_mob dog name �蹷

���������Ѷ :  add_mob, build, delete_mob


HELP);
	return 1;
}
