//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
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
        if( me->fighting() ) return notify_fail("������ս���С�\n");
        if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
        if( !arg ) return notify_fail("ָ���ʽ��set_tax <˰��>\n");
        value = to_int(arg);
        if( !intp(value) ) return notify_fail("˰������������̬��\n");
        if( value > 4 && value < 51 ) {
                kingdom_data(me->query("kingdom/id"),"data","set","tax",arg);
                CHANNEL_D->do_channel(me, "kingdom", sprintf("���ڴ�֣��������˰�ʵ���Ϊ%d%%��\n",value));
                 return 1; }
        else { return notify_fail("˰�������5%~50%��\n");}
        
        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ : set_tax <˰��>
                                                                                
�����趨����˰�ʵ�ָ�������󳼶������趨˰�ʣ��Ե��ڹ�����֧��
˰���� 5 % �� 50 % ֮�䣬����������̰�Ĺ����ǻ��������������ģ���
�����ƶ���˰��֮ǰ��Ҫ���˿����Ƶ�����׼����
                                                                                
���ѶϢ : kingdom_stat


HELP
        );
        return 1;
}
