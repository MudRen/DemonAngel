//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/ally.c
// by smallpen

#pragma optimize
#pragma save_binary
#include <ansi.h>
string show_ally(object me,string id);
int do_time(object me);
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *ob,*ob1;
        string cancel,country;
        int flag,i,j;
        seteuid(getuid());
        if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
        if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
        if( !arg ) {
                show_ally(me,me->query("kingdom/id"));
                return 1;       
        }
        
        if( sscanf(arg, "%s with %s", cancel, country)!=2 ) {
                if( sscanf(arg, "with %s",country)!=1) {
                        return notify_fail("ָ���ʽ : ally <cancel> with ĳ���� \n");}
                else {  
                        if(!check_kingdom(country))  return notify_fail("û���������\n");
                        flag=1;}
                }
        else {
                if(cancel!="cancel")    return notify_fail("ָ���ʽ : ally <cancel> with ĳ���� \n");
                if(!check_kingdom(country))  return notify_fail("û���������\n");
                flag=0;
        }
//����          
                
        if( flag==1) {
                if(country==me->query("kingdom/id")) return notify_fail("�㲻�ܸ��Լ����ˡ�\n");
                if(kingdom_data(me->query("kingdom/id"), "ally","check",country)) return notify_fail("�˹��Ѿ������ͬ���ˡ�\n");
                ob = users();
                for(i=0;i<sizeof(ob); i++) {
                        if(country==ob[i]->query("kingdom/id")) {
                                if(ob[i]->query("kingdom/minister") || ob[i]->query("kingdom/king")) {
                                        ob1 = users();
                                        for(j=0;j<sizeof(ob1);j++) {
                                                if(ob1[i]->query_temp("ally") == me->query("kingdom/id")) {
                                                        if(!kingdom_data(me->query("kingdom/id"), "ally", "add",country)) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                                                        if(!kingdom_data(country,"ally","add",me->query("kingdom/id"))) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                                                        write(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "��ʽ�������������"+to_chinese_kingdom(country)  + "���ͬ��Э�顣\n"+NOR);
                                                        shout(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "��ʽ�������������"+to_chinese_kingdom(country)  + "���ͬ��Э�顣\n"+NOR);
                                                        ob1[i]->delete_temp("ally");
                                                        ob1[i]->save();
                                                        return 1;
                                                                                                }
                                                                }       
                                        write(HIY""+"�������"+to_chinese_kingdom(ob[i]->query("kingdom/id"))+"��ͬ�����顣\n"+NOR);
                                        tell_object(ob[i], full_kingdom(me->query("kingdom/id"))+"��"+ me->query("name") + "Ҫ��͹������ͬ�˹�ϵ��\n");
                                        //ob[i]->command(kingdom ��ʽҪ�����ҹ�����ͬ�˹�ϵ��) ;
                                        me->set_temp("ally",ob[i]->query("kingdom/id"));
                                        call_out("do_time_check",10,me);
                                        return 1;
                                                                                }
                                
                                                        }
                                        }
                return notify_fail("�Է�û�й��������ϡ�\n");
                }
        

//���ͬ��      
if(flag==0) {
        if(country==me->query("kingdom/id")) return notify_fail("�㲻�ܸ��Լ�������ˡ�\n");
                if(!kingdom_data(me->query("kingdom/id"), "ally","check",country)) return notify_fail("�˹���δ�͹��ͬ�ˡ�\n");
                if(!kingdom_data(me->query("kingdom/id"), "ally", "sub",country)) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                if(!kingdom_data(country,"ally","sub",me->query("kingdom/id"))) return notify_fail("������������û�취���Է�д�������ڡ�\n");
                        write(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "��ʽ���������������"+to_chinese_kingdom(country)  + "��ͬ��Э�顣\n"+NOR);
                        shout(HIY""+to_chinese_kingdom(me->query("kingdom/id")) + "��ʽ���������������"+to_chinese_kingdom(country)  + "��ͬ��Э�顣\n"+NOR);
                        return 1;
                        
}
}
string show_ally(object me,string id)
{
        string *list,str="";
        int i;
        str += sprintf("Ŀǰ%s��ͬ�˹��У�\n\n",to_chinese_kingdom(id) );
                if(!list = kingdom_data(id,"ally","query_all"))
                        str += "�������ͬ�˹���\n\n";
                else {
                        for(i=0; i<sizeof(list);i++) {
                                str += sprintf("%s\n",full_kingdom(list[i]));
                        }
                        str += sprintf("\n�� %d ����\n\n",sizeof(list));
                }
                return me->start_more(str);
                
}       

int do_time_check(object me)
{
        if(!me->query_temp("ally")) remove_call_out(do_time(me));
        else call_out("do_time", 6, me);
        return 1;
}

int do_time(object me)
{
        if( me->query_temp("ally") ) {
                me->delete_temp("ally");
                write("�����ӶԷ��������������ˡ�\n");
        }
        return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : ally with <����>             :  �ͳ�����Э��
           ally cancel with <����>      :  ��ֹ���˹�ϵ
           ally                         :  �쿴Ŀǰͬ�˵Ĺ��ҡ�
                                                                                
���ָ����Ժ��������ҽ��ˡ�����ͨ���Ǳ�ʾ�����Ѻ�֮��, Ҳͬʱ����
�˻����ַ���Э��, �����ڶ�ͬ�˹���ս֮ǰ, һ��Ҫ�Ƚ��ͬ�˹�ϵ����
���������Ժ�, ˫��������Ϳ��Ի���ͨ���ؿ�������, ����֮��, ��û��
����Ȩ�������ϵ��
                                                                                
����ʱ, ��Ҫ�����󳼵�ͬ��, ����ֹ����ʱֻҪƬ������������Ч�ˡ�

���ѶϢ : declare

HELP
        );
        return 1;
}       
