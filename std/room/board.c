//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /std/room/board

inherit ROOM;

void setup()
{
	string id, file;

	::setup();
	seteuid(getuid());
	id =  explode(base_name(this_object()), "/")[1];
	file =  explode(base_name(this_object()), "/")[2];
	load_object(KINGDOM_DIR+id+"/data/"+id+file);
}
