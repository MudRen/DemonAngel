//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// gender.c

string gender_self(string sex)
{
	switch(sex) {
		case "Ů��": return "��";	break;
		default: return "��";
	}
}

string gender_pronoun(string sex)
{
	switch(sex) {
		case "������":	return "�k";	break;
		case "����":	return "��";	break;
		case "Ů��":	return "��";	break;
		case "����":
		case "����":	return "��";	break;
		default: return "��";
	}
}

