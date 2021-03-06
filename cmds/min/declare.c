//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/declare.c
// by smallpen
// modify by bor @DA, 3/6 2003 for war, peace

#pragma optimize
#pragma save_binary

#include <ansi.h>

//inherit F_CLEAN_UP;			// 由于 war 的关系, 取消此继承, 不过造成记忆体没办法释放, 自己想一下怎么改吧

string show_declare(object me,string id);
void do_wait_war_end(string id, string enemy_id);

int main(object me, string arg)
{
        object ob;
        string id, action,country;

        seteuid(getuid());
        if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
        if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");

	id = me->query("kingdom/id");
        if( !arg ) {
                show_declare(me, id);
                return 1;       
        }
        
        if( sscanf(arg, "%s with %s", action, country)!=2 ) {
                if( sscanf(arg, "%s",country)!=1) {
                        return notify_fail("指令格式 : declare <war/peace/hate/forgive/war> with 某国 \n");}
                if(!check_kingdom(country)) {
                        return notify_fail("没有这个国家\n");}
                else {
                        show_declare(me,country);
                        return 1;
                }
	}
        if( action=="hate") {
                if(country==id) return notify_fail("你不能敌视自己");
                if(!check_kingdom(country)) return notify_fail("没有这个国家\n");
                if(kingdom_data(id, "declare","check","hate",country)) return notify_fail("此国已经被贵国敌视了。\n");
                if(!kingdom_data(id, "declare", "add", "hate",country)) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                if(!kingdom_data(country,"declare","add","hated", id)) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                write(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "宣布从现在起敌视" +to_chinese_kingdom(country) + "。\n");
                shout(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "宣布从现在起敌视"+to_chinese_kingdom(country)  + "。\n");
	} else if(action=="forgive") {
                if(country==id) notify_fail("你不能解除敌视。\n");
                if(!check_kingdom(country)) return notify_fail("没有这个国家。\n");
                if(!kingdom_data(id, "declare", "check", "hate", country)) return notify_fail("贵国没有敌视此国。\n");
                if(!kingdom_data(id, "declare", "sub", "hate", country)) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                if(!kingdom_data(country,"declare", "sub", "hated", id)) return notify_fail("国家资料有误，没办法将对方写入资料内。\n");
                write(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "宣布从现在起停止敌视" +to_chinese_kingdom(country) + "。\n");
                shout(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "宣布从现在起停止敌视"+to_chinese_kingdom(country)  + "。\n");
        } else if(action == "war") {	// by bor @DA, 3/6 2003
        	// 目前 war, peace 暂时不判定对方是否有大臣... 呵呵, 偷打 @@
                if(country==id) return notify_fail("你不能跟自己战争。\n");
                if(!check_kingdom(country)) return notify_fail("没有这个国家。\n");
        	if(kingdom_data(id, "ally","check",country)) return notify_fail("贵国还跟他们结盟中, 不能直接宣战。\n");
                if(kingdom_data(id, "war", "check", country, 1)) return notify_fail("贵国跟该国家正在战争中。\n");
		kingdom_data(id, "war", "set", country);
		kingdom_data(country, "war", "set", id);
		call_out( "do_wait_war_end", kingdom_data(id, "war", "query_par", country, "time"), id, country);
                write(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "宣布与" +to_chinese_kingdom(country) + "互相宣战, 进行战争。\n");
                shout(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "宣布与" +to_chinese_kingdom(country)  + "互相宣战, 进行战争。\n");
	} else if(action == "peace") {	// by bor @DA, 3/6 2003
                if(country==id) return notify_fail("你不能对自己国家送出和平。\n");
                if(!check_kingdom(country)) return notify_fail("没有这个国家。\n");
                if(!kingdom_data(id, "war", "check", country, 1)) return notify_fail("贵国没有和该国家战争。\n");
		call_out( "do_wait_war_end", 0, id, country);
                write(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "对" +to_chinese_kingdom(country) + "送出和平信, 两国从此和睦相处。\n");
                shout(HIY"我 - " + NOR+me->short(1)+"代表"+to_chinese_kingdom(id) + "对" +to_chinese_kingdom(country)  + "送出和平信, 两国从此和睦相处。\n");
	}
	return 1;
}

