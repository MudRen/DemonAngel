//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/adm/put_ship.c
//
//	˵��:
//		��ʽ���в���ȱʧ�����磬ĳ�ۿ��Ѿ��� ship �ˣ���ʱ���� put_ship �󣬻ᷢ��������?
//	���磬�������˴������Ǹۿ��ֱ��󿳣���..ϵͳ������??���ⶼҪ����λȥ˼��һ���ˣ���������
//	��д����ĳ�ʽ���ǿ���ͷ���ѣ���˻��� BUG ����������ģ���Ȼ����д���ˣ��Ǹ�λ����û����
//	�� ~~~~ ��������һ�ᣬĿǰ�Ĵ�ֻ save д�� /include/ship.h �ڣ�����Ŀǰ�Ǵ�ֻ�� board ȫ��
//	��Ҫ����ȥд���ܿ��Ե��ϼ�д�ģ���Ҫ�Լ������Ծ��ˡ�
//		��ֻ�ĸ����Ӻʹ�ֻ��������ʱ���ֶ�ȥ�İɣ���Ȼ���Լ��ο������short �� long ȥ�ĸ�
//	��ֻʹ�ðɡ�
//
// by bor @DA, 2/24 2003
// by bor @DA, 2/25 2003
// by bor @DA, 3/4 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

#include <ship.h>

int main(object me, string arg)
{
	string par, cod, id, file;
	object ob, port_ob;
	mapping port = ([
		"port1"	: "/d/gourd/ship_port.c",		// port1 ��ǵ�Сд
	]);

	if(!wizardp(me)) return 0;
	if(!arg) return notify_fail("ָ���ʽ : put_ship <here | cancel> <ϵͳ�ۿڴ��� | ����>\n");

	if( sscanf(arg, "%s %s", par, cod) != 2 ) return notify_fail("ָ���ʽ : put_ship <here | cancel> <ϵͳ�ۿڴ��� | ����>\n");

	par = lower_case(par);
	cod = lower_case(cod);

	switch(par) {
		case "here":	// ��ǵ�վ��ĳ���ҵĸۿ�����ָ��
			if( member_array(cod, keys(port))==-1 ) return notify_fail("�Ҳ���������ϵͳ�ۿڴ��� !\n");
			if( !(id = environment(me)->query("kingdom_id")) ) return notify_fail("���ﲻ�ǹ��ҵ���̬!");
			if( !check_kingdom(id) ) return notify_fail("���ﲻ�ǹ��ҵ���̬!");
			kingdom_data(id, "open", "set", "door", 1);
			kingdom_data(id, "open", "set", "land", port[cod]);
			kingdom_data(id, "open", "set", "port", base_name(environment(me))+".c");
			kingdom_data(id, "open", "set", "room", KINGDOM_DIR+id+"/ship/ship.c");	// ��¼��ֻ
			message_vision("$N����һ�ѹ��������������ô��ģ�����һ��ͨ�̸ۿڡ�\n", me);
			file = KINGDOM_DIR+id+"/ship/ship.c";
			if( file_size(file) == -1 ) cp( "/d/ship/ship.c", file );

			// 1. ����ֻ
			if( !objectp(ob = find_object(file)) ) {
				call_other(file, "???");
				ob = find_object(file);
			}
			ob->set("port1", port[cod]);				// ϵͳ�ۿ�
			ob->set("port2", base_name(environment(me))+".c");	// ���Ҹۿ�
			ob->set("kingdom_id", id);
			do_save_ship(ob);
			destruct(ob);

			// 2. ����ϵͳ�ۿ�
			if( !objectp(port_ob = find_object(port[cod])) ) {
				call_other(port[cod], "???");
				port_ob = find_object(port[cod]);
			}
			port_ob->add("objects/", ([file:1]) );
			do_saveroom(port_ob);

			// 3. ������Ҹۿ�
			environment(me)->set("type", "port" );
			do_saveroom(environment(me));

			break;
		case "cancel":	// ע�⿴һ�³�ʽ���ƺ������ҵ� ship �Լ�ϵͳ�ۿڶ�û��˵���Ǻǣ�͵һ������
				// �Լ�����~~ ��Ȼ�ô˹��ܺ�, �Ժ󿪻���ֻһ������, ��Ϊϵͳ�ۿ�û������������
			if( !check_kingdom(cod) ) return notify_fail("�Ҳ���������� !");
			if( !kingdom_data(cod, "open", "check") ) return notify_fail("�ù���û����· !");
			if( !kingdom_data(cod, "open", "del") ) return notify_fail("�ù���û����·���� !");
			// ���ҵĸۿ�����, ���д��ϵͳĳ����Ѷ��, �Ժ󷽱� cancel (Ŀǰ����û�����ҵ� port)
			// ����˵, �ο� /adm/daemons/chinesed.c �ڵ� add_kingdom_name()
			write("��ȡ���� "+ cod +" ����· !\n");
			break;
		default:
			return notify_fail("ָ���ʽ : put_ship <here | cancel> <ϵͳ�ۿڴ��� | ����>\n");
	}
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : put_ship <here | cancel> <ϵͳ�ۿڴ��� | ����>

put_ship	here	�ۿڴ���	�ڸô���ĳ�ۿڴ��Ž���������̴�[��ǵ�վ��ĳ���Ҹۿ�����ָ��]
put_ship	cancel	����		ȡ���ù��ҵ���·�ʸ�

Ŀǰ�ṩ����:
	ϵͳ�ۿڴ���		ʵ�ʶ�Ӧ�ĸۿ�·��
	-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	port1			"/d/gourd/ship_port.c"

HELP
	);
	return 1;
}
