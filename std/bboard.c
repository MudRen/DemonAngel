//ÄàÌ¶ÖĞ¹ú
//http://mud.lovefinal.com
//Final(ÕÂÅô)
//ÄàÌ¶ÖĞ¹ú(Final)¸ºÔğ¼òÌå»¯¹¤×÷  °æÈ¨ÊôÓÚÔ­×÷Õß
// /std/bboard.c

#include <ansi.h>

#define BOARD_CAPACITY query("capacity")

inherit ITEM;
inherit F_SAVE;

void setup()
{
	string loc;

	if( stringp(loc = query("location")) ) {
		move(loc);
	}
	set("no_get", 1);
	restore();
}

void init()
{
	add_action("do_post", "post");
	add_action("do_read", "read");
	add_action("do_discard", "discard");
	add_action("do_followup", "followup");
}

string query_save_file()
{
	string id;

	if( !stringp(id = query("board_id")) ) return 0;
	return DATA_DIR + "board/" + id;
}

string short()
{
	mapping *notes;
	int i, unread, last_read_time;

	notes = query("notes");
	if( !pointerp(notes) || !sizeof(notes) )
		return ::short() + " [ Ã»ÓĞÈÎºÎÁôÑÔ ]";

	if( this_player() ) {
		last_read_time = (int)this_player()->query("board_last_read/" + (string)query("board_id"));
		for(unread = 0, i=sizeof(notes)-1; i>=0; i--, unread ++)
			if( notes[i]["time"] <= last_read_time ) break;
	}
	if( unread )
		return sprintf("%s [ %d ÕÅÁôÑÔ£¬%d ÕÅÎ´¶Á ]", ::short(), sizeof(notes), unread);
	else
		return sprintf("%s [ %d ÕÅÁôÑÔ ]", ::short(), sizeof(notes));
}

string long()
{
	mapping *notes;
	int i, last_time_read;
	string msg, myid;

	notes = query("notes");
	msg = query("long");
	msg = msg + "ÁôÑÔ°æµÄÊ¹ÓÃ·½·¨Çë¼û help board¡£\n";
	if( !pointerp(notes) || !sizeof(notes) ) return query("long");

	last_time_read = this_player()->query("board_last_read/" + (string)query("board_id"));
	for(i=0; i<sizeof(notes); i++)
		msg += sprintf("%s[%2d]" NOR "  %-40s %12s (%s)\n",
			( notes[i]["time"] > last_time_read ? HIY: ""),
			i+1, notes[i]["title"], notes[i]["author"], ctime(notes[i]["time"])[0..15] );
	return msg;
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, string text)
{
	mapping *notes;

	note["msg"] += text;
	notes = query("notes");
	if( !pointerp(notes) || !sizeof(notes) )
		notes = ({ note });
	else
		notes += ({ note });

	// Truncate the notes if maximum capacity exceeded.
	if( sizeof(notes) > BOARD_CAPACITY )
		notes = notes[BOARD_CAPACITY / 2 .. BOARD_CAPACITY];

	set("notes", notes);
	tell_object(me, "ÁôÑÔÍê±Ï¡£\n");

	save();
	return;
}

private int do_post(string arg)
{
	mapping note;
	if(!arg) return notify_fail("ÁôÑÔÇëÖ¸¶¨Ò»¸ö±êÌâ¡£\n");
	
	note = allocate_mapping(4);
	note["title"] = arg;
	note["author"] = this_player()->name_id(1);
	note["time"] = time();
	note["msg"] = "";
	this_player()->edit( (: done_post, this_player(), note :) );
	return 1;
}

