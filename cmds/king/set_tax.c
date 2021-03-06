//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/set_tax.c
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
        if( !arg ) return notify_fail("指令格式：set_tax <税率>\n");
        value = to_int(arg);
        if( !intp(value) ) return notify_fail("税率请用整数型态。\n");
        if( value > 4 && value < 51 ) {
                kingdom_data(me->query("kingdom/id"),"data","set","tax",arg);
                CHANNEL_D->do_channel(me, "kingdom", sprintf("我在此郑重宣布将税率调整为%d%%。\n",value));
                 return 1; }
        else { return notify_fail("税率请介于5%~50%。\n");}
        
        return 1;
}

int help(object me)
{
        write(@HELP

指令格式 : set_tax <税率>
                                                                                
这是设定王国税率的指令，国王与大臣都可以设定税率，以调节国库收支。
税率在 5 % 到 50 % 之间，狂征暴敛的贪心国王是会遭受人民唾弃的，所
以在制定高税率之前，要有人口外移的心理准备。
                                                                                
相关讯息 : kingdom_stat


HELP
        );
        return 1;
}
