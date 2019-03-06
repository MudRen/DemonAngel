//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/channeld.c
 
#include <ansi.h>
#include <net/dns.h>

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
 
mapping channels = ([
	"sys":	([	"msg_speak": HIB "��ϵͳ��%s��%s\n" NOR, "wiz_only": 1 ]),
	"wiz":	([	"msg_speak": HIY "����ʦ��%s��%s\n" NOR,
				"msg_emote": HIY "����ʦ��%s" NOR,
				"wiz_only": 1
			]),
	"chat":	([	"msg_speak": HIC "�����ġ�%s��%s\n" NOR,
				"msg_emote": HIC "�����ġ�%s" NOR,
			 ]),
	"rumor":([	"msg_speak": HIM "��ҥ�ԡ�%s��%s\n" NOR,
				"msg_emote": HIM "��ҥ�ԡ�%s" NOR,
				"anonymous": "ĳ��"
			]),
	"music":([	"msg_speak": WHT "���������%s���ţ�%s\n" NOR,
				"msg_emote": WHT "���������%s" NOR
			 ]),
        "kingdom":([    "msg_speak": HIG"��%s��%s��%s\n" NOR,
                        "msg_emote": HIG"��%s��%s"NOR , "kingdom_only": 1
                ]),
]);
 
void create()
{
	seteuid(getuid());	// This is required to pass intermud access check.
}
 
varargs int do_channel(object me, string verb, string arg, int emote)
{
	object *ob;
	string *tuned_ch, who;

 	if( verb== "" ) return 0;
 
	// Check if this is a channel emote.
	if( verb[<1] == '*' ) {
		emote = 1;
		verb = verb[0..<2];
	}

	if( !mapp(channels) || undefinedp(channels[verb]) )
		return 0;

	if( userp(me) ) {
		if(channels[verb]["wiz_only"] && !wizardp(me) ) return 0;
		if( channels[verb]["kingdom_only"] && !me->query("kingdom") ) return 0;

//		if( arg==(string)me->query_temp("last_channel_msg") )
//			return notify_fail("�ý�̸Ƶ��˵���벻Ҫ�ظ���ͬ��ѶϢ��\n");

		// If we speaks something in this channel, then must tune it in.
		tuned_ch = me->query("channels");
		if( !pointerp(tuned_ch) )
			me->set("channels", ({ verb }) );
		else if( member_array(verb, tuned_ch)==-1 )
			me->set("channels", tuned_ch + ({ verb }) );

		// Support of channel emote
		if( emote ) {
			string vb, emote_arg;
			if( stringp(arg) ) {
				if( sscanf(arg, "%s %s", vb, emote_arg)!= 2 ) {
					vb = arg;
					emote_arg = "";
				}
				arg = EMOTE_D->do_emote(me, vb, emote_arg, 1);
				if( !arg ) arg = me->name_id(1) + vb + " " + emote_arg + "\n";
				if( channels[verb]["anonymous"] ) {
					if(!arg) return 0;
				}
			}
		}
	}

	if( channels[verb]["anonymous"] )
		who = channels[verb]["anonymous"];
	else if( userp(me) || !stringp(who = me->query("channel_id")) )
		who = me->query("name") + "(" + capitalize(me->query("id")) + ")";

	// Ok, now send the message to those people listening us.
	ob = filter_array( users(), "filter_listener", this_object(), channels[verb] );
	if( !arg ) return notify_fail("���Ѿ��� "+verb+" Ƶ���ˡ�\n");

	if( emote ) {
		string msg;
		if( !channels[verb]["msg_emote"] )
			return notify_fail("���Ƶ������ emote��\n");
		if( verb == "kingdom" )
			msg = sprintf(channels[verb]["msg_emote"], (me->query("kingdom/id")? to_chinese_kingdom(me->query("kingdom/id")):"ð����Ƶ��"), arg);
 		else msg = sprintf( channels[verb]["msg_emote"], arg );
//		if( msg[<1] != '\n' ) msg += "\n";
		message( "channel:" + verb, msg, ob );
	} else {
		string msg;
		if( verb == "kingdom" ) {
			msg = sprintf( channels[verb]["msg_speak"], (me->query("kingdom/id")? to_chinese_kingdom(me->query("kingdom/id")):"ð����Ƶ��"), who, arg);
		} else msg = sprintf( channels[verb]["msg_speak"], who, arg );
		if( strsrch(msg, '\n')==-1 ) msg += "\n";
		message( "channel:" + verb, msg, ob );
	}
/*	if( arrayp(channels[verb]["extra_listener"]) ) {
		channels[verb]["extra_listener"] -= ({ 0 });
		if( sizeof(channels[verb]["extra_listener"]) )
			channels[verb]["extra_listener"]->relay_channel(me, verb, arg);
	}
	
	if( !undefinedp(channels[verb]["intermud"])
	&&	base_name(me) != channels[verb]["intermud"] )
		channels[verb]["intermud"]->send_msg(
			channels[verb]["channel"], me->query("id"), me->name(1), arg, 0,
			channels[verb]["filter"] );
*/
//	if( userp(me) ) 
//		me->set_temp("last_channel_msg", arg);

	return 1;
}
 
int filter_listener(object ppl, mapping ch)
{
	// Don't bother those in the login limbo.
	if( !environment(ppl) ) return 0;
	
	if( ch["wiz_only"] ) return wizardp(ppl);
        if( ch["kingdom_only"] ) {
                if( this_player()->query("kingdom/id") != ppl->query("kingdom/id") ) return 0;
        }
	return 1;
}

// register_relay_channel()
//
// This function allows non-user objects like npcs, daemons, etc to sign-up
// a channel for listenin. The way non-user objects listening channels is
// via a mudlib apply function relay_channel().
/* 
void register_relay_channel(string channel)
{
	object ob;
 
	ob = previous_object();
	if( undefinedp(channels[channel]) || !ob) return;
	if( arrayp(channels[channel]["extra_listener"]) ) {
		if( member_array(ob, channels[channel]["extra_listener"]) >=0 ) return;
		channels[channel]["extra_listener"] += ({ ob });
	} else
		channels[channel]["extra_listener"] = ({ ob });
}
*/