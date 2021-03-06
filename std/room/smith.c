//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/smith.c
// by amgbell @ DA

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <weapon.h>

inherit ROOM;

string chinese_weapon_name(string english);
int sort();

void init()
{
	int change=0;
	if (!query("long") || query("long")=="0\n" || query("long")=="0\n\n") {
		set("long",@LONG
你走进一家铁铺，炙热的热风扑面而来。几个赤着上身的工匠正在这里
打铁，有的拉扯风箱，有的抡着铁锤，叮叮当当地敲个不停，左边的地上，
还有几名老铁匠正围在一张桌旁，对摊在桌上的一张大设计图讨论着。
LONG);
		change=1;
	}

	if (!query("short")) {
		set("short","铁铺");
		change=1;
	}
//	if (change) do_saveroom(this_object());
        add_action("do_make","make");
        add_action("do_list","list");
        add_action("do_remake","remake");
        sort();
}

int do_make(string arg)
{
	object me, ob;
	int level,i=1;
	string type,str,file;

        me=this_player();

        if(me->query("kingdom/id")!=environment(me)->query("kingdom_id"))
        	return notify_fail("What？\n");
	if(!me->query("kingdom/king") && !me->query("kingdom/minister") )
		return notify_fail("What？\n");

        if (!arg) {
	        write(sprintf("贵国铁铺发展: %d\n", develop_data(me->query("kingdom/id"), "query_par", "smith", "dev") ));
        } else if (sscanf(arg,"%d %s",level,type)==2) {
        	if (member_array(type, WEAPON_TYPES)==-1) return notify_fail("目前不开放此种武器的制作。\n");

		if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "weapon")
		>= kingdom_data(me->query("kingdom/id"), "data", "query_par", "max_weapon") )
			return notify_fail("贵国武器上限已额满，请删除不必要的武器再建。\n");

//        	if (develop_data(me->query("kingdom/id"), "query_par", "smith", "dev") < level ) 
//	                return notify_fail("贵国的发展不足以制作此等级的武器。\n");
	        if (level < 10) return notify_fail("武器等级必须大于10。\n");
	        if (level >50 ) return notify_fail("武器等级必须小于50。\n");

	        if (kingdom_data(me->query("kingdom/id"),"data","query_par","gold") < level*2000) {
	                return notify_fail("贵国的国库已经没有钱制作武器了。\n");
	        } else {
	                kingdom_data(me->query("kingdom/id"),"data","sub","gold",level*2000);
        	}

	        str="#include <weapon.h>\n";
        	str+="#include <ansi.h>\n";
	        str+="inherit "+upper_case(type)+";\n";
        	str += "void create() {\n";

	        str += "\tset_name(\""+chinese_weapon_name(type)+"\", ({\""+type+"\"}) );\n";
        	str+="\tset_weight(10); \n";
	       	str += "\tset(\""+"new"+"\""+", 1);\n";

	        str+="\tif( clonep() )\n";
        	str+="\t\tset_default_object(__FILE__);\n";
	        str+="\telse {\n";
        	str+="\t\tset(\"long\", @LONG\n";
	        str+="一把"+to_chinese_kingdom(me->query("kingdom/id"))+"打造出来的"+chinese_weapon_name(type)+"。\n";
        	str+="LONG );\n"; 

	       	str += "\t\tset(\""+"unit"+"\""+",\""+"把"+"\");\n";
	        //str += "set(\""+"value"+"\""+",30);\n";

		str += "\t\tset(\""+"weapon_prop/wl"+"\""+","+level/10+");\n";
		str += "\t\tset(\""+"weapon_prop/Mh"+"\""+","+level/10+");\n";

        	str += "\t\tset(\""+"type"+"\""+",\""+type+"\");\n";
	        str += "\t\tset(\""+"level"+"\""+","+level+");\n";
        	str += "\t\tset(\""+"skill"+"\""+","+level*2+");\n";
	        str += "\t\tset(\""+"owner"+"\""+",\""+me->query("id")+"\");\n";
        	str += "\t\tset(\""+"kingdom"+"\""+",\""+me->query("kingdom/id")+"\");\n";
        	str+="\t}\n";
	        str+="\tinit_"+type+"("+level/3+");\n";
	        str+="\tsetup();\n";
        	str+="}\n";

		if (!me->query("last_wp/"+me->query("kingdom/id"))) {
        		do {
		                file=KINGDOM_DIR+me->query("kingdom/id")+"/weapon/"+me->query("id")+"_"+sprintf("%d",i)+".c";
		                i++;
		        }       while (file_size(file) >= 0);
			me->set("last_wp/"+me->query("kingdom/id"),i);
		        me->save();
		} else {
		        i=me->query("last_wp/"+me->query("kingdom/id"));
		        i++;
		        file=KINGDOM_DIR+me->query("kingdom/id")+"/weapon/"+me->query("id")+"_"+sprintf("%d",i)+".c";
		        me->set("last_wp/"+me->query("kingdom/id"),i);
		        me->save();
		}
	        write_file(file,str,1);

	        message_vision("$N要求铁匠做一把"+level+"级的"+chinese_weapon_name(type)+"。\n"NOR,me);
	        message_vision("铁匠把"+level+"级的"+chinese_weapon_name(type)+"交给$N。\n"NOR,me);

		kingdom_data(me->query("kingdom/id"), "data", "add", "weapon", 1);
	        ob = new(file);
        	ob->move(me);
        } else return notify_fail("make <level> <type>\n");

        sort();
        return 1;
}

