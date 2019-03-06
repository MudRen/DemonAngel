//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/furnace.c
// by bor @DA

#pragma optimize
#pragma save_binary

//#define DEBUG

inherit ROOM;

#include <ansi.h>

int	flag=-1,		// �Ƿ����ڹ�¯, �ڶ�û�й�¯
	mp,			// Ŀǰ charge ��������ֵ
	furnace_count_ini,	// ���� load ʱħ��¯����������ת��
	furnace_count,		// ��¼Ŀǰת��Ȧ��, ����������ֵ�仯
	lost_count;		// ��¼ʧ�ܵĴ���

object ob, env;

private int into_furnace( object me );
private int furnace_reward();

void setup()
{
	seteuid(getuid());
	env = this_object();
	::setup();
}

void init()
{
	if( userp(this_player()) && ( wizardp(this_player()) || this_player()->query("kingdom/id")==env->query("kingdom_id")  )  ) {
		add_action("do_load", "load");
	}
	add_action("do_charge", "charge");
}

private int do_load(string arg)
{
	object me = this_player();
	string item;

	if( !userp(me) ) return 0;
	if( flag==1 ) return 0;
	if(me->query("kingdom/id")!=environment(me)->query("kingdom_id")) return notify_fail("What��\n");
	if(!me->query("kingdom/king") && !me->query("kingdom/minister") ) return notify_fail("What��\n");
	if( !arg ) return notify_fail("load <��Ʒ> into furnace\n");
	if( sscanf(arg, "%s into furnace", item)!=1 ) return notify_fail("load <��Ʒ> into furnace\n");
	if( !objectp( ob = present(item, me) ) ) return notify_fail("������û�д���Ʒ!!\n");
	if( !ob->query("armor_type") && !ob->query("skill_type") )
		return notify_fail("�ⲻ��һ��װ��!!\n");
	if( !ob->query("new") ) return notify_fail("���װ�������»�!!\n");
	if( ob->query("equipped") ) return notify_fail("����װ����!!\n");

	if( !ob->query("kingdom") || ob->query("kingdom")!=me->query("kingdom/id") )
	if( !ob->query("kingdom/king") && ob->query("owner")!=ob->query("id") )
		return notify_fail("�����Ʒӵ���߲�����!!\n");

	if( ob->query("level")<23 ) return notify_fail("�����Ʒ̫�����ˣ���������ħ�����ʡ�\n");

	mp = random(30) + 10;			// ������ʼֵ

	furnace_count_ini = random(53)+7;	// ���� 6 ��
	flag = 1;				// ����������Ҳ�� load
	into_furnace(me);
	return 1;
}

object furnace_msg_ob()
{
	object *inv;
	
	inv = all_inventory(env);
	if( zerop(inv) ) return 0;
	return inv[random(sizeof(inv))];
}

private int into_furnace( object me )
{
	ob->move(VOID_OB);
	message_vision(WHT"$N��$n����ħ��¯�С�\n\n"NOR, me, ob);
	message_vision(HIM"ħ��¯������ɫ�Ĺ�â, ���뿪ʼ�䶯��\n\n\n"NOR, me);
	furnace_count = 0;
	call_out("furnace_count_msg", 2 );
	return 1;
}

private int furnace_count_msg()
{
	object ob2;
	furnace_count_ini --;

	ob2 = furnace_msg_ob();
	if( furnace_count>10+random(2) )
		mp = mp - (54+random(2));		// ÿת��ʣ��ķ���
	else mp = mp - ( 105+random(3) );

#ifdef DEBUG
	message_vision("init:"+furnace_count_ini+", lost_count:"+lost_count+", furnace_count:"+furnace_count+"\n\n", ob2);
#endif

	if( furnace_count_ini ) {	// ת��ת��
		// �������, ���Խ� furnace ͣ����[������Ҫ 7 Ȧ��, ���ܵ�]
		if( furnace_count>6 ) {
			if( ( mp>4000 && 50>random(100) )
			|| ( lost_count<=5 && lost_count>=3 && 3>random(100) )
			|| ( 2>random(100) )
			) {
				call_out("furnace_drop", 0 );
				return 1;
			} else if( 50>random(100) && (mp <= -2500 || lost_count>=7) ) {	// ��� mp ���ز���ͳԵ���Ʒ
				if(ob2) message_vision(HIC"ħ��¯ͻȻ������, Ȼ�����еĴ��뽥��ֹͣ�˻ ...\n\n"NOR, ob2);
				destruct(ob);
				flag = -1;
				return 1;
			}
		}

		if( mp<0 ) {
			lost_count += 1;
			if(ob2) message_vision("[1;5;31mħ��¯����������, �����Ĺ�â��ʼ���� ...[0m\n", ob2);
		} else {
			furnace_count += 1;
			lost_count = 0;
//			if(ob2) message_vision(HIY"ħ��¯�Ĵ����ȶ����ζ�, ����ǿ�ҵ�ħ����â ...[�� "+furnace_count+" Ȧ]\n\n"NOR, ob2);
			if(ob2) message_vision(HIY"ħ��¯�Ĵ����ȶ����ζ�, ����ǿ�ҵ�ħ����â ...\n\n"NOR, ob2);
		}
		call_out("furnace_count_msg", 0 );
	} else {	// ����ת��
		if(ob2) message_vision(WHT"ħ��¯�Ļ��������, �����Ĺ�âɢȥ��, ħ��¯��ȫ�ָ���ֹ ...\n"NOR, ob2);
		call_out("furnace_drop", 0 );
	}
	return 1;
}

