//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/swer.c
// by smallpen

#pragma optimize
#pragma save_binary
#include <ansi.h>
inherit ROOM;
int do_adopt_check(object me,object ob,string become1);
int do_swear_check(object me,object ob);
int do_show_family(object me);
void init()
{
        add_action("do_adopt", "adopt");
        add_action("do_swear","swear");
}

int do_adopt(string arg)
{
        string who="",word="����",sex="��",word1="��Ů��",sex1="��",name;
        string *parent,*child,*brother;
        int i;
        object me = this_player(),ob;
        
        seteuid(getuid());
        
        parent = me->query("parent");
        child = me->query("child");
        brother = me->query("brother");
        if( me->is_busy()) return notify_fail("��������æ�š�\n");
        if( me->is_fight() ) return notify_fail("��������ս���С�\n");
        if( !arg ) {
                do_show_family(me);
                return 1;
        } 
        if( sscanf(arg, "%s as %s" , name,who)!=2 ) return notify_fail("��ʽ : adopt <����> as <child/parent>��\n");
        if( !(ob = present(name, environment(me)) )) return notify_fail("�Է��������ֳ�ࡣ�\n");
        if( !(who=="child" || who=="parent")) return notify_fail("��ʽ : adopt <����> as <child/parent>��\n"); 
        if( me->query("id")==ob->query("lover") ) return notify_fail("���Ѿ������������ˡ�\n");
        for(i=0;i<sizeof(parent);i++) {
                if(ob->query("id")==parent[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
        for(i=0;i<sizeof(child);i++) {
                if(ob->query("id")==child[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
        for(i=0;i<sizeof(brother);i++) {
                if(ob->query("id")==brother[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
        if( me->query("gender")=="Ů��") sex="��";
        if( ob->query("gender")=="����") {
                sex1="��";
                word ="�ɰ�";
                word1="�ɶ���";}
        if( who=="child") {
                write(sex+"������"+ob->query("name")+"��"+word1+"��\n");
                tell_object(ob,me->query("name")+"������"+sex1+"��"+word1+"��\n");
                tell_room(environment(me),sex+"������"+ob->query("name")+"��"+word1+"��\n",({me,ob}));
                me->set_temp("adopt",ob);
                me->set_temp("become","parent");
                if(me!=ob->query_temp("adopt")) call_out("do_adopt_check",10,me,ob,word1);
        }
        if( who=="parent") {
                write(sex+"�����"+ob->query("name")+"��"+word+"��\n");
                tell_object(ob,me->query("name")+"�����"+sex1+"��"+word+"��\n");
                tell_room(environment(me),sex+"�����"+ob->query("name")+"��"+word+"��\n",({me,ob}));
                me->set_temp("adopt",ob);
                me->set_temp("become","child");
                if(me!=ob->query_temp("adopt")) call_out("do_adopt_check",10,me,ob,word);
        }
        
                return 1;
}

int do_swear(string arg)
{
        string who="",sex="��",sex1="��";
        string *parent,*child,*brother;
        int i;
        object me = this_player(),ob;
        
        seteuid(getuid());
        
        parent = me->query("parent");
        child = me->query("child");
        brother = me->query("brother");
        if( me->is_busy()) return notify_fail("��������æ�š�\n");
        if( me->is_fight() ) return notify_fail("��������ս���С�\n");
        if( !arg ) {
                do_show_family(me);
                return 1;
        } 
        if(sscanf(arg,"%s",who)==1) {
                if( !(ob = present(who, environment(me)) )) return notify_fail("�Է��������ֳ�ࡣ�\n");
                if( me->query("id")==ob->query("lover") ) return notify_fail("���Ѿ������������ˡ�\n");
                for(i=0;i<sizeof(parent);i++) {
                        if(ob->query("id")==parent[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
                for(i=0;i<sizeof(child);i++) {
                        if(ob->query("id")==child[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
                for(i=0;i<sizeof(brother);i++) {
                        if(ob->query("id")==brother[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
                if( me->query("gender")=="Ů��") sex="��";
                if( ob->query("gender")=="����") sex1="��";
                //�ֵ�
                if( me->query("gender")=="����" && ob->query("gender")=="����") {
                        write(sex+"������"+ob->query("name")+"���Ϊ�ֵܡ�\n");
                        tell_object(ob,me->query("name")+"������"+sex1+"���Ϊ�ֵܡ�\n");
                        tell_room(environment(me),sex+"������"+ob->query("name")+"���Ϊ�ֵܡ�\n",({me,ob}));
                        me->set_temp("swear",ob);
                        me->set_temp("become","mm");
                        if(me!=ob->query_temp("swear")) call_out("do_swear_check",10,me,ob);
                }
                //����
                if(  (me->query("gender")=="����" && ob->query("gender")=="Ů��") ||  (me->query("gender")=="Ů��" && ob->query("gender")=="����")) {
                        write(sex+"������"+ob->query("name")+"���Ϊ���á�\n");
                        tell_object(ob,me->query("name")+"������"+sex1+"���Ϊ���á�\n");
                        tell_room(environment(me),sex+"������"+ob->query("name")+"���Ϊ���á�\n",({me,ob}));
                        me->set_temp("swear",ob);
                        me->set_temp("become","mf");
                        if(me!=ob->query_temp("swear")) call_out("do_swear_check",10,me,ob);
                        }
                //���
                if(  me->query("gender")=="Ů��" && ob->query("gender")=="Ů��")  {
                        write(sex+"������"+ob->query("name")+"���Ϊ��á�\n");
                        tell_object(ob,me->query("name")+"������"+sex1+"���Ϊ��á�\n");
                        tell_room(environment(me),sex+"������"+ob->query("name")+"���Ϊ��á�\n",({me,ob}));
                        me->set_temp("swear",ob);
                        me->set_temp("become","ff");
                        if(me!=ob->query_temp("swear")) call_out("do_swear_check",10,me,ob);
                }
        }
        else {
                return notify_fail("��ʽ : swear <����>��\n");
        }
        return 1;
}

int do_adopt_check(object me,object ob,string become1)
{
        string *parent,*child;
        if( me==ob->query_temp("adopt") ) {
                
                if( me->query_temp("become")=="parent" && ob->query_temp("become")=="child")  {
                //����������    
                
                me->delete_temp("adopt");
                ob->delete_temp("adopt");
                me->delete_temp("become");
                ob->delete_temp("become");
                if( arrayp(child = me->query("child")) ) {
                        if( member_array(ob->query("id"), child)==-1 )
                                me->set("child", child + ({ob->query("id")}) );
                } else me->set("child", ({ob->query("id")}) );
                
                if( arrayp(parent = ob->query("parent")) ) {
                        if( member_array(me->query("id"), parent)==-1 )
                                ob->set("parent", parent + ({me->query("id")}) );
                } else ob->set("parent", ({me->query("id")}) );
                
                CHANNEL_D->do_channel(me, "chat",sprintf("�Ҿ�����%s��%s��", ob->name_id(1), become1));
                }
                if( me->query_temp("become")=="child" && ob->query_temp("become")=="parent")  {
                //����������    
                me->delete_temp("adopt");
                ob->delete_temp("adopt");
                me->delete_temp("become");
                ob->delete_temp("become");
                if( arrayp(parent = me->query("parent")) ) {
                        if( member_array(ob->query("id"), parent)==-1 )
                                me->set("parent", parent + ({ob->query("id")}) );
                } else me->set("parent", ({ob->query("id")}) );
                
                if( arrayp(child = ob->query("child")) ) {
                        if( member_array(me->query("id"), child)==-1 )
                                ob->set("child", child + ({me->query("id")}) );
                } else ob->set("child", ({me->query("id")}) );
                CHANNEL_D->do_channel(ob, "chat",sprintf("�Ҿ�����%s��%s��", me->name_id(1), become1));
                }
                
                
}
        else {
                write("����"+ob->query("name")+"��������ĺ���...\n");
                tell_object(ob,"����һ��ʱ��ĳ�Ĭ�������"+me->short(1)+"�ĺ��⣡\n");
                me->delete_temp("adopt");
                ob->delete_temp("adopt");
                me->delete_temp("become");
                ob->delete_temp("become");
                return 1;}
}

int do_swear_check(object me,object ob)
{
        string *brother,*brother1;
        if( me==ob->query_temp("swear") ) {
                
                if( ob->query_temp("swear")==me)  {
                if( arrayp(brother = me->query("brother")) ) {
                        if( member_array(ob->query("id"), brother)==-1 )
                                me->set("brother", brother + ({ob->query("id")}) );
                } else me->set("brother", ({ob->query("id")}) );
                
                if( arrayp(brother1 = ob->query("brother")) ) {
                        if( member_array(me->query("id"), brother1)==-1 )
                                ob->set("brother", brother1 + ({me->query("id")}) );
                } else ob->set("brother", ({me->query("id")}) );
                
                if(me->query_temp("become")=="mm") CHANNEL_D->do_channel(me, "chat",sprintf("�Ҿ�����%s���Ϊ�ֵܡ�", ob->name_id(1)));
                if(me->query_temp("become")=="mf") CHANNEL_D->do_channel(me, "chat",sprintf("�Ҿ�����%s���Ϊ���á�", ob->name_id(1)));
                if(me->query_temp("become")=="ff") CHANNEL_D->do_channel(me, "chat",sprintf("�Ҿ�����%s���Ϊ��á�", ob->name_id(1)));
                me->delete_temp("swear");
                ob->delete_temp("swear");
                me->delete_temp("become");
                ob->delete_temp("become");
                return 1;}
                }
                
        else {
                write("����"+ob->query("name")+"��������ĺ���...\n");
                tell_object(ob,"����һ��ʱ��ĳ�Ĭ�������"+me->short(1)+"�ĺ��⣡\n");
                me->delete_temp("swear");
                ob->delete_temp("swear");
                me->delete_temp("become");
                ob->delete_temp("become");
                return 1;}
}

int do_show_family(object me)
{
        string *parent,*child,*brother;
        parent = me->query("parent");
        child = me->query("child");
        brother = me->query("brother");
        write("�����ڵļ����У�\n");
        if(me->query("parent")) write("��ĸ��" + implode(parent, ", ") + "��\n");
        if(me->query("lover")) write("��ż��" +me->query("lover") + "��\n");
        if(me->query("brother")) write("�ֵ���ã�" + implode(brother, ", ") + "��\n");
        if(me->query("child")) write("��Ů��" + implode(child, ", ") + "��\n");
}