int do_list(string arg)
{
        string dir,*items,file,str;
        object me;
        int i=0;

        me=this_player();

        
        if(me->query("kingdom/id")!=environment(me)->query("kingdom_id"))
        	return notify_fail("What？\n");

	if(!me->query("kingdom/king") && !me->query("kingdom/minister") )
		return notify_fail("What？\n");

        sort();

        if (!me->query("smith")) return notify_fail("你目前没有打造任何东西。\n");

        str=sprintf("编号      名字                     拥有者         技能");

        for (i=0;i < sizeof(keys(me->query("smith"))) ;i++ )
        {
                file=me->query("smith/"+i);
                str+=sprintf("\n%-10d%-25s%-15s%-8d",
                        i,
                        file->query("name")+"("+file->query("id")+")",
                        file->query("owner"),
                        file->query("skill"));
        }
        me->start_more(str+"\n");

        return 1;
}


int do_remake(string arg)
{
        object me, ob;
        string name;

        me=this_player();
        
        if(me->query("kingdom/id")!=environment(me)->query("kingdom_id"))
        	return notify_fail("What？\n");

	if(!me->query("kingdom/king") && !me->query("kingdom/minister") )
		return notify_fail("What？\n");

        sort();
        if (me->query("smith/"+to_int(arg))) {
	        if( !me->can_afford((me->query("smith/"+to_int(arg)))->query("value")) )
	        	return notify_fail("你身上没有足够的钱。\n");
	        me->pay_money((me->query("smith/"+to_int(arg)))->query("value"));
	        me->save();

		ob = new(me->query("smith/"+to_int(arg)));
                ob->move(me);
                name=(me->query("smith/"+to_int(arg)))->query("name");
                message_vision("$N要求铁匠重做"+name+"。\n"NOR,me);
                message_vision("铁匠把"+name+"重做一把交给$N。\n"NOR,me);
                return 1;
        }

        return notify_fail("没有这个编号。\n");
}

string chinese_weapon_name(string english)
{

	if (english=="blade") return "刀子";
	if (english=="sword") return "剑";
	if (english=="axe") return "斧头";
	if (english=="dagger") return "匕首";
	if (english=="hammer") return "锤子";
	if (english=="whip") return "鞭子";
	if (english=="spear") return "矛";
	if (english=="staff") return "棍棒";
	if (english=="wand") return "魔杖";

	return "未知武器";
}

int sort()
{
	//mapping file_list=([]);
	string dir,*items,file;
	object me;
	int i,id_len,serial=0;

	me=this_player();

	dir=KINGDOM_DIR+me->query("kingdom/id")+"/weapon/";
	items=get_dir(dir);

	me->delete("smith");

	if (me->query("kingdom/king")) {//king
	        for (i=0;i<sizeof(items) ; i++) {
	                me->set("smith/"+i,dir+items[i]);
        	}
	} else { //min
	        id_len=strlen(me->query("id"));
	        serial=0;
	        for (i=0;i<sizeof(items) ; i++) {
	                if (strlen(items[i]) < id_len) continue;
        	        if (items[i][0..(id_len-1)] == me->query("id")) {
	                        me->set("smith/"+serial,dir+items[i]);
        	                serial++;
                	}
	        }
	}
}
