//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/usr/ident.c
// by bor @RG, 5/19 2003

#pragma optimize
#pragma save_binary

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string type, str="";

	seteuid(getuid(me));
	if(!arg) return notify_fail("ʹ�ø�ʽ : ident <��Ʒ>\n");
	if( !(ob = present(arg, me)) ) return notify_fail("������û����һ��������\n");

	message_vision(HIC"$N��ͷ����"NOR"$nڤ�� !\n\n", me, ob);
	me->start_busy(2);

	switch( ob->query("type") ) {
		case "ring":		type = "��ָ";		break;
		case "shield":		type = "����";		break;
		case "body":		type = "����";		break;
		case "gloves":		type = "����";		break;
		case "necklace":	type = "����";		break;
		case "boots":		type = "Ь��";		break;
		case "armor":		type = "�ۻ�";		break;
		case "cloak":		type = "����";		break;
		case "head":		type = "ͷ��";		break;
		case "leggings":	type = "�ּ�";		break;

		case "blade":		type = "��������";	break;
		case "fork":		type = "��������";	break;
		case "staff":		type = "��������";	break;
		case "throwing":	type = "Ͷ��������";	break;
		case "wand":		type = "ħ��������";	break;
		case "spear":		type = "ì�������";	break;
		case "whip":		type = "��������";	break;
		case "axe":		type = "��������";	break;
		case "hammer":		type = "��������";	break;
		case "dagger":		type = "ذ��������";	break;
		case "sword":		type = "��������";	break;
	}

	if( ob->query("armor_type") ) {
		str += sprintf("���� : %s(%s)  ���� : %d\t��ֵ : %d %s\n\n", ob->query("name"), capitalize(ob->query("id")), ob->query_weight(), ob->query("value"), "ö���" );
		str += sprintf("��ʽ : ����    �������� : %s\t���ߵȼ� : %d    �˺������� : %d\n\n", type, ob->query("armor_prop/ac"), ob->query("armor_prop/db") );
		str += sprintf("ʹ�õȼ� : %d    ����� : %s\n", ob->query("level"), ob->query("kingdom")?ob->query("kingdom"):"???" );
		str += "\n����ֵ : ";
		if(ob->query("add_attr"))
		foreach( string add, int tmp in ob->query("add_attr") ) {
			str += sprintf("%s : %d, ", add, tmp );
		}
	} else if( ob->query("skill_type") ) {
		str += sprintf("���� : %s(%s)  ���� : %d    ��ֵ : %d %s\n\n", ob->query("name"), capitalize(ob->query("id")), ob->query_weight(), ob->query("value"), "ö���" );
		str += sprintf("��ʽ : %s  �ȼ� : %d\t��Ҫ���� : %d    ����˺��� : %d\n\n", type, ob->query("level"), ob->query("skill"), ob->query("weapon_prop/Mh") );
		str += sprintf("����� : %s\n", ob->query("kingdom")?ob->query("kingdom"):"???" );

		if( ob->query("invoke_magic") ) {
			str += sprintf("\n��ӡħ�� : %s       ʣ����� : %d    ����� : %d%%\n", ob->query("invoke_magic"), ob->query_temp("invoke_times"), ob->query_temp("broken") );
		}
		str += "\n����ֵ : ";
		if(ob->query("add_attr"))
		foreach( string add, int tmp in ob->query("add_attr") ) {
			str += sprintf("%s : %d, ", add, tmp );
		}
	} else return notify_fail("�ⲻ��װ����������\n");

	write(str+"\n");
	return 1;
}  

int help(object me)
{
	write ("ʹ�ø�ʽ��ident <��Ʒ>\n");
	return 1;
}    

/*
���ͷ���ų����ߤλ���ڤ�� !
���� : �����ߤλ���(Newbie's war ring)  ���� : 2        ��ֵ 70 ö���
��ʽ : ����     �������� : ��ָ ���ߵȼ� : 0    �˺������� : 2
ʹ�õȼ� : 5    ����� : neve_island

���� : ���鷨��(Holy soul staff)        ���� : 359      ��ֵ 2410 ö���
��ʽ : �������� �ȼ� : 80       ��Ҫ���� : 160  ����˺��� : 80
����� : shogunate
��ӡħ�� : ����֮��(Spirit_hammer)       ʣ����� : 10   ����� : 80%
����ֵ :   �ǻ� : 5

���� : ��֮��(Staff of moon)    ���� : 128      ��ֵ 550 ö���

��ʽ : �������� �ȼ� : 18       ��Ҫ���� : 36   ����˺��� : 18

����� : ??

��ӡħ�� : ������(Cure)  ʣ����� : 5    ����� : 0%

> 
���� : а����(Dragon wand)      ���� : 56       ��ֵ 710 ö���

��ʽ : ħ��������       �ȼ� : 25       ��Ҫ���� : 50   ����˺��� : 20

����� : ??

��ӡħ�� : �����(Dragon_breath)         ʣ����� : 10   ����� : 60%


*/