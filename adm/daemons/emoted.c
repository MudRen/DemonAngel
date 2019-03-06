//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /adm/daemons/emoted.c
// modify by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_SAVE;

mapping emote;

void create()
{
        seteuid(getuid());
        if( !restore() && !mapp(emote) ) emote = ([]);
}

int remove()
{
        save();

        return 1;
}

string query_save_file() { return DATA_DIR + "emoted"; }

// chat* hmm pawlo ����
// verb == hmm
// arg  == pawlo ����
// ���еı���  Ϊ�ڶ�����
varargs mixed do_emote(object me, string verb, string arg, int channel_emote)
{
        string str, my_gender, target_gender, msg_postfix, rest="";
        object target;
//      $N��            �Լ������֡�
//      $n��            ��������֡�
//      $P��            �Լ����˳ƴ����ʡ�
//      $p��            ������˳ƴ����ʡ�
//      $T��            emote �ĵڶ���������

        if( !environment(me) ) return 0;
        if( !mapp(emote) || undefinedp(emote[verb]) ) return 0;
        if(me->query("quiet")==1) return notify_fail(HIR"�����ڱ������У����ʺϿ��ڱ���κ������\n"NOR);

        my_gender = me->query("gender");        // ȡ���Լ����Ա�
        // Determine the pattern to be searched and the target.
        if( stringp(arg) && arg != "" ) {
                sscanf(arg, "%s %s", arg, rest);        // ˳��ȡ�� player �� �ڶ�����
                if( !target = present(arg, environment(me)) ) {
                        target = find_player(arg);
                        if(rest!="") msg_postfix = "_rest";
                        if( !objectp(target) ) {
                                if( rest!="") rest = arg +" "+rest ;
                                else rest = arg;
                                msg_postfix = "_rest";
                        }
                        else {
                                target_gender = target->query("gender");        // ȡ��Ŀ����Ա�
				if(target->query("env/no_emote")) return 0;
                                if( target==me ) {
                                        msg_postfix = "_self";
                                        target = 0;
                                } else msg_postfix = "_target";
                        }
                }
                else {
                        target_gender = target->query("gender");
                        if(target->query("env/no_emote")) return 0;
                        if( target==me ) {
                                msg_postfix = "_self";
                                target = 0 ;
                        } else msg_postfix = "_target" ;
                }
                // �����µڶ������Ļ����� XXX_rest Ϊ��ʾ�ķ���
/* mark for janmin
                if(rest!="") msg_postfix = "_rest";
                if( !objectp(target) ) {
                        if( rest!="" ) rest = arg +" "+rest;
                        else rest = arg;
                        msg_postfix = "_rest";
                }
*/
        } else msg_postfix = "";        // ֻ�� emote û�м��֣���ֻ��һ������ʱ


        // �Լ����������Ĵ���
        if( stringp(str = emote[verb]["myself" + msg_postfix]) ) {
                str = replace_string(str, "$N", me->name(channel_emote));
                str = replace_string(str, "$P", gender_self(my_gender));
                str = replace_string(str, "$n", objectp(target)?target->name():gender_self(my_gender) );
                str = replace_string(str, "$p", objectp(target)?gender_pronoun(target_gender):gender_pronoun(my_gender) );
                str = replace_string(str, "$T", stringp(rest)?rest:"");
                if( !channel_emote ) message("vision", CYN+str+NOR, me);
        }
        // �Է�������ѶϢ����
        if( objectp(target) && (msg_postfix=="_target"?stringp(str = emote[verb]["target"]):stringp(str = emote[verb]["target_rest"])) ) {
                str = replace_string(str, "$N", me->name(channel_emote));
                str = replace_string(str, "$P", gender_pronoun(my_gender));
                str = replace_string(str, "$n", target->name());
                str = replace_string(str, "$p", gender_self(target_gender));
                str = replace_string(str, "$T", stringp(rest)?rest:"");

                if( !channel_emote ) message("vision", CYN+str+NOR, target);
        }

        // �����˿����Ĵ���
        if( stringp(str = emote[verb]["others"+msg_postfix]) ) {
                str = replace_string(str, "$N", me->name(channel_emote));
                str = replace_string(str, "$P", gender_pronoun(my_gender));
                str = replace_string(str, "$n", objectp(target)?target->name():gender_pronoun(my_gender) );
                str = replace_string(str, "$p", objectp(target)?gender_pronoun(target_gender):gender_pronoun(my_gender) );
                str = replace_string(str, "$T", stringp(rest)?rest:"");
                if( !channel_emote ) {
                	if(objectp(target)) message("vision", CYN+str+NOR, environment(target), ({me, target}));
                	else message("vision", CYN+str+NOR, environment(me), ({me, target}));
                } else return str;
        }

        if( channel_emote ) return 0;

        // Let NPC know we are doing emote on him.
        if( objectp(target) ) target->relay_emote(me, verb);
        return 1;
}

int set_emote(string pattern, mapping def)
{
        emote[pattern] = def;
        return save();
}
int delete_emote(string pattern)
{
        map_delete(emote, pattern);
        return save();
}
mapping query_emote(string pattern)

{
        if( !undefinedp(emote[pattern]) ) return emote[pattern];
        else return ([]);
}
string *query_all_emote()
{
        return keys(emote);
}
