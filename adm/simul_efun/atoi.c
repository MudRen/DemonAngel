//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// atoi.c

int atoi(string str)
{
	int v;

	if( !stringp(str) || !sscanf(str, "%d", v) ) return 0;
	return v;
}
