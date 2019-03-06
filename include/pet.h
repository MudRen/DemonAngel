// /include/pet.h
// by bor @DA, 3/11 2003

int do_mount(string arg)
{
        object me = this_player();

	if( !arg || !id(arg)) return 0;

	if(me->query("id") != this_object()->query("owner")) {
		message_vision("$N͵͵�������߽�$n, ��$nһ��������ȥ��\n", me, this_object() );
		return 1;
	}

	message_vision("$NһԾ������$n, ��ƽ���ȵ����š�\n", me, this_object() );

	if( me->query("list/pet")) {
		if( me->query("list/pet/damage") ) {
			me->add_temp("apply/damage", me->query("list/pet/damage"));
		}
		if( me->query("list/pet/armor") ) {
			me->add_temp("apply/armor", me->query("list/pet/armor"));
		}
		if( me->query("list/pet/kee") ) {
			// charge ʱ���� apply/kee, ֱ�� 0, Ҫ feed bean ʱ����dismount �� feed
			me->add_temp("apply/kee", me->query("list/pet/kee"));
		}
		me->set_temp("riding_pet", 1);
	}
	this_object()->move("/d/special/no_reborn_room.c");
	return 1;
}

int do_feed(string arg)
{
	object me = this_player(), ob, pet_ob;
	string food, who;

	if(!arg) return notify_fail("ָ���ʽ: feed <ĳ��> to <ĳ����>\n");
	if( sscanf(arg, "%s to %s", food, who)!= 2 ) return notify_fail("ָ���ʽ: feed <ĳ��> to <ĳ����>\n");
	if( !objectp( ob = present(food, me) ) ) return notify_fail("������û�д���Ʒ��\n");
	if( !ob->is_bean() ) return notify_fail("������û���κο��������ﲹ���������� !!\n");
	if( !objectp( pet_ob = present(who, environment(me)) ) ) return notify_fail("�㸽��û��ͷ���� !!\n");
	if( pet_ob->query("owner")!=me->query("id") ) return notify_fail("��ͷ���������˦��, ����������������ȥ��\n");
	ob->direct_move(pet_ob);
	pet_ob->force_me("eat bean");
	return 1;
}
