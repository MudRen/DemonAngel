//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/adm/cpasswd.c
// by bor @DA

inherit F_CLEAN_UP;

string random_pass();

int main(object me, string arg)
{
	object ob, ob_link;
	string pass;

	seteuid(getuid());
	if( !arg ) return notify_fail("ָ���ʽ : cpasswd <���>\n");

	pass = random_pass();
	if( ob = find_player(arg) ) {
		ob_link = ob->query_temp("link_ob");
		ob_link->set("password", crypt(pass, 0) );
		ob_link->save();
        } else {
		ob = new(LOGIN_OB);
		ob->set("id",arg);
		if( !ob->restore() ) return notify_fail("û�������ҡ�\n");
		ob->set("password", crypt(pass, 0) );
		ob->save();
		destruct(ob);
	}
	write("������ĳ� : "+pass+"\n");
	return 1;
}

string random_pass()
{
	string *a1 = ({"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p",
	"q","r","s","t","u","v","w","x","y","z","1","2","3","4","A","B","C","D","E","F",
	"G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
	"5","6","7","8","9","0"
	}), pass="", b1;

	// ���� 8 �� pass ������
	for(int i=0;i<8;i++) {
		b1 = a1[random(sizeof(a1))];
		if( strsrch(b1, pass) != -1 ) b1 = a1[random(sizeof(a1))];
		if( strsrch(b1, pass) != -1 ) b1 = a1[random(sizeof(a1))];
		if( strsrch(b1, pass) != -1 ) b1 = a1[random(sizeof(a1))];
		pass += b1;
	}

	return pass;
}

int help(object me)
{
	write(@HELP

ָ���ʽ : cpasswd <���>

��������˻��������룬���д����ָ�������ԭ����
���롣

���ָ�� : passwd

HELP
	);
	return 1;
}

