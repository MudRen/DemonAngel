//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/king/add_help.c
// by amgbell @ DA

//#pragma optimize
//#pragma save_binary
inherit F_CLEAN_UP;

void do_write(object me,string str);

int main(object me, string arg)
{
        me->edit( (: call_other, __FILE__, "do_write", me :) );
        return 1;
}

void do_write(object me,string str)
{
        string *str_arg;

        str = ansi_color( str );

        if( strlen(str) > 8000 ) {
                write("��Ĳ���̫���ˡ�\n");
                return;
        }
        str_arg = explode(str, "\n");

        if( sizeof(str_arg) > 50 ) {
                write("���������ʮ�����ڡ�\n");
                return;
        }
        str = kill_all_bug(str);

        write_file(KINGDOM_DIR+me->query("kingdom/id")+"/data/introduce.txt",str);
//        write(("/open/"+me->query("kingdom/id")+"/introduce.txt"));
        write("ok!\n");

}
int help()
{
        write(@HELP

ָ���ʽ : add_help
 
���ǹ��������趨���Ҽ���ָ�

���������Ѷ :  set_short, set_long, add_mob, add_desc, rooms, areas
                special_rooms, saveroom

HELP
        );
        return 1;
}
