//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/swer.c
// by smallpen

#pragma optimize
#pragma save_binary
#include <ansi.h>
inherit ROOM;
int do_adopt_check(object me,object ob,string become1);
int do_swear_check(object me,object ob);
int do_show_family(object me);
void init()
{
        add_action("do_adopt", "adopt");
        add_action("do_swear","swear");
}

int do_adopt(string arg)
{
        string who="",word="干妈",sex="你",word1="干女儿",sex1="你",name;
        string *parent,*child,*brother;
        int i;
        object me = this_player(),ob;
        
        seteuid(getuid());
        
        parent = me->query("parent");
        child = me->query("child");
        brother = me->query("brother");
        if( me->is_busy()) return notify_fail("你现在正忙着。\n");
        if( me->is_fight() ) return notify_fail("你现在在战斗中。\n");
        if( !arg ) {
                do_show_family(me);
                return 1;
        } 
        if( sscanf(arg, "%s as %s" , name,who)!=2 ) return notify_fail("格式 : adopt <对象> as <child/parent>。\n");
        if( !(ob = present(name, environment(me)) )) return notify_fail("对方好像不在现场唷？\n");
        if( !(who=="child" || who=="parent")) return notify_fail("格式 : adopt <对象> as <child/parent>。\n"); 
        if( me->query("id")==ob->query("lover") ) return notify_fail("他已经是你家族的人了。\n");
        for(i=0;i<sizeof(parent);i++) {
                if(ob->query("id")==parent[i]) return notify_fail("他已经是你家族的人了。\n");
                }
        for(i=0;i<sizeof(child);i++) {
                if(ob->query("id")==child[i]) return notify_fail("他已经是你家族的人了。\n");
                }
        for(i=0;i<sizeof(brother);i++) {
                if(ob->query("id")==brother[i]) return notify_fail("他已经是你家族的人了。\n");
                }
        if( me->query("gender")=="女性") sex="你";
        if( ob->query("gender")=="男性") {
                sex1="你";
                word ="干爸";
                word1="干儿子";}
        if( who=="child") {
                write(sex+"打算收"+ob->query("name")+"当"+word1+"。\n");
                tell_object(ob,me->query("name")+"打算收"+sex1+"当"+word1+"。\n");
                tell_room(environment(me),sex+"打算收"+ob->query("name")+"当"+word1+"。\n",({me,ob}));
                me->set_temp("adopt",ob);
                me->set_temp("become","parent");
                if(me!=ob->query_temp("adopt")) call_out("do_adopt_check",10,me,ob,word1);
        }
        if( who=="parent") {
                write(sex+"打算拜"+ob->query("name")+"当"+word+"。\n");
                tell_object(ob,me->query("name")+"打算拜"+sex1+"当"+word+"。\n");
                tell_room(environment(me),sex+"打算拜"+ob->query("name")+"当"+word+"。\n",({me,ob}));
                me->set_temp("adopt",ob);
                me->set_temp("become","child");
                if(me!=ob->query_temp("adopt")) call_out("do_adopt_check",10,me,ob,word);
        }
        
                return 1;
}

int do_swear(string arg)
{
        string who="",sex="你",sex1="你";
        string *parent,*child,*brother;
        int i;
        object me = this_player(),ob;
        
        seteuid(getuid());
        
        parent = me->query("parent");
        child = me->query("child");
        brother = me->query("brother");
        if( me->is_busy()) return notify_fail("你现在正忙着。\n");
        if( me->is_fight() ) return notify_fail("你现在在战斗中。\n");
        if( !arg ) {
                do_show_family(me);
                return 1;
        } 
        if(sscanf(arg,"%s",who)==1) {
                if( !(ob = present(who, environment(me)) )) return notify_fail("对方好像不在现场唷？\n");
                if( me->query("id")==ob->query("lover") ) return notify_fail("他已经是你家族的人了。\n");
                for(i=0;i<sizeof(parent);i++) {
                        if(ob->query("id")==parent[i]) return notify_fail("他已经是你家族的人了。\n");
                }
                for(i=0;i<sizeof(child);i++) {
                        if(ob->query("id")==child[i]) return notify_fail("他已经是你家族的人了。\n");
                }
                for(i=0;i<sizeof(brother);i++) {
                        if(ob->query("id")==brother[i]) return notify_fail("他已经是你家族的人了。\n");
                }
                if( me->query("gender")=="女性") sex="你";
                if( ob->query("gender")=="男性") sex1="你";
                //兄弟
                if( me->query("gender")=="男性" && ob->query("gender")=="男性") {
                        write(sex+"打算与"+ob->query("name")+"结拜为兄弟。\n");
                        tell_object(ob,me->query("name")+"打算与"+sex1+"结拜为兄弟。\n");
                        tell_room(environment(me),sex+"打算与"+ob->query("name")+"结拜为兄弟。\n",({me,ob}));
                        me->set_temp("swear",ob);
                        me->set_temp("become","mm");
                        if(me!=ob->query_temp("swear")) call_out("do_swear_check",10,me,ob);
                }
                //兄妹
                if(  (me->query("gender")=="男性" && ob->query("gender")=="女性") ||  (me->query("gender")=="女性" && ob->query("gender")=="男性")) {
                        write(sex+"打算与"+ob->query("name")+"结拜为兄妹。\n");
                        tell_object(ob,me->query("name")+"打算与"+sex1+"结拜为兄妹。\n");
                        tell_room(environment(me),sex+"打算与"+ob->query("name")+"结拜为兄妹。\n",({me,ob}));
                        me->set_temp("swear",ob);
                        me->set_temp("become","mf");
                        if(me!=ob->query_temp("swear")) call_out("do_swear_check",10,me,ob);
                        }
                //姊妹
                if(  me->query("gender")=="女性" && ob->query("gender")=="女性")  {
                        write(sex+"打算与"+ob->query("name")+"结拜为姊妹。\n");
                        tell_object(ob,me->query("name")+"打算与"+sex1+"结拜为姊妹。\n");
                        tell_room(environment(me),sex+"打算与"+ob->query("name")+"结拜为姊妹。\n",({me,ob}));
                        me->set_temp("swear",ob);
                        me->set_temp("become","ff");
                        if(me!=ob->query_temp("swear")) call_out("do_swear_check",10,me,ob);
                }
        }
        else {
                return notify_fail("格式 : swear <对象>。\n");
        }
        return 1;
}

