//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/furnace.c
// by bor @DA

#pragma optimize
#pragma save_binary

//#define DEBUG

inherit ROOM;

#include <ansi.h>

int	flag=-1,		// 是否正在灌炉, 内定没有灌炉
	mp,			// 目前 charge 法力的数值
	furnace_count_ini,	// 当你 load 时魔力炉乱数决定的转数
	furnace_count,		// 纪录目前转几圈了, 用来计算数值变化
	lost_count;		// 纪录失败的次数

object ob, env;

private int into_furnace( object me );
private int furnace_reward();

void setup()
{
	seteuid(getuid());
	env = this_object();
	::setup();
}

void init()
{
	if( userp(this_player()) && ( wizardp(this_player()) || this_player()->query("kingdom/id")==env->query("kingdom_id")  )  ) {
		add_action("do_load", "load");
	}
	add_action("do_charge", "charge");
}

private int do_load(string arg)
{
	object me = this_player();
	string item;

	if( !userp(me) ) return 0;
	if( flag==1 ) return 0;
	if(me->query("kingdom/id")!=environment(me)->query("kingdom_id")) return notify_fail("What？\n");
	if(!me->query("kingdom/king") && !me->query("kingdom/minister") ) return notify_fail("What？\n");
	if( !arg ) return notify_fail("load <物品> into furnace\n");
	if( sscanf(arg, "%s into furnace", item)!=1 ) return notify_fail("load <物品> into furnace\n");
	if( !objectp( ob = present(item, me) ) ) return notify_fail("你身上没有此物品!!\n");
	if( !ob->query("armor_type") && !ob->query("skill_type") )
		return notify_fail("这不是一件装备!!\n");
	if( !ob->query("new") ) return notify_fail("这件装备不是新货!!\n");
	if( ob->query("equipped") ) return notify_fail("你正装备着!!\n");

	if( !ob->query("kingdom") || ob->query("kingdom")!=me->query("kingdom/id") )
	if( !ob->query("kingdom/king") && ob->query("owner")!=ob->query("id") )
		return notify_fail("这件物品拥有者不是你!!\n");

	if( ob->query("level")<23 ) return notify_fail("这件物品太脆弱了，不能利用魔法改质。\n");

	mp = random(30) + 10;			// 当作初始值

	furnace_count_ini = random(53)+7;	// 最少 6 次
	flag = 1;				// 不让其他人也能 load
	into_furnace(me);
	return 1;
}

object furnace_msg_ob()
{
	object *inv;
	
	inv = all_inventory(env);
	if( zerop(inv) ) return 0;
	return inv[random(sizeof(inv))];
}

private int into_furnace( object me )
{
	ob->move(VOID_OB);
	message_vision(WHT"$N把$n送入魔力炉中。\n\n"NOR, me, ob);
	message_vision(HIM"魔力炉发出白色的光芒, 触须开始蠕动。\n\n\n"NOR, me);
	furnace_count = 0;
	call_out("furnace_count_msg", 2 );
	return 1;
}

private int furnace_count_msg()
{
	object ob2;
	furnace_count_ini --;

	ob2 = furnace_msg_ob();
	if( furnace_count>10+random(2) )
		mp = mp - (54+random(2));		// 每转后剩余的法力
	else mp = mp - ( 105+random(3) );

#ifdef DEBUG
	message_vision("init:"+furnace_count_ini+", lost_count:"+lost_count+", furnace_count:"+furnace_count+"\n\n", ob2);
#endif

	if( furnace_count_ini ) {	// 转阿转阿
		// 三种情况, 可以将 furnace 停下来[但至少要 7 圈后, 才能掉]
		if( furnace_count>6 ) {
			if( ( mp>4000 && 50>random(100) )
			|| ( lost_count<=5 && lost_count>=3 && 3>random(100) )
			|| ( 2>random(100) )
			) {
				call_out("furnace_drop", 0 );
				return 1;
			} else if( 50>random(100) && (mp <= -2500 || lost_count>=7) ) {	// 如果 mp 严重不足就吃掉物品
				if(ob2) message_vision(HIC"魔力炉突然剧烈震动, 然后所有的触须渐渐停止了活动 ...\n\n"NOR, ob2);
				destruct(ob);
				flag = -1;
				return 1;
			}
		}

		if( mp<0 ) {
			lost_count += 1;
			if(ob2) message_vision("[1;5;31m魔力炉的能量不足, 发出的光芒开始减弱 ...[0m\n", ob2);
		} else {
			furnace_count += 1;
			lost_count = 0;
//			if(ob2) message_vision(HIY"魔力炉的触须稳定地游动, 发出强烈的魔法光芒 ...[第 "+furnace_count+" 圈]\n\n"NOR, ob2);
			if(ob2) message_vision(HIY"魔力炉的触须稳定地游动, 发出强烈的魔法光芒 ...\n\n"NOR, ob2);
		}
		call_out("furnace_count_msg", 0 );
	} else {	// 结束转动
		if(ob2) message_vision(WHT"魔力炉的活动渐渐减慢, 在最后的光芒散去后, 魔力炉完全恢复静止 ...\n"NOR, ob2);
		call_out("furnace_drop", 0 );
	}
	return 1;
}