string show_declare(object me,string id)
{
        string *list,*list1,str="";
        int i;
        str += sprintf("目前%s的交战国有：\n\n",to_chinese_kingdom(id) );
                if(!list = kingdom_data(id,"declare","query_all","hate"))
                        str += "贵国尚无交战国。\n\n";
                else {
                        for(i=0; i<sizeof(list);i++) {
                                str += sprintf("%s\n",full_kingdom(list[i]));
                        }
                        str += sprintf("\n共 %d 国。\n\n",sizeof(list));
                }
                str += sprintf("目前敌视%s的国家有：\n\n",to_chinese_kingdom(id) );
                if(!list1 = kingdom_data(id,"declare","query_all","hated"))
                        
                        str += "无国家敌视贵国。\n\n";
                else {
                        for(i=0; i<sizeof(list1);i++) {
                                str += sprintf("%s\n",full_kingdom(list1[i]));
                        }
                        str += sprintf("\n共 %d 国。\n\n",sizeof(list1));
                }
                return me->start_more(str);
                
}


// 各位可以从下面的写法, 可以延伸到 logind.c 上, 就是固定时间 reboot ...
int query_war_end() { return find_call_out("do_wait_war_end"); }

// war 程式拉 ~~ 一小时为限制, 时间到就结束
void do_wait_war_end(string id, string enemy_id)	// by bor @DA, 3/6 2003
{
	mapping war;
	int score, score_, gold;

	war = kingdom_data(id, "war", "query", enemy_id);

	shout("在这场战争中, "+full_kingdom(id)+"一共从"+full_kingdom(enemy_id)+"掠夺了 "+war["gold"]+" 枚金币。\n");
	write("在这场战争中, "+full_kingdom(id)+"一共从"+full_kingdom(enemy_id)+"掠夺了 "+war["gold"]+" 枚金币。\n");
	shout("并宰了对方 "+war["npc"]+" 只生物, 摧毁了 "+war["room"]+" 间房间。\n");
	write("并宰了对方 "+war["npc"]+" 只生物, 摧毁了 "+war["room"]+" 间房间。\n");
	shout("并杀了对方 "+war["enemy"]+" 名玩家, 摧毁了 "+war["building"]+" 座建筑物。\n\n");
	write("并杀了对方 "+war["enemy"]+" 名玩家, 摧毁了 "+war["building"]+" 座建筑物。\n\n");
	shout("在这场战争中, "+full_kingdom(enemy_id)+"一共从"+full_kingdom(id)+"掠夺了 "+war["gold_"]+" 枚金币。\n");
	write("在这场战争中, "+full_kingdom(enemy_id)+"一共从"+full_kingdom(id)+"掠夺了 "+war["gold_"]+" 枚金币。\n");
	shout("并宰了对方 "+war["npc_"]+" 只生物, 摧毁了 "+war["room_"]+" 间房间。\n");
	write("并宰了对方 "+war["npc_"]+" 只生物, 摧毁了 "+war["room_"]+" 间房间。\n");

	shout("并杀了对方 "+war["enemy_"]+" 名玩家, 摧毁了 "+war["building_"]+" 座建筑物。\n\n");
	write("并杀了对方 "+war["enemy_"]+" 名玩家, 摧毁了 "+war["building_"]+" 座建筑物。\n\n");

	score  = war["building"]  * 10 + war["enemy"]  * 5 + war["npc"] *1 + war["room"] /10;
	score_ = war["building_"] * 10 + war["enemy_"] * 5 + war["npc_"]*1 + war["room_"]/10;

	if( score > score_ ) {
		shout("最后判定"+full_kingdom(id)+"赢得了这场战争。\n");
		write("最后判定"+full_kingdom(id)+"赢得了这场战争。\n");
		gold = (score - score_) * 1000;
		shout(full_kingdom(enemy_id)+"必须赔偿"+full_kingdom(id)+" "+gold+" 枚金币。\n\n");
		write(full_kingdom(enemy_id)+"必须赔偿"+full_kingdom(id)+" "+gold+" 枚金币。\n\n");
		kingdom_data(id, "data", "add", "gold", gold);
		kingdom_data(enemy_id, "data", "sub", "gold", gold);
	} else if( score < score_ ) {
		shout("最后判定"+full_kingdom(enemy_id)+"赢得了这场战争。\n");
		write("最后判定"+full_kingdom(enemy_id)+"赢得了这场战争。\n");
		gold = (score_ - score) * 1000;
		shout(full_kingdom(id)+"必须赔偿"+full_kingdom(enemy_id)+" "+gold+" 枚金币。\n\n");
		write(full_kingdom(id)+"必须赔偿"+full_kingdom(enemy_id)+" "+gold+" 枚金币。\n\n");
		kingdom_data(id, "data", "sub", "gold", gold);
		kingdom_data(enemy_id, "data", "add", "gold", gold);
	} else {
		shout("最后判定"+full_kingdom(id)+"与"+full_kingdom(enemy_id)+"不分胜负。\n");
		write("最后判定"+full_kingdom(id)+"与"+full_kingdom(enemy_id)+"不分胜负。\n");
	}

	kingdom_data(id, "war", "del", enemy_id);
	kingdom_data(enemy_id, "war", "del", id);

	return ;
}

