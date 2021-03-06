//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/adm/put_ship.c
//
//	说明:
//		程式中有不少缺失，例如，某港口已经有 ship 了，这时候又 put_ship 后，会发生怎样呢?
//	又如，国家有了船，可是港口又被误砍，那..系统会怎样??　这都要靠各位去思考一下了，由于在下
//	我写这类的程式都是开个头而已，因此会有 BUG 是在所难免的，不然都我写好了，那各位不就没事做
//	了 ~~~~ 阿，忘了一提，目前的船只 save 写于 /include/ship.h 内，可是目前登船只能 board 全名
//	，要怎样去写才能可以登上简写的，就要自己动动脑经了。
//		船只的改名子和船只叙述，暂时请手动去改吧，不然请自己参考房间的short 和 long 去改给
//	船只使用吧。
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
		"port1"	: "/d/gourd/ship_port.c",		// port1 请记得小写
	]);

	if(!wizardp(me)) return 0;
	if(!arg) return notify_fail("指令格式 : put_ship <here | cancel> <系统港口代号 | 国家>\n");

	if( sscanf(arg, "%s %s", par, cod) != 2 ) return notify_fail("指令格式 : put_ship <here | cancel> <系统港口代号 | 国家>\n");

	par = lower_case(par);
	cod = lower_case(cod);

	switch(par) {
		case "here":	// 请记得站在某国家的港口内下指令
			if( member_array(cod, keys(port))==-1 ) return notify_fail("找不到这样的系统港口代号 !\n");
			if( !(id = environment(me)->query("kingdom_id")) ) return notify_fail("这里不是国家的型态!");
			if( !check_kingdom(id) ) return notify_fail("这里不是国家的型态!");
			kingdom_data(id, "open", "set", "door", 1);
			kingdom_data(id, "open", "set", "land", port[cod]);
			kingdom_data(id, "open", "set", "port", base_name(environment(me))+".c");
			kingdom_data(id, "open", "set", "room", KINGDOM_DIR+id+"/ship/ship.c");	// 记录船只
			message_vision("$N找了一堆工人来在这里敲敲打打的，建造一座通商港口。\n", me);
			file = KINGDOM_DIR+id+"/ship/ship.c";
			if( file_size(file) == -1 ) cp( "/d/ship/ship.c", file );

			// 1. 处理船只
			if( !objectp(ob = find_object(file)) ) {
				call_other(file, "???");
				ob = find_object(file);
			}
			ob->set("port1", port[cod]);				// 系统港口
			ob->set("port2", base_name(environment(me))+".c");	// 国家港口
			ob->set("kingdom_id", id);
			do_save_ship(ob);
			destruct(ob);

			// 2. 处理系统港口
			if( !objectp(port_ob = find_object(port[cod])) ) {
				call_other(port[cod], "???");
				port_ob = find_object(port[cod]);
			}
			port_ob->add("objects/", ([file:1]) );
			do_saveroom(port_ob);

			// 3. 处理国家港口
			environment(me)->set("type", "port" );
			do_saveroom(environment(me));

			break;
		case "cancel":	// 注意看一下程式，似乎连国家的 ship 以及系统港口都没砍说，呵呵，偷一下懒，
				// 自己补吧~~ 不然用此功能后, 以后开机船只一样会跑, 因为系统港口没砍掉船的连结
			if( !check_kingdom(cod) ) return notify_fail("找不到这个国家 !");
			if( !kingdom_data(cod, "open", "check") ) return notify_fail("该国家没有连路 !");
			if( !kingdom_data(cod, "open", "del") ) return notify_fail("该国家没有连路资料 !");
			// 国家的港口资料, 最好写在系统某个资讯内, 以后方便 cancel (目前我是没砍国家的 port)
			// 比如说, 参考 /adm/daemons/chinesed.c 内的 add_kingdom_name()
			write("你取消了 "+ cod +" 的连路 !\n");
			break;
		default:
			return notify_fail("指令格式 : put_ship <here | cancel> <系统港口代号 | 国家>\n");
	}
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : put_ship <here | cancel> <系统港口代号 | 国家>

put_ship	here	港口代号	在该处与某港口代号建立连结的商船[请记得站在某国家港口内下指令]
put_ship	cancel	国家		取消该国家的连路资格

目前提供如下:
	系统港口代号		实际对应的港口路径
	-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	port1			"/d/gourd/ship_port.c"

HELP
	);
	return 1;
}
