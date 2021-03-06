//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/set_mob.c
// by bor @DA, 4/25 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

void show_npc( object mob );
private int check_legal_name(string name);
private int check_legal_id(string id);

int main(object me, string arg)
{
	object env, ob;
	string arg1, arg2, type, set, *list=({}), mob_file;
string *set_type = ({ "name", "id", "long", "nickname", "level", "unit",
	"gender", "aggressive", "no_corpse", "die_msg", "home", "chasing",
	"polite", "reward"
});
	int value, npc_cost;
	mapping dbase;

	seteuid(getuid());
	if( !arg ) return notify_fail("指令格式 : set_mob <生物名称> <参数类型> <设定值>\n");
	env = environment(me);
	if( ob = present(arg, env) ) {	// 查询该 npc 资料
		if( !ob->query("kingdom") || ob->query("kingdom")!=me->query("kingdom/id") )
			return notify_fail("What?");
		show_npc(ob);
		return 1;
	}
	if( sscanf(arg, "%s %s", arg1, arg2) != 2 )
		return notify_fail("指令格式 : set_mob <生物名称> <参数类型> <设定值>\n");
	if( !(ob = present(arg1, env)) ) {
		// 如果你没下过 home change 的话，就只是一般的 mob 修改而已
		if( !( ob = me->query_temp("change_mob") ) ) return notify_fail("没有这个 MOB !!\n");
	}
	if( file_size(full_name(ob)) == -1) return notify_fail("没有这个 MOB !!\n");
	if( ob->is_character() && userp(ob) ) return notify_fail("这不是一只生物。\n");
	if( ob->query("kingdom") != me->query("kingdom/id") )
		return notify_fail("这不是贵国的生物。\n");

	if( sscanf(arg2, "%s %s", type, set) != 2 ) {
		return notify_fail("指令格式 : set_mob <生物名称> <参数类型> <设定值>\n");
	}
	if( !mapp(dbase = ob->query_entire_dbase()) ) return 0;

	if( !arrayp(list = ob->query("refresh_data")) && sizeof(list)==4)
		return notify_fail("该生物资料有误, 无法判定权限。\n");

	// 判定你有没有权利改 NPC
	if( list[0]!=me->query("id") && !me->query("kingdom/king") )
		return notify_fail("你权限不够, 没办法修改该生物。\n");

	if( ob->query_temp("barracks") )
		return notify_fail("他正离营状态, 不能作修改。\n");

//	if( file_size(ob->query("home")+".c") == -1 )
//		return notify_fail("他的家已经被销毁，无法生存下去了 !!\n");

	if( member_array(type, set_type) == -1) return notify_fail("没有这样的参数类型。\n");

	switch(type) {
		case "name":
		case "nickname":
			if( type == "nickname" && set =="-d") {
				if( !dbase["nickname"] ) return notify_fail("OK !\n");
				ob->delete("nickname");
			} else {
				if(strlen(set)>30) return notify_fail("你的参数太长了。\n");
				set = ansi_color(set);
				if( !check_legal_name(set) ) return notify_fail("不好意思，你取的 name 不符合规定 !!\n");
				if( sscanf(set, "[%*s") || sscanf(set, "%*s[%*s") ) dbase[type]=set+"[0m";
				else dbase[type]=set;
			}
			break;
		case "id":
			if(strlen(set)>30) return notify_fail("你的参数太长了。\n");

			if(type=="id") {
				if( !check_legal_id(set) ) return notify_fail("英文内包含不合法的单字或不当使用。\n");
			}
			dbase[type] = set;
			break;
		case "long":
			if( !sscanf(set, "%d", value) ) value = 0;
			switch( value ) {
				case 0:	// 不会自动排版
				case 1:	// 自动排版
					me->edit( (: call_other, __FILE__, "do_changelong", ob, value :) );
					return 1;
					break;
				default:
					return notify_fail("没有这样的参数。\n");
			}
			break;
		case "polite":
		case "no_corpse":
		case "aggressive":
		case "chasing":
			value = atoi(set);
			if( value<0 ) return notify_fail("不能设定这样的参数。\n");
			if( value != 0 && value != 1 ) return notify_fail("不能设定这样的参数。\n");
			if(type =="polite") {
				if( dbase["type"]!="barracks" ) return notify_fail("生物只有军人类型，才能设定此参数。\n");
			}
			dbase[type] = value;
			write(dbase["name"]+"("+dbase["id"]+")的 "+ type +" 设定为 " + value +"\n");
			break;
		case "level":
			if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
			if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");

			value = atoi(set);
			if( value==-1 ) return notify_fail("不能设定这样的参数。\n");
			if( value == dbase["level"] ) return notify_fail("MOB 的等级本来就是这个等级 !!\n");
			if( value > 50 ) return notify_fail("MOB 等级不能超过 50。\n");
			if( value < 1 ) return notify_fail("MOB 的等级不能这么低 !!\n");
			if( value > dbase["level"] ) {
				npc_cost = ( value - dbase["level"] ) * 5000;
				if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < npc_cost )
					return notify_fail("贵国国库金额不足。\n");
				dbase["level"] = value;
				write(dbase["name"]+"的等级设定为 "+ value +"\n");
				kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", npc_cost );
			} else {
				dbase["level"] = value;
				write(dbase["name"]+"的等级设定为 "+ value +"\n");
			}
			break;
		case "die_msg":
			if( set == "-d") {
				ob->delete("die_msg");
				break;
			}
			set = ansi_color( set );
			set = kill_all_bug(set);
			dbase[type] = set+"\n";
			break;
		default:
			write("目前暂时不开放此参数类型。\n");
			return 1;
	}

	if( !save_npc(ob) ) return notify_fail("储存 MOB 资料失败, 请回报给管理者 !!\n");
	write("OK !\n");

	mob_file = base_name(ob);

	if(objectp(ob)) destruct(ob);
	if(find_object(mob_file)) destruct(find_object(mob_file));
	ob = new(mob_file);
	ob->move(env);			// 哪一格改 mob 就把 mob 移到该格就可

	refresh_room(env);
        return 1;
}

