//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /feature/team.c

#include <ansi.h>
#include <command.h>
#include <dbase.h>
#include <origin.h>

static object leader, *team;

int set_leader(object ob)
{
	if( ob==this_object() )
		error("set_leader: Cannot set this_object() as leader.\n");
	leader = ob;
}

object query_leader() { return leader; }

int follow_me(object ob, string dir)
{
	if( ob != leader
	||	!living(this_object())
	||	!living(ob) )
	return 0;

	if( GO_CMD->main(this_object(), dir) ) return 1;
	tell_object(this_object(), HIG "�����" + ob->name() + "�ˡ�\n" NOR);
	return 0;
}

int add_team_member(object ob)
{
	if( ob==this_object() ) return 0;

	if( arrayp(team) ) {
		if( member_array(ob, team)==-1 ) {
			team += ({ ob });
			for(int i=sizeof(team)-1; i>=0; i--)
				team[i]->set_team(team);
		} else
			return 0;
	} else {
		team = ({ this_object(), ob });
		ob->set_team(team);
	}
	return 1;
}

int is_team_leader()
{
	return arrayp(team) && team[0]==this_object();
}

int set_team(object *t)
{
	team = t;
}

varargs int dismiss_team(object ob)
{
	int i;

	if( !arrayp(team) ) return 0;
	
	if( !ob ) {
		if( team[0]==this_object() ) {
			for(i=1; i<sizeof(team); i++)
				team[i]->set_team(0);
		} else {
			for(i=0; i<sizeof(team); i++)
				team[i]->dismiss_team( this_object() );
		}
		team = 0;
	} else
		team -= ({ ob });

	return 1;
}

object *query_team()
{
	return team;
}

