//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/buy_kingdom.c

#include <ansi.h>

inherit ROOM;

int check_legal_id(string id);
int check_legal_name(string name);

void create()
{
	set("short", "圆顶建筑");
	set("long", @LONG
黑市，专门买国家的。

	使用格式：buy_kingdom <中文> <英文>

LONG
	);
	set("exits", ([
	"north":	"/d/gourd/gourd_recall"
	]));
	set("no_fight", 1);
	setup();
}

void init()
{
	add_action("do_buy", "buy_kingdom");
}

int do_buy(string arg)
{
	object me = this_player();
	string name, id;

        seteuid(getuid());
//	if(!me->query_temp("kingdom_build")) return notify_fail("暂时不开放建国了...不然人人都是国王 .. 有点诡异。\n");
	if( !arg ) return notify_fail("指令格式：buy_kingdom <中文> <英文>\n");
	if( me->query("kingdom") ) return notify_fail("建国必须平民才行。\n");
	if( sscanf(arg, "%s %s", name, id)!=2 )
		return notify_fail("指令格式：buy_kingdom <中文> <英文>\n");
//	if( !(me->can_afford(300000)) )
//		return notify_fail("你身上不够 30 万金币，无法建国 !!\n");
	if(!check_legal_name(name)||!check_legal_id(id)) return 1;
	if( check_kingdom(id) ) return notify_fail("此国号已经有国家正在使用，请换个英文 !!\n");
	if( file_size(DATA_DIR+"nuke/kingdom/"+id) == -2 )
		return notify_fail("此国号曾经出现在历史上，请换个英文。\n");
	mkdir(KINGDOM_DIR+id);
	mkdir(DATA_DIR+"nuke/kingdom/"+id);
	mkdir(DATA_DIR+"kingdom/"+id);
	create_kingdom(me, id, name);
	KINGDOM_D->creat_kingdom_data(id, name, me);

	shout(HIM"【建国资讯】"+HIY+"由"+me->name_id(1)+HIY+"所领导的国家 -- "+name+"("+id+")正式成立。\n"+NOR);
	write(HIM"【建国资讯】"+HIY+"由"+me->name_id(1)+HIY+"所领导的国家 -- "+name+"("+id+")正式成立。\n"+NOR);

//	me->pay_money(300000);
	me->save();

        return 1;
}

int check_legal_name(string name)
{
	int i;

	if(name=="") return 0;

	i = strlen(name);
        
	if( (strlen(name) < 4) || (strlen(name) > 12 ) ) {
		write("国家中文名字必须是 2 到 6 个中文字。\n");
		return 0;
	}
	while(i--) {
		if( name[i]<='' ) {
			write("国家中文名字不能用控制字元。\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("请您用“中文”取国家名字。\n");
			return 0;
		}
	}
	return 1;
}

int check_legal_id(string id)
{
	int i;

	if(id=="") return 0;
	i = strlen(id);

	if( i < 3 || i > 15 ) {
		write("国家英文名字必须是 3 到 15 个英文字母。\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z')
		if( id[i] != '_') {
			write("你只能使用英文或者 _ 的符号来当作国家的英文。\n");
			return 0;
		}

	return 1;
}
