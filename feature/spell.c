//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// /feature/spell.c

#include <ansi.h>
#include <dbase.h>

mapping spells;
mapping sp_learned;
mapping spell_map;

mapping query_spells() { return spells; }
mapping query_sp_learned() { return sp_learned; }

void set_spell(string spell, int val)
{
//	if( !find_object(SPELL_D(spell))
//	&&	file_size(SPELL_D(spell)+".c") < 0 )
//		error("F_SPELL: No such spell (" + spell + ")\n");

	if( !mapp(spells) ) spells = ([ spell: val ]);
	else spells[spell] = val;
}

int delete_spell(string spell)
{
	if( mapp(spells) ) {
		map_delete(spells, spell);
		if( mapp(sp_learned) ) {
			map_delete(sp_learned, spell);
			return undefinedp(sp_learned[spell]);
		}
		return undefinedp(spells[spell]);
	}
	return 0;
}

// This function 'map' a spell <spell> to another spell <mapped_to>.
// If 2nd argument not given, cancel the mapped spell <spell>.
varargs void map_spell(string spell, string mapped_to)
{
	if( !mapped_to && mapp(spell_map) ) {
		map_delete(spell_map, spell);
		return;
	}

//	if( !find_object(SPELL_D(spell))
//	&&	file_size(SPELL_D(spell)+".c") < 0 )
//		error("F_SPELL: No such spell (" + spell + ")\n");

	if( !mapp(spells) || undefinedp(spells[mapped_to]) )
		return;
		
	if( !mapp(spell_map) ) spell_map = ([ spell: mapped_to ]);
	else spell_map[spell] = mapped_to;
}

string query_spell_mapped(string spell)
{
	if( mapp(spell_map) && !undefinedp(spell_map[spell]) )
		return spell_map[spell];
	return 0;
}

varargs int query_spell(string spell, int raw)
{
	if( !raw ) {
		int s;
		
		s = query_temp("apply/" + spell);
		if( mapp(spells) ) {
			s += spells[spell] / 2;
			if( mapp(spell_map) )
				s += spells[spell_map[spell]];
		}
		return s;
	}
	if( mapp(spells) && !undefinedp(spells[spell]) ) return spells[spell];
	return 0;
}

mapping query_spell_map()
{
	return spell_map;
}

varargs void improve_spell(string spell, int amount, int weak_mode)
{
	int spi;

//	if( !find_object(SPELL_D(spell))
//	&&	file_size(SPELL_D(spell)+".c") < 0 )
//		error("F_SPELL: No such spell (" + spell + ")\n");

	if( !weak_mode || !userp(this_object()) ) {
		if( !mapp(spells) ) spells = ([]);
		if( undefinedp(spells[spell]) ) spells[spell] = 0;
	}

	// Give learning penalty to those learning too much spells.
	spi = query("spi");
	if( sizeof(sp_learned) > spi )
		amount /= sizeof(sp_learned) - spi;

	if( !amount ) amount = 1;

	if( !mapp(sp_learned) ) sp_learned = ([ spell : amount ]);
	else (int)sp_learned[spell] += amount;

	if( (!weak_mode || !userp(this_object()))
	&&	sp_learned[spell] > (spells[spell] + 1) * (spells[spell] + 1) ) {
		spells[spell]++;
		sp_learned[spell] = 0;
		tell_object(this_object(), HIC "��ġ�" + to_chinese(spell) + "�������ˣ�\n" NOR);
		SPELL_D(spell)->spell_improved(this_object());
	}
}