int do_adopt_check(object me,object ob,string become1)
{
        string *parent,*child;
        if( me==ob->query_temp("adopt") ) {
                
                if( me->query_temp("become")=="parent" && ob->query_temp("become")=="child")  {
                //收人作儿子    
                
                me->delete_temp("adopt");
                ob->delete_temp("adopt");
                me->delete_temp("become");
                ob->delete_temp("become");
                if( arrayp(child = me->query("child")) ) {
                        if( member_array(ob->query("id"), child)==-1 )
                                me->set("child", child + ({ob->query("id")}) );
                } else me->set("child", ({ob->query("id")}) );
                
                if( arrayp(parent = ob->query("parent")) ) {
                        if( member_array(me->query("id"), parent)==-1 )
                                ob->set("parent", parent + ({me->query("id")}) );
                } else ob->set("parent", ({me->query("id")}) );
                
                CHANNEL_D->do_channel(me, "chat",sprintf("我决定收%s当%s。", ob->name_id(1), become1));
                }
                if( me->query_temp("become")=="child" && ob->query_temp("become")=="parent")  {
                //拜人作儿子    
                me->delete_temp("adopt");
                ob->delete_temp("adopt");
                me->delete_temp("become");
                ob->delete_temp("become");
                if( arrayp(parent = me->query("parent")) ) {
                        if( member_array(ob->query("id"), parent)==-1 )
                                me->set("parent", parent + ({ob->query("id")}) );
                } else me->set("parent", ({ob->query("id")}) );
                
                if( arrayp(child = ob->query("child")) ) {
                        if( member_array(me->query("id"), child)==-1 )
                                ob->set("child", child + ({me->query("id")}) );
                } else ob->set("child", ({me->query("id")}) );
                CHANNEL_D->do_channel(ob, "chat",sprintf("我决定收%s当%s。", me->name_id(1), become1));
                }
                
                
}
        else {
                write("看来"+ob->query("name")+"不接受你的好意...\n");
                tell_object(ob,"你用一段时间的沉默，婉拒了"+me->short(1)+"的好意！\n");
                me->delete_temp("adopt");
                ob->delete_temp("adopt");
                me->delete_temp("become");
                ob->delete_temp("become");
                return 1;}
}

int do_swear_check(object me,object ob)
{
        string *brother,*brother1;
        if( me==ob->query_temp("swear") ) {
                
                if( ob->query_temp("swear")==me)  {
                if( arrayp(brother = me->query("brother")) ) {
                        if( member_array(ob->query("id"), brother)==-1 )
                                me->set("brother", brother + ({ob->query("id")}) );
                } else me->set("brother", ({ob->query("id")}) );
                
                if( arrayp(brother1 = ob->query("brother")) ) {
                        if( member_array(me->query("id"), brother1)==-1 )
                                ob->set("brother", brother1 + ({me->query("id")}) );
                } else ob->set("brother", ({me->query("id")}) );
                
                if(me->query_temp("become")=="mm") CHANNEL_D->do_channel(me, "chat",sprintf("我决定与%s结拜为兄弟。", ob->name_id(1)));
                if(me->query_temp("become")=="mf") CHANNEL_D->do_channel(me, "chat",sprintf("我决定与%s结拜为兄妹。", ob->name_id(1)));
                if(me->query_temp("become")=="ff") CHANNEL_D->do_channel(me, "chat",sprintf("我决定与%s结拜为姊妹。", ob->name_id(1)));
                me->delete_temp("swear");
                ob->delete_temp("swear");
                me->delete_temp("become");
                ob->delete_temp("become");
                return 1;}
                }
                
        else {
                write("看来"+ob->query("name")+"不接受你的好意...\n");
                tell_object(ob,"你用一段时间的沉默，婉拒了"+me->short(1)+"的好意！\n");
                me->delete_temp("swear");
                ob->delete_temp("swear");
                me->delete_temp("become");
                ob->delete_temp("become");
                return 1;}
}

int do_show_family(object me)
{
        string *parent,*child,*brother;
        parent = me->query("parent");
        child = me->query("child");
        brother = me->query("brother");
        write("你现在的家人有：\n");
        if(me->query("parent")) write("父母：" + implode(parent, ", ") + "。\n");
        if(me->query("lover")) write("配偶：" +me->query("lover") + "。\n");
        if(me->query("brother")) write("兄弟姊妹：" + implode(brother, ", ") + "。\n");
        if(me->query("child")) write("儿女：" + implode(child, ", ") + "。\n");
}
