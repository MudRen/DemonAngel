//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/people.c
// by amgbell @DA

//#pragma optimize
//#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string *list;
        int i;

        list = people_data(me->query("kingdom/id"),"query_all");

        for (i=0;i<sizeof(list) ;i++ )
        {
                write(list[i]+"\n");
        }

        return 1;
}

int help(object me)
{
        write(@HELP

ָ���ʽ��

��ָ���������֪����������Щ�ˡ�



HELP
        );
        return 1;
}
