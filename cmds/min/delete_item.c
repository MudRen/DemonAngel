//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/min/delete_item.c
// by amgbell@hoe

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	object ob,*all_ob;
	int i;

	if (!arg) return notify_fail("ָ���ʽ : delete_item <item>\n");
	ob=present(arg,me);

	if (!ob) return notify_fail("������û������������\n");

	if (ob->query("kingdom") != me->query("kingdom/id"))
		return notify_fail("������ǹ������Ʒ��\n");

	if( !me->query("kingdom/king") && ob->query("owner")!=me->query("id") )
		return notify_fail("���ӵ���߲�����!!\n");
	if( ob->query("equipped") ) return notify_fail("����װ����������\n");
	// ��� wp �� coating Ч��, ��ʱ������
	if( ob->query_temp("coating") ) return notify_fail("�������������ħ��������, ������������!!\n");

	message_vision("$N���˰�$n��ȥ���ա�\n",me,ob);

	all_ob=children(full_name(ob));

	rm(full_name(ob));

	if( ob->query("skill_type") ) {
		kingdom_data(me->query("kingdom/id"), "data", "sub", "weapon", 1);
		kingdom_data(me->query("kingdom/id"), "data", "add", "weapon_num", 1);
	} else if( ob->query("armor_type") ) {
		kingdom_data(me->query("kingdom/id"), "data", "sub", "armory", 1);
		kingdom_data(me->query("kingdom/id"), "data", "add", "armory_num", 1);
	}

	for (i=0;i<sizeof(all_ob) ;i++ ) {
		if(!objectp(all_ob[i])) continue;
		if(!environment(all_ob[i])) continue;
		if( !environment(all_ob[i])->is_character() ) continue;
		all_ob[i]->unequip();
		destruct(all_ob[i]);
	}
        return 1;
}

int help()
{
        write(@HELP

ָ���ʽ : delete_item <item>

���ǹ��������������һЩû�õ��������ߵ�ָ��, ���Ѿ��ò����Ĵμ�
������, ���Եõ���������Ʒ�Ĳ���, ���ڷ�չ̫������Դȱ���Ĺ��Ҷ���,
���Ǵٽ������ķ���֮һ��

��ע�� : ������һ����Ʒ������, ӵ�������Ʒ�������´����ߺ�ᷢ��
���Ķ���������� ... ��Ȼ�ܿ���, ����Ϊ�˹��ҵĽ��� ...

���������Ѷ :  make_weapon, set_item, give

HELP
        );
        return 1;
}
