//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
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
        if( me->fighting() ) return notify_fail("������ս���С�\n");
        if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
        if( !arg ) return notify_fail("ָ���ʽ��pool_gold <��Ŀ>\n");
        value = to_int(arg);
        if( !intp(value) ) return notify_fail("��Ŀ����������̬��\n");
        if( value >me->query("gold")) return notify_fail("��û����ô��Ǯ��\n");
        if( value <50000 ) return notify_fail("��һ��Ͷ��50000ö������ϡ�\n");
        kingdom_data(me->query("kingdom/id"),"data","add","gold",value);
        me->add("gold",-value);
        CHANNEL_D->do_channel(me, "kingdom", sprintf("�����ڹ����д��� %d ö��ң��ҹ��Ĺ������Ѿ����� %d ö����ˡ�\n",value,kingdom_data(me->query("kingdom/id"),"data","query_par","gold")));
        log_file("aaa", sprintf("pool_gold(object):%O\n", call_stack(1) ) );
        log_file("aaa", sprintf("pool_gold(function):%O\n", call_stack(2) ) );
        log_file("aaa", sprintf("pool_gold(origin)):%O\n", call_stack(3) ) );
        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ : pool_gold <��Ŀ>

������󳼿��Խ��Լ����ϵĽ�ǮͶ������С� 
                                                                                
���ѶϢ : set_tax


HELP
        );
        return 1;
}
