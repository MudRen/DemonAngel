//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// help.c

#include "/doc/help.h"

inherit F_CLEAN_UP;

string *default_search = DEFAULT_SEARCH_PATHS;

int main(object me, string arg)
{
	int i;
	string file, *search;

	// If no topic specified, give the topics.
	if( !arg ) {
		cat(HELP_DIR + "help/topics");
		return 1;
	}

	// Else, try if a command name is specified.
	seteuid(getuid());
	if( stringp(file = me->find_command(arg)) ) {
		notify_fail("�����ָ����ڣ����ǲ�û����ϸ��˵���ļ���\n");
		return file->help(me);
	}

        // Find a kingdom introduction
        if (sscanf(arg,"kingdom %s",arg))
        {
                if (file_size(KINGDOM_DIR+arg+"/data/introduce.txt")==-1)
	                return notify_fail("�������û�м�顣\n");
                else {
                	me->start_more(read_file(KINGDOM_DIR+arg+"/data/introduce.txt"));
                	return 1;
                }
        }

	if( wizardp(me) ) search = WIZ_SEARCH_PATHS;
	else search = DEFAULT_SEARCH_PATHS;

	// Search the individual search path first.
//	if( pointerp(search = me->query("help_search_path")) ) {
	if( pointerp(search) ) {
		i = sizeof(search);
		while(i--) if( file_size(search[i] + arg)>0 ) {
			me->start_more( read_file(search[i] + arg) );
			return 1;
		}
	}

	// Support efun/lfun help with same name as other topics such as
	// ed() and ed command.
	sscanf(arg, "%s()", arg);

	// Finally, search the default search paths.
	if( pointerp(default_search) ) {
		i = sizeof(default_search);
		while(i--) if( file_size(default_search[i] + arg)>0 ) {
			me->start_more( read_file(default_search[i] + arg) );
			return 1;
		}
	}

	return notify_fail("û��������������˵���ļ���\n");
}

int help(object me)
{
	write(@HELP
ָ���ʽ��help <����>              ���磺> help cmds
          help <��������>()        ���磺> help call_out()

���ָ���ṩ�����ĳһ�������ϸ˵���ļ������ǲ�ָ�����⣬���ṩ���й�
������ļ���
HELP
	);
	return 1;
}
