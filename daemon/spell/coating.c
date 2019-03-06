//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /daemon/spell/coating.c
// by bor @DA
// ħ����Ĥ (coating)
/*
> cast coating
���૆��� : ����� ����
> �㽫ħ����������а������, ֱ��а���ȷ���������â ...

*/
#include <ansi.h>

int cast_spell(object me, object target)
{
	object *ob;
	if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	// target Ҫװ��... ���� cast
	if( objectp(target) ) {
		if(!target->query("skill_type") || !target->query("equipped"))
			return notify_fail("��������������ܲ�ħ��������\n");
	}
	if( !target ) {
		if( sizeof(all_inventory(me)))
		ob = filter(all_inventory(me), (: objectp($1) && $1->query("skill_type") && $1->query("equipped")
		:)  );
		if( sizeof(ob) )target = ob[0];
	}
	if( !target || !target->query("equipped") ) return notify_fail("��������������ܲ�ħ��������\n");
	if( target->query_temp("spell_effect/coating") ) return notify_fail("����������Ѿ���ħ�������ˡ�\n");
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");

	me->start_busy(2);
	me->add("mp", -15);
	message_vision(HIC"$N�૆��� : ����� ...\n"NOR, me);
	call_out("coating", 0, me, target);
	return 1;
}

int coating(object me, object target)
{
	me->start_busy(1);

	if(!target) return 0;

	if( random( 40 ) > me->query_skill("cast",1)*3 + me->query_spell("coating", 1)/10 + me->query_kar()*4 ) {
		message_vision("$Nʩ��ʧ���ˡ�\n", me);
	} else {
		// ���ж�һ�� wp �Ƿ��� cast �÷���
		if( target->query_temp("spell_effect/coating") ) {
			write("����������Ѿ���ħ�������ˡ�\n");
			return 1;
		} else {
			string *list=({});
			me->add_temp("apply/str", 1);
			me->add_temp("apply/damage", 10);
			if( !(list = target->query_temp("spell_effect")) )
				target->set_temp("spell_effect", ({ "coating" }));
			else {
				if( member_array("coating", list)==-1 ) {
					list += ({ "coating" });
					target->set_temp("sprll_effect", list);
				}
			}
			target->set_temp("coating_ob", me);
			message_vision(HIY"$N��ħ����������$n��, ֱ��$n����������â ...\n"NOR, me, target);
			target->set_temp("short", RED"����"NOR+ target->query("name") );
			call_out("remove_coating", 60, target);
			me->start_busy(1);
		}
	}
	return 1;
}

int remove_coating(object target)
{
	object ob;

	if( objectp(target) )
		ob = target->query_temp("coating_ob");

	if( objectp(ob) ) {
		ob->add_temp("apply/str", -1);
		ob->add_temp("apply/damage", -10);
	}

	if(objectp(target)) {	// ����û������
		string *list = ({});
		if( arrayp(list = target->query_temp("spell_effect") ) )
			if( member_array("coating", list) != -1 )
				list -= ({ "coating" });
		if( zerop(list) ) target->delete_temp("spell_effect");
		else target->set_temp("spell_effect", list);

		if( target->query_temp("apply") ) target->delete_temp("apply");

		target->delete_temp("short");
		target->delete_temp("coating_ob");
	}
	message_vision(HIY"Ʈ����$Nǰ����ħ���������˼���, ��ʧ�ˡ�\n"NOR, target);
	return 1;
}

int invoke(object me, object target, object wp)
{
	object *ob;
	if( me->is_busy() ) return notify_fail("����һ��������û����ɡ�\n");
	if( objectp(wp)) target = wp;

	// target Ҫװ��... ���� cast
	if( objectp(target) ) {
		if(!target->query("skill_type") || !target->query("equipped"))
			return notify_fail("��������������ܲ�ħ��������\n");
	}
	if( !target ) {
		if( sizeof(all_inventory(me)))
		ob = filter(all_inventory(me), (: objectp($1) && $1->query("skill_type") && $1->query("equipped")
		:)  );
		if( sizeof(ob) )target = ob[0];
	}
	if( !target || !target->query("equipped") ) return notify_fail("��������������ܲ�ħ��������\n");
	if( target->query_temp("spell_effect/coating") ) return notify_fail("����������Ѿ���ħ�������ˡ�\n");
	if( (int)me->query_mp() < 20 ) return notify_fail("��ķ���������\n");
	if( !wp ) return notify_fail("������û�����ֶ�����\n");
	if( wp->query_temp("invoke_times") < 1 ) return notify_fail("��������ķ�ӡ�Ѻľ���...\n");

	me->add("mp", -10);
	me->start_busy(2);
        message_vision(HIY"$Nר������$n�з�ӡ������...\n\n"NOR, me, wp);
	wp->add_temp("invoke_times", -1);
	call_out("check_wand", 0, me, target, wp);
	return 1;
}

int check_wand(object me, object target, object wp)
{
	if( random( 60 ) > me->query_skill("invoke",1)*2/3 + me->query_kar()/4 ) {
		message_vision(HIG"$N������ӡʧ��, $n����һ���Ѻ�\n", me, wp);
		wp->add_temp("broken", 20);
		return 1;
	}
	if( wp->query_temp("broken") >= 100 ) {
		message_vision(HIG"$N���е�$n���һ����Ƭ...\n", me, wp);
		destruct(wp);
	} else {
		// ���ж�һ�� wp �Ƿ��� cast �÷���
		if( target->query_temp("spell_effect/coating") ) {
			write("����������Ѿ���ħ�������ˡ�\n");
			return 1;
		} else {
			string *list=({});
			me->add_temp("apply/str", 1);
			me->add_temp("apply/damage", 10);
			if( !(list = target->query_temp("spell_effect")) )
				target->set_temp("spell_effect", ({ "coating" }));
			else {
				if( member_array("coating", list)==-1 ) {
					list += ({ "coating" });
					target->set_temp("sprll_effect", list);
				}
			}
			target->set_temp("coating_ob", me);
			message_vision(HIY"$N��ħ����������$n��, ֱ��$n����������â ...\n"NOR, me, target);
			target->set_temp("short", RED"����"NOR+ target->query("name") );
			call_out("remove_coating", 60, target);
			me->start_busy(1);
		}
	}
	return 1;
}
