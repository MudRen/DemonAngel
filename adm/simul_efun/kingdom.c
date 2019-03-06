//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// room : /adm/simul_efun/kingdom
// by bor @RG,
/*
	���и������й����ĺ���

*/

#pragma optimize
#pragma save_binary

int create_kingdom(object king, string id, string name)	// ������ʽ
{
	string file, str;

	mkdir(KINGDOM_DIR+id+"/npc");
	mkdir(KINGDOM_DIR+id+"/armory");
	mkdir(KINGDOM_DIR+id+"/item");
	mkdir(KINGDOM_DIR+id+"/weapon");
	mkdir(KINGDOM_DIR+id+"/detail");
	mkdir(KINGDOM_DIR+id+"/data");
	mkdir(KINGDOM_DIR+id+"/ship");

	file = KINGDOM_DIR+id+"/kingdom.c";

	str = "// room : " + file + "\n";

	str += @ROOM_CODE
#include <ansi.h>
inherit ROOM;

void create()
{
	set("long", @TEXT
�����ǹ�������Ҫ�ĵط���Ҳ�ǹ��ҵľ���������ƽʱ�������
����̸�۹�����Ҫ���ߵ���ѳ����������Ĵ�������ϵ�Ź����ܲ�
�ܴ��ڣ���ν���ڹ��ڣ�����������ϣ�������ܺúñ������
TEXT);
	set("type", "normal");		//�趨��������
	set("no_delete", 1);		//�ø����ƻ�

ROOM_CODE
	;
// �����Ĺ����趨
	str += sprintf("\tset(\"short\", %O);\n",  name+"����");
	str += sprintf("\tset(\"kingdom_id\", %O);\n", id );

	// refresh_data ��ʽ��({ ������, ����ʱ��, ��������, ������ʱ�� })
	str += sprintf("\tset(\"refresh_data\", %O);\n", ({ king->query("id"), ctime(time()), king->query("id"), ctime(time()) }) );

	str += "\tsetup();\n\treplace_program(ROOM);\n}\n";

	write_file(file, str, 1);

	king->set("kingdom/id", id);				// ����Ӣ��
	king->set("kingdom/king", king->query("id"));		// ����Ԫ��
	king->add_path( ({ "/cmds/min/", "/cmds/king/" }) );
	king->set("cwd", KINGDOM_DIR+id+"/");
	king->set("home", file);
	king->save();

	king->move(file);
	return 1;
}

int check_kingdom(string id)	// �������Ƿ���ڣ����ھͻ�Ӧ 1
{
	if( file_size(KINGDOM_DIR+ id +"/") != -2 ) return 0;
	return 1;
}

int do_saveroom(object env)
{
	string file, str, *name, *list=({});
	mapping dbase;
	int i;
string *no_save = ({
	"short", "long", "type", "refresh_data", "valid_startroom", "no_clean_up", "item_desc"
});

	if(!env) return 0;
	if( env->query("no_save") ) return 0;
	file = base_name(env)+".c";
	dbase = env->query_entire_dbase();

	str = "// room : " + file + "\n";
	str += "// saveroom by "+ this_player(1)->query("id")+" @DA, "+ctime(time())+"\n";

	str += "#include <ansi.h>\n";
	if( !dbase["type"] || dbase["type"] == "normal" ) str += "inherit ROOM;\n\n";
	else str += "inherit "+upper_case(dbase["type"])+";\n\n";

	str += "void create()\n{\n";

	str += sprintf("\tset(\"short\", %O);\n", dbase["short"] );

	if(strsrch(dbase["long"], "LONG")!=-1) {
		dbase["long"] = replace_string(dbase["long"], repeat_string(" ", 10), "");
		dbase["long"] = replace_string(dbase["long"], "LONG", "" );
	}
	str += sprintf("\tset(\"long\", @LONG\n%sLONG\n\t);\n", dbase["long"] );
	str += sprintf("\tset(\"type\", %O);\n", dbase["type"] );

	if( arrayp(list = dbase["refresh_data"]) ) {
		if(this_player(1)) {
			list[2] = this_player()->query("id");
			list[3] = ctime(time());
		}
	} else {
		if(this_player(1)) list = ({ this_player()->query("id"), ctime(time()), this_player()->query("id"), ctime(time()) });
	}

	// refresh_data ��ʽ��({ ������, ����ʱ��, ��������, ������ʱ�� })
	str += sprintf("\tset(\"refresh_data\", %O);\n", list );

	if( dbase["item_desc"] && sizeof(dbase["item_desc"]) ) {
		str += sprintf("\tset(\"item_desc\", ([\n");
		list = keys(dbase["item_desc"]);
		for(i=0; i<sizeof(dbase["item_desc"]); i++)
			str += sprintf("\"%s\" : @TEXT\n%sTEXT\n,  ", list[i], dbase["item_desc"][list[i]] );
		str += "\n]));\n";
	}

	name = keys(dbase);
	for(i=0; i<sizeof(name); i++) {
		if( member_array(name[i], no_save)!= -1 ) continue;
		if( stringp(dbase[name[i]]) )
			str += sprintf("\tset(\"%s\", %O);\n", name[i], kill_all_bug(dbase[name[i]]) );
		else 
			str += sprintf("\tset(\"%s\", %O);\n", name[i], dbase[name[i]] );
	}

	str += "\n\tsetup();\n";

	if( !dbase["type"] || dbase["type"] =="normal" ) {
		str += "\treplace_program(ROOM);\n";
		str += "}\n";
	} else {
		str += "\treplace_program("+upper_case(dbase["type"])+");\n";
		str += "}\n";
	}

	// Replace current directory with __DIR__ macro to make relocatable code.
	i = strlen(file)-1;
	while( (i > 0) && (file[i]!='/')) i--;
	if( i>0 ) {
//		write("ĿǰĿ¼��" + file[0..i] + " �� __DIR__ ȡ����\n");
		str = replace_string(str, "\"" + file[0..i], "__DIR__\"");
	}

	if( !write_file(file, str, 1) ) return 0;
	return 1;
}

int save_npc(object mob)
{
	mapping dbase;
	string mob_file, str, *list;
	object *all;

	if(!objectp(mob)) return 0;
	dbase = mob->query_entire_dbase();

	mob_file = full_name(mob);

	str = "// mob : " + mob_file+"\n";
	if( this_player()->query("id") ) str += "// save by " + this_player()->query("id") + "  on " + ctime(time())[0..15]+"\n";
	else str += "// save by system on " + ctime(time())[0..15]+"\n";

//#define TAVERN_NPC		"/std/char/tavern"
//#define MAGE_NPC		"/std/char/mage"
//#define MISC_SHOP_NPC		"/std/char/misc_shop"
//#define BARRACKS_NPC		"/std/char/barracks"

	if( !dbase["type"] || dbase["type"] =="npc" )
		str += "inherit NPC;\n";
	else
		str += "inherit " + upper_case(dbase["type"])+"_NPC;\n";
	str += "#include <ansi.h>\n\n";

	str += sprintf("void create()\n{\n");

	str += sprintf("\tset_name( %O, %O );\n", kill_all_bug(dbase["name"]), text_id(dbase["id"]) );
	str += sprintf("\tset(\"long\", @LONG_TEXT\n%sLONG_TEXT\n\t);\n", kill_all_bug(dbase["long"]) );
	str += sprintf("\tset(\"type\", %O);\n", dbase["type"] );
	str += sprintf("\tset(\"level\", %O);\n", dbase["level"] );
	str += sprintf("\tset(\"home\", %O);\n", dbase["home"] );

	if( arrayp(list = dbase["refresh_data"]) && sizeof(list)==4 ) {
		if(this_player(1)) {
			list[2] = this_player()->query("id");
			list[3] = ctime(time());
		}
	} else {
		if(this_player(1)) list = ({ this_player()->query("id"), ctime(time()), this_player()->query("id"), ctime(time()) });
	}

	// refresh_data ��ʽ��({ ������, ����ʱ��, ��������, ������ʱ�� })
	str += sprintf("\tset(\"refresh_data\", %O);\n", list );

	str += sprintf("\tset(\"kingdom\", %O);\n", dbase["kingdom"] );

	if(dbase["nickname"]) str += sprintf("\tset(\"nickname\", %O);\n", kill_all_bug(dbase["nickname"]) );

	str += sprintf("\tset(\"race\", %O);\n", dbase["race"] );
	str += sprintf("\tset(\"gender\", %O);\n", dbase["gender"] );
	str += sprintf("\tset(\"unit\", %O);\n", dbase["unit"] );
	if(dbase["aggressive"]) str += sprintf("\tset(\"aggressive\", %O);\n", dbase["aggressive"] );
	if(dbase["chasing"]) str += sprintf("\tset(\"chasing\", %O);\n", dbase["chasing"] );
	if(dbase["reward"]) str += sprintf("\tset(\"reward\", %O);\n", dbase["reward"] );
	if(dbase["polite"]) str += sprintf("\tset(\"polite\", %O);\n", dbase["polite"] );
	if(dbase["no_corpse"]) str += sprintf("\tset(\"no_corpse\", %O);\n", dbase["no_corpse"] );
	if(dbase["die_msg"]) str += sprintf("\tset(\"die_msg\", @TEXT\n%sTEXT\n\t);\n", kill_all_bug(dbase["die_msg"]) );

	all = all_inventory(mob);

	if(sizeof(all)) {
		list=({ });
		for(int i=0;i<sizeof(all);i++) {
			if(!objectp(all[i])) continue;
			if( file_size(full_name(all[i]))==-1) continue;
			if (all[i]->query("equipped")) {
				if(all[i]->query("weapon_prop")) {
					str += sprintf("\tcarry_object(%O)->wield();\n", full_name(all[i]) );
				}
				if(all[i]->query("armor_type")) {
					str += sprintf("\tcarry_object(%O)->wear();\n", full_name(all[i]) );
				}
				list += ({ full_name(all[i]) });
			}
			list -= ({0});
		}
	}

	if(sizeof(list)>0) str += sprintf("\tset(\"eq\", %O);\n", list );

	if( !dbase["type"] || dbase["type"] =="npc" )
		str += sprintf("\tsetup();\n}");
	else
		str += sprintf("\tsetup_npc();\n}");

	reset_eval_cost();
	write_file(mob_file, str, 1);
	return 1;
}

int do_saveitem(object ob)		// by amgbell
{
        int i,weapon=0,armor=0,quest=0,food=0;
        string file, str="", type, *list;
        mapping dbase;
        object *all;

	file = base_name(ob)+".c";
	dbase = ob->query_entire_dbase();

	str += "// item : " + file + "\n";
	if(this_player(1)) str += "// saveitem by "+ this_player(1)->query("id")+" @ "+ctime(time())+"\n\n";
	else str += "// saveitem by system @ "+ctime(time())+"\n\n";

	if(ob->query("weapon_prop")) weapon=1;  //wp
	if(ob->query("armor_type")) armor=1;  //eq
	if(ob->query("quest_item")) quest=1;
	if(ob->query("food")) food=1;

	if (weapon) str+="#include <weapon.h>\n";
	if (armor)  str+="#include <armor.h>\n";
	str+="#include <ansi.h>\n";

        type=ob->query("type");

        str += "inherit "+upper_case(type)+";\n\n";
        str += "void create() {\n";
//        str += "set_name(\""+ob->query("name")+"\", ({\""+text_item_id(ob->query("id"))+"\"}) );\n";
	str += sprintf("\tset_name( %O, %O );\n", dbase["name"], text_item_id(dbase["id"]) );

        str+="\tset_weight("+ob->query_weight()+");\n";
        if (ob->query("new")==1) str += "\tset(\""+"new"+"\""+","+1+");\n";

        str+="\tif( clonep() )\n";
        str+="\t\tset_default_object(__FILE__);\n";
        str+="\telse {\n";
        str+="\t\tset(\"long\", @LONG\n";
        str+=ob->query("long");
        str+="LONG );\n"; 

        str += "\t\tset(\""+"unit"+"\""+",\""+ob->query("unit")+"\");\n";
//        str += "\t\tset(\""+"value"+"\","+ob->query("value")+");\n";
        str += "\t\tset(\""+"type"+"\""+",\""+ob->query("type")+"\");\n";

	if( ob->query("add_attr") )
	str += sprintf("\t\tset(\"add_attr\", %O );\n", ob->query("add_attr") );

	if( armor ) {
		str += sprintf("\t\tset(\"armor_prop/ac\", %d);\n", ob->query("armor_prop/ac") );
		str += sprintf("\t\tset(\"armor_prop/db\", %d);\n", ob->query("armor_prop/ac") );
	} else {
		str += sprintf("\t\tset(\"weapon_prop/wl\", %d);\n", ob->query("weapon_prop/wl") );
		str += sprintf("\t\tset(\"weapon_prop/Mh\", %d);\n", ob->query("weapon_prop/Mh") );
	}

	if( ob->query("invoke_magic") )
		str += sprintf("\t\tset(\"invoke_magic\", %O);\n", ob->query("invoke_magic") );

        str += "\t\tset(\""+"level"+"\""+","+ob->query("level")+");\n";
        
	if( weapon ) str += "\t\tset(\""+"skill"+"\""+","+ob->query("level")*2+");\n";
                
        if (ob->query("no_copy")) str += "\t\tset(\""+"no_copy"+"\""+","+1+");\n";

        str += "\t\tset(\""+"owner"+"\""+",\""+ob->query("owner")+"\");\n";
        str += "\t\tset(\""+"kingdom"+"\""+",\""+ob->query("kingdom")+"\");\n";
        str+="\t}\n";

        if (weapon) str+="\tinit_"+ob->query("type")+"("+ob->query("level")/3+");\n";
        str+="\tsetup();\n";
        str+="}\n";

        if( !write_file(file, str, 1) ) return 0;
	destruct(find_object(file));
	call_other(file, "???");

        return 1;
}

int set_all_the_same_objects(object ob,string type,mixed value) {	// by amgbell
        string base_file;
        int i;
        object *obs;

        base_file=base_name(ob);
        obs=children(base_file);
        
        for (i=0;i<sizeof(obs) ;i++ )
        {
                obs[i]->set(type,value);
        }
        base_file->set(type,value);
//destruct(find_object(base_file));

        return 1;
}

//�������ɫ���ָ�û��ɫ���ֲ�
int diff_ansistr(string str) {		// by amgbell
	string str2,temp,temp2="",*arr;
	int i;

	arr=explode(str,"");
//if (sizeof(arr)==1 ) return 0;

	for (i=0;i<sizeof(arr) ;i++ ) {
	        sscanf(arr[i],"[%sm%*s",temp);
	        temp="["+temp+"m";
	        arr[i]=replace_string(arr[i],temp,"");
	        temp2+=arr[i];
	}
	return strlen(str)-strlen(temp2);
}

//sprintf() ����ansi��Ԫ���в�,�����������
//ex.Ҫ��һ������Ϊ10��string(��color)
//sprintf("%10s",correct_strin("xxxxx",10))
string correct_string(string str,int space) {		// by amgbell

	int i,diff;
	int curr_space;

	diff=diff_ansistr(str);
	if (diff==0) return str;

	curr_space=space-(strlen(str)-diff);

	for (i=0;i<curr_space;i++ ) {
	        str+=" ";//���ո�
	}
	return str;
}

//set_long���Զ�ģʽ
//��������е��ĸպ���ansi�Ĳ��ݾ�ʧ����
string auto_set_long(string str) {		// by amgbell

	int i,line,lines,pointer;
	string temp="",*arr,assemble="";

	arr=explode(str,"\n");

	for (i=0;i<sizeof(arr) ;i++ ) {
		assemble+=arr[i];
	}

	pointer = 0;
	for (i=0;i<strlen(assemble) ;i++ ) {
		if ((strlen(assemble[pointer..i]) - diff_ansistr(assemble[pointer..i]) == 60) ) {
		        if (is_chinese(assemble[i..i+1])) {
		                temp += assemble[pointer .. i+1] + "\n";
		                pointer=i;
		        } else {
		                temp += assemble[pointer .. i] + "\n";
		                pointer=i;
		        }
		}
	}
        return temp;
}

varargs mixed kingdom_data(string id, string type, string prop, string set, mixed data)
{
	return KINGDOM_D->kingdom_data(id, type, prop, set, data);
}

varargs mixed people_data(string id, string prop, string tar)
{
	return KINGDOM_D->people_data(id, prop, tar);
}

varargs mixed develop_data(string id, string prop, string dp_tar, string tar, int data)
{
	return KINGDOM_D->develop_data(id, prop, dp_tar, tar, data);
}
