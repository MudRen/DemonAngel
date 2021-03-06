//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/daemons/auto.c
// by bor @DA, 2/23 2003
/*
kingdom_develop:
	程式的计算方式甚为简陋, 请自行修改以及补上各位想要的判定即可, 例如是否要补上
	倒退数值, 如,该国家被 RA 过,那么就在 kingdom_data 内补上 bad_par 的数值, 以后
	就参考 bad_par 作一个负向修正.

*/

#pragma optimize
#pragma save_binary

//inherit F_CLEAN_UP;				// 记得不要用，不然隔一段时间就被系统销毁了，那就跑不起来了

// 各位可以将此资讯于一开始建国时写入，当作一个基本资讯
// 可以针对某国家情形限制发展
#define MAX_DEVELOP	80

//#define DEBUG


string *port_list = ({				// 记录系统港口的列表，当你有新的系统港口出现时，记得来补一下
	"/d/gourd/ship_port.c",			// 不然是没用的唷 .... 另提一下，各位看官想一下怎么记录港口列
						// 表而不用这么麻烦一个一个填写至此
	});

void create()
{
	call_out("kingdom_develop", 20);
	call_out("sys_port", 5);		// 系统港口初始化
}

void kingdom_develop()
{
	string *str, *list=({});
	mapping K_DEV = ([]);
	int i, j, gold, dev, tmp, max_tmp, flag = -1;

	str = get_dir(KINGDOM_DIR);

	if( zerop(str) ) call_out("kingdom_develop", 1200);	// 20 分钟后继续判定

	for(i=0; i<sizeof(str); i++) {	// 每一国家开始作判定

#ifdef DEBUG
		log_file("develop_log", sprintf("[%s]%s log\n", ctime(time())[0..19], str[i]) );
#endif

		if( file_size(kingdom_data_path(str[i])+".o") == -1 ) continue;	// 避免档案毁损
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

			if( kingdom_data(str[i], "open", "check") ) {	// 如果连路
				if( dev>= MAX_DEVELOP ) continue;
			} else {
				if( dev>= MAX_DEVELOP*3/4 ) continue;
			}

			// 依照发展值来计算何时可以升级
			max_tmp = dev * dev * 3 + 1000;

			if( max_tmp < 1 ) max_tmp = 1000;
			if( !(tmp = K_DEV[list[j]]["tmp"]) ) tmp = 0;

			if( gold >= dev*dev*25 + 1000 ) {	// 金钱足够才能增加 tmp
				tmp += 20 + random(30);	// 或者写成 tmp += 20 - bad_par;  bad_par 自行去取得相关数值
				gold -= dev*dev*25 + 1000;
				flag = 1;
			}

			if( tmp >= max_tmp ) {
				tmp -= max_tmp;
				dev += 1;
				flag = 1;
			}

			if( flag == -1) continue;

			// 写入资料, 这种写法上有待加强，不然资料多的话，一直存取，会造成负担的
			// 提示一下, 各位可以用 array 方式一次写进国家的 develop
			develop_data(str[i], "set", list[j], "gold", gold );
			develop_data(str[i], "set", list[j], "tmp", tmp );
			develop_data(str[i], "set", list[j], "dev", dev );

#ifdef DEBUG
			log_file("develop_log", sprintf("[%s]%s: %s -> dev:%d, gold:%d, tmp:%d\n", ctime(time())[0..19], str[i], list[j], dev, gold, tmp ) );
#endif

		}
	} // 所有国家处理完毕
	call_out("kingdom_develop", 1200); // 20 分钟
}

// 初始化所有系统港口
void sys_port()
{
	object ob, *all, *all_no_path_ship=({}), port;
	string path;

	if( sizeof(port_list)>0 ) {
	for(int i=0; i<sizeof(port_list); i++) {
		if( !objectp(ob = find_object(port_list[i])) ) {	// 由于一开机或者没人走动的房间是不会有 object 的
			call_other( port_list[i], "???" );		// 因此必须让该房间变成 object 才能让船只动起来
			ob = find_object( port_list[i] );
		}
		if(!ob) continue;
		if( ob->query("type")!="port" ) continue;		// 确定一下系统的港口是否有 "port" 的标记
		all = all_inventory(ob);				// 取得所有该房间的所有物件(有可能刚好有玩家,NPC,ITEM,...)

		// 1. 开始过滤并取得正确的船只
		// 方案一: 使用 foreach 去判定
//		foreach(object a_ob in all) {
//			if( a_ob->query("type")!="ship" ) continue;
//			all_no_path_ship += ({a_ob});
//		}
		// 方案二直接用 filter 去过滤
		all_no_path_ship = filter(all, (:
			objectp($1) && $1->query("type")=="ship"
		:), this_object() );

		// 2. 开始替每艘船标示基本资讯(如, 出口...)
		if( sizeof(all_no_path_ship)>0 ) {
			for(int j=0; j<sizeof(all_no_path_ship); j++) {
				all_no_path_ship[j]->set("exits/out", all_no_path_ship[j]->query("port1") );
				all_no_path_ship[j]->set("ship_out", all_no_path_ship[j]->query("port1") );
				all_no_path_ship[j]->set("path_flag", 2);	// 系统港口 -> 国家港口
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

// 准备移到船只集合地
int ship_standby(object ship, object port)
{
	message_vision(ship->name() + "的水手吆喝道 :“要开船啦 !! 下一站是" + port->query("short") + ", 没上船的旅客请赶快 !”\n", ship );
	call_out("ship_move", 10+random(4), ship );
	return 1;
}

// 移进船只集合地
int ship_move(object ship)
{
	int flag;

	flag = ship->query("path_flag");

	if( flag==1 ) ship->set("path_flag", 2);	// 表示船回主大陆, 以为下次用
	else ship->set("path_flag", 1); 		// 表示船回国家, 以为下次用

	message_vision(ship->name()+"一阵震动后, 离开码头, 向无际的海洋驶去。\n", ship);
	ship->delete("exits/out");
	ship->set("shiping", 1);
	ship->move(SHIP_CORPSE);
	return 1;
}

// 冒险船移到港口内
void sys_ship(object *all_ship)
{
	object ship, port, port_next;
	int flag;

	for(int i=0; i<sizeof(all_ship); i++) {
		ship = all_ship[i];			// 取得第 N 艘的冒险船
		flag = ship->query("path_flag");

		if( !port_next = find_object(ship->query("port"+flag) ) ) {
			call_other(ship->query("port"+flag), "???");
			port_next = find_object(ship->query("port"+flag));
		}

		if( flag==1 ) flag = 2;
		else flag = 1;

		// 标示将要前往哪一个停靠站
		if( !port = find_object(ship->query("port"+flag) ) ) {
			call_other(ship->query("port"+flag), "???");
			port = find_object(ship->query("port"+flag));
		}
		if( base_name(environment(ship)) == SHIP_CORPSE ) {
			ship->move( port );
			ship->delete("shiping");
			ship->set("exits/out", base_name(port)+".c" );
			message_vision(ship->name()+"驶入" + port->query("short") + "进行水源补充与交换货品。\n", ship );
			call_out("ship_standby", 80+random(6), ship, port_next );
		}		
	}
	call_out("sys_ship", 180+random(6), all_ship);
}
