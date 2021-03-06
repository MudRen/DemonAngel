//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/pool_gold.c
// by smallpen

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int value;

        seteuid(getuid(me));
        if( me->fighting() ) return notify_fail("你正在战斗中。\n");
        if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
        if( !arg ) return notify_fail("指令格式：pool_gold <数目>\n");
        value = to_int(arg);
        if( !intp(value) ) return notify_fail("数目请用整数型态。\n");
        if( value >me->query("gold")) return notify_fail("你没有这么多钱。\n");
        if( value <50000 ) return notify_fail("请一次投入50000枚金币以上。\n");
        kingdom_data(me->query("kingdom/id"),"data","add","gold",value);
        me->add("gold",-value);
        CHANNEL_D->do_channel(me, "kingdom", sprintf("我又在国库中存了 %d 枚金币，我国的国库存底已经增到 %d 枚金币了。\n",value,kingdom_data(me->query("kingdom/id"),"data","query_par","gold")));
        log_file("aaa", sprintf("pool_gold(object):%O\n", call_stack(1) ) );
        log_file("aaa", sprintf("pool_gold(function):%O\n", call_stack(2) ) );
        log_file("aaa", sprintf("pool_gold(origin)):%O\n", call_stack(3) ) );
        return 1;
}

int help(object me)
{
        write(@HELP

指令格式 : pool_gold <数目>

国王或大臣可以将自己身上的金钱投入国库中。 
                                                                                
相关讯息 : set_tax


HELP
        );
        return 1;
}