void show_npc( object mob )
{
	string str;
	object me = this_player();
	mapping dbase;

	dbase = mob->query_entire_dbase();

	str = sprintf("[1;30m"+dbase["name"]+"("+dbase["id"]+")"+"的资料如下 :\n\n[m");

	str += sprintf("name : %s\t\tid : %s\tlevel : %d\n", dbase["name"], dbase["id"], dbase["level"] );
	str += sprintf("nickname : %s\n", dbase["nickname"]?dbase["nickname"]:"无");
	str += sprintf("race : %s\t\tgender : %s\t\tunit : %s\n", dbase["race"], dbase["gender"], dbase["unit"] );
	str += sprintf("aggressive : %d\t\tchasing : %d\t\treward : %s\n", dbase["aggressive"], dbase["chasing"], dbase["reward"]?dbase["reward"]:"无" );
	str += sprintf("no_corpse : %d\t\twimpy : %d\t\tpolite : %d\n", dbase["no_corpse"], dbase["wimpy"], dbase["polite"] );
	str += sprintf("die_msg : %s\n", dbase["die_msg"]?dbase["die_msg"]:"无" );
	str += "long :\n";
	str += sprintf("%s\n", dbase["long"] );

	me->start_more(str);
	return ;
}

private int check_legal_id(string id)
{
	int i;
	string *banned_id = ({"bor","zethus","fuck","sbada"});

	i = strlen(id);
        
	if( (strlen(id) < 2) || (strlen(id) > 20 ) ) return 0;
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) return 0;
	for(i=0;i<sizeof(banned_id);i++) {
		if(strsrch(id, banned_id[i]) != -1) {
			write("对不起，你的内容有部份文字将会造成别人困扰。\n");
			return 0;
		}
	}
	return 1;
}

private int check_legal_name(string name)
{
        int i;
string *banned_name = ({
	"你", "你", "我", "他", "她", "牠", "它", "祂", "您", "干", "贱",
	"他妈的", "贱人", "鸭", "摇屁屁小水鸭","夜云","会飞的鸭子","奄奄一息"
});
	i = strlen(name);
        
	if( (strlen(name) < 4) || (strlen(name) > 30 ) ) return 0;
	while(i--) {
		if( name[i]<=' ' ) return 0;
		if( i%2==0 && !is_chinese(name[i..<0]) ) return 0;
	}
	for(i=0;i<sizeof(banned_name);i++) {
		if(strsrch(name, banned_name[i]) != -1) return 0;
	}
	return 1;
}

void do_changelong(object ob, int flag, string str)  // 设定 mob long
{
	string *str_arg;

	str = ansi_color( str );

	if( strlen(str) > 8192 ) {
		write("你的参数太长了。\n");
		return;
	}
	str_arg = explode(str, "\n");

	if( sizeof(str_arg) > 11 ) {
		write("请控制在十行以内。\n");
		return;
	}
	str = kill_all_bug(str);

	if( flag==0 || flag ==1) ob->set("long", str);

	if( save_npc(ob) ) write("OK !\n");
	else write("[1;30m修改失败。\n[m");
        return ;
}

