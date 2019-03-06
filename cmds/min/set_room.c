//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/set_room.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	object env;
	mapping dbase;
	string *data, str;
	string *set_only = ({"no_teleport", "no_summon", "no_cast", "no_fight", "no_mob",
		"no_recall", "no_quit", "dark", "outdoors"});

	seteuid(getuid(me));
	if( me->is_busy() ) return notify_fail("��Ķ�����û����ɡ�\n");
	if( me->is_fighting() ) return notify_fail("�㻹��ս���С�\n");
	if( !env = environment(me)) return notify_fail("�Ҳ���������\n");
	if( !me->query("kingdom/id")) return 0;
	if( env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("���ﲻ���ҹ���������\n");

	dbase = env->query_entire_dbase();
	data = dbase["refresh_data"];

	if(!arg) {
		str = "�������Ļ����������� :\n";
		str += "\ttype            : "+dbase["type"]+"\n";
		str += "\tmake_owner      : "+data[0]+"\n";
		str += "\tmake_time       : "+data[1]+"\n";
		str += "\tlast_owner      : "+data[2]+"\n";
		str += "\tlast_update     : "+data[3]+"\n";
		str += "\tno_summon       : "+dbase["no_summon"]+"\n";
		str += "\tno_teleport     : "+dbase["no_teleport"]+"\n";
		str += "\tdark            : "+dbase["dark"]+"\n";
		str += "\tno_mob          : "+dbase["no_mob"]+"\n";
		str += "\tno_cast         : "+dbase["no_cast"]+"\n";
		str += "\tno_fight        : "+dbase["no_fight"]+"\n";
		str += "\tno_recall       : "+dbase["no_recall"]+"\n";
		str += "\tno_quit         : "+dbase["no_quit"]+"\n";
		str += "\toutdoors        : "+dbase["outdoors"]+"\n";

		me->start_more(str);
		return 1;
	}

	if( dbase["no_change"] ) return notify_fail("������������趨���޷������������ǡ���������쿴��\n");

	if(member_array(arg, set_only) != -1) {
		if( dbase[arg]==1 ) {
			dbase[arg] = 0;
			env->delete(arg);
		} else {
			dbase[arg] = 1;
			env->set(arg, 1);
		}

		write("�㽫 "+arg+ " �趨Ϊ "+ dbase[arg] + "\n");
		do_saveroom(env);
		return 1;
	} else return notify_fail("ָ���ʽ : set_room <��������>\n");
	return 1;
}

int help()
{
	write(@HELP

ָ���ʽ : set_room <��������>

���ǹ�������ʱ��ָ��֮һ, ���ָ�������趨һЩ�Ƚ�����ķ�������,
Ŀǰ�����趨�������� : <�������趨ֵΪ 1 ��״��, 0 ����״����>
��������κβ������ῴ��Ŀǰ�����״̬��

 1. outdoors    : �����������ɻ���, ��������������￴������ѶϢ��
 2. no_quit     : ������������� quit��
 3. no_recall   : ��������������� recall ָ�
 4. no_fight    : �˴���ֹս����
 5. no_cast     : �˴���ֹʩ����
 6. no_mob      : �˴� mob ����ͨ�С�
 7. no_summon   : �˴���ֹ summon .
 8. type        : �任��ͨ����Ļ�����̬��Ŀǰ������任�Ļ�����̬�� :
                  normal        :       �����ⷿ������ͨ����
                  board         :       ���Թ㳡
                  gate          :       �ؿ�
                  ���������ʹ�� set_room type gate ��һ�㷿��ת�� gate
                  ��ֻ�ܱ任��ͨ�������̬��
 9. add_room    : ��ĳ��������һ����ͨ���䡣
                  ���� : set_room add_room west : ��������һ�����䡣
11. repair here : �����ݻٵĽ��������Ҫ�����ؽ�, ���۸����µĲ�ࡣ
11. dark        : �������趨Ϊ�ڰ��ģ�1 Ϊ�ڰ�, 0 ��ָ�������

������뵽Ҫ�����, ������������硣
PS. 2-7 ����������, ���� ....

���ѶϢ : makeroom, set_short, set_long, saveroom

HELP
	);
	return 1;
}