//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// terrain_daemon.c
// This file reads in the map of TMI-2's terrain and the accompanying
// descriptions. It defines two procedures which take a pair of integers
// and return the short and long description of the room at the x,y
// coordinates passed. It runs as a daemon, and it will load the first
// time it's called. Written by Mobydick@TMI in July 1992, to interact
// with a modified version of the virtual room server written by Truilkan
// and Whiplash.
// Added the exits function and corrected a bug in the terrain reader on
// 8-17-92, Mobydick

#define TERRAINPATH "/d/grid/data/grid.terrain"
#define DESCPATH "/d/grid/data/grid.descs"
#define EXITPATH "/d/grid/data/grid.exits"

mixed *terrain ;
string *descs, *ldescs ;
mixed *exits ;

void create() {

	int i, SIZE, NUMDESCS;
	string str, str2 ;

	seteuid(getuid()) ;

	SIZE = sizeof(explode(read_file(EXITPATH), "\n"));		// by bor @DA, 3/11 2003
	NUMDESCS = SIZE;

	terrain = allocate(SIZE) ;
	exits = allocate(SIZE) ;
	descs = allocate(NUMDESCS) ;
	ldescs = allocate(NUMDESCS) ;
	for (i=0 ; i<SIZE ; i++) {
		str = read_file (TERRAINPATH,i+1,1) ;
		sscanf (str,"%s\n",str2) ;
		terrain[i] = explode (str2," ") ;
	}
	for (i=0 ; i<SIZE ; i++) {
		str = read_file (EXITPATH,i+1,1) ;
		sscanf(str,"%s\n",str2) ;
		exits[i] = explode (str2," ") ;
	}
	for (i=0 ; i<NUMDESCS ; i++) {
		str = read_file(DESCPATH,i*2+1,1) ;
		sscanf(str,"%s\n",descs[i]) ;
		ldescs[i] = read_file(DESCPATH,i*2+2,1) ;
	}
}

string get_short(int x, int y) {

	int i ;

	sscanf(terrain[x][y],"%d",i) ;
	return descs[i] ;
}

string get_long(int x, int y) {

	int i ;

	sscanf(terrain[x][y],"%d",i) ;
	return ldescs[i] ;
}

int get_exits(int x, int y) {

	int i ;

	sscanf(exits[x][y],"%d",i) ;
	return i ;
}
