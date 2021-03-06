//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/build.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

private int make_room(object me, string type, string arg);
private int make_base_post_office(string id, string file);

int main(object me, string arg)
{
	string type, dir, *dir_list = ({"east","west","north","south","down","up"});
	int gold, limit_room;

	seteuid(getuid());
	if( !arg ) return notify_fail("指令格式 : build <特殊建筑物类型> <方向>\n");
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !me->query("kingdom/id") || !environment(me)->query("kingdom_id")
	|| environment(me)->query("kingdom_id") != me->query("kingdom/id")
	) return notify_fail("这里不是贵国的土地。\n");
	if( sscanf(arg, "%s %s", type, dir) != 2 ) return notify_fail("指令格式 : build <特殊建筑物类型> <方向>\n");
	if( member_array(dir, dir_list)==-1 ) return notify_fail("没有这个方向。\n");
	if( environment(me)->query("exits/"+dir) ) return notify_fail("这个方向已经有房间了。\n");
	switch( type ) {
		case "shop":
		case "tavern":
		case "herb_shop":
		case "misc_shop":
		case "bank":
		case "post_office":
		case "board":
			gold = 50000;	limit_room = 15;
			break;
		case "smith":
		case "armory":
			gold = 50000;	limit_room = 20;
			break;
		case "barracks":
			gold = 100000;	limit_room = 25;
			break;
		case "trainyard":
		case "gate":
		case "stable":
			gold = 250000;	limit_room = 30;
			break;
		case "magic_tower":
		case "church":
			gold = 250000;	limit_room = 35;
			break;
		case "furnace":
		case "hero_guild":
			gold = 500000;	limit_room = 50;
			break;
		default:
			return notify_fail("目前不开放此特殊建筑物。\n");
	}

	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "gold") < gold )
		return notify_fail("贵国国库金额不足。\n");

	if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "room") < limit_room )
		return notify_fail("贵国房间数未达到 "+ limit_room +" 无法设置。\n");

	if( !make_room(me, type, dir) ) return 1;

	kingdom_data(me->query("kingdom/id"), "data", "sub", "gold", gold);
	return 1;
}

