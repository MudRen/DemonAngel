//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
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

指令格式：

此指令可以让你知道国家有哪些人。



HELP
        );
        return 1;
}
