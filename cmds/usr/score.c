//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// score.c
//modify by amgbell@DA

#include <ansi.h>
#include <combat.h>

inherit F_CLEAN_UP;

void create() { seteuid(ROOT_UID); }

int main(object me, string arg)
{
        object ob;
        string line, tmp, *list;
        int i;

        if(!arg) ob = me;
        else {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("你要察看谁的状态？\n");
                if (!wizardp(me) && !ob->accept_info(me, "score") )
                        return notify_fail("只有巫师能察看别人的状态。\n");
        }

        seteuid(getuid(ob));

        line = sprintf( BOLD "%s" NOR "%s\n\n", RANK_D->query_rank(ob), ob->short(1) );

        line = sprintf("%s 你是一%s第%s级的%s%s。\n\n", line,
                (tmp = ob->query("unit")) ? tmp : "个",
                chinese_number(ob->query("level")),
                to_chinese(ob->query("race")),
                (tmp = ob->query("gender")) ? to_chinese(tmp) : "" );

        line = sprintf(
                "%s 力量 [%2d/%2d]  智慧 [%2d/%2d]  敏捷 [%2d/%2d]\n"
                  " 毅力 [%2d/%2d]  体质 [%2d/%2d]  运气 [%2d/%2d]\n\n", line,
                ob->query_str(), ob->query("str"),
                ob->query_int(), ob->query("int"),
                ob->query_dex(), ob->query("dex"),
                ob->query_sta(), ob->query("sta"),
                ob->query_con(), ob->query("con"),
                ob->query_kar(), ob->query("kar"));

// 身体状态         
	if( sizeof(ob->all_condition()) > 0 ) {
		tmp = "";
		for(i=0; i<sizeof(ob->all_condition()); i++) {
			tmp += to_chinese(keys(ob->all_condition())[i]) + ", ";
		}
		line += sprintf(" 身体状况 : %s\n\n", tmp);
		reset_eval_cost();
	}

// 通缉
	if( sizeof(list = ob->query("arrest"))>0 ) {
		tmp = "";
		for(i=0; i<sizeof(list); i++)
			tmp += list[i] + ", ";
		line += sprintf(" 通缉状况 : %s\n\n", tmp);
		reset_eval_cost();
	}

        line += sprintf(" <体力> %3d/%3d (%3d%%)      " , 
                ob->query_hp(),ob->query_base_hp(),
                ob->query_hp()*100/ob->query_base_hp());

        line += sprintf("<法力> %3d/%3d (%3d%%)\n\n\n" , 
                ob->query_mp(),ob->query_base_mp(),
                ob->query_mp()*100/ob->query_base_mp());

// 武器
	line += sprintf(" 右手武器等级 %4d    最大伤害力 %4d    最小伤害力 %4d\n\n",
		ob->query_wl(), ob->query_Mh(), ob->query_mh());

// 防护
	line += sprintf(" 防御能力等级 %4d    额外防御力 %4d    战斗经验 %10d\n\n",
		ob->query_ac(), ob->query_db(), ob->query("exp") );

        line += sprintf(" 身上带着 %d 枚金币, 银行尚有 %d 枚金币",
                 ob->query("gold"), ob->query("bank_gold") );

        write(line+"\n");
        return 1;
}


int help(object me)
{
        write(@HELP
指令格式 : score
           score <对象名称>                   (巫师专用)
 
这个指令可以显示你(你)或指定对象(含怪物)的基本资料。
基本资料的设定请参阅 'help setup'。
 
其他相关指令：hp
HELP
    );
    return 1;
}