int make_room(object me, string type, string arg)
{
	int num;
	string new_arg, new_file, str, short, long;
	object env;

	env = environment(me);

	// 我用实际房间数和房间流水号的总和作为下一间房间档名的依据
	num = kingdom_data(me->query("kingdom/id"), "data", "query_par", "room") +
		kingdom_data(me->query("kingdom/id"), "data", "query_par", "room_num");

	new_file = KINGDOM_DIR+me->query("kingdom/id")+"/"+(string)num;

	if( file_size(new_file+".c")!=-1 ) {
		write("这个档案已经存在，请恰管理者前往察看、修正。\n");
		return 1;
	}

	new_arg = inverse_dir(arg);

	str = "// room : " + new_file + "\n";
	str += "// saveroom by "+ me->query("id")+"    "+ctime(time())+"\n\n";
	str += "#include <ansi.h>\n";
	if( type !="normal" )
		str += "inherit " + upper_case(type) +";\n";
	else str += "inherit ROOM;\n";

	str += "void create()\n{\n";

	switch( type ) {
		case "bank":
			short = "银行";
			long = "你走进了一家银行, 行员们正在柜枱后忙碌着, 几个浑身肌肉的警卫正\n";
			long +="狠狠的盯着你看。一个面带微笑的办事员走了过来, 等着为你服务。这里是\n";
			long +="世界闻名的大奸商查克开的银行, 存在这里的钱虽然绝对安全, 但是却没利\n";
			long +="息。你可以在这里存(deposit)/提(withdraw)款和转帐(transfer)。";
			break;
		case "board":
			short = "留言版";
			long = "这是一个供人留言记事的留言板。";
			break;
		case "shop":
			short = "商店";
			long ="走进这家装备店, 你一眼就被那些挂在墙上的武器防具所吸引, 一个\n";
			long +="带着微笑的壮汉站在柜枱前欢迎你, 一面盯着你身上看, 像是随时准备为\n";
			long +="你量身打造装备一般。这里是史坎布雷有名的盖兹装备店, 主人以打造高\n";
			long +="级的魔法武器闻名于整个大陆, 在这里, 你可以安心的买卖(buy/sell)东\n";
			long +="西而不用担心被骗, 你可以先看看(list)货物, 或请老板帮你估价(value)\n";
			long +=", 如果你想要试试看(try), 老板也不会说怎样的。";
			break;
		case "post_office":
			short = "邮局";
			long ="你走进一家小邮局, 几个邮差正坐在一堆信箱旁边整理信件, 他们边聊\n";
			long +="天边把信件塞入不同的信箱中。在这堆信箱中应该也有你的吧, 如果你想看\n";
			long +="看有没有你的信, 你可以找找看有没有你的信箱(search mailbox)。";
			break;
		case "trainyard":
			short = "训练听";
			long ="这里是一个充斥着汗水与呼喊声的训练厅, 宽敞的大厅里是一个方形\n";
			long +="的广场, 有许\多人正在场上卖力地锻练着, 呼喊声与刀剑撞击声不断传来\n";
			long +=", 广场边堆满了一些训练道具和武器装备, 几个看起来像是教练模样的人\n";
			long +="正站在场边对着场上的人指指点点。你可以在这里训练(train)技能、提\n";
			long +="升(advance)等级、查看(list)技能种类和训练所需代价(cost)。";
			break;
		case "magic_tower":
			short = "法术研习营";
			long ="这里是一个安静明亮的研习室, 研习室的正中有一张长条桌, 两旁则是\n";
			long +="直达屋顶的书架, 架上摆了画满各式奇怪符号的书籍, 大部份是有关魔法的,\n";
			long +="在这里, 你可以翻看看(list)有什么适合你目前程度的法术可学, 也可以静\n";
			long +="下心来研习(study)法术。";
			break;
		case "smith":
			short = "铁铺";
			long = "你走进一家铁铺，炙热的热风扑面而来。几个赤着上身的工匠正在这里\n";
			long += "打铁，有的拉扯风箱，有的抡着铁锤，叮叮当当地敲个不停，左边的地上，\n";
			long += "还有几名老铁匠正围在一张桌旁，对摊在桌上的一张大设计图讨论着。";
			break;
		case "armory":
			short = "防具屋";
			long = "你走进一家挂满皮革金属和布料的店铺，裁缝们正坐在柜台后面的一个\n";
			long += "长桌边边聊天边将一件件的盔甲防具组合起来，有几位工匠正在弯着一条条\n";
			long += "的藤枝，似乎正在做盾牌。";
			break;
		case "furnace":
			short = "魔力炉";
			long = "你走进一个庞大的炉房，炉房中间飘浮着一个奇怪的物体，那个像肉团\n";
			long +="般，长着许多恶心触须的东西就是魔力炉(furnace)。魔力炉的触须从炉体\n";
			long +="软软地垂到地面上，就像只大章鱼一般。走到这里，你有一种力量往魔力炉\n";
			long +="那边塌陷的感觉，虽然不强烈，但是却令人很难受。在魔力炉的四周异常的\n";
			long +="洁净，不仅一点灰尘也没有，连空气的流动也似乎停止了。";
			break;
		case "tavern":
			short = "旅馆";
			long ="这里是一家小旅馆，专门供给过路的旅客们歇歇脚用的，里面的房间装\n";
			long +="饰的非常舒适，不管你受了多大的伤害或者是旅途劳累，你都可以在这里安\n";
			long +="心的在里面休养，不用怕被人打扰，这是这一家温柔乡旅社独特的风格。在\n";
			long +="一旁的是一位相当可爱的女侍，正在等着各位有需要的人进入休息。";
			break;
		case "herb_shop":
			short = "药店";
			long ="你走进一家充满药草味的药店, 店里陈列着各种瓶瓶罐罐, 你可以在这\n";
			long +="里买到各种伤药绷带甚至大补丸, 如果你觉得该补一补了, 可以用 list 看\n";
			long +="看有什么货色, 再考虑要不要买(buy)。";
			break;
		case "misc_shop":
			short = "杂货店";
			long ="这里是杂货店，店里摆满着各式各样冒险用的杂货货品，您可以努力的找\n";
			long +="找看，是否有您自己需要或是迫切需要的的东西。用 list 看看你需要的东西\n";
			long +="吧。";
			break;
		case "gate":
			short = "关卡";
			long ="这里是一个关卡，路两旁各盖了一座检查哨，路中央还横着拒马，几个\n";
			long +="横枪执刀的卫兵正在哨站旁检查行人，并且向他们收过路税。";
			break;
		case "hero_guild":
			short = "英雄会馆";
			long = "这里是供各路英雄聚集的地方, 除了有免费的住宿外, 同时又可以跟\n";
			long += "来自四方的英雄们聚会和交换消息, 所以会馆中常常挤满了各地的英雄和\n";
			long += "情报贩子, 同时, 也有许多英雄在这里互相锻炼(drill)或传授各种进阶\n";
			long += "的技能, 这些技能往往是一个英雄穷其一生钻研而来的, 如果你的资格够\n";
			long += "了, 而且也有其他的英雄愿意帮你, 你便可以在这里学到一些不一样的技\n";
			long += "能。你可以在这里锻炼(drill)、查看(list)能获得的进阶技能种类和询问\n";
			long += "锻练所需的代价(cost)。";
			break;
		case "barracks":
			short = "军营";
			long = "你走近一座军营的大门, 几个持矛的士兵正在木寨围成的拒马前站着,\n";
			long += "穿过大门, 你可以看见一片操场, 象征着军纪的军旗正在操场上飘扬着。\n";
			long += "操场边缘有一长列营房, 许多士兵正在靠营房的操场边活动操练。";
			break;
		case "stable":
			short = "马房";
			long = "你走进一间充满了草料香味的马厩\，到处可以看到一些壮硕高大强壮的\n";
			long += "马。整个马厩\被一条走道分开，走道两旁被分成一格格的，有的养了马，有\n";
			long += "的还空着。有几个工人正拉着堆着草料的车子，把草料铲进马面前的食槽里\n";
			long += "，马的喷气声和嘶鸣声此起彼落，这里的马儿都是来自远古流传下来的最强\n";
			long += "悍的马种，想要骑这些马儿的人势必首先要能自己去驯服他们，否则马儿是\n";
			long += "不会承认您是牠的主人的。";
			break;
		case "church":
			short = "教堂";
			long = "你走进一间幽静的教堂，从屋顶上的七彩琉璃窗透入的光芒中，你隐约\n";
			long += "看见有些牧师正在烛光环绕的祭坛前祈祷，他们专心与心中崇拜的神衹沟通，\n";
			long += "浑然不觉你的到来。";
			break;
		default:
			write("目前不提供 "+type+" 的特殊建筑物。\n");
			return 1;
	}
	str += sprintf("\tset(\"short\", %O);\n", short );
	str += sprintf("\tset(\"long\", @TEXT\n%s\nTEXT\n);\n", long );
	str += sprintf("\tset(\"type\", %O);\n", type);

	// refresh_data 格式：({ 制造者, 建造时间, 最后更新者, 最后更新时间 })
	str += sprintf("\tset(\"refresh_data\", ({ %O, %O, %O, %O }));\n",
		me->query("id"), ctime(time()), me->query("id"), ctime(time()) );

	str += sprintf("\tset(\"kingdom_id\", %O);\n", me->query("kingdom/id"));
	str += sprintf("\tset(\"exits\", %O);\n", ([ new_arg: base_name(env) ]));

	str += "\n\tsetup();\n";
	str += "\treplace_program("+upper_case(type)+");\n";
	str += "}\n";

	if( !write_file(new_file+".c", str, 1) ) {
		write("你没有建造房间的权利，请通知管理者。\n");
		return 1;
	}

	message_vision("$N找了一堆工人来在 "+capitalize(arg)+" 敲敲打打的，做出一间房间。\n", me);

	// 原房间也要开个方向
	env->add("exits",([ arg: new_file ]));
	if( !do_saveroom(env) ) {
		write("本房间没有存档的权利，请通知管理者。\n");
		return 1;
	}

	if( type=="board" ) {
		make_base_post_office(me->query("kingdom/id"), (string)num);
	}

	kingdom_data(me->query("kingdom/id"), "special_room", "add", type, new_file+".c");
	return 1;
}

