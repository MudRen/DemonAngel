//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/daemons/kingdomd.c
// by bor @RG, DA

/*
	写国家的方法中，有些人是以 .C 的方式将国家资讯、人民资料..
	..等写入到所谓的王座内，不过此法已经有点过时。
	目前尚有许许多多的结构，如：虚拟、或者以存成 .O 的型态..等
	以 .O 的型态又分几类写作方式...当然拉，我只列出两个来做一下
	说明：
		1. 一种如下撰写的 kingdomd.c 型态，此法，必须一个一
		   个定义函数出来，比较麻烦。没定义完整，相对的也不
		   能用。
		2. 另一种为以 set, add, ... 等方法直接写入国家档案内
		   此法，简易...也不用事先将函数完全定义出来。这留待
		   各位的研究。

	至于说处理手法，你可以考量一下是否要将所有资讯存成一个 .O 内
	或者将 ally, people ... 等资讯独立出来，至于差异在哪，目前保
	留一下...等各位有实际实作过，才比较有感觉。

				by bor @DA, 2002
				modify by bor @DA, 2003 2/22
*/

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_DBASE;

mapping	kingdom=([]), people=([]), develop=([]), research=([]);

void clear_data();

varargs int save_data(string id)
{
// id	: 国家
	save_object(kingdom_data_path(id));
	return 1;
}

varargs int restore_data(string id)
{
	if( file_size(kingdom_data_path(id)+".o") == -1 ) return 0;
	clear_data();
	restore_object(kingdom_data_path(id));
	return 1;
}

void clear_data()
{
	kingdom = ([]);		// 国家资讯
	people = ([]);		// 人民资料
	develop = ([]);		// 发展
	research = ([]);	// 研发
	return ;
}

void create() { seteuid(getuid()); }

int creat_kingdom_data(string id, string name, object king)
{
// 一开始建国才会呼叫此函数
	restore_data(id);
// 国家资讯
	kingdom = ([
	"open":(["door":0,"land":0,"room":0,"port":0]),	// land: 系统港口, room: 船只档案, port: 国家港口, door: 正式连路

	// initial : 国家最原始的开国资讯(国王, 开国日)
	"initial":(["king":king->name_id(1),"birthday":time(),"id":king->query("id")]),

	// throne_time 记录一开始国王登基的时间
	"throne_time":time(),

	// ra_door 正式启动 RA, ra 记录谁启动的
	"ra_door":0,"ra":([]),"arrest":([]),

	// 同盟、敌视、开发的职业
	"ally":([]),"declare":(["hate":([]),"hated":([]),]),"class":([]),

	"tmp":([]),	// 暂存的, 给未来预留用的	by bor @DA, 3/5 2003
	"war":([]),	// 记录战争用的, 例如: war:(["test":([
			//				"time"	: xxx,		倒数用的(最多打 1 小时)
			//				"gold"	: xxx,		掠夺
			//				"enemy"	: xxx,		杀敌数
			//				"npc"	: xxx,		杀守卫数
			//				"room"	: xxx,		破坏一般房屋数
			//				"building" : xxx,		破坏一般房屋数
			//			])])

	// special_room : 特殊建筑物的记录,
	"special_room":([]),

	// 权力的象征,
	//	king		: 国王的资讯
	//	minister	: 大臣
	"power":([
		"king":([king->query("id"):time(),]),
		"minister":([]),
	]),

	"story":0, "time_gate":0,
	// 其他重要资讯(数值类)
	"tax":5,"people":1,"gold":500000,
	"room_num":0,"room":1,"max_room":150,
	"npc_num":0,"npc":0,"max_npc":150,
	"weapon_num":0,"weapon":0,"max_weapon":100,
	"armory_num":0,"armory":0,"max_armory":100,
	"item_num":0,"item":0,"max_item":50,
	]); // end kingdom mapping

// 人民资讯
	people = ([
		// 记录玩家入国时间
		king->query("id"):ctime(time()+1),
	]);

// 发展资讯
	develop = ([
	// 暂时以 magic_tower, gate 撑场面吧，需要再用函数(develop_data)来补
	// dev: 发展的真正数值, gold 剩余投资金额, tmp 目前暂时累积的发展数值
	//							by bor@DA, 2003 2/22
//		"magic_tower"	: (["dev":0,"gold":0,"tmp":0]),	// 可以招来 mage npc 的最高等级
//		"gate"		: (["dev":0,"gold":0,"tmp":0]),	// 看守关卡的士兵最高等级
	]);

	save_data(id);
	CHINESE_D->add_kingdom_name(id, name);
	return 1;
}

