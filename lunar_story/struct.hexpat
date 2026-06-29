// SKILL IDS
enum Skill : u8 {
Nothing = 0x00,
Sword_Dance = 0x01,
Explosive_Staff = 0x02,
Flash_Cut = 0x03,
Vigor = 0x04,
Dragon_Protect = 0x05,
Dragon_Anger = 0x06,
Dragon_Healing = 0x07,
Dragon_Grief = 0x08,
Thunderbolt = 0x09,
Thunder_Bomb = 0x0A,
Thunder_Thrust = 0x0B,
Spark_Ball = 0x0C,
Heal_Litany = 0x0D,
Calm_Litany = 0x0E,
Saint_Litany = 0x0F,
Althena_Litany = 0x10,
Miracle_Litany = 0x11,
Cleanse_Litany = 0x12,
Fear_Litany = 0x13,
Escape_Litany = 0x14,
Flame_Bomb = 0x15,
Flame_Circle = 0x16,
Flameria = 0x17,
Power_Drive = 0x18,
Ice_Lance = 0x19,
Ice_Wall = 0x1A,
Blizzard = 0x1B,
Ice_Shell = 0x1C,
Power_Slash = 0x1D,
Power_Sweep = 0x1E,
Sonic_Riser = 0x1F,
Power_Up = 0x20,
Healing_Song = 0x21,
Purity_Song = 0x22,
Cascade_Song = 0x23,
Escape_Song = 0x24,
Temptation_Song = 0x25,
Tranquil_Song = 0x26,
Inferno = 0x27,
Nitro_Dagger = 0x28,
Tornado = 0x29,
Rock_N_Roll = 0x2A,
Sleep = 0x2B,
Confusion = 0x2C,
Magic_Box = 0x2D,
Stone = 0x2E,
Flash_Arrow = 0x2F,
Flash_Wind = 0x30,
};
// ITEM IDS
enum Item : u8 {
Nothing = 0x00,
Dagger = 0x01,
Short_Sword = 0x02,
Long_Sword = 0x03,
Broad_Sword = 0x04,
Saber = 0x05,
Ice_Blade = 0x06,
Silver_Sword = 0x07,
Samurai_Blade = 0x08,
Flame_Sword = 0x09,
Bastard_Sword = 0x0A,
Great_Sword = 0x0B,
Wind_Sword = 0x0C,
Crystal_Sword = 0x0D,
Dark_Sword = 0x0E,
Master_Sword = 0x0F,
Insane_Sword = 0x10,
Althenas_Sword = 0x11,
Mace = 0x12,
Flail = 0x13,
Ice_Mace = 0x14,
Water_Mace = 0x15,
Judgment_Mace = 0x16,
Holy_Mace = 0x17,
Dark_Mace = 0x18,
Sling = 0x19,
Poison_Darts = 0x1A,
Small_Bow = 0x1B,
Battle_Bow = 0x1C,
Stone_Bow = 0x1D,
Holy_Bow = 0x1E,
Pixies_Bow = 0x1F,
Dream_Bow = 0x20,
Starlight_Bow = 0x21,
Fortune_Cane = 0x22,
Water_Cane = 0x23,
Fire_Cane = 0x24,
Dream_Cane = 0x25,
Ice_Cane = 0x26,
Ethereal_Cane = 0x27,
Sages_Cane = 0x28,
Wind_Cane = 0x29,
Dragon_Cane = 0x2A,
Peasant_Clothes = 0x2C,
Heavy_Clothes = 0x2D,
Leather_Clothes = 0x2E,
Leather_Armor = 0x2F,
Iron_Armor = 0x30,
Chain_Mail = 0x31,
Steel_Armor = 0x32,
Holy_Armor = 0x33,
Silver_Armor = 0x34,
Carapace_Armor = 0x35,
Dark_Armor = 0x36,
Insane_Armor = 0x37,
Dragon_Armor = 0x38,
Cool_Clothes = 0x39,
Purity_Clothes = 0x3A,
Sages_Clothes = 0x3B,
Radiance_Clothes = 0x3C,
Saint_Clothes = 0x3D,
Holy_Clothes = 0x3E,
Robe = 0x3F,
Magic_Robe = 0x40,
Sorcerers_Robe = 0x41,
Intelligent_Robe = 0x42,
Saints_Robe = 0x43,
Wisdom_Robe = 0x44,
Spirit_Robe = 0x45,
Sages_Robe = 0x46,
Holy_Robe = 0x47,
Aegis_Robe = 0x48,
Garbage_Can_Lid = 0x4A,
Wooden_Shield = 0x4B,
Iron_Shield = 0x4C,
Silver_Shield = 0x4D,
Steel_Shield = 0x4E,
Holy_Shield = 0x4F,
Dark_Shield = 0x50,
Insane_Shield = 0x51,
Dragon_Shield = 0x52,
Iron_Bracelet = 0x53,
Silver_Bracelet = 0x54,
White_Bracelet = 0x55,
Crystal_Bracelet = 0x56,
Jewel_Bracelet = 0x57,
Star_Bracelet = 0x58,
Stone_Bracelet = 0x59,
Iron_Armlet = 0x5A,
Steel_Armlet = 0x5B,
Silver_Armlet = 0x5C,
Crystal_Armlet = 0x5D,
Rainbow_Armlet = 0x5E,
Dragon_Armlet = 0x5F,
Hell_Armlet = 0x60,
Fire_Armlet = 0x61,
Wind_Armlet = 0x62,
Detonator_Armlet = 0x63,
Spook_Armlet = 0x64,
Scarf = 0x66,
Hat = 0x67,
Headband = 0x68,
Iron_Helmet = 0x69,
Steel_Helmet = 0x6A,
Holy_Helmet = 0x6B,
Dark_Helmet = 0x6C,
Insane_Helmet = 0x6D,
Dragon_Helmet = 0x6E,
Bandanna = 0x6F,
Fruity_Bandanna = 0x70,
Spirit_Bandanna = 0x71,
Lucky_Bandanna = 0x72,
Dragon_Bandanna = 0x73,
Holy_Bandanna = 0x74,
Jade_Hairpin = 0x75,
Rainbow_Tiara = 0x76,
Ruby_Tiara = 0x77,
Fire_Tiara = 0x78,
Spook_Hairpin = 0x79,
Holy_Hairpin = 0x7A,
Phantom_Ribbon = 0x7B,
Wrath_Ring = 0x7D,
Crystal_Pendant = 0x7E,
Healing_Ring = 0x7F,
Chiros_Tail = 0x80,
Fresh_Ring = 0x81,
Refresher_Ring = 0x82,
Angel_Ring = 0x83,
Tri_Ring = 0x84,
Ice_Pendant = 0x85,
Flame_Ring = 0x86,
Barrier_Ring = 0x87,
Hell_Ring = 0x88,
Fortune_Ring = 0x89,
Shiros_Tail = 0x8A,
Gale_Ring = 0x8B,
Ghaleons_Tear = 0x8C,
Protection_Ring = 0x8D,
Devil_Pendant = 0x8E,
Spirit_Talisman = 0x8F,
Dragon_Wings = 0x90,
Lunas_Bromide_1 = 0x91,
Lunas_Bromide_2 = 0x92,
Mias_Bromide_1 = 0x93,
Mias_Bromide_2 = 0x94,
Mias_Bromide_3 = 0x95,
Mias_Bromide_4 = 0x96,
Jess_Bromide_1 = 0x97,
Jess_Bromide_2 = 0x98,
Jess_Bromide_3 = 0x99,
Jess_Bromide_4 = 0x9A,
Xenobia_Bromide = 0x9B,
Herb = 0x9C,
Healing_Nut = 0x9D,
Star_Light = 0x9E,
Silver_Light = 0x9F,
Angels_Tear = 0xA0,
Cleaning_Water = 0xA1,
Antidote = 0xA2,
Holy_Water = 0xA3,
Dragonfly_Wing = 0xA4,
Phacias_Bromide = 0xA5,
Soap = 0xA6,
Royces_Bromide = 0xA7,
Alexs_Ocarina = 0xA8,
Dragon_Ring = 0xA9,
Dragon_Diamond = 0xAA,
Sea_Chart = 0xAB,
Application = 0xAC,
Althenas_Mirror = 0xAD,
Old_Notebook = 0xAE,
Thieves_Guide = 0xAF,
Thieves_Crest = 0xB0,
Balloon_Blueprint = 0xB1,
Fluffy_Bug = 0xB2,
Dragon_Necklace = 0xB3,
Balloon_Engine = 0xB4,
Rememberizer = 0xB5,
};

