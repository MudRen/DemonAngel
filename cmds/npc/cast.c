//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /cmds/npc/cast.c
// modify bor @DA

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string spells, spl, trg;
	object target;
	
	seteuid(getuid());

	if( me->is_busy() ) return notify_fail("( ����һ��������û����ɣ�����ʩ����)\n");
	if( environment(me)->query("no_cast") ) return notify_fail("���ﲻ׼ʩ����\n");

	if( !arg ) return notify_fail("ָ���ʽ��cast <����> [on <Ŀ��>]\n");
	if( sscanf(arg, "%s on %s", spl, trg)==2 ) {
		if( spl == " " ) return notify_fail("ָ���ʽ��cast <����> [on <Ŀ��>]\n");
		target = present(trg, environment(me));
		if( !target ) target = present(trg, me);
		if( !target ) return notify_fail("����û�� " + trg + "��\n");
	} else {
		spl = arg;
		target = 0;
	}

	if( !me->query_spell(spl, 1) ) return notify_fail("��ûѧϰ�����ķ�����\n");
	return (int)SPELL_D(spl)->cast_spell(me, target);
}

int help (object me)
{
        write(@HELP
ָ���ʽ : cast <����> on <����>
 
���ָ������ʩ����ĳ������. ��ָ������ʱ, ��ʩ�����Է���, ���
ʩ���Լ�����, ����ս����ʩ�����Է���, ���Զ�ʩ�ڵ������ϡ�

�������ָ��: magic, learn, spells
 
HELP
	);
        return 1;
}
