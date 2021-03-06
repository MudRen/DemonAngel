//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/add_mob.c
// by bor @DA

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

#define NPC_COST	5000

int main(object me,string arg)
{
	int num, lv;
	string file, type, NPC_CODE, name, id;
	object env, ob;

	seteuid(getuid());
	if( !(env = environment(me)) ) return 0;
	if( env->query("kingdom_id")!=me->query("kingdom/id") ) return notify_fail("这不是贵国的领土!!\n");
	if( !arg || !sscanf(arg, "%d %s", lv, type) ) return notify_fail("指令格式：add_mob <等级> <从何处招>\n");
	if( lv>45 || lv<1 ) return notify_fail("目前不开放这些等级的mob。\n");

	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < NPC_COST * lv )
		return notify_fail("贵国国库金额不足。\n");

	num = kingdom_data(me->query("kingdom/id"), "data", "query_par", "npc")
		+ kingdom_data(me->query("kingdom/id"), "data", "query_par", "npc_num");

	file = KINGDOM_DIR+me->query("kingdom/id")+"/npc/"+(string)num;

	if(!kingdom_data(me->query("kingdom/id"), "special_room", "check", type))
		return notify_fail("贵国没有 "+type+" 这类型的特殊建筑物, 无法创造生物。\n");

	if( lv>15 ) {
		if( type=="stable" ) {
			if( lv>20 ) return notify_fail("马匹的等级, 不得超过 20。\n");
			if( lv > develop_data(me->query("kingdom/id"), "query_par", "stable", "dev") )
				return notify_fail("贵国发展不足, 没办法创造高等级生物。\n");
		} else
			if( lv > develop_data(me->query("kingdom/id"), "query_par", type, "dev") )
				return notify_fail("贵国发展不足, 没办法创造高等级生物。\n");
	}

// 初始设定
	switch(type) {
		case "tavern":
			if ( lv<=5 ) { name = "小孩";id = "child"; }
			else { name = "居民";id = "man"; }
			break;
		case "barracks":
			if ( lv<=15 ) { name = "守卫";id = "guard"; }
			else { name = "军人";id = "guard"; }
			break;
		case "misc_shop":
			if ( lv<=10 ) { name = "实习商人";id = "merchant"; }
			else { name = "商人";id = "merchant"; }
			break;
		case "magic_tower":
			if ( lv<=10 ) { name = "小魔法师";id = "mage"; }
			else { name = "法师";id = "mage"; }
			break;
		case "church":
			if ( lv<=10 ) { name = "小牧师";id = "cleric"; }
			else { name = "牧师";id = "cleric"; }
			break;
		case "stable":
			if ( lv<=10 ) { name = "幼马";id = "horse"; }
			else { name = "野马";id = "horse"; }
			break;
		default:	// 这是 人类 type 的 default
			write("注意 : “"+type+"”中没有定义过 !!\n");
			return 1;
	}


// NPC 基本型态
	NPC_CODE = "// NPC : " +file+".c\n";
	NPC_CODE += "// savenpc by "+ me->query("id")+"    "+ctime(time())+"\n\n";

	NPC_CODE += "inherit "+upper_case(type)+"_NPC;\n\n";

	NPC_CODE += "#include <ansi.h>\n\n";
	NPC_CODE += "void create()\n{\n";
	NPC_CODE += "\tset_name(\""+name+"\", ({\""+id+"\", \""+id[0..0]+"\", \""+id[0..1]+"\"}) );\n";
	NPC_CODE += sprintf("\tset(\"long\", @TEXT\n%s\nTEXT\n\t);\n", "你看见一只第"+chinese_number(lv)+"级的"+name+"。" );
	NPC_CODE += sprintf("\tset(\"type\", %O);\n", type );
	NPC_CODE += sprintf("\tset(\"level\", %O);\n", lv );
	NPC_CODE += sprintf("\tset(\"refresh_data\", %O);\n", ({ this_player()->query("id"), ctime(time()), this_player()->query("id"), ctime(time()) }) );
	NPC_CODE += sprintf("\tset(\"home\", %O);\n", base_name(env) );
	NPC_CODE += sprintf("\tset(\"kingdom\", %O);\n", me->query("kingdom/id") );
	if( type=="stable") {
		NPC_CODE += sprintf("\tset(\"ridable\", 1);\n");
	}
	NPC_CODE += "\tsetup_npc();\n\n";
	NPC_CODE += "}\n";
    
	write_file(file+".c", NPC_CODE, 1);

	if( !(ob = call_other( file, "???" )))
		ob = new(file);

	if(!objectp(ob)) return notify_fail("有错误发生, 请通知管理者。\n");

	ob->move(env);
	message_vision("$N双手一招, 召唤出$n\n", me, ob);

	env->add("objects/",([ file:1 ]));
	do_saveroom(env);
	refresh_room(env);

	kingdom_data(me->query("kingdom/id"), "data", "add", "npc", 1);
	kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", NPC_COST * lv );
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式：add_mob <等级> <从何处招>

国王或大臣利用此指令可创造mob。

例如： add_mob 20 tavern

目前可以招收的有：

  tavern        : 这里招来的生物就是一般的百姓，他们爱好和平，只会站着被
                  打，然后等死。
  misc_shop     : 这里能招到一些商人, 他们可以贩卖一些货物来帮助冒险者, 同
                  时帮国家赚钱。
  barracks      : 从军营里招出来的军人 -- 王国的防卫力量，如果你进入交战国
                  或是被通缉，当心被他们整群追杀。
  church	: 从教堂召出的生物通常具有神圣的力量，虽然战力不强，但是等
  		  级越高，就会越有帮助。
  magic_tower   : 从魔法塔召出的生物都是一些魔法师，擅长施各种魔法，而且战
		  斗力也不差。
  stable	: 野马

HELP
	);
	return 1;
}
