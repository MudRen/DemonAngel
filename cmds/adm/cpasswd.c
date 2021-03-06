//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/adm/cpasswd.c
// by bor @DA

inherit F_CLEAN_UP;

string random_pass();

int main(object me, string arg)
{
	object ob, ob_link;
	string pass;

	seteuid(getuid());
	if( !arg ) return notify_fail("指令格式 : cpasswd <玩家>\n");

	pass = random_pass();
	if( ob = find_player(arg) ) {
		ob_link = ob->query_temp("link_ob");
		ob_link->set("password", crypt(pass, 0) );
		ob_link->save();
        } else {
		ob = new(LOGIN_OB);
		ob->set("id",arg);
		if( !ob->restore() ) return notify_fail("没有这个玩家。\n");
		ob->set("password", crypt(pass, 0) );
		ob->save();
		destruct(ob);
	}
	write("密码更改成 : "+pass+"\n");
	return 1;
}

string random_pass()
{
	string *a1 = ({"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p",
	"q","r","s","t","u","v","w","x","y","z","1","2","3","4","A","B","C","D","E","F",
	"G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
	"5","6","7","8","9","0"
	}), pass="", b1;

	// 创造 8 个 pass 出来。
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

指令格式 : cpasswd <玩家>

由于许多人会忘记密码，因而写出该指令来清除原本的
密码。

相关指令 : passwd

HELP
	);
	return 1;
}

