//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// updated.c

void create() { seteuid(getuid()); }

void check_user(object ob)
{
	if( ob->query_hp()>=5000 ) ob->set("hp", ob->query("base_hp") );
	if( ob->query_mp()>=5000 ) ob->set("mp", ob->query("base_mp") );
	if( ob->query("max_hp") ) ob->delete("max_hp");
	if( ob->query("max_mp") ) ob->delete("max_mp");
}
