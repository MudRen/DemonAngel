//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/abdicate.c
// appoint by bor @RG
// modify by amgbell@DA from appoint.c

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        seteuid(getuid());
        if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
        if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
        if( !arg ) return notify_fail("指令格式 : abdicate <大臣> \n");
        if( !me->query("kingdom/id") ) return 0;
        if( !(ob = present(arg, environment(me)) )) return notify_fail("你想让位给谁？\n");
        if( !userp(ob) ) return notify_fail(ob->name() + "不是玩家身份。\n");

        if( ob == me ) return notify_fail("你不能让位给自己。\n");
        if( !ob->query("kingdom/id")
        || ob->query("kingdom/id") != me->query("kingdom/id") )
                return notify_fail("你想让外国人当国王？\n");

        if( !ob->query("kingdom/minister") ) return notify_fail("他不是大臣 !!\n");

        if( !kingdom_data(me->query("kingdom/id"), "power", "sub", "king", me->query("id")) ) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
        if( !kingdom_data(me->query("kingdom/id"), "power", "sub", "minister", ob->query("id")) ) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
        if( !kingdom_data(me->query("kingdom/id"), "power", "set", "king", ob->query("id")) ) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");

        if( !kingdom_data(me->query("kingdom/id"), "power", "add", "minister", me->query("id")) ) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
        
        ob->set("kingdom/king", ob->query("id")); //受位者当king
        ob->delete("kingdom/min");

        me->delete("kingdom/king");
        me->set("kingdom/minister", ob->query("id"));//自己变min
        
        ob->set("home",KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c");
        // 设定大臣基本权力
        ob->add_path( ({"/cmds/min/","/cmds/king/"}) );
        me->sub_path( ({"/cmds/king/"}) );
        ob->save();
        me->save();	// by bor@DA, 2/26 2003
        CHANNEL_D->do_channel(me, "kingdom", sprintf("我郑重宣布将王位让给"+ob->name_id(1)+"。"));
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : abdicate <某位大臣>

这是国王将王位让给某位大臣的指令, 国王使用这个指令会将王位传给指定
的大臣, 而自己转任王国的大臣。由于担任国王是一个艰钜的责任, 所以在
你传位前, 最好仔细考虑过, 并且征求对方的同意, 以免引发国家内乱。

相关讯息 : appoint, fire
HELP
        );
        return 1;
}
