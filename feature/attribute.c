//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /feature/attribute.c

#include <dbase.h>
#include <skill.h>

int query_str()
{
	return (int)query("str") + (int)query("apply/str")
		+ query_temp("apply/str");
}

int query_con()
{
	return (int)query("con") + (int)query("apply/con") / 5
		+ query_temp("apply/con");
}

int query_int()
{
	return (int)query("int") + (int)query("apply/int") / 5
		+ query_temp("apply/int");
}

int query_dex()
{
	return (int)query("dex") + (int)query("apply/dex") / 5
		+ query_temp("apply/dex");
}

int query_kar()
{
	return (int)query("kar") + (int)query("apply/kar") / 4
		+ query_temp("apply/composure");
}

int query_sta()
{
	return (int)query("sta") + (int)query("apply/sta") / 4
		+ query_temp("apply/sta");
}

int query_hp()
{
	return (int)query("hp");
}
int query_mp()
{
	return (int)query("mp");
}

int query_base_hp()
{
	return 34 + (int)query("con")*5 + (int)query("apply/con")*3 + (int)query_temp("apply/con")*2;
}

int query_base_mp()
{
	return 20 + (int)query("int")*5 + (int)query("apply/int")*3 + (int)query_temp("apply/int")*2;
}

int query_attr( string par )
{
	return (int)query(par);
}

int query_wl()
{
	return (int)query_temp("apply/wl")+(int)query("apply/wl");
}

int query_Mh()
{
	return (int)query_temp("apply/Mh")+(int)query("apply/Mh")+(int)query_temp("apply/damage")+(int)query("apply/damage");
}

int query_mh()
{
	return query_Mh()/2+1;
}

int query_ac()
{
	return (int)query_temp("apply/ac")+(int)query("apply/ac");
}

int query_db()
{
	return (int)query_temp("apply/db")+(int)query("apply/db");
}

int query_wp_sk(string type) // ��Ӧ����ҵ� wp ����
{
	return (int)query_skill(type,1)+(int)query_skill("advance_"+type,1);
}

