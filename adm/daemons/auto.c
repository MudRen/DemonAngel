//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/auto.c
// by bor @DA, 2/23 2003
/*
kingdom_develop:
	��ʽ�ļ��㷽ʽ��Ϊ��ª, �������޸��Լ����ϸ�λ��Ҫ���ж�����, �����Ƿ�Ҫ����
	������ֵ, ��,�ù��ұ� RA ��,��ô���� kingdom_data �ڲ��� bad_par ����ֵ, �Ժ�
	�Ͳο� bad_par ��һ����������.

*/

#pragma optimize
#pragma save_binary

//inherit F_CLEAN_UP;				// �ǵò�Ҫ�ã���Ȼ��һ��ʱ��ͱ�ϵͳ�����ˣ��Ǿ��ܲ�������

// ��λ���Խ�����Ѷ��һ��ʼ����ʱд�룬����һ��������Ѷ
// �������ĳ�����������Ʒ�չ
#define MAX_DEVELOP	80

//#define DEBUG


string *port_list = ({				// ��¼ϵͳ�ۿڵ��б��������µ�ϵͳ�ۿڳ���ʱ���ǵ�����һ��
	"/d/gourd/ship_port.c",			// ��Ȼ��û�õ�� .... ����һ�£���λ������һ����ô��¼�ۿ���
						// ���������ô�鷳һ��һ����д����
	});

void create()
{
	call_out("kingdom_develop", 20);
	call_out("sys_port", 5);		// ϵͳ�ۿڳ�ʼ��
}

void kingdom_develop()
{
	string *str, *list=({});
	mapping K_DEV = ([]);
	int i, j, gold, dev, tmp, max_tmp, flag = -1;

	str = get_dir(KINGDOM_DIR);

	if( zerop(str) ) call_out("kingdom_develop", 1200);	// 20 ���Ӻ�����ж�

	for(i=0; i<sizeof(str); i++) {	// ÿһ���ҿ�ʼ���ж�

#ifdef DEBUG
		log_file("develop_log", sprintf("[%s]%s log\n", ctime(time())[0..19], str[i]) );
#endif

		if( file_size(kingdom_data_path(str[i])+".o") == -1 ) continue;	// ���⵵������
		if( !(list = develop_data(str[i], "query_all")) ) continue;
		K_DEV = develop_data(str[i], "query");

#ifdef DEBUG
		log_file("develop_log", sprintf("[%s]%s:starting\n", ctime(time())[0..19], str[i]) );
#endif

		for(j=0; j<sizeof(list); j++) {

#ifdef DEBUG
			log_file("develop_log", sprintf("[%s]%s: %s\n", ctime(time())[0..19], str[i], list[j]) );
#endif

			if(!(gold = K_DEV[list[j]]["gold"])) continue;
			if(gold<0) continue;
			dev = K_DEV[list[j]]["dev"];

			if( kingdom_data(str[i], "open", "check") ) {	// �����·
				if( dev>= MAX_DEVELOP ) continue;
			} else {
				if( dev>= MAX_DEVELOP*3/4 ) continue;
			}

			// ���շ�չֵ�������ʱ��������
			max_tmp = dev * dev * 3 + 1000;

			if( max_tmp < 1 ) max_tmp = 1000;
			if( !(tmp = K_DEV[list[j]]["tmp"]) ) tmp = 0;

			if( gold >= dev*dev*25 + 1000 ) {	// ��Ǯ�㹻�������� tmp
				tmp += 20 + random(30);	// ����д�� tmp += 20 - bad_par;  bad_par ����ȥȡ�������ֵ
				gold -= dev*dev*25 + 1000;
				flag = 1;
			}

			if( tmp >= max_tmp ) {
				tmp -= max_tmp;
				dev += 1;
				flag = 1;
			}

			if( flag == -1) continue;

			// д������, ����д�����д���ǿ����Ȼ���϶�Ļ���һֱ��ȡ������ɸ�����
			// ��ʾһ��, ��λ������ array ��ʽһ��д�����ҵ� develop
			develop_data(str[i], "set", list[j], "gold", gold );
			develop_data(str[i], "set", list[j], "tmp", tmp );
			develop_data(str[i], "set", list[j], "dev", dev );

#ifdef DEBUG
			log_file("develop_log", sprintf("[%s]%s: %s -> dev:%d, gold:%d, tmp:%d\n", ctime(time())[0..19], str[i], list[j], dev, gold, tmp ) );
#endif

		}
	} // ���й��Ҵ������
	call_out("kingdom_develop", 1200); // 20 ����
}