private int make_base_post_office(string id, string file)
{
	string str;
	str = "// room : KINGDOM_DIR+id+/data/"+id+file + "\n";
	str += "// saveroom by "+ this_player()->query("id")+"    "+ctime(time())+"\n\n";
	str += @ROOM
#include <ansi.h>
inherit BULLETIN_BOARD;
void create()
{
	set_name("留言板", ({ "board" }) );
ROOM
	;
	str += sprintf("\tset(\"location\", %O);\n", KINGDOM_DIR+id+"/"+file);
	str += sprintf("\tset(\"board_id\", %O);\n", id+file);

	str += "\tsetup();\n";
	str += "\tset(\"capacity\", 70);\n";
	str += "\treplace_program(BULLETIN_BOARD);\n}";

	write_file( KINGDOM_DIR+id+"/data/"+id+file+".c", str , 1);
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : build <特殊建筑物类型> <方向>

这是国王与大臣用来建立特殊建筑物的指令，开发人可以向东西南北
上下六个方向中的任一个还没有出口的方向建立出口, 这时那个方向就会
多出所指定的建筑, 而开发者也会自动走过去, 并可以用下列指令设定新房间
的性质 :

        set_short       : 设定房间的名字, 就是你看到的第一行。
        set_long        : 设定房间的描述, 就是你看到的那堆描述。
        add_mob         : 为这个房间添加一些生物。
        add_desc        : 为这个房间加入一些可以看的描述。
        saveroom        : 当你把房间的一切都设定好了,记得一定要存起来。
        delete_room     : 删除多余的房间。

目前开放建立的特殊建筑如下 :
        名称    中文名称        需要房间数/费用 功用
*     tavern    旅馆            15/50000        可以招收一般mob, 住宿
*     shop      商店            15/50000        买卖物品，收税
*   herb_shop   药店            15/50000        卖药，收税
*     bank      银行            15/50000        存钱 -- 纯服务
*   post_office 邮局            15/50000        收发信件 -- 纯服务
*     board     留言版          15/50000        留言和讨论事务, 一国最多两个
      vote      投票所          15/50000        举行公投, 一国最多两个
*    smith      铁铺		20/50000	制造更好的武器
*    armory	防具铺		20/50000	制造更好的装备
      baker     面包店          20/80000        买卖、生产食物
?     stable    马厩            20/80000        提供马儿
*     barracks  军营            25/100000       招收军队，建立武力
*     prison    监狱            25/100000       专门关犯人用的
*    trainyard  训练场          30/250000       研发所有技能与开发新技能
*    gate       关卡            30/250000       详细功能请 help gate
*    prairie    畜牧场          35/300000       畜牧、买卖来赚钱
?  equipment    研发室          35/300000        研发武器、装备
*  magic_tower  法术研习营      35/300000       研发魔法技能与开发新法术
?    altar      祭坛            50/500000       增强武器防具的威力
   magic_circle 魔法阵          50/500000       召唤强力魔法生物，须研发配合
?  hero_guild   英雄会馆        50/500000       召唤强力自然生物，须研发配合

* : 已完成      ? : 可建，但功能尚未完全开放
其他相关资讯 :  set_short, set_long, add_mob, add_desc, rooms, areas
                special_rooms, saveroom, delete_room, linkroom

HELP
	);
	return 1;
}
