//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
//#pragma optimize all

#include "/adm/simul_efun/atoi.c"
#include "/adm/simul_efun/chinese.c"
#include "/adm/simul_efun/file.c"
#include "/adm/simul_efun/gender.c"
#include "/adm/simul_efun/object.c"
#include "/adm/simul_efun/path.c"
#include "/adm/simul_efun/wizard.c"
#include "/adm/simul_efun/system.c"		// by bor
#include "/adm/simul_efun/kingdom.c"		// by bor

// This must be after gender.c
#include "/adm/simul_efun/message.c"

void create()
{
	seteuid(ROOT_UID);
	write("simul_efun loaded successfully.\n");
}
