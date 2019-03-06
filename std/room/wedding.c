//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/wedding.c
// by smallpen

#pragma optimize
#pragma save_binary

inherit ROOM;
int do_me_check(object me,object ob1,object ob2);
int do_ob1_check(object me,object ob1,object ob2);
int do_ob2_check(object me,object ob1,object ob2);
int do_fail(object me,object ob1,object ob2);
void init()
{
        add_action("do_marry", "marry");
        add_action("do_answer","answer");
}

int do_marry(string arg)
{
        string man,woman,sex="��";
        object me = this_player(),ob1,ob2;
        string *parent,*child,*brother;
        int i;
        seteuid(getuid());
        
        if( me->is_busy()) return notify_fail("��������æ�š�\n");
        if( !arg || sscanf(arg, "%s with %s", man,woman)!=2 ) return notify_fail("��ʽ : marry <�з�> with <Ů��>��\n");
        if( !(ob1 = present(man, environment(me)) )) return notify_fail("�з��������ֳ�ࡣ�\n");
        if( !(ob2 = present(woman, environment(me)) )) return notify_fail("Ů���������ֳ�ࡣ�\n");
        parent = ob1->query("parent");
        child = ob1->query("child");
        brother = ob1->query("brother");
        if( ob1->query("gender")!="����" || ob2->query("gender")!="Ů��") return notify_fail("��ʽ : marry <�з�> with <Ů��>��\n"); 
        for(i=0;i<sizeof(parent);i++) {
                if(ob2->query("id")==parent[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
        for(i=0;i<sizeof(child);i++) {
                if(ob2->query("id")==child[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
        for(i=0;i<sizeof(brother);i++) {
                if(ob2->query("id")==brother[i]) return notify_fail("���Ѿ������������ˡ�\n");
                }
        if( ob1->query("lover")) return notify_fail("�з��Ѿ�����ˣ�\n");
        if( ob2->query("lover")) return notify_fail("Ů���Ѿ�����ˣ�\n");
        if( me->query("gender")=="����") sex="��";
        write("��˵���������츽���ҵ�Ȩ�����ڴ˵��ҽ�Ϊ"+ob1->query("name")+"��"+ob2->query("name")+"����֤�顣\n\n");
        tell_room(environment(me),me->query("name")+"˵���������츽���ҵ�Ȩ�����ڴ˵��ҽ�Ϊ"+ob1->query("name")+"��"+ob2->query("name")+"����֤�顣\n\n",me);
        write(sex+"��ǰ����һ������ʼ֤�顣\n\n");
                tell_room(environment(me),me->query("name")+"��ǰ����һ������ʼ֤�顣\n\n",me);
                write(sex+"˵����"+ob1->query("name")+"����Ը������һ����ʱ���չ�"+ob2->query("name")+"����������ð�գ�Ŭ��׬Ǯ�����ӻ���\n\n");
        tell_room(environment(me),me->query("name")+"˵����"+ob1->query("name")+"����Ը������һ����ʱ���չ�"+ob2->query("name")+"����������ð�գ�Ŭ��׬Ǯ�����ӻ���\n\n",me);
        call_out("do_me_check", 1,me,ob1,ob2);
                return 1;
}

int do_answer(string arg)
{
        string ans;
        object me=this_player();

        seteuid(getuid());
        if(!me->query_temp("wedding")) return notify_fail("������Ҫ���ɣ�\n"); 
        if(me->query_temp("wedding") && !me->query_temp("answer")) return notify_fail("��û����ش𣬲��ü���\n");
        if(!arg ||sscanf(arg,"%s",ans)!=1) return notify_fail("��ش�Yes or ��Ը�⣡\n");
        if(!(ans =="yes" || ans=="��Ը��")) return notify_fail("��ش�Yes or ��Ը�⣡\n");
        if(me->query("gender")=="����") message_vision("$P΢Ц��˵������Ը�⡣\n\n",me);
        if(me->query("gender")=="Ů��") message_vision("$P��ͷ�ߴ���Ӧ������Ը��...\n\n",me);
        me->delete_temp("answer");
        me->set_temp("swer","yes");
        return 1;
}

int do_me_check(object me,object ob1,object ob2)
{
        ob1->set_temp("wedding","ok");
        ob2->set_temp("wedding","ok");
        ob1->set_temp("answer","ok");
        call_out("do_ob1_check",10,me,ob1,ob2);

        return 1;
}

int do_ob1_check(object me,object ob1,object ob2)
{
        string sex="��";
        if(me->query("gender") =="Ů��") sex="��";
        if( ob1->query_temp("swer") ) {
                ob1->delete_temp("swer");
                ob1->delete_temp("wedding");
                ob2->set_temp("answer","ok");
                write(sex+"˵����"+ob2->query("name")+"����Ը��һ������"+ob1->query("name")+"�������������ˣ�����ƶ����ϲ������������\n\n");
                tell_room(environment(me),me->query("name")+"˵����"+ob2->query("name")+"����Ը��һ������"+ob1->query("name")+"�������������ˣ�����ƶ����ϲ������������\n\n",me);
                call_out("do_ob2_check",10,me,ob1,ob2);
                
        }
        else {
                call_out("do_fail",2,me,ob1,ob2);
                return 1;}
}
int do_ob2_check(object me,object ob1,object ob2)
{
        if( ob2->query_temp("swer") ) {
                ob2->delete_temp("swer");
                ob2->delete_temp("answer");
                ob2->delete_temp("wedding");
                ob1->set("lover",ob2->query("id"));
                ob2->set("lover",ob1->query("id"));
                write(me->query("name")+"�󺰣�������"+ob1->query("name")+"��"+ob2->query("name")+"��Ϊ���ޣ�Ը���֮������ף��������ˡ�\n");
                shout(me->query("name")+"�󺰣�������"+ob1->query("name")+"��"+ob2->query("name")+"��Ϊ���ޣ�Ը���֮������ף��������ˡ�\n");
                return 1;
                
        }
        else {
                call_out("do_fail",2,me,ob1,ob2);
                return 1;}
}
int do_fail(object me,object ob1,object ob2)
 {
        string sex="��";
        if(me->query("gender")=="Ů��") sex="��";
        ob1->delete_temp("wedding");
        ob2->delete_temp("wedding");
        ob1->delete_temp("answer");
        ob2->delete_temp("answer");
        ob1->delete_temp("swer");
        ob2->delete_temp("swer");
        write(sex+"˵����������һ���г��ɣ������������ⳡ������Ч��\n\n");
        tell_room(environment(me),me->query("name")+"˵����������һ���г��ɣ������������ⳡ������Ч��\n\n",me);
        return 1;
 }      
