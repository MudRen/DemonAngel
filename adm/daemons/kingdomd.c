//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/kingdomd.c
// by bor @RG, DA

/*
	д���ҵķ����У���Щ������ .C �ķ�ʽ��������Ѷ����������..
	..��д�뵽��ν�������ڣ������˷��Ѿ��е��ʱ��
	Ŀǰ����������Ľṹ���磺���⡢�����Դ�� .O ����̬..��
	�� .O ����̬�ַּ���д����ʽ...��Ȼ������ֻ�г���������һ��
	˵����
		1. һ������׫д�� kingdomd.c ��̬���˷�������һ��һ
		   �����庯���������Ƚ��鷳��û������������Ե�Ҳ��
		   ���á�
		2. ��һ��Ϊ�� set, add, ... �ȷ���ֱ��д����ҵ�����
		   �˷�������...Ҳ�������Ƚ�������ȫ���������������
		   ��λ���о���

	����˵�����ַ�������Կ���һ���Ƿ�Ҫ��������Ѷ���һ�� .O ��
	���߽� ally, people ... ����Ѷ�������������ڲ������ģ�Ŀǰ��
	��һ��...�ȸ�λ��ʵ��ʵ�������űȽ��ио���

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
// id	: ����
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
	kingdom = ([]);		// ������Ѷ
	people = ([]);		// ��������
	develop = ([]);		// ��չ
	research = ([]);	// �з�
	return ;
}

void create() { seteuid(getuid()); }

int creat_kingdom_data(string id, string name, object king)
{
// һ��ʼ�����Ż���д˺���
	restore_data(id);
// ������Ѷ
	kingdom = ([
	"open":(["door":0,"land":0,"room":0,"port":0]),	// land: ϵͳ�ۿ�, room: ��ֻ����, port: ���Ҹۿ�, door: ��ʽ��·

	// initial : ������ԭʼ�Ŀ�����Ѷ(����, ������)
	"initial":(["king":king->name_id(1),"birthday":time(),"id":king->query("id")]),

	// throne_time ��¼һ��ʼ�����ǻ���ʱ��
	"throne_time":time(),

	// ra_door ��ʽ���� RA, ra ��¼˭������
	"ra_door":0,"ra":([]),"arrest":([]),

	// ͬ�ˡ����ӡ�������ְҵ
	"ally":([]),"declare":(["hate":([]),"hated":([]),]),"class":([]),

	"tmp":([]),	// �ݴ��, ��δ��Ԥ���õ�	by bor @DA, 3/5 2003
	"war":([]),	// ��¼ս���õ�, ����: war:(["test":([
			//				"time"	: xxx,		�����õ�(���� 1 Сʱ)
			//				"gold"	: xxx,		�Ӷ�
			//				"enemy"	: xxx,		ɱ����
			//				"npc"	: xxx,		ɱ������
			//				"room"	: xxx,		�ƻ�һ�㷿����
			//				"building" : xxx,		�ƻ�һ�㷿����
			//			])])

	// special_room : ���⽨����ļ�¼,
	"special_room":([]),

	// Ȩ��������,
	//	king		: ��������Ѷ
	//	minister	: ��
	"power":([
		"king":([king->query("id"):time(),]),
		"minister":([]),
	]),

	"story":0, "time_gate":0,
	// ������Ҫ��Ѷ(��ֵ��)
	"tax":5,"people":1,"gold":500000,
	"room_num":0,"room":1,"max_room":150,
	"npc_num":0,"npc":0,"max_npc":150,
	"weapon_num":0,"weapon":0,"max_weapon":100,
	"armory_num":0,"armory":0,"max_armory":100,
	"item_num":0,"item":0,"max_item":50,
	]); // end kingdom mapping

// ������Ѷ
	people = ([
		// ��¼������ʱ��
		king->query("id"):ctime(time()+1),
	]);

// ��չ��Ѷ
	develop = ([
	// ��ʱ�� magic_tower, gate �ų���ɣ���Ҫ���ú���(develop_data)����
	// dev: ��չ��������ֵ, gold ʣ��Ͷ�ʽ��, tmp Ŀǰ��ʱ�ۻ��ķ�չ��ֵ
	//							by bor@DA, 2003 2/22
//		"magic_tower"	: (["dev":0,"gold":0,"tmp":0]),	// �������� mage npc ����ߵȼ�
//		"gate"		: (["dev":0,"gold":0,"tmp":0]),	// ���عؿ���ʿ����ߵȼ�
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
		case "open":	// ��½��Ѷ
			switch(prop) {
				case "set": // ��½ʱ���ǵ�Ҫ�����Σ����ܼ�¼ land, room, port ���������е��õ�����
				case "add":
					if(!kingdom[type]) kingdom[type] = ([]);
					kingdom[type][set] = data;
					save_data(id);
					return 1;
					break;
				case "sub":
				case "del": // �γ���½
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
				case "check": // ��鿴���Ƿ���½����
					if(!kingdom[type]) return 0;
					if(!kingdom[type]["door"]) return 0;
					return 1;
					break;
				default:
					return 0;
			}
			break;
		case "initial":	// ������Ѷ
			break;
		case "arrest":	// ͨ��
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
				case "del":	// ��� arrest
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
				case "check": // ��鿴�� set �Ƿ�ͨ��
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
		case "ally":	// ͬ��		by amgbell
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
		case "declare":	// ���ӡ�������
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
			// ��¼ս���õ�, ����: war:(["test":([
			//				"time"	: xxx,		�����õ�(���� 1 Сʱ)
			//				"gold"	: xxx,		�Ӷ�
			//				"enemy"	: xxx,		ɱ����
			//				"npc"	: xxx,		ɱ������
			//				"room"	: xxx,		�ƻ�һ�㷿����
			//				"building" : xxx,	�ƻ�һ�㷿����
			//			])])
			// set : "test" ��ָ����id,
			// data: ({��Ŀ,�趨})	�� ({"gold",1000})
			switch(prop) {
				case "set":
					if(!kingdom["war"]) kingdom["war"] = ([]);
					if(!kingdom["war"][set]) kingdom["war"][set] = ([]);
					if(undefinedp(data)) {	// ��ʾ����ս, ��δ���κε�ս���Ӷ�...
						kingdom["war"][set]["time"] = 3600;	// ��ʾͣսʱ��
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
					// data: "time", "gold", "enemy", .... ��
					if(!kingdom["war"]) return 0;
					if(!kingdom["war"][set]) return 0;
					if(!kingdom["war"][set][data]) return 0;
					return kingdom["war"][set][data];
					break;
				case "check":	// ����Ƿ� war �Ƿ������� , time �Ƿ���
						// ֻ�� "check", ��ʾ����Ƿ� war ��,
						// data = 1, ��ʾ����Ƿ���ĳ���� war ��,
						// data = 2, ��ʾ��� time �Ƿ���
					if(!kingdom["war"]) return 0;
					if(undefinedp(set)) {	// ��ָ����Ƿ��� war ������
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
		case "class":	// ����ְҵ
			break;
		case "special_room":	// ���⽨����
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
		case "power":	// Ȩ��
			// set : king, minister
			switch(prop) {
				case "set":	// �趨һ������
					if(!kingdom[type]) kingdom[type] = ([]);
					if(!kingdom[type][set]) kingdom[type][set] = ([]);
					kingdom[type][set][data] = ctime(time());
					save_data(id);
					return 1;
					break;
				case "add":	// ����һ������, data : player id
					if(!kingdom[type]) kingdom[type] = ([]);
					if(!kingdom[type][set]) kingdom[type][set] = ([]);
					if( !kingdom[type][set][data] ) {
						kingdom[type][set][data] = ctime(time());
						save_data(id);
						return 1;
					}
					break;
				case "sub":	// �Ƴ�һ������
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if( !kingdom[type][set][data] ) return 0;
					map_delete( kingdom[type][set], data );
					save_data(id);
					return 1;
					break;
				case "del":	// ��չ���
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
				case "check":	// ����Ƿ�Ϊ����
					if(!kingdom[type]) return 0;
					if(!kingdom[type][set]) return 0;
					if(!kingdom[type][set][data]) return 0;
					return 1;
					break;
				default:
					return 0;
			}
			break;
		case "data":	// ��ֵ��
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
		case "other":	// �ִ���
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
		case "add": // join ���
			if(people[tar]) return 0;
			people[tar] = ctime(time())[0..19];
			kingdom["people"] += 1;
			save_data(id);
			return 1;
		break;
		case "sub": // ������ѹ�
			if(!people[tar]) return 0;
			map_delete(people, tar);
			kingdom["people"] -= 1;
			save_data(id);
			return 1;
		break;
		case "del":	// ���
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
		case "query_par": // ��Ӧ����һ�����յ�
			if(!people) return 0;
			if(!people[tar]) return 0;
			return people[tar];
		break;
		case "check": // ��������Ƿ�Ϊ��������
			if(!people) return 0;
			if(!people[tar]) return 0;
			return 1;
		break;
	}
	return 0;
}

varargs mixed develop_data(string id, string prop, string dp_tar, string tar, int data)
//Ҳ����д�� : varargs mixed develop_data(string id, string prop, string *dp_tar, int data)
// dp_tar �ĳ� array �ķ�ʽ... ���� dp_tar �Ľṹ���ܿ������� ({"gate","tmp",5}) �����ķ�ʽ
// ��������������Ľṹ����ô��ʽ��͵ø�һ�������� if(!develop[dp_tar[0]]) develop[tar_par[0]] = ([])
//	by bor @DA, 2/22 2003
{
// tar ��ָ gate, magic_tower, ... �ȷ�չ
	restore_data(id);
	switch(prop) {
		case "set":	// ֱ���趨�÷�չ����ֵ
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
			} else {	// ������ʹ�ô˲���
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
			} else { // ��ĳ����ֵ
				if(!develop[dp_tar][tar]) return 0;
				return develop[dp_tar][tar];
			}
			break;
		case "check":	// �뵽Ҫ��ɶ�ڲ�
			break;
	}
	return 0;
}
