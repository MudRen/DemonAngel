//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// edit.c

void input_line(string line, string text, function callback);

int edit(function callback)
{
	write("�����뿪�� '.'��ȡ�������� '~q'��ʹ���ڽ��б༭���� '~e'��\n");
	write("����������������������������������������������������������\n");
	input_to( (:input_line:), "", callback);
	return 1;
}

void input_line(string line, string text, function callback)
{
	if( line=="." ) {
		(*callback)(text);
		return;
	} else if( line=="~q" ) {
		write("����ȡ����\n");
		return;
	} else if( line=="~e" ) {
	} else
		text += line + "\n";
	input_to( (:input_line:), text, callback);
}
