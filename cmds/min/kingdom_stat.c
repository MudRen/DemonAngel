//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/kingdom_stat.c
// by bor @RG Last Modify by smallpen

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int i, flag,j=0;
        string id,house, str ="", *list, *sp_room_list=({"board","shop","bank","post_office","trainyard","magic_tower","smith","armory","stable"});
        mapping sp_room;

        seteuid(getuid(me));
        if( !id = me->query("kingdom/id") ) return notify_fail("你不能查寻该国资料或是不能使用该指令。\n");

        str += full_kingdom(id) +"国家资讯如下：\n";
        str +="----------------------------------------------------------------------\n";
        str += sprintf("现任国王：\t%s\n", kingdom_data(id, "power", "query_all", "king")[0] );
        str += "辅政大臣：\n";

        if(!list = kingdom_data(id, "power", "query_all", "minister"))
                str += "\t\t贵国尚未任命辅政大臣。\n";
        else {
                for(i=0; i<sizeof(list); i++ ) {
                        str += sprintf("\t\t%s\n", list[i] );
                }
                str += sprintf("\t共 %d %s\n", sizeof(list), "位" );
        }

	str += sprintf("国家状态 :\t%s\n", kingdom_data(id, "open", "check")>0?"已开放":"" );

        str += "通缉要犯：\n";
        if(list = kingdom_data(id, "arrest", "query_all")) {
                for(i=0; i<sizeof(list); i++ ) {
                        str += sprintf("\t%s,\n", list[i] );
                }
                str += sprintf("\t共 %d %s\n", sizeof(list), "位" );
        }

        str += "目前人民：\t共 " +kingdom_data(id, "data", "query_par", "people")+ " 人\n";
        str += "国库存底：\t金币 "+kingdom_data(id, "data", "query_par", "gold")+ " 枚      税率 : " + kingdom_data(id, "data", "query_par", "tax") +" %\n";

        str += sprintf("国土面积：\t共 %3d 间房间   房间流水号：%4d   房间额度：%3d\n",
                kingdom_data(id, "data", "query_par", "room"),
                kingdom_data(id, "data", "query_par", "room_num"),
                kingdom_data(id, "data", "query_par", "max_room"));

        str += sprintf("生物数量：\t共 %3d 只生物   生物流水号：%4d   生物额度：%3d\n",
                kingdom_data(id, "data", "query_par", "npc"),
                kingdom_data(id, "data", "query_par", "npc_num"),
                kingdom_data(id, "data", "query_par", "max_npc"));

        str += sprintf("武器数量：\t共 %3d 件       武器流水号：%4d   武器额度：%3d\n",
                kingdom_data(id, "data", "query_par", "weapon"),
                kingdom_data(id, "data", "query_par", "weapon_num"),
                kingdom_data(id, "data", "query_par", "max_weapon"));
        
        str += sprintf("防具数量：\t共 %3d 件       防具流水号：%4d   防具额度：%3d\n",
                kingdom_data(id, "data", "query_par", "armory"),
                kingdom_data(id, "data", "query_par", "armory_num"),
                kingdom_data(id, "data", "query_par", "max_armory"));

        str += sprintf("任务品数量：\t共 %3d 件       任务品流水号：%3d  任务品额度：%3d\n",
                kingdom_data(id, "data", "query_par", "item"),
                kingdom_data(id, "data", "query_par", "item_num"),
                kingdom_data(id, "data", "query_par", "max_item"));

        str += "特殊建筑：\n";
        if( mapp(sp_room = kingdom_data(id, "special_room", "query")) ) {
                for( i=0; i<sizeof(sp_room_list); i++ ) {
                        if( sp_room[sp_room_list[i]] && list = keys(sp_room[sp_room_list[i]]) ) {
                            
                        str += sprintf("\t  %s：共 %d 座,\n",sp_room_list[i], sizeof(list));
                                flag += sizeof(list);
                        }
                }
                if( flag>0 ) str += sprintf("\n\t\t总共有 %d 座特殊建筑物。\n", flag);
        }
        str +="-----------------------------------------------------------------------";
        flag = 0;
        sp_room = 0;
        me->start_more(str);
        return 1;
}

int help(object me)
{
        write(@HELP

指令格式 : kingdom_stat

这是国王与大臣用来了解国家目前发展情形的工具。

相关资讯 :

HELP
        );
        return 1;
}
