//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
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
