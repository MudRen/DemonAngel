//
// file: globals.h
//
// This file is #included in all objects automatically by the driver.
// (See config file of driver)

// Directories

#define COMMAND_DIR		"/cmds/"
#define CONFIG_DIR		"/adm/etc/"
#define DATA_DIR		"/data/"
#define HELP_DIR		"/doc/"
#define LOG_DIR			"/log/"
#define KINGDOM_DIR		"/open/"
#define AREA_DIR		"/d/"			// ϵͳ�������λ��
// Daemons

#define ALIAS_D			"/adm/daemons/aliasd"
#define CHANNEL_D		"/adm/daemons/channeld"
#define CHAR_D			"/adm/daemons/chard"
#define CHINESE_D		"/adm/daemons/chinesed"
#define COMBAT_D		"/adm/daemons/combatd"
#define COMMAND_D		"/adm/daemons/cmd_d"
#define EMOTE_D			"/adm/daemons/emoted"
#define FINGER_D		"/adm/daemons/fingerd"
#define INQUIRY_D		"/adm/daemons/inquiryd"
#define LOGIN_D			"/adm/daemons/logind"
#define NATURE_D		"/adm/daemons/natured"
#define PROFILE_D		"/adm/daemons/profiled"
#define RANK_D			"/adm/daemons/rankd"
#define SECURITY_D		"/adm/daemons/securityd"
#define UPDATE_D		"/adm/daemons/updated"
#define VIRTUAL_D		"/adm/daemons/virtuald"
#define WEAPON_D		"/adm/daemons/weapond"

#define AUTO_D			"/adm/daemons/auto"

#define CLASS_D(x)		("/daemon/class/" + x)
#define SKILL_D(x)		("/daemon/skill/" + x)
#define CONDITION_D(x)		("/daemon/condition/" + x)
#define SPELL_D(x)		("/daemon/spell/"+ x)

#define KINGDOM_D		"/adm/daemons/kingdomd"

// Clonable/Non-inheritable Standard Objects

#define GOLD_OB			"/obj/money/gold"

//#define COIN_OB			"/obj/money/coin"
#define CORPSE_OB		"/obj/corpse"
#define LOGIN_OB		"/obj/login"
#define MASTER_OB		"/adm/obj/master"

#define MAILBOX_OB		"/obj/mailbox"
#define SILVER_OB		"/obj/money/silver"
#define SIMUL_EFUN_OB		"/adm/obj/simul_efun"
#define USER_OB			"/obj/user"
#define VOID_OB			"/obj/void"

#define LOADUSER_OB		"/obj/loaduser"

// Inheritable Standard Objects

#define BULLETIN_BOARD		"/std/bboard"
#define CHARACTER		"/std/char"
#define CLASS_GUILD		"/std/room/class_guild"
#define COMBINED_ITEM	"/std/item/combined"
#define EQUIP			"/std/equip"
#define FORCE			"/std/force"
//#define HOCKSHOP		"/std/room/hockshop"
#define ITEM			"/std/item"
#define LIQUID			"/std/liquid"
#define MONEY			"/std/money"
#define NPC				"/std/char/npc"
#define POWDER			"/std/medicine/powder"
#define ROOM			"/std/room"
#define SKILL			"/std/skill"
#define SSERVER			"/std/sserver"

#define BANK			"/std/room/bank"
#define BOARD			"/std/room/board"
#define SHOP			"/std/room/shop"
#define POST_OFFICE		"/std/room/post_office"
#define ACTIONROOM		"/std/room/actionroom"
#define PRAY			"/std/room/pray"
#define TRAINYARD		"/std/room/trainyard"
#define MAGIC_TOWER		"/std/room/magic_tower"
#define ARMORY			"/std/room/armory"
#define SMITH			"/std/room/smith"
#define FURNACE			"/std/room/furnace"
#define TAVERN			"/std/room/tavern"
#define HERB_SHOP		"/std/room/herb_shop"
#define MISC_SHOP		"/std/room/misc_shop"
#define GATE			"/std/room/gate"
#define HERO_GUILD		"/std/room/hero_guild"
#define BARRACKS		"/std/room/barracks"
#define STABLE			"/std/room/stable"
#define CHURCH			"/std/room/church"

#define SHIP			"/std/ship/ship"
#define SHIP_CORPSE		"/std/ship/ship_corpse"
#define PORT			"/std/room/port"
#define SWEAR			"/std/room/swear"
#define WEDDING			"/std/room/wedding"
#define GIFT_SHOP		"/std/room/gift_shop"
#define PET_SHOP		"/std/room/pet_shop"

// NPC modulus
#define TAVERN_NPC		"/std/char/tavern"
#define MAGIC_TOWER_NPC		"/std/char/magic_tower"
#define MISC_SHOP_NPC		"/std/char/misc_shop"
#define BARRACKS_NPC		"/std/char/barracks"
#define CHURCH_NPC		"/std/char/church"
#define STABLE_NPC		"/std/char/stable"


// User IDs

#define ROOT_UID		"Root"
#define BACKBONE_UID	"Backbone"
#define DOMAIN_UID		"Domain"
#define MUDLIB_UID		"Mudlib"

// Features

#define F_ACTION		"/feature/action.c"
#define F_ALIAS			"/feature/alias.c"
#define F_APPRENTICE		"/feature/apprentice.c"
#define F_ATTACK		"/feature/attack.c"
#define F_ATTRIBUTE		"/feature/attribute.c"
#define F_AUTOLOAD		"/feature/autoload.c"
#define F_CLEAN_UP		"/feature/clean_up.c"
#define F_COMMAND		"/feature/command.c"
#define F_CONDITION		"/feature/condition.c"
#define F_DAMAGE		"/feature/damage.c"
#define F_DBASE			"/feature/dbase.c"
#define F_EDIT			"/feature/edit.c"
#define F_EQUIP			"/feature/equip.c"
#define F_FINANCE		"/feature/finance.c"
#define F_FOOD			"/feature/food.c"
#define F_LIQUID		"/feature/liquid.c"
#define F_MASTER		"/std/char/master.c"
#define F_MESSAGE		"/feature/message.c"
#define F_MORE			"/feature/more.c"
#define F_MOVE			"/feature/move.c"
#define F_NAME			"/feature/name.c"
#define F_SAVE			"/feature/save.c"
#define F_SKILL			"/feature/skill.c"
#define F_TEAM			"/feature/team.c"
#define F_TREEMAP		"/feature/treemap.c"
#define F_VENDOR		"/feature/vendor.c"

#define F_SPELL			"/feature/spell.c"

#define F_IRC			"/feature/irc.c"

// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it 
// in effect.

#undef PROFILE_COMMANDS
