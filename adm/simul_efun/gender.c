//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// gender.c

string gender_self(string sex)
{
	switch(sex) {
		case "女性": return "你";	break;
		default: return "你";
	}
}

string gender_pronoun(string sex)
{
	switch(sex) {
		case "中性神":	return "祂";	break;
		case "男性":	return "他";	break;
		case "女性":	return "她";	break;
		case "雄性":
		case "雌性":	return "牠";	break;
		default: return "它";
	}
}

