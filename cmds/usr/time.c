//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// time.c

inherit F_CLEAN_UP;

string time_string(int time);

int main(object me, string arg)
{
	write("������" + NATURE_D->game_time() + "��\n");
	write("����ʱ�̣�"+time_string( time()) +"\n");
	return 1;
}

string time_string(int time)
{
	return "���"+(int)(localtime(time)[5]-1911)+"��"+(localtime(time)[4]+1)+"��"
		+localtime(time)[3]+"��(����"+chinese_number(localtime(time)[6])+")"+localtime(time)[2]
		+"��"+localtime(time)[1]+"��"+localtime(time)[0]+"��";
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ������(��)֪�����ڵ�ʱ����

HELP
    );
    return 1;
}