int help(object me)
{
        write(@HELP

指令格式 : declare <war/peace/hate/forgive> with <国家> - 国王大臣专用
           declare              看自己国家的战争状况。
           declare <kingdom>    看某个国家的战争状况。
                                                                                
这个指令可以和其他国家宣战/谈和/敌视/解除敌视。
如果不加任何参数，就可以看见国家的战争状况。
                                                                                
当两个国家发生摩擦时, 可以先对对方宣布敌视以表达不满, 当 A 国开始敌
视 B 国时, AB 两国的关卡会全面对对方的人民封闭, 且 A 国的战斗生物会主
动攻击 B 国人民, 当 B 国的生物被 A 国国民在 B 国境外消灭时, 战神会取
走该生物的魂魄。在敌视状态下, A 国不得攻打 B 国的关卡和建筑物。
                                                                                
敌视状态可以用 declare forgive with <国家> 解除。
                                                                                
当两国关系恶劣到必须发动全面性战争时, 两国便必须互相宣战以进入战斗
状态。
                                                                                
在这个世界里, 宣战的国际方式是 : 先递送战书给对方的国王或大臣, 并
等待对方的回音, 如果对方一直不回应, 那么就无法进入战争状态。只要进
入交战状态, 战争就可以随时发生。一旦跟其他国家宣战成立, 双方所设立
的关卡和特殊禁区都会全面封锁彼此的部队, 而当一方的人员或部队进入敌
国境内, 将会遭到对方军事部队的主动攻击, 双方可以靠着消灭对方的生物
与摧毁建筑物得到胜利点数, 在二到三天(真实时间约 2-3 小时)的战争过程
后, 系统会统计双方胜利点数并宣布胜利的一方。如果在战争中，战争双方
彼此又宣战了一次，则战争的持续时间便会再延长两天(真实时间为两个小时)。
                                                                                
未接上大陆的国家不能对其他国家宣战或敌视。
                                                                                
战争状态可以由双方 declare peace with <国家> 解除。解除战争状态时，
如果要求解除方是战败方，那系统仍将会统计战争结果，战败的一方仍需要
赔偿。若要求停战的一方是战胜方，则不统计战果。
                                                                                
注意 : 在战争中死亡的人将直接通过战神殿复活。战神会给予战死者惩罚,
他不像月神那么和善。如果是一般 mob 战死, 他的灵魂将会被监禁, 在下
次 reboot 前都不会再回到原位。事实上, 只要 mob 踏出国门, 他的灵魂
就由战神掌握了。

HELP
        );
        return 1;
}       
