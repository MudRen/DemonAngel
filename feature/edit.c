//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// edit.c

void input_line(string line, string text, function callback);

int edit(function callback)
{
	write("结束离开用 '.'，取消输入用 '~q'，使用内建列编辑器用 '~e'。\n");
	write("─────────────────────────────\n");
	input_to( (:input_line:), "", callback);
	return 1;
}

void input_line(string line, string text, function callback)
{
	if( line=="." ) {
		(*callback)(text);
		return;
	} else if( line=="~q" ) {
		write("输入取消。\n");
		return;
	} else if( line=="~e" ) {
	} else
		text += line + "\n";
	input_to( (:input_line:), text, callback);
}
