//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
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
        if( !id = me->query("kingdom/id") ) return notify_fail("�㲻�ܲ�Ѱ�ù����ϻ��ǲ���ʹ�ø�ָ�\n");

        str += full_kingdom(id) +"������Ѷ���£�\n";
        str +="----------------------------------------------------------------------\n";
        str += sprintf("���ι�����\t%s\n", kingdom_data(id, "power", "query_all", "king")[0] );
        str += "�����󳼣�\n";

        if(!list = kingdom_data(id, "power", "query_all", "minister"))
                str += "\t\t�����δ���������󳼡�\n";
        else {
                for(i=0; i<sizeof(list); i++ ) {
                        str += sprintf("\t\t%s\n", list[i] );
                }
                str += sprintf("\t�� %d %s\n", sizeof(list), "λ" );
        }

	str += sprintf("����״̬ :\t%s\n", kingdom_data(id, "open", "check")>0?"�ѿ���":"" );

        str += "ͨ��Ҫ����\n";
        if(list = kingdom_data(id, "arrest", "query_all")) {
                for(i=0; i<sizeof(list); i++ ) {
                        str += sprintf("\t%s,\n", list[i] );
                }
                str += sprintf("\t�� %d %s\n", sizeof(list), "λ" );
        }

        str += "Ŀǰ����\t�� " +kingdom_data(id, "data", "query_par", "people")+ " ��\n";
        str += "�����ף�\t��� "+kingdom_data(id, "data", "query_par", "gold")+ " ö      ˰�� : " + kingdom_data(id, "data", "query_par", "tax") +" %\n";

        str += sprintf("���������\t�� %3d �䷿��   ������ˮ�ţ�%4d   �����ȣ�%3d\n",
                kingdom_data(id, "data", "query_par", "room"),
                kingdom_data(id, "data", "query_par", "room_num"),
                kingdom_data(id, "data", "query_par", "max_room"));

        str += sprintf("����������\t�� %3d ֻ����   ������ˮ�ţ�%4d   �����ȣ�%3d\n",
                kingdom_data(id, "data", "query_par", "npc"),
                kingdom_data(id, "data", "query_par", "npc_num"),
                kingdom_data(id, "data", "query_par", "max_npc"));

        str += sprintf("����������\t�� %3d ��       ������ˮ�ţ�%4d   ������ȣ�%3d\n",
                kingdom_data(id, "data", "query_par", "weapon"),
                kingdom_data(id, "data", "query_par", "weapon_num"),
                kingdom_data(id, "data", "query_par", "max_weapon"));
        
        str += sprintf("����������\t�� %3d ��       ������ˮ�ţ�%4d   ���߶�ȣ�%3d\n",
                kingdom_data(id, "data", "query_par", "armory"),
                kingdom_data(id, "data", "query_par", "armory_num"),
                kingdom_data(id, "data", "query_par", "max_armory"));

        str += sprintf("����Ʒ������\t�� %3d ��       ����Ʒ��ˮ�ţ�%3d  ����Ʒ��ȣ�%3d\n",
                kingdom_data(id, "data", "query_par", "item"),
                kingdom_data(id, "data", "query_par", "item_num"),
                kingdom_data(id, "data", "query_par", "max_item"));

        str += "���⽨����\n";
        if( mapp(sp_room = kingdom_data(id, "special_room", "query")) ) {
                for( i=0; i<sizeof(sp_room_list); i++ ) {
                        if( sp_room[sp_room_list[i]] && list = keys(sp_room[sp_room_list[i]]) ) {
                            
                        str += sprintf("\t  %s���� %d ��,\n",sp_room_list[i], sizeof(list));
                                flag += sizeof(list);
                        }
                }
                if( flag>0 ) str += sprintf("\n\t\t�ܹ��� %d �����⽨���\n", flag);
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

ָ���ʽ : kingdom_stat

���ǹ�����������˽����Ŀǰ��չ���εĹ��ߡ�

�����Ѷ :

HELP
        );
        return 1;
}
