//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/finger.c

//SKYMONARCH By 2003/3/8

#include <ansi.h>

int main(object me, string arg)
{
        int i, num;
        string str, *finger, msg;
        object ob;

//        seteuid(ROOT_UID);
        finger = me->query("finger");
        if( !arg ) {
                msg = "";
                str = me->name() + "�ĺ���Ŀǰ�����ϵ��У�\n";
                if( sizeof(finger) ) {
                        for(i=0;i<sizeof(finger);i++) {
                                if( ob = find_player(finger[i]) ) {
                                        msg += sprintf(HIY"[%2d]"NOR" %s\n", i + 1, ob->short() );
                                        num++;
                                }
                        }
                        if( !num ) str += "��Ŀǰû���κκ������ߡ�\n";
                        else str += msg;
                } else str += "�㻹û���趨����������\n"; 
                me->start_more(str);
        } else if( sscanf(arg,"-d %s", arg) ) {
                if( pointerp(finger) ) {
                        if( member_array(arg, finger) == -1 )
                                return notify_fail( capitalize(arg) + " ������ĺ��������С�\n");
                        else me->set("finger", finger - ({ arg }) );
                } else return notify_fail("�㻹û���趨����������\n");
                write("��� " + capitalize(arg) + " ����ĺ���������ȥ����\n");
        } else if( sscanf(arg, "-a %s", arg) ) {
                if( file_size(DATA_DIR + "login/" + arg[0..0] + "/" + arg + __SAVE_EXTENSION__) < 0 )
                        return notify_fail("û����λʹ���ߡ�\n");
                if( arg == me->query("id") )
                        return notify_fail("�㲻�ܰ��Լ��������������\n");
                if( !pointerp(finger) ) me->set("finger", ({ arg }) );
                else {
                        if( member_array(arg, finger) != -1 )
                                return notify_fail( capitalize(arg) + " �Ѿ�����ĺ��������С�\n");
                        else me->set("finger", finger + ({ arg }) );
                }
               write("��� " + capitalize(arg) + " ������ĺ��������С�\n");
        } else if( arg == "-l" ) {
                str = "Ŀǰ" + me->name() + "�ĺ��������У�\n";
                        str += HIC"��������������������������\n"NOR;
                if( sizeof(finger) ) {
                        for(i=0;i<sizeof(finger);i++) {
                                if( !objectp(ob = FINGER_D->acquire_login_ob(finger[i])) ) {
                                        me->set("finger", finger - ({ finger[i] }) );
                                        write("��ĺ��� " + capitalize(finger[i]) + " �������������ʧ�ˡ�\n");
                                }
                                str += sprintf(HIY"[%2d]"NOR" %s\n", i + 1,
                                        ob->query("name") + "(" + capitalize(finger[i]) + ")");
                        }
                        str += YEL"------------------------------------------\n"NOR;
                        str += "Ŀǰ���� " + sizeof(finger) + " λ���ѡ�\n";
                } else str += "�㻹û���趨����������\n";
                        str += YEL"==========================================\n"NOR;
                me->start_more(str);
        } else if( arg == "-all" ) {
                if( !wizardp(me) ) return notify_fail("�㲻��ʹ�����������\n");
          	else me->start_more(FINGER_D->finger_all());
        } else {
                write( FINGER_D->finger_user(arg) );
	}
        return 1;
}

int help(object me)
{
        write(@HELP
----------------------------------------
ָ���ʽ��finger [-l|-a|-d] <���>
----------------------------------------
˵����
 finger         �г�Ŀǰ�����ߵĺ���
 finger -a      �����µ� id ��������
 finger -d      ��ĳ���˵� id ��������ȥ��
 finger -l      �г����еĺ�������
 finger <���>  ��ѯ�������
----------------------------------------
HELP);
        return 1;
}
