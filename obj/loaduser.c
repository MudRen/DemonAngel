//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /obj/loaduser.c

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;
inherit F_CLEAN_UP;

int restore()
{
	seteuid(this_object()->query("id"));
	return ::restore();
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

        id = query("id", 1);
        if( !stringp(id) ) return 0;
        return sprintf(DATA_DIR+ "user/%c/%s", id[0], id);
}

int save()
{
	int res;

//	save_autoload();
	res = ::save();
	clean_up_autoload();		// To save memory
	return res;
}