int do_read(string arg)
{
	int num;
	mapping *notes, last_read_time;
	string myid;

	last_read_time = this_player()->query("board_last_read");
	myid = query("board_id");
	notes = query("notes");

	if( !pointerp(notes) || !sizeof(notes) )
		return notify_fail("ÁôÑÔ°åÉÏÄ¿Ç°Ã»ÓĞÈÎºÎÁôÑÔ¡£\n");

	if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½£ºread <ÁôÑÔ±àºÅ>|new|next\n");
	if( arg=="new" || arg=="next" ) {
		if( !mapp(last_read_time) || undefinedp(last_read_time[myid]) )
			num = 1;
		else
			for(num = 1; num<=sizeof(notes); num++)
				if( notes[num-1]["time"] > last_read_time[myid] ) break;
			
	} else if( !sscanf(arg, "%d", num) )
		return notify_fail("ÄãÒª¶ÁµÚ¼¸ÕÅÁôÑÔ£¿\n");

	if( num < 1 || num > sizeof(notes) )
		return notify_fail("Ã»ÓĞÕâÕÅÁôÑÔ¡£\n");
	num--;
	this_player()->start_more( sprintf(
"[%d] %-40s %s(%s)\n----------------------------------------------------------------------\n",
		num + 1, notes[num]["title"], notes[num]["author"], ctime(notes[num]["time"])[0..9])
		+ notes[num]["msg"] );

	// Keep track which post we were reading last time.
	if( !mapp(last_read_time) )
		this_player()->set("board_last_read", ([ myid: notes[num]["time"] ]) );
	else 
		if( undefinedp(last_read_time[myid]) || notes[num]["time"] > last_read_time[myid] )
			last_read_time[myid] = notes[num]["time"];

	return 1;
}

private int do_discard(string arg)
{
	mapping *notes;
	int num;

	if( !arg || sscanf(arg, "%d", num)!=1 )
		return notify_fail("Ö¸Áî¸ñÊ½£ºdiscard <ÁôÑÔ±àºÅ>\n");
	notes = query("notes");
	if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
		return notify_fail("Ã»ÓĞÕâÕÅÁôÑÔ¡£\n");
	num--;
	if( notes[num]["author"] != (string) this_player(1)->name_id(1)
	&&	(string)SECURITY_D->get_status(this_player(1)) != "(admin)" )
		return notify_fail("Õâ¸öÁôÑÔ²»ÊÇÄãĞ´µÄ¡£\n");

	notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
	set("notes", notes);
	save();
	write("É¾³ıµÚ " + (num+1) + " ºÅÁôÑÔ....Ok¡£\n");
	return 1;
}

private int do_followup(string arg)
{
	mapping *notes, note;
	int num;
	string title, *text;

	if( !arg || sscanf(arg, "%d", num)!=1 )
		return notify_fail("Ö¸Áî¸ñÊ½£ºfollowup <ÁôÑÔ±àºÅ>\n");
	notes = query("notes");
	if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
		return notify_fail("Ã»ÓĞÕâÕÅÁôÑÔ¡£\n");

	num--;

	if(strsrch(notes[num]["title"], "Re:")!=-1)
		title = notes[num]["title"];
	else title = "Re:" + notes[num]["title"];

	note = allocate_mapping(4);
	note["title"] = title;
	note["author"] = this_player()->name_id(1);
	note["time"] = time();

	// ´¦Àí»ØÓ¦µÄ post ÏÔÊ¾ÄÄĞ©ĞĞ
	text = explode( notes[num]["msg"], "\n" );

	title = sprintf(GRN"> %s ÔÚ %s ÁôÏÂÕâÆªÁôÑÔ£º\n\n"NOR,
		notes[num]["author"],
		"[" + ctime(notes[num]["time"])[0..15] + "]");

	num = sizeof(text);

	// Ö»ÏÔÊ¾ 30 ĞĞ
	if(num>30) num = 30;
	for(int i=0; i<num; i++ ) {
		if( text[i] == "" || strsrch(text[i], "> ") != -1) continue;
		if(strsrch(text[i],"[")!=-1)
			title += GRN + "> " + text[i] + NOR + "\n";
		else title += GRN + "> " + text[i] + "\n";
	}

	title += "\n";
	note["msg"] = title;
	this_player()->edit( (: done_post, this_player(), note :), title );
	return 1;
}