varargs mixed kingdom_data(string id, string type, string prop, string set, mixed data)
{
// type: open, initial, arrest, ra, ally, declare, class, special_room, power, data, other
// prop: set, add, sub, del, query, query_all, query_par, check
	restore_data(id);
	switch(type) {
		case "open":	// 连陆资讯
			switch(prop) {
				case "set": // 连陆时，记得要用三次，才能记录 land, room, port 这三个，有点烂的作法
				case "add":
					if(!kingdom[type]) kingdom[type] = ([]);
					kingdom[type][set] = data;
					save_data(id);
					return 1;
					break;
				case "sub":
				case "del": // 拔除连陆
					if(!kingdom[type]) return 0;
					kingdom[type]["land"] = 0;
					kingdom[type]["room"] = 0;
					kingdom[type]["port"] = 0;
					kingdom[type]["door"] = 0;
					save_data(id);
					return 1;
					break;
				case "query":
					if(!kingdom[type]) return 0;
					return kingdom[type];
					break;
				case "query_all":
					break;
				case "query_par":
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					return kingdom[type][set];
					break;
				case "check": // 检查看看是否连陆国家
					if(!kingdom[type]) return 0;
					if(!kingdom[type]["door"]) return 0;
					return 1;
					break;
				default:
					return 0;
			}
			break;
		case "initial":	// 开国资讯
			break;
		case "arrest":	// 通缉
			switch(prop) {
				case "set":
					if(!kingdom[type]) kingdom[type] = ([]);
					kingdom[type][set] = ctime(time())[0..19];
					save_data(id);
					return 1;
					break;
				case "add":
					if(!kingdom[type]) kingdom[type] = ([]);
					if(!kingdom[type][set]) {
						kingdom[type][set] = ctime(time())[0..19];
						save_data(id);
						return 1;
					}
					break;
				case "sub":
					if(!kingdom[type]) return 0;
					if(kingdom[type][set]) {
						map_delete(kingdom[type], set);
						save_data(id);
						return 1;
					}
					break;
				case "del":	// 清空 arrest
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					kingdom[type] = ([]);
					save_data(id);
					return 1;
					break;
				case "query":
					if(!kingdom[type]) return 0;
					if(zerop(kingdom[type])) return 0;
					return kingdom[type];
					break;
				case "query_all":
					if(!kingdom[type]) return 0;
					if(zerop(keys(kingdom[type]))) return 0;
					else return keys(kingdom[type]);
					break;
				case "query_par":
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					return kingdom[type][set];
					break;
				case "check": // 检查看看 set 是否被通缉
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					return 1;
					break;
				default:
					return 0;
			}
			break;
		case "ra":	// RA
			break;
		case "ally":	// 同盟		by amgbell
			switch(prop) {
                                case "set":
                                        break;
                                case "add":
                                        kingdom[type][set] =ctime(time())[0..19];;
                                        save_data(id);
                                        return 1;
                                        break;
                                case "sub":
                                        if(!kingdom[type][set]) return 0;
                                        if(kingdom[type][set]) {
                                                map_delete(kingdom[type], set);
                                                save_data(id);
                                                return 1;
                                                }
                                        break;
                                case "del":
                                        break;
                                case "query":
                                        break;
                                case "query_all":
                                        if(!kingdom[type]) return 0;
                                        if(kingdom[type]==0) return 0;
                                        return keys(kingdom[type]);
                                        break;
                                case "query_par":
                                        if(!kingdom[type][set]) return 0;
                                        if(kingdom[type][set]==0) return 0;
                                        return kingdom[set];
                                        break;
                                case "check":
                                        if(kingdom[type][set]==0) return 0;
                                        if(!kingdom[type][set]) return 0;
                                        return 1;
                                        break;
                                default:
                                        return 0;
                        } 
			break;
		case "declare":	// 敌视、被敌视
			switch(prop) {
                                case "set":
                                        break;
                                case "add":
                                	if(!kingdom[type][set]) kingdom[type][set] = ([]);
                                        kingdom[type][set][data] =ctime(time())[0..19];
                                        save_data(id);
                                        return 1;
                                        break;
                                case "sub":
                                        if(!kingdom[type][set]) return 0;
                                        if(kingdom[type][set][data]) {
                                                map_delete(kingdom[type][set], data);
                                                save_data(id);
                                                return 1;
					}
                                        break;
                                case "del":
                                        break;
                                case "query":
                                        break;
                                case "query_all":
                                        if(!kingdom[type]) return 0;
                                        if(kingdom[type]==0) return 0;
					if(undefinedp(set)) {
						if( zerop(keys(kingdom[type])) ) return 0;
						return keys(kingdom[type]);
					} else {
						if( !kingdom[type][set] ) return 0;
						if( zerop(keys(kingdom[type][set])) ) return 0;
						return keys(kingdom[type][set]);
					}
                                        break;
                                case "query_par":
                                        if(!kingdom[type][set]) return 0;
                                        if(kingdom[type][set]==0) return 0;
                                        return kingdom[set];
                                        break;
                                case "check":
                                        if(kingdom[type][set]==0) return 0;
                                        if(!kingdom[type][set]) return 0;
					if(undefinedp(data)) {
	                                        return 1;
					} else {
						if(!kingdom[type][set][data]) return 0;
						return 1;
					}
                                        break;
                                default:
                                        return 0;
                        } 
			break;
		case "war":
			// 记录战争用的, 例如: war:(["test":([
			//				"time"	: xxx,		倒数用的(最多打 1 小时)
			//				"gold"	: xxx,		掠夺
			//				"enemy"	: xxx,		杀敌数
			//				"npc"	: xxx,		杀守卫数
			//				"room"	: xxx,		破坏一般房屋数
			//				"building" : xxx,	破坏一般房屋数
			//			])])
			// set : "test" 泛指国家id,
			// data: ({项目,设定})	如 ({"gold",1000})
			switch(prop) {
				case "set":
					if(!kingdom["war"]) kingdom["war"] = ([]);
					if(!kingdom["war"][set]) kingdom["war"][set] = ([]);
					if(undefinedp(data)) {	// 表示刚宣战, 尚未有任何的战功掠夺...
						kingdom["war"][set]["time"] = 3600;	// 标示停战时间
					} else {
						kingdom["war"][set][data[0]] = data[1];
					}
                                        save_data(id);
       	                                return 1;
					break;
				case "add":
					if(!kingdom["war"]) return 0;
					if(!kingdom["war"][set]) return 0;
					if( sizeof(data)!=2 ) return 0;
					if(!kingdom["war"][set][data[0]]) kingdom["war"][set][data[0]] = 0;
					kingdom["war"][set][data[0]] += data[1];
                                        save_data(id);
       	                                return 1;
					break;
				case "sub":
					if(!kingdom["war"]) return 0;
					if(!kingdom["war"][set]) return 0;
					if( sizeof(data)!=2 ) return 0;
					if(!kingdom["war"][set][data[0]]) return 0;
					kingdom["war"][set][data[0]] -= data[1];
                                        save_data(id);
       	                                return 1;
					break;
				case "del":
					if(!kingdom["war"]) return 0;
					if(undefinedp(set)) {
						kingdom["war"] = ([]);
					} else {
						if(!kingdom["war"][set]) return 0;
						map_delete(kingdom["war"], set);
					}
                                        save_data(id);
					return 1;
					break;
				case "query":
					if(!kingdom["war"]) return 0;
					if(undefinedp(set)) {
						if(zerop(keys(kingdom["war"]))) return 0;
						return kingdom["war"];
					} else {
						if(!kingdom["war"][set]) return 0;
						if(zerop(keys(kingdom["war"][set]))) return 0;
						return kingdom["war"][set];
					}
					break;
				case "query_all":
					if(!kingdom["war"]) return 0;
					if(undefinedp(set)) {
						if(zerop(keys(kingdom["war"]))) return 0;
						return keys(kingdom["war"]);
					} else {
						if(!kingdom["war"][set]) return 0;
						if(zerop(keys(kingdom["war"][set]))) return 0;
						return keys(kingdom["war"][set]);
					}
					break;
				case "query_par":
					// data: "time", "gold", "enemy", .... 等
					if(!kingdom["war"]) return 0;
					if(!kingdom["war"][set]) return 0;
					if(!kingdom["war"][set][data]) return 0;
					return kingdom["war"][set][data];
					break;
				case "check":	// 检查是否 war 是否启动了 , time 是否到了
						// 只有 "check", 表示检查是否 war 中,
						// data = 1, 表示检查是否与某国家 war 中,
						// data = 2, 表示检查 time 是否到了
					if(!kingdom["war"]) return 0;
					if(undefinedp(set)) {	// 表指检查是否有 war 进行中
						if(zerop(keys(kingdom["war"]))) return 0;
						return 1;
					}
					if( data == 1 ) {
						if(!kingdom["war"][set]) return 0;
						return 1;
					} else {
						if(!kingdom["war"][set]) return 0;
						if(!kingdom["war"][set]["time"]<=0) return 0;
						return 1;
					}
					break;
			}
			break;
		case "tmp":
			switch(prop) {
				case "set":
					break;
				case "add":
					break;
				case "sub":
					break;
				case "del":
					break;
				case "query":
					break;
				case "query_all":
					break;
				case "query_par":
					break;
				case "check":
					break;
			}
			break;
		case "class":	// 开发职业
			break;
		case "special_room":	// 特殊建筑物
			switch(prop) {
				// set : "bank", "board", "post_office", "shop"
				case "set":
					break;
				case "add":
					if(!kingdom[type]) kingdom[type] = ([]);
					if(!kingdom[type][set]) kingdom[type][set] = ([]);
					if(!kingdom[type][set][data])
						kingdom[type][set][data] = 1;
					else kingdom[type][set][data] += 1;
					kingdom["room"] += 1;
					save_data(id);
					return 1;
					break;
				case "sub":
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if(!kingdom[type][set][data]) return 0;
					map_delete( kingdom[type][set], data );
					if( zerop(kingdom[type][set]) )
						map_delete( kingdom[type], set );
					kingdom["room"] -= 1;
					kingdom["room_num"] += 1;
					save_data(id);
					return 1;
					break;
				case "del":
					break;
				case "query":
					if(!kingdom[type]) return 0;
					if(undefinedp(set)) {
						if( zerop(kingdom[type]) ) return 0;
						return kingdom[type];
					} else {
						if( !kingdom[type][set] ) return 0;
						if( zerop(kingdom[type][set]) ) return 0;
						return kingdom[type][set];
					}
					break;
				case "query_all":
					if(!kingdom[type]) return 0;
					if(undefinedp(set)) {
						if( zerop(kingdom[type]) ) return 0;
						return keys(kingdom[type]);
					} else {
						if( !kingdom[type][set] ) return 0;
						if( zerop(kingdom[type][set]) ) return 0;
						return keys(kingdom[type][set]);
					}
					break;
				case "query_par":
					break;
				case "check":
					if(!kingdom[type]) return 0;
					if(undefinedp(data)) {
						if(!kingdom[type][set]) return 0;
					} else {
						if(!kingdom[type][set]) return 0;
						if(!kingdom[type][set][data]) return 0;
					}
					return 1;
					break;
				default:
					return 0;
			}
			break;
		case "power":	// 权力
			// set : king, minister
			switch(prop) {
				case "set":	// 设定一名贵族
					if(!kingdom[type]) kingdom[type] = ([]);
					if(!kingdom[type][set]) kingdom[type][set] = ([]);
					kingdom[type][set][data] = ctime(time());
					save_data(id);
					return 1;
					break;
				case "add":	// 增加一名贵族, data : player id
					if(!kingdom[type]) kingdom[type] = ([]);
					if(!kingdom[type][set]) kingdom[type][set] = ([]);
					if( !kingdom[type][set][data] ) {
						kingdom[type][set][data] = ctime(time());
						save_data(id);
						return 1;
					}
					break;
				case "sub":	// 移除一名贵族
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if( !kingdom[type][set][data] ) return 0;
					map_delete( kingdom[type][set], data );
					save_data(id);
					return 1;
					break;
				case "del":	// 清空贵族
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					map_delete( kingdom[type], set );
					save_data(id);
					return 1;
					break;
				case "query":
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if(zerop(kingdom[type][set]) ) return 0;
					return kingdom[type][set];
					break;
				case "query_all":
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if(zerop(kingdom[type][set]) ) return 0;
					return keys(kingdom[type][set]);
					break;
				case "query_par":
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if(!kingdom[type][set][data]) return 0;
					return kingdom[type][set][data];
					break;
				case "check":	// 检查是否为贵族
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if(!kingdom[type][set][data]) return 0;
					return 1;
					break;
				default:
					return 0;
			}
			break;
		case "data":	// 数值类
			switch(prop) {
				case "set":
//					if(!kingdom[set]) return 0;
					kingdom[set] = data;
					save_data(id);
					return 1;
					break;
				case "add":
//					if(!kingdom[set]) return 0;
					kingdom[set] += data;
					save_data(id);
					return 1;
					break;
				case "sub":
//					if(!kingdom[set]) return 0;
					kingdom[set] -= data;
					save_data(id);
					return 1;
					break;
				case "del":
					break;
				case "query":
					break;
				case "query_all":
					break;
				case "query_par":
					if(!kingdom[set]) return 0;
					if(kingdom[set]==0) return 0;
					return kingdom[set];
					break;
				case "check":
					break;
				default:
					return 0;
			}
			break;
		case "other":	// 字串类
			switch(prop) {
				case "set":
					kingdom[set] = data;
					save_data(id);
					return 1;
					break;
				case "add":
					break;
				case "sub":
					break;
				case "del":
					if(!kingdom[set]) return 0;
					if(!stringp(kingdom[set])) return 0;
					map_delete(kingdom, set);
					save_data(id);
					return 1;
					break;
				case "query":
					break;
				case "query_all":
					break;
				case "query_par":
					if(!kingdom[set]) return 0;
					if(kingdom[set]==0) return 0;
					return kingdom[set];
					break;
				case "check":
					if(!kingdom[set]) return 0;
					if(kingdom[set]==0) return 0;
					return 1;
					break;
				default:
					return 0;
			}
			break;
		default:
			return 0;
	}	// end type switch
	return 0;
}

