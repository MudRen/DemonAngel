//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// time.c

inherit F_CLEAN_UP;

string time_string(int time);

int main(object me, string arg)
{
	write("现在是" + NATURE_D->game_time() + "。\n");
	write("现在时刻："+time_string( time()) +"\n");
	return 1;
}

string time_string(int time)
{
	return "民国"+(int)(localtime(time)[5]-1911)+"年"+(localtime(time)[4]+1)+"月"
		+localtime(time)[3]+"号(星期"+chinese_number(localtime(time)[6])+")"+localtime(time)[2]
		+"点"+localtime(time)[1]+"分"+localtime(time)[0]+"秒";
}

int help(object me)
{
     write(@HELP
指令格式: time

这个指令让你(你)知道现在的时辰。

HELP
    );
    return 1;
}