// ��ʼ������ϵͳ�ۿ�
void sys_port()
{
	object ob, *all, *all_no_path_ship=({}), port;
	string path;

	if( sizeof(port_list)>0 ) {
	for(int i=0; i<sizeof(port_list); i++) {
		if( !objectp(ob = find_object(port_list[i])) ) {	// ����һ��������û���߶��ķ����ǲ����� object ��
			call_other( port_list[i], "???" );		// ��˱����ø÷����� object �����ô�ֻ������
			ob = find_object( port_list[i] );
		}
		if(!ob) continue;
		if( ob->query("type")!="port" ) continue;		// ȷ��һ��ϵͳ�ĸۿ��Ƿ��� "port" �ı��
		all = all_inventory(ob);				// ȡ�����и÷�����������(�п��ܸպ������,NPC,ITEM,...)

		// 1. ��ʼ���˲�ȡ����ȷ�Ĵ�ֻ
		// ����һ: ʹ�� foreach ȥ�ж�
//		foreach(object a_ob in all) {
//			if( a_ob->query("type")!="ship" ) continue;
//			all_no_path_ship += ({a_ob});
//		}
		// ������ֱ���� filter ȥ����
		all_no_path_ship = filter(all, (:
			objectp($1) && $1->query("type")=="ship"
		:), this_object() );

		// 2. ��ʼ��ÿ�Ҵ���ʾ������Ѷ(��, ����...)
		if( sizeof(all_no_path_ship)>0 ) {
			for(int j=0; j<sizeof(all_no_path_ship); j++) {
				all_no_path_ship[j]->set("exits/out", all_no_path_ship[j]->query("port1") );
				all_no_path_ship[j]->set("ship_out", all_no_path_ship[j]->query("port1") );
				all_no_path_ship[j]->set("path_flag", 2);	// ϵͳ�ۿ� -> ���Ҹۿ�
				path = all_no_path_ship[j]->query("port2");
				if( !port = find_object(path) ) {
					call_other(path, "???");
					port = find_object(path);
				}
				call_out("ship_standby", 80+random(6), all_no_path_ship[j], port );
			}
		}
		call_out("sys_ship", 180+random(6), all_no_path_ship);
	}
	}
}

// ׼���Ƶ���ֻ���ϵ�
int ship_standby(object ship, object port)
{
	message_vision(ship->name() + "��ˮ��ߺ�ȵ� :��Ҫ������ !! ��һվ��" + port->query("short") + ", û�ϴ����ÿ���Ͽ� !��\n", ship );
	call_out("ship_move", 10+random(4), ship );
	return 1;
}

// �ƽ���ֻ���ϵ�
int ship_move(object ship)
{
	int flag;

	flag = ship->query("path_flag");

	if( flag==1 ) ship->set("path_flag", 2);	// ��ʾ��������½, ��Ϊ�´���
	else ship->set("path_flag", 1); 		// ��ʾ���ع���, ��Ϊ�´���

	message_vision(ship->name()+"һ���𶯺�, �뿪��ͷ, ���޼ʵĺ���ʻȥ��\n", ship);
	ship->delete("exits/out");
	ship->set("shiping", 1);
	ship->move(SHIP_CORPSE);
	return 1;
}

// ð�մ��Ƶ��ۿ���
void sys_ship(object *all_ship)
{
	object ship, port, port_next;
	int flag;

	for(int i=0; i<sizeof(all_ship); i++) {
		ship = all_ship[i];			// ȡ�õ� N �ҵ�ð�մ�
		flag = ship->query("path_flag");

		if( !port_next = find_object(ship->query("port"+flag) ) ) {
			call_other(ship->query("port"+flag), "???");
			port_next = find_object(ship->query("port"+flag));
		}

		if( flag==1 ) flag = 2;
		else flag = 1;

		// ��ʾ��Ҫǰ����һ��ͣ��վ
		if( !port = find_object(ship->query("port"+flag) ) ) {
			call_other(ship->query("port"+flag), "???");
			port = find_object(ship->query("port"+flag));
		}
		if( base_name(environment(ship)) == SHIP_CORPSE ) {
			ship->move( port );
			ship->delete("shiping");
			ship->set("exits/out", base_name(port)+".c" );
			message_vision(ship->name()+"ʻ��" + port->query("short") + "����ˮԴ�����뽻����Ʒ��\n", ship );
			call_out("ship_standby", 80+random(6), ship, port_next );
		}		
	}
	call_out("sys_ship", 180+random(6), all_ship);
}
