//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/herb_shop.c
// by bor @RG

#pragma optimize
#pragma save_binary

inherit ROOM;

private string *got_list( string dir );
private void reset_list();
private object find_list(string id);

void setup()
{
	seteuid(getuid());
	reset_list();
	::setup();
}

void init()
{
	add_action("do_list","list");
	add_action("do_buy","buy");
}

private int do_list(string arg)
{
	string msg="", *str, *list=({});

	msg += "Ŀǰ�ṩ����Ʒ����, ��ӭ����(buy):\n";

	list = got_list( "/obj/herb_shop/" );

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		msg += sprintf("    %-35s %5d ö���  ���� %3d %s\n",
			list[i]->short(1), list[i]->query("value"),
			tmp_dbase["list"][list[i]], list[i]->query("unit"));
	this_player()->start_more(msg);
	return 1;
}

private string *got_list( string dir )
{
	string *str, *list=({});

	str = get_dir(dir);
	for(int i=0;i<sizeof(str);i++) {
		if( file_size( dir+str[i] )<0 ) continue;
		if( member_array( dir+str[i], list) != -1 ) continue;
		list += ({ dir+str[i] });
	}
	return list;
}

private int do_buy(string arg)
{
	int count = 1;
	string id, file;
	object ob;

	if(!arg) return notify_fail("��Ҫ��ʲô ?\n");
	if(sscanf(arg,"%d %s", count, id) != 2) id = arg;

	if( !objectp(ob = find_list(id)) )
		return notify_fail("��Ҫ��ʲô������\n");

	file = full_name(ob);

	for(int i=0; i<count; i++) {
		if(tmp_dbase["list"][file] < 1) return notify_fail("�Բ���, ���������Ѿ�������, �����������\n");
		if( ob->query("base_value") )
			if(!this_player()->can_afford(ob->query("base_value"))) return notify_fail("���Ǯ������\n");
		else 
			if(!this_player()->can_afford(ob->query("value"))) return notify_fail("���Ǯ������\n");
		if(!ob->move(this_player())) {
			destruct(ob);
			return notify_fail("���ò�����.\n");
		}
		tmp_dbase["list"][file] -= 1;
		if( ob->query("base_value") )
			this_player()->pay_money(ob->query("base_value"));
		else this_player()->pay_money(ob->query("value"));
		message_vision("$N������һ"+ob->query("unit")+"$n��\n",this_player(), ob);
	}
	return 1;
}

private object find_list(string id)	// ���������Ҫ���������Ƿ����
{
	string *list;
	object ob;

	list = got_list( "/obj/herb_shop/" );

	if( sizeof(list)>0 )
	for(int i=0; i<sizeof(list); i++) {
		ob = new(list[i]);
		if( id != ob->query("id") ) {
			destruct(ob);
			continue;
		}
		return ob;
	}
	return 0;
}

private void reset_list()
{
	string *list;
	list = got_list( "/obj/herb_shop/" );
	set_temp("list", ([]));				// ���趨Ϊ [], ��������趨

	if( sizeof(list)>0 )
	for(int i=0;i<sizeof(list);i++)
		tmp_dbase["list"][list[i]] = 30;	// tmp_dbase ��ʹ�÷�����ο� dbase.c
	return;
}