int help(object me)
{
        write(@HELP
指令格式 : set_mob <生物名称> <参数类型> <设定值>

这是国王与大臣用来帮 mob 做设定的指令，用这个指令他可以改变一些 mob
的参数，使他看起来更适合环境。
以下是目前开放设定的参数类型 :
 name   :       设定生物的中文名字。
 id     :       设定生物的英文名字。
 nickname:      设定生物的绰号。例如 set_mob ruby nickname 大魔王
                你就可以看到 “大魔王”茹比(Ruby)。
                你可以用 nickname -d 把原先的 nickname 消除。
                nickname 的色彩用法请参考 help nick
 long   :       设定生物的描述, 就是你看到的那堆描述。
 race   :       设定种族，目前有 : 人类、野兽、妖魔、鸟类 ...
 unit   :       设定单位，例如 : 位、只、头、条 ...
 gender :       男性或女性、雄性或雌性。
 aggressive :   如果设了这个值为 1，这只生物就会抓狂了 ...
 chasing :      让 mob 会主动追击敌人，如果敌人在战斗中逃跑，他会尽力地
                追杀逃跑的敌人，直到追丢了为止。设 0 就会解除追杀。
                  例子 : set_mob <mob> chasing <1/0>

 ask    :       设定生物对某些问题的答覆，例如 :
                set_mob soldier ask ruby，这时会回答你在编辑器中输入
                的讯息，如果什么都没写，生物对这个问题就不会回答。
                你可以用 set_mob <id> ask what 来查询这个生物目前会回答
                的所有问题。
 ask -d  :      把某个问题的答覆取消

 chat_msg :     设定生物会一直喃喃说着某些讯息, 例如 :
                set_mob bagger chat_msg 乞丐拉着你道 : 大爷 !! 可怜小的吧 !!
                你可以用 set_mob <id> chat_msg what 来查询这个生物目前所
                有会讲的讯息
 chat_msg -d <讯息编号> : 删除这只生物的某些会讲的讯息。
 chat_msg_combat : 设定生物在战斗时会讲的话, 用法跟 chat_msg 相同
                  set_mob beggar chat_msg_combat 乞丐哀道 : 别打了 !! 救人啊 !!

 reward :       当 mob 被打死后，他会多出这一件遗物。不过这件东西只能是任务
                专用物品。例如 : set_mob dragon reward gem，当然，你要有 gem
                这样当你每次干掉 dragon，你就会捡到一块宝石
                如果你要取消 rewared, 可以用 set_mob <mob> reward none

 no_corpse :    设成 1 时，当 mob 被打死，他不会留下尸体，身上的装备也不会留
                下来。设成 0 就可以解除这种状况。

 die_msg :      当 mob 被打死时，最后留下的讯息。例如 :
                恶魔脸上露出不能相信的表情，对着$N大吼 : 怎么可能 ?? 我是不
                会被打败的 !!
                他想要用力抓住$N，但是终于化成一块石头。
                这里的 $N 是表示打败他的人的名字。
 die_msg -d :   删除 die_msg

 home   :       要 mob 搬家。例如 :
                  先找到要搬家的 mob，下 set_mob dog home change 指令，然后
                  走到他的新家，再下 set_mob dog home here。这样狗狗就会搬到
                  新家了。如果不想他搬家，用 set_mob dog home cancel。

 owner  :       帮 mob 换新主人, 新主人必须也是大臣。只有原主人和国王能用。

 level  :       帮 mob 变更等级，当然该花的钱还是会花的。

 sp_attack :    帮 mob 设定特殊攻击的型态和讯息，例如 :
                  增加特攻 : set_mob <mob> sp_attack <特攻型态> <特攻讯息>
                  取消特攻 : set_mob <mob> sp_attack -d <特攻型态>
                特攻讯息的写法 : $N狠狠地在$n的脚上咬了一口。
                        $N 表示正在使用特攻的生物名字
                        $n表示被攻击的对象的名字
                特殊攻击的型态请参考 help special_attack

 path   :       让 mob 会在特定的路线来回走动，例如 :
                 设定路线  set_mob <mob> path east, east, west, west
                 取消路线  set_mob <mob> path -d
                mob 走动的路线必需是一个回路，让它可以周而复始的一直走动,
                路线的每个方向都必需完整，而且用逗点隔开。所有的生物中，
                只有军事类的生物会在走动时同时搜寻敌人。路线的设定与消除
                都只能在 mob 的家才能进行，而且不能让他走出国境。

 wimpy :        当 mob 被打到体力低于设定的数值时他就会到处乱逃。
                set_mob <mob> wimpy <数值>

 polite :       给军营类生物的参数，如果设定，他就会对英雄以上的人敬礼。
                例 : set_mob soldier polite <1 or 0>

如果你在 set_mob 后面直接加 mob 的 id, 那就可以看到该 mob 的所有设定值。

例 : set_mob dog name 疯狗

其他相关资讯 :  add_mob, build, delete_mob


HELP);
	return 1;
}