struct Characterstats {
u16 current_Health;
u16 Total_health;
u16 current_mp;
u16 Total_mp;
u16 Attack;
u16 Defence;
u16 Agility;
u16 Wisdom;
u16 Magic_En;
u8 Attacks;
u8 Range;
u8 Base_Attack;
u8 Base_Defence;
u8 Base_Agility;
u8 Base_Wisdom;
u8 Base_Magic_En;
u8 Base_Attacks;
u8 Base_Range;
u8 Base_Luck;
u8 Level;
u8 Luck;
Item Weapon;
Item Armor;
Item Shield;
Item Helmet;
Item Accessory1;
Item Accessory2;
padding[6];
Skill Spell_1;
Skill Spell_2;
Skill Spell_3;
Skill Spell_4;
Skill Spell_5;
Skill Spell_6;
Skill Spell_7;
Skill Spell_8;
padding[6];
u32 Total_Exp;
u32 Exp_To_Next_Level;

};

struct Bag {
Item item_1;
Item item_2;
Item item_3;
Item item_4;
Item item_5;
Item item_6;
Item item_7;
Item item_8;
Item item_9;
Item item_10;
Item item_11;
Item item_12;
Item item_13;
Item item_14;
Item item_15;
Item item_16;
Item item_17;
Item item_18;
Item item_19;
Item item_20;
Item item_21;
Item item_22;
Item item_23;
Item item_24;
Item item_25;
Item item_26;
Item item_27;
Item item_28;
Item item_29;
Item item_30;
Item item_31;
Item item_32;
Item item_33;
Item item_34;
Item item_35;
Item item_36;
Item item_37;
Item item_38;
Item item_39;
Item item_40;
Item item_41;
Item item_42;
Item item_43;
Item item_44;
Item item_45;
Item item_46;
Item item_47;
Item item_48;
Item item_49;
Item item_50;
Item item_51;
Item item_52;
Item item_53;
Item item_54;
Item item_55;
Item item_56;
Item item_57;
Item item_58;
Item item_59;
Item item_60;
Item item_61;
Item item_62;
Item item_63;
Item item_64;
Item item_65;
Item item_66;
Item item_67;
Item item_68;
Item item_69;
Item item_70;
Item item_71;
Item item_72;
Item item_73;
Item item_74;
Item item_75;
Item item_76;
Item item_77;
Item item_78;
Item item_79;
Item item_80;
Item item_81;
Item item_82;
Item item_83;
Item item_84;
Item item_85;
Item item_86;
Item item_87;
Item item_88;
Item item_89;
Item item_90;
Item item_91;
Item item_92;
Item item_93;
Item item_94;
Item item_95;
Item item_96;
Item item_97;
Item item_98;
Item item_99;
Item item_100;

};
Bag Nall_Storage @ 0x698;
Characterstats Alex @ 0x358;
Characterstats nash @ 0x398;
Characterstats jessica @ 0x3D8;
Characterstats Mia @ 0x418;
Characterstats Kyle @ 0x458;
Characterstats Luna @ 0x498;
Characterstats Ramus @ 0x4D8;
Characterstats ghaleon @ 0x518;
Characterstats Laike @ 0x558;
Characterstats tempest @ 0x598;
Characterstats dragon_master_alex @ 0x5D8;
u32 Money @ 0x714;