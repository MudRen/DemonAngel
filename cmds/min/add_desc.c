//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/add_desc.c
// by smallpen

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object env;
        string *desc,str,item;
        mapping room_item;
        int i;
        
        seteuid(getuid(me));
        env = environment(me);
        //��ѯ���з����ϸ������
        if(!arg) {
                
                if(!mapp(room_item=env->query("item_desc")) ) return notify_fail("Ŀǰ����û���κ�ϸ������, ��Ҫ�﷿��������ϸ������ ?\n");
                if(env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("���ﲻ�ǹ��������!\n");
                desc = keys(room_item);
                str = "����� item_desc �У�"HIY;
                for(i=0;i<sizeof(desc);i++) {
                        if(i == (sizeof(desc)-1)) {
                                str += desc[i] + "��\n"NOR;
                        } else {
                                str += desc[i] + "��";
                        }
                }
                me->start_more(str);
                return 1;
        }
        //����ϸ������
        if( sscanf(arg,"-a %s",item) == 1) {
                if(!(env->query("item_desc/"+item)) ) {
                        //�鿴��û���ظ���item_desc
                        me->edit( (: call_other, __FILE__, "do_change", me,item :) );
                } else return notify_fail("���� item_desc �Ѿ����ڴ˼䷿����!\n");
        } else if( sscanf(arg,"-d %s",item) == 1) {
                //ɾ���ض���item_desc
                if( env->query("item_desc/"+item) ) {
                        env->delete("item_desc/"+item);
                        do_saveroom(env);
                        write("���� item_desc �Ѿ�ɾ�������!\n");
                        return 1;
                } else return notify_fail("û�д��� item_desc ���ڴ˼䷿����!\n");
        } else return notify_fail("ָ���ʽ������ο�Help��˵��!\n");
        
        return 1;
}

void do_change(object me, string items, string str)
{
        string *str_arg;

        str = ansi_color( str );

        if( strlen(str) > 8000 ) {
                write("��Ĳ���̫���ˡ�\n");
                return;
        }
        str_arg = explode(str, "\n");

        if( sizeof(str_arg) > 10 ) {
                write("�������ʮ�����ڡ�\n");
                return;
        }
        str = kill_all_bug(str);
        environment(me)->add("item_desc", ([items:str]));
        write("ϸ�������������!\n");
        do_saveroom(environment(me));
        return ;
}

int help(object me)
{
        write(@HELP

ָ���ʽ : add_desc -a <�ض���>         : ����һ������
           add_desc -d <�ض���>         : ȥ��һ������
           add_desc                     : ��ѯ���е�����
                                                                                
���ǹ��������������������ָ��, ���ָ������Ϊ��������ϸ����������
�������� look <�ض���>ʱ���������������ָ��ֻ�Ǹı���������, ����
���һ�ж�Ū����, Ҫ�ǵ��� saveroom �ѷ����������
                                                                                
add_desc ���ṩһ���༭��, �������������������ȥ, ��Ȼ, ��Ҳ��
���� NCSA �ṩ�� copy - paste ���������ƵĹ��������Ѿ���õ�������
�������༭���Ժ� <enter> �ٰ� '.' �Ϳ�����������ˡ���ɺ����
���� look <�ض���> ��������ɵĽ����
                                                                                
ע�����
        �����ʹ�� " �˷��ţ�������ܻ���ɸø��д���ѶϢ��
                                                                                
                                                                                
���������Ѷ :  set_short, set_long, add_mob, add_desc, rooms, areas
                special_rooms, saveroom

HELP
        );
        return 1;
}
