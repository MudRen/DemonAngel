//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/king/abdicate.c
// appoint by bor @RG
// modify by amgbell@DA from appoint.c

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        seteuid(getuid());
        if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
        if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
        if( !arg ) return notify_fail("ָ���ʽ : abdicate <��> \n");
        if( !me->query("kingdom/id") ) return 0;
        if( !(ob = present(arg, environment(me)) )) return notify_fail("������λ��˭��\n");
        if( !userp(ob) ) return notify_fail(ob->name() + "���������ݡ�\n");

        if( ob == me ) return notify_fail("�㲻����λ���Լ���\n");
        if( !ob->query("kingdom/id")
        || ob->query("kingdom/id") != me->query("kingdom/id") )
                return notify_fail("����������˵�������\n");

        if( !ob->query("kingdom/minister") ) return notify_fail("�����Ǵ� !!\n");

        if( !kingdom_data(me->query("kingdom/id"), "power", "sub", "king", me->query("id")) ) return notify_fail("������������û�취���Է�д�������ڡ�\n");
        if( !kingdom_data(me->query("kingdom/id"), "power", "sub", "minister", ob->query("id")) ) return notify_fail("������������û�취���Է�д�������ڡ�\n");
        if( !kingdom_data(me->query("kingdom/id"), "power", "set", "king", ob->query("id")) ) return notify_fail("������������û�취���Է�д�������ڡ�\n");

        if( !kingdom_data(me->query("kingdom/id"), "power", "add", "minister", me->query("id")) ) return notify_fail("������������û�취���Է�д�������ڡ�\n");
        
        ob->set("kingdom/king", ob->query("id")); //��λ�ߵ�king
        ob->delete("kingdom/min");

        me->delete("kingdom/king");
        me->set("kingdom/minister", ob->query("id"));//�Լ���min
        
        ob->set("home",KINGDOM_DIR+me->query("kingdom/id")+"/kingdom.c");
        // �趨�󳼻���Ȩ��
        ob->add_path( ({"/cmds/min/","/cmds/king/"}) );
        me->sub_path( ({"/cmds/king/"}) );
        ob->save();
        me->save();	// by bor@DA, 2/26 2003
        CHANNEL_D->do_channel(me, "kingdom", sprintf("��֣����������λ�ø�"+ob->name_id(1)+"��"));
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : abdicate <ĳλ��>

���ǹ�������λ�ø�ĳλ�󳼵�ָ��, ����ʹ�����ָ��Ὣ��λ����ָ��
�Ĵ�, ���Լ�ת�������Ĵ󳼡����ڵ��ι�����һ�����ҵ�����, ������
�㴫λǰ, �����ϸ���ǹ�, ��������Է���ͬ��, ���������������ҡ�

���ѶϢ : appoint, fire
HELP
        );
        return 1;
}