private int furnace_drop()
{
	flag = -1;

	// ת��Ȧ�����С�� 8 , ��ô����������, ��������ֵ
	if( furnace_count > 7 ) {
		ob->set("new", 0);
		furnace_reward();
	}
	ob->move(env);
//	message_vision(WHT"\n$N��ž����һ����ħ��¯�е��˳�����[����... �� "+ furnace_count+" Ȧ]\n"NOR, ob);
	message_vision(WHT"\n$N��ž����һ����ħ��¯�е��˳�����\n"NOR, ob);
	return 1;
}

private int furnace_reward()
{
	int tmp, num, ac, db, wl, Mh, lv;
	string attr;
	string *add_normal = ({ "ac", "db", "wl", "Mh" });

	// 1. ����ħ��¯ȫ����ת��(furnace_count) ��������������
	tmp = random(60);

	if( tmp>=45  ) attr = add_normal[random(sizeof(add_normal))];
	else if( tmp<45 && tmp>=35 )	attr = "kar";
	else if( tmp<35 && tmp>=25 )	attr = "sta";
	else if( tmp<25 && tmp>=18 )	attr = "con";
	else if( tmp<18 && tmp>=10 )	attr = "str";
	else if( tmp<10 && tmp>=5 )	attr = "dex";
	else attr = "int";

	if( member_array(attr, add_normal)!=-1 ) num = furnace_count/5;
	else num = furnace_count/10;
	if(num<1) num=1;

	ac = furnace_count/10;
	db = furnace_count/10;
	wl = furnace_count/10;
	Mh = furnace_count/10;

	lv = ob->query("level") + ob->query("level") * furnace_count/100;

	if( ob->query("armor_type") ) {
		ob->set("armor_prop/ac", ac);
		ob->set("armor_prop/db", db);
	} else {
		ob->set("weapon_prop/wl", wl);
		ob->set("weapon_prop/Mh", Mh);
	}

	if( ob->query("type")=="wand" || ob->query("type")=="staff" ) {
		string *spell_list;
		// ȡ�� invoke_magic ��ʽ�кܶ���... ����ֻ��������:
		// 1. ֱ��ȡ�� /daemon/spell/
		// spell_list = get_dir("/daemon/spell/");
		// ob->set("invoke_magic", replace_string(spell_list[random(sizeof(spell_list))], ".c", "") );

		// 2. �����ҽ� /daemon/spell/ ���»���Ϊ��ְҵ��ѧ��Ŀ¼, �� /daemon/spell/ħ��ʦ/
		//    ���, �Ҷ��⻮��һ��Ŀ¼���õ�������Щ�����ɹ����� invoke_magic, ����:
		spell_list = get_dir("/daemon/furnace/spell/");
		ob->set("invoke_magic", spell_list[random(sizeof(spell_list))] );
	}

#ifdef DEBUG
	if( ob->query("armor_type") )
		ob->set_name("make"+ob->query("level")+"_tick"+furnace_count+"_lv"+lv+"_"+attr+num, ({ ob->query("id") }) );
	else ob->set_name("make"+ob->query("level")+"_tick"+furnace_count+"_sk"+(lv*2)+"_"+attr+num, ({ ob->query("id") }) );
#endif

	ob->set("level", lv);
	ob->set("add_attr/"+attr, num);			// ����ֵ, ������ ac, db, wl, Mh, ... ���ظ�, �ô�: Ψһ��

	if( !do_saveitem(ob) ) return 0;
	return 1;
}

private int do_charge(string arg)
{
	object me=this_player();

	message_vision("$N�ս�ħ��¯�Ĵ���, �����еľ��������ͽ�ȥ��\n\n", me);
	call_out("charge_furnace", 0, me, arg );
	return 1;
}

private int charge_furnace(object me, string arg)
{
	object ob;
	if( arg=="corpse" ) {
		ob = present(arg, env);
		if(!ob) ob = present(arg, me);
		if( ob && ob->is_corpse() ) mp += (600 + random(100));
		destruct(ob);
	} else if( arg=="furnace" ) {
		if( flag==1 ) mp += me->query("mp");
		me->set("mp", 0);
	}
	message_vision("ħ��¯ͻȻ����һ��ǿ�ҵ�������, ��$N�ľ���������һ�ɶ��� !\n", me);
	message_vision("$NͻȻ��ħ��¯������\n", me);
	return 1;
}