private int furnace_drop()
{
	flag = -1;

	// 转的圈数如果小于 8 , 那么当作掉出来, 不处理数值
	if( furnace_count > 7 ) {
		ob->set("new", 0);
		furnace_reward();
	}
	ob->move(env);
//	message_vision(WHT"\n$N“啪”地一声从魔力炉中掉了出来。[挖列... 才 "+ furnace_count+" 圈]\n"NOR, ob);
	message_vision(WHT"\n$N“啪”地一声从魔力炉中掉了出来。\n"NOR, ob);
	return 1;
}

private int furnace_reward()
{
	int tmp, num, ac, db, wl, Mh, lv;
	string attr;
	string *add_normal = ({ "ac", "db", "wl", "Mh" });

	// 1. 根据魔力炉全部的转数(furnace_count) 来决定掉出来的
	tmp = random(60);

	if( tmp>=45  ) attr = add_normal[random(sizeof(add_normal))];
	else if( tmp<45 && tmp>=35 )	attr = "kar";
	else if( tmp<35 && tmp>=25 )	attr = "sta";
	else if( tmp<25 && tmp>=18 )	attr = "con";
	else if( tmp<18 && tmp>=10 )	attr = "str";
	else if( tmp<10 && tmp>=5 )	attr = "dex";
	else attr = "int";

	if( member_array(attr, add_normal)!=-1 ) num = furnace_count/5;
	else num = furnace_count/10;
	if(num<1) num=1;

	ac = furnace_count/10;
	db = furnace_count/10;
	wl = furnace_count/10;
	Mh = furnace_count/10;

	lv = ob->query("level") + ob->query("level") * furnace_count/100;

	if( ob->query("armor_type") ) {
		ob->set("armor_prop/ac", ac);
		ob->set("armor_prop/db", db);
	} else {
		ob->set("weapon_prop/wl", wl);
		ob->set("weapon_prop/Mh", Mh);
	}

	if( ob->query("type")=="wand" || ob->query("type")=="staff" ) {
		string *spell_list;
		// 取得 invoke_magic 方式有很多种... 以下只介绍两种:
		// 1. 直接取得 /daemon/spell/
		// spell_list = get_dir("/daemon/spell/");
		// ob->set("invoke_magic", replace_string(spell_list[random(sizeof(spell_list))], ".c", "") );

		// 2. 由于我将 /daemon/spell/ 底下划分为各职业可学的目录, 如 /daemon/spell/魔法师/
		//    因此, 我额外划分一个目录放置到底有哪些法术可供当作 invoke_magic, 如下:
		spell_list = get_dir("/daemon/furnace/spell/");
		ob->set("invoke_magic", spell_list[random(sizeof(spell_list))] );
	}

#ifdef DEBUG
	if( ob->query("armor_type") )
		ob->set_name("make"+ob->query("level")+"_tick"+furnace_count+"_lv"+lv+"_"+attr+num, ({ ob->query("id") }) );
	else ob->set_name("make"+ob->query("level")+"_tick"+furnace_count+"_sk"+(lv*2)+"_"+attr+num, ({ ob->query("id") }) );
#endif

	ob->set("level", lv);
	ob->set("add_attr/"+attr, num);			// 附加值, 避免与 ac, db, wl, Mh, ... 等重复, 好处: 唯一性

	if( !do_saveitem(ob) ) return 0;
	return 1;
}

private int do_charge(string arg)
{
	object me=this_player();

	message_vision("$N握紧魔力炉的触手, 把所有的精神力输送进去。\n\n", me);
	call_out("charge_furnace", 0, me, arg );
	return 1;
}

private int charge_furnace(object me, string arg)
{
	object ob;
	if( arg=="corpse" ) {
		ob = present(arg, env);
		if(!ob) ob = present(arg, me);
		if( ob && ob->is_corpse() ) mp += (600 + random(100));
		destruct(ob);
	} else if( arg=="furnace" ) {
		if( flag==1 ) mp += me->query("mp");
		me->set("mp", 0);
	}
	message_vision("魔力炉突然生出一股强烈的吸引力, 把$N的精神力吸得一干二净 !\n", me);
	message_vision("$N突然被魔力炉弹开。\n", me);
	return 1;
}
