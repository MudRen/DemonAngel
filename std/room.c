//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room.c

#pragma save_binary

#include <dbase.h>
//#include <room.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

//static mapping doors;

int query_max_encumbrance() { return 100000000000; }

int is_room() { return 1; }

int clean_up(int inherit_flag)
{
	mapping items;

    // Don't clean up if any NPCs we created were wandering somewhere.
    // This may introduce a potential deadlock that when room-A holds
    // an NPC from room-B while room-B holds another NPC from room-A.
    // Anyway, such condition is really rare and its only fault is leaving
    // the room not cleaned up when deadlock exists. So, we just merely
    // ignore it :P                                 - Annihilator
	if( mapp(items = query_temp("objects")) )
		foreach(string file, object ob in items) {
			if( objectp(ob)
			&&	ob->is_character()
			&&	environment(ob)!=this_object() )
			return 1;
		}
	return ::clean_up(inherit_flag);
}

private object make_inventory(string file)
{
	object ob;

	ob = new(file);
	if(!ob) return 0;
	ob->move(this_object());
	ob->set("startroom", base_name(this_object()));
	return ob;
}

void reset()
{
	mapping ob_list, ob;

	set("valid_startroom", 1);

	ob_list = query("objects");
	if( mapp(ob_list) ) {
		if( !mapp(ob = query_temp("objects")) ) ob = ([]);
		foreach(string file, int amount in ob_list) {
			if( amount==1 ) {
				if( !objectp(ob[file]) ) ob[file] = make_inventory(file);
			} else {
				int i;
				for(i=amount-1; i>=0; i--) {
					if( objectp(ob[file + " " + i]) ) continue;
					ob[file + " " + i] = make_inventory(file);
				}
			}
		}
		set_temp("objects", ob);
	}
}

/*

// Redirect item_desc of the door to this function in default.
string look_door(string dir)
{
	if( !mapp(doors) || undefinedp(doors[dir]) )
		return "��Ҫ��ʲô��\n";
	if( doors[dir]["status"] & DOOR_CLOSED )
		return "���" + doors[dir]["name"] + "�ǹ��ŵġ�\n";
	else
		return "���" + doors[dir]["name"] + "�ǿ��ŵġ�\n";
}

varargs int open_door(string dir, int from_other_side)
{
	mapping exits;
	object ob;

	if( !mapp(doors) || undefinedp(doors[dir]) )
		return notify_fail("�������û���š�\n");

	if( !(doors[dir]["status"] & DOOR_CLOSED) )
		return notify_fail( doors[dir]["name"] + "�Ѿ��ǿ��ŵ��ˡ�\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: open_door: attempt to open a door with out an exit.\n");

	if( from_other_side )
		message("vision", "���˴���һ�߽�" + doors[dir]["name"] + "���ˡ�\n", this_object());
	else if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->open_door(doors[dir]["other_side_dir"], 1) ) return 0;
	}

	doors[dir]["status"] &= (!DOOR_CLOSED);
	return 1;
}

varargs int close_door(string dir, int from_other_side)
{
	mapping exits;
	object ob;

	if( !mapp(doors) || undefinedp(doors[dir]) )
		return notify_fail("�������û���š�\n");

	if( (doors[dir]["status"] & DOOR_CLOSED) )
		return notify_fail( doors[dir]["name"] + "�Ѿ��ǹ��ŵ��ˡ�\n");

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: close_door: attempt to open a door with out an exit.\n");

	if( from_other_side )
		message("vision", "���˴���һ�߽�" + doors[dir]["name"] + "�����ˡ�\n", this_object());
	else if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->close_door(doors[dir]["other_side_dir"], 1) ) return 0;
	}

	doors[dir]["status"] |= DOOR_CLOSED;
	return 1;
}

int check_door(string dir, mapping door)
{
	// If we have no responding door, assume it is correct.
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 1;

	door["status"] = doors[dir]["status"];
	return 1;
}

varargs void create_door(string dir, mixed data, string other_side_dir, int status)
{
	mapping d, exits, item_desc;
	object ob;

	exits = query("exits");
	if( !mapp(exits) || undefinedp(exits[dir]) )
		error("Room: create_door: attempt to create a door without exit.\n");

	// Compact mode.
	if( stringp(data) ) {
		d = allocate_mapping(4);
		d["name"] = data;
		d["id"] = ({ dir, data, "door" });
		d["other_side_dir"] = other_side_dir;
		d["status"] = status;
	} else if( mapp(data) )
		d = data;
	else
		error("Create_door: Invalid door data, string or mapping expected.\n");

	set("item_desc/" + dir, (: look_door, dir :) );

	if( objectp(ob = find_object(exits[dir])) ) {
		if( !ob->check_door(other_side_dir, d) )
			return;
	}

	if( !mapp(doors) ) doors = ([ dir: d ]);
	else doors[dir] = d;
}

mapping query_doors() { return doors; }

mixed query_door(string dir, string prop)
{
	if( !mapp(doors) || undefinedp(doors[dir]) ) return 0;
	else return doors[dir][prop];
}
*/

int valid_leave(object me, string dir)
{
/*	if( mapp(doors) && !undefinedp(doors[dir]) ) {
		if( doors[dir]["status"] & DOOR_CLOSED )
			return notify_fail("������Ȱ�" + doors[dir]["name"] + "�򿪣�\n");
		// if ( door[dir]["status"] & DOOR_HAS_TRAP ) ....
	}*/
	return 1;
}

void setup()
{
	seteuid(getuid());
	this_object()->reset();
}