varargs mixed people_data(string id, string prop, string tar)
{
	restore_data(id);
	switch(prop) {
		case "set":
		break;
		case "add": // join 入国
			if(people[tar]) return 0;
			people[tar] = ctime(time())[0..19];
			kingdom["people"] += 1;
			save_data(id);
			return 1;
		break;
		case "sub": // 离国、叛国
			if(!people[tar]) return 0;
			map_delete(people, tar);
			kingdom["people"] -= 1;
			save_data(id);
			return 1;
		break;
		case "del":	// 清空
		break;
		case "query":
			if(!people) return 0;
			if(zerop(people)) return 0;
			return people;
		break;
		case "query_all":
			if(!people) return 0;
			if(zerop(people)) return 0;
			return keys(people);
		break;
		case "query_par": // 回应是哪一个大臣收的
			if(!people) return 0;
			if(!people[tar]) return 0;
			return people[tar];
		break;
		case "check": // 检查该玩家是否为本国的人
			if(!people) return 0;
			if(!people[tar]) return 0;
			return 1;
		break;
	}
	return 0;
}

varargs mixed develop_data(string id, string prop, string dp_tar, string tar, int data)
//也可以写成 : varargs mixed develop_data(string id, string prop, string *dp_tar, int data)
// dp_tar 改成 array 的方式... 这样 dp_tar 的结构可能看起来是 ({"gate","tmp",5}) 这样的方式
// 不过如果是那样的结构，那么程式你就得改一下啰，比如 if(!develop[dp_tar[0]]) develop[tar_par[0]] = ([])
//	by bor @DA, 2/22 2003
{
// tar 泛指 gate, magic_tower, ... 等发展
	restore_data(id);
	switch(prop) {
		case "set":	// 直接设定该发展的数值
			if(!develop) develop = ([]);
			if(!develop[dp_tar]) {
				develop[dp_tar] = ([]);
				develop[dp_tar]["dev"] = 0;
				develop[dp_tar]["gold"] = 0;
				develop[dp_tar]["tmp"] = 0;
			}
			if(!develop[dp_tar][tar]) develop[dp_tar][tar] = 0;
			develop[dp_tar][tar] = data;
			save_data(id);
			return 1;
			break;
		case "add":
			if(!develop) develop = ([]);
			if(!develop[dp_tar]) {
				develop[dp_tar] = ([]);
				develop[dp_tar]["dev"] = 0;
				develop[dp_tar]["gold"] = 0;
				develop[dp_tar]["tmp"] = 0;
			}
			if(!develop[dp_tar][tar]) develop[dp_tar][tar] = 0;
			develop[dp_tar][tar] += data;
			save_data(id);
			return 1;
			break;
		case "sub":
			if(!develop) develop = ([]);
			if(!develop[dp_tar]) {
				develop[dp_tar] = ([]);
				develop[dp_tar]["dev"] = 0;
				develop[dp_tar]["gold"] = 0;
				develop[dp_tar]["tmp"] = 0;
			}
			if(!develop[dp_tar][tar]) develop[dp_tar][tar] = 0;
			develop[dp_tar][tar] -= data;
			if(develop[dp_tar][tar]<0) develop[dp_tar][tar] = 0;
			save_data(id);
			return 1;
			break;
		case "del":
			if(!develop) return 0;
			if(!develop[dp_tar]) return 0;
			if(undefinedp(tar)) {
				map_delete(develop,dp_tar);
				save_data(id);
				return 1;
			} else {	// 不建议使用此部份
				if(!develop[dp_tar][tar]) return 0;
				map_delete(develop[dp_tar], tar);
				save_data(id);
				return 1;
			}
			break;
		case "query":
			if(!develop) return 0;
			if(zerop(develop)) return 0;
			return develop;
			break;
		case "query_all":
			if(!develop) return 0;
			if(undefinedp(dp_tar)) {
				if(zerop(develop)) return 0;
				return keys(develop);
			} else {
				if(!develop[dp_tar]) return 0;
				if(zerop(develop[dp_tar])) return 0;
				return keys(develop[dp_tar]);
			}
			break;
		case "query_par":
			if(!develop) return 0;
			if(!develop[dp_tar]) return 0;
			if(undefinedp(tar)) {
				if(zerop(develop)) return 0;
				return keys(develop);
			} else { // 查某个数值
				if(!develop[dp_tar][tar]) return 0;
				return develop[dp_tar][tar];
			}
			break;
		case "check":	// 想到要用啥在补
			break;
	}
	return 0;
}
