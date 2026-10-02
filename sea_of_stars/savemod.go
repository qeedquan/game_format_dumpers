/*

https://gist.github.com/pR0Ps/3bb738b92e07e2db475bd2d463d4c080
https://en.wikipedia.org/wiki/LEB128

*/

package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"log"
	"os"
	"strings"
)

var (
	maxout = flag.Bool("maxout", false, "max out")
)

func main() {
	log.SetPrefix("sea-of-stars-savemod: ")
	log.SetFlags(0)

	flag.Usage = usage
	flag.Parse()
	if flag.NArg() < 1 {
		usage()
	}

	v, err := decode(flag.Arg(0))
	check(err)

	if *maxout {
		maximize(v)
	}

	b, err := json.MarshalIndent(v, "", "\t")
	check(err)

	f := os.Stdout
	if flag.NArg() >= 2 {
		f, err = os.Create(flag.Arg(1))
		check(err)
	}

	h := uleb128enc(len(b))
	f.Write(h)
	f.Write(b)
	f.Close()
}

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func usage() {
	fmt.Fprintln(os.Stderr, "usage: [options] save.sos [newsave.sos]")
	flag.PrintDefaults()
	os.Exit(2)
}

func decode(name string) (map[string]any, error) {
	b, err := os.ReadFile(name)
	if err != nil {
		return nil, err
	}

	v := make(map[string]any)
	h := uleb128dec(b)
	b = b[len(h):]
	err = json.Unmarshal(b, &v)
	return v, err
}

func maximize(v map[string]any) {
	x := getval("currencySaveData/currencyQuantities/values", v).([]any)
	x[0] = int(99999999)

	x = getval("inventorySaveData/ownedInventoryItems/values", v).([]any)
	for i := range x {
		x[i] = int(255)
	}
}

func getval(s string, v map[string]any) any {
	t := strings.Split(s, "/")
	n := len(t)
	for i := 0; i < n-1; i++ {
		v = v[t[i]].(map[string]any)
	}
	return v[t[n-1]]
}

func uleb128enc(v int) []byte {
	p := []byte{}
	for {
		b := byte(v & 0x7f)
		if v >>= 7; v != 0 {
			b |= 0x80
		}

		p = append(p, b)
		if v == 0 {
			break
		}
	}
	return p
}

func uleb128dec(b []byte) []byte {
	p := []byte{}
	for _, v := range b {
		p = append(p, v)
		if v&0x80 == 0 {
			break
		}
	}
	return p
}

var INVENTORY = map[string]string{
	"Abacus":                                 "6a39fd9b315b53a4faa9e3736d820eff",
	"AdamantineStaff":                        "5d108fe330c777241bb2b7c5326acc54",
	"AdventurerVest":                         "3ac3907f841cc2a40bd0fdce51cd52e2",
	"AetherwoodCork":                         "807d9f5c8b8f5514abcf261a36dc1711",
	"AmuletOfOnboarding":                     "b6acbe8e6e78e014d830094e248870af",
	"ApogeeDaggers":                          "a164640364ccf3546b0b9a0ac82b59cf",
	"ArcaneAmulet":                           "d8a7bdab9aa9a6e4e95036b0eff55239",
	"AssassinsPin":                           "88810f8353ed7404bb576582cc39189f",
	"AzureCape":                              "722415b4304ba6444b3f86b7b277d5c0",
	"BambooSlicer":                           "0a9e0ac0bb822b349af356af38ad6a5d",
	"BasicArmor":                             "a31ee5ffc1b693148be7c48150ebff81",
	"BlueLeaf":                               "588f0765e48c5124a8d9f671b57db116",
	"BoneArmor":                              "581aaf64cd0270b4bbf12d9ce9ea4ec0",
	"BoxerShorts":                            "a1d886ffc9682c54ebda876deeed58b4",
	"CalciteLid":                             "108a40870288c934d94c1661286ff1f0",
	"CauldronLid":                            "b9995b298ada14e4887faf134942b564",
	"CelestialRay":                           "23cd65231a0ab0c45be5987e87455136",
	"CloudSword":                             "5877570357bf9f441ae01cd06bccd9f4",
	"CloudySimulacrum":                       "2e09170437a631e46ac9b9669464618c",
	"ConchItem_RainbowStar":                  "d810ad9125b56864b92ea9b3bdadad51",
	"CopperStaff":                            "10d0cb7c4836f794bb6f4d965f2b76c8",
	"CoralDaggers":                           "d78f39987eaedcc42b938fc1763bba59",
	"CoralStaff":                             "70a7707a760f40046b71b4b2e111a708",
	"CoralSword":                             "16d199bda90813f40a28fd9203865374",
	"Cornucopia":                             "fb067e7ba3b744342bbca13afcfb2a50",
	"CosmicCape":                             "d1d1bcd5dbc41d648a812fbc7d1861b2",
	"CypressCork":                            "1a8eae5901ae6754a8899a58a692a2b3",
	"DextrousBangle":                         "f93c6f846bc2f0b4484e896221759b94",
	"DocarriArmor":                           "98223d461dbc41a409926f2a1409f7ec",
	"DullSimulacrum":                         "e26fa36b128e76041938bf3c86ad8eef",
	"EarthshineStaff":                        "27a72590849651b4ba1cf80fe6be8d4a",
	"EclipseArmor":                           "911324cc7daad5b41a0af317180a42db",
	"EnchantedChainLink":                     "d311de20fa85a5148a7b523f0af76f47",
	"EnchantedScarf":                         "9e03ef3b70751944abae3f3880c733b7",
	"EvergreenLeaf":                          "af3e10fe5b7abd940baadad96a4e5e7c",
	"EyeOfYomara":                            "e7e2fc32454eda44d9d93ba6009d8752",
	"FirmamentEdge":                          "7d6c888ffacc1cd4ab3ce414b294c67e",
	"FishingItem_MagicHook":                  "7b4c2ced735d9ff41ad7fae6e7dc71d6",
	"FishingItem_PassVIP":                    "7ba76f034da41cd4d9de1c4267a031ef",
	"GamblersEarring":                        "478d680b15f759d44987b2cef327ce2f",
	"GarlsApron":                             "86737d6ef697c204187aea8533ec4244",
	"GreenLeaf":                              "0ee892db1da195541bcbe578898265b5",
	"HeliacalEarrings":                       "acadc7386a182444692a4622393aac6b",
	"IgneousStaff":                           "e93c519d3c18fa245937cc461e4de24d",
	"Ingredient_Apple":                       "1050b67b61f94084d970b6ae4c33dc01",
	"Ingredient_Bone":                        "9a6abc7114f0eb9409f27b6816830fff",
	"Ingredient_Egg":                         "a17b0505c55affc45a066431eb30c655",
	"Ingredient_Fish":                        "7f49bbd04a7b4b84092aec1d8f54d1cb",
	"Ingredient_Grains":                      "841382ac016092346b0cf860a932c3c7",
	"Ingredient_Lettuce":                     "21471472fcbc68149b8cf7a9dac2b785",
	"Ingredient_MapleSyrup":                  "4b5c4bf16feb4b448bdc3cf8057f2be0",
	"Ingredient_Meat":                        "0b7efbffd76a27f489ea26df56bbc5ad",
	"Ingredient_Milk":                        "b8f81159f93c18740ba72fffdd12a13e",
	"Ingredient_Mushroom":                    "8a5e759b4475ca04d882e7d2b0c9b47a",
	"Ingredient_Onion":                       "4ffc27dc684ae1e48b5a48909f79c3ca",
	"Ingredient_Peach":                       "47336b026e675b34f99d949b4c2f67d0",
	"Ingredient_Pepper":                      "094de5a55e6f5444aaf870aad7e78297",
	"Ingredient_Potato":                      "13dea75b6b52c814b939519cb2b0675c",
	"Ingredient_RedBerry":                    "1f83e925faef7584b9f34b0723137d76",
	"Ingredient_Seafood":                     "76b491199a5df8745a77f2a20ae8bc38",
	"Ingredient_Tomato":                      "f8bf6d10c6c6da840883935fa4aa8c9c",
	"KeyItemWizardLab_CoinofUndeathAccord":   "791d1b17113c71a42a4b0a08f5be7676",
	"KeyItemWizardLab_RedCrystal":            "d0ecc064753be7d48b7818b0113d10f8",
	"KeyItemWizardLab_WellItem":              "2cb456c00ee26754895cab1ef09f5024",
	"KeyItem_AirElementalHexagonalSocketKey": "d605805dcc79f554faf8af072b133c8e",
	"KeyItem_AirElementalTriangularSocketKey":  "91949467e3e270d459a609213183ecaf",
	"KeyItem_AlumniCoin":                       "d15dc445af50b0d46b185ca1e3b6d67e",
	"KeyItem_BluePearl":                        "2125d95821df6824a828a69bd902bf14",
	"KeyItem_ClockworkGardenKey":               "fc97e4a59d8cf79419322000ce72afb8",
	"KeyItem_Conch":                            "5eb73f88e6c96f94797fa11b7d11b061",
	"KeyItem_CookieJar":                        "08ae384f758e8be4ba4e7d58975838e6",
	"KeyItem_CoralHammer":                      "3de9715179fe13d44bf0ac2d38ce5db4",
	"KeyItem_CoralHammerUpgraded":              "f0faa32c4f2b19e4d9a1c825c5a23771",
	"KeyItem_DecryptedDataChip":                "b139bc7db13b9ab4d93f2d1b10816c1d",
	"KeyItem_DukeKey":                          "e9e25324a369a4d4e9331778a4deb8b5",
	"KeyItem_FactoryBlueprintDisc":             "20e59602e0dabaf4eb02fc6826cc780b",
	"KeyItem_FactoryCraneKey":                  "503a7b18abfa01249b986399fe588505",
	"KeyItem_FactoryPowerBlock":                "503f82df95dcc16408b338ebf3974c39",
	"KeyItem_FactoryRawMaterial":               "e1bd356c4c92f9b4a9ae9557740a8b7c",
	"KeyItem_FactoryWireplateSheet":            "01e9b3e17b5f4c647b43afaba1305bc4",
	"KeyItem_FineBrush":                        "55277ab6cbce74147937da9db8e530f4",
	"KeyItem_FishingDungeon_DoorKey":           "e6efe37cf14f7114db73cda5972f8da3",
	"KeyItem_FishingHutBlueprint":              "33547d6f7d3ba254e876b1256e5c6e53",
	"KeyItem_FleshMancerLair_Fish":             "b6181ca295fc4964da34df0379e5ead0",
	"KeyItem_FleshMancerLair_Vase01":           "3002629170d8ec448a27d1bfc69bc9b2",
	"KeyItem_FleshMancerLair_Vase02":           "349d0c0d0fec3d845bf2dbb16b14b160",
	"KeyItem_FleshMancerLair_Vase03":           "ae301ae0d0834f14e8ed770c2c9cfba6",
	"KeyItem_FlimsyHammer":                     "aae87498b3763054086daf64fec4c1ed",
	"KeyItem_ForbiddenCavernKey":               "cc1057ec537f0c842bdbb572265b9a17",
	"KeyItem_GoldenFish":                       "8b255d22228b85244a4bb673b2b8586b",
	"KeyItem_GoldenPelicanVIPpass":             "f3fddcfa74a471740830ff34bbb256d2",
	"KeyItem_Graplou":                          "c9447122a421a2640b315d36b2562ad2",
	"KeyItem_GreenFlame":                       "70b52ef97031bd74fa467314fbcb11e6",
	"KeyItem_GreenPearl":                       "aa4d810d27c12864eb74a976a24a6c5a",
	"KeyItem_HauntedMansion_Bad_Sandwich":      "970faa3ecbd4a6f4bb50719ba804d3ec",
	"KeyItem_HauntedMansion_Crown":             "d476f6c7455257948854ed1cc65afee7",
	"KeyItem_HauntedMansion_KnightHelm":        "759ad2684304f1f41ab1c7ca59a1ef9f",
	"KeyItem_HauntedMansion_Regular_Sandwich":  "e3fb5a2625fe837428d704747054077c",
	"KeyItem_HauntedMansion_Supreme_Sandwich":  "e94e5414de65af34a810b8f89c117b6b",
	"KeyItem_HiddenMarketPass":                 "31525df92a16eb94ba068dff6876c562",
	"KeyItem_HydralionPearl":                   "0e74dbdddec12d64f9bc85152d4331b8",
	"KeyItem_IncompleteDataStrip":              "da09de33b7886b14aa651746c28689d4",
	"KeyItem_Locket":                           "b901a02219536cf43af09aa7ae1d7326",
	"KeyItem_Lucent_GhostCookie":               "5dc17c895fa172b47b22fba330496a8e",
	"KeyItem_Lucent_Shed_Key":                  "db37449de93d8dd4ba50111ced8f89e1",
	"KeyItem_MagicSeashell":                    "b391f0c6724c8d443adec6105be71661",
	"KeyItem_MagicalFishingHook":               "5c63abeb5da9f114ba2c2da954e59d82",
	"KeyItem_Map":                              "aefb6b3d640e4804d85814203c8baa2c",
	"KeyItem_MasterKey":                        "5430316fcbe43364191d2c0ba415e415",
	"KeyItem_MineKey":                          "f7046c4e3f1a9fa45ae10bb5f7c76013",
	"KeyItem_MoonCradleDungeonKey":             "1f912127975af7b4f8c7316fe4d6a625",
	"KeyItem_MoraineOfficeKey":                 "c5f18f0632cff954eb6a3bc67eb9c7fe",
	"KeyItem_Moraine_Key":                      "ba8e4259fdc96ac48aebd98867165d9c",
	"KeyItem_NecromancerLair_SoulStone":        "3df62cf7dbeaa4a4ebc243672b8dacb8",
	"KeyItem_PinkPearl":                        "efa941d37f7e8a741bffda3674865874",
	"KeyItem_Probe":                            "4ca8a003a14a791458c38e8739f32344",
	"KeyItem_PurplePearl":                      "0aed24b71deeec34689a568297b730ba",
	"KeyItem_PushBracelet":                     "5b77e66a1d52fce4cbab840d6dd157c4",
	"KeyItem_QuestionPack01":                   "92577167b3635ef45b5bb4449e0db946",
	"KeyItem_QuestionPack02":                   "24ff003b0e4c78047b638dccac197484",
	"KeyItem_QuestionPack03":                   "dc7c66a209c025f4697e8e8491e098cd",
	"KeyItem_QuestionPack04":                   "33d4a1a7ec0d9b741a8a175d2c24e8c7",
	"KeyItem_QuestionPack05":                   "8cae32b464ca8e844b378263d8d34011",
	"KeyItem_QuestionPack06":                   "1e31e8cf36ae60841a47f3d9f2fce3bf",
	"KeyItem_QuestionPack07":                   "fe30e0ddff22ff94081ceecff3a5d5fd",
	"KeyItem_QuestionPack08":                   "b299ede2f42dd2e458fc1fa65fbe3863",
	"KeyItem_QuestionPack09":                   "08ec181ba4b1e0147be8d62ce1973ab1",
	"KeyItem_QuestionPack10":                   "98606956383da154fb4c64737d96c898",
	"KeyItem_QuestionPack11":                   "ace6400b0e4dcd344b58181d9a10994f",
	"KeyItem_RomayaJournal":                    "ca355ae6b0e5289469961e23ecc819d1",
	"KeyItem_SS2_KeyA":                         "42595a0119f967845b9397365508ba64",
	"KeyItem_SS2_KeyB":                         "bc821a537ec005c498861cbea8cffe92",
	"KeyItem_Seashell":                         "2295d1bfeec0f8844b477f95c919c74f",
	"KeyItem_SheetMusic01":                     "46742572097b4014fb8da9f198d0942b",
	"KeyItem_SheetMusic02":                     "3b000cb7c50ea4a4f85dad1ad78a12a4",
	"KeyItem_SheetMusic03":                     "25e534eb1a920ed4897ad72ae4ff9453",
	"KeyItem_SheetMusic04":                     "86cd787e0f837ff458f6be93fbb995d3",
	"KeyItem_SheetMusic05":                     "43eddaeda003ea148b7dc68a09ef80cc",
	"KeyItem_SheetMusic06":                     "e7d15540dc5a0d44ba8b43a1160dc534",
	"KeyItem_SheetMusic07":                     "a9c546d8c82f54048a911c909db5bb93",
	"KeyItem_ShopBlueprint":                    "c7697b21842b62b41968ca1d03749259",
	"KeyItem_SkyBase_AiCore":                   "8c001ec3683345a4cbc7c43782dacbdd",
	"KeyItem_SolsticeAmulet":                   "4586380c0f09cc943bdacf7acf50a3a2",
	"KeyItem_SongShroomMarshKey":               "c9e2bf06d9f76f442b45863d8909ced5",
	"KeyItem_SpasBlueprint":                    "542f2e8deac123745ab1e57442a956cc",
	"KeyItem_StormKey":                         "0616ef249bcbe5b42abfd07c541cee31",
	"KeyItem_SunkenRuinGem_A":                  "e488a0e3327d6214a9ba85ec2c34a5eb",
	"KeyItem_SunkenRuinGem_B":                  "892c6828010cd0442a3393c5dd45e6c6",
	"KeyItem_SunkenRuinGem_C":                  "5523dc3139186874695c75c920c337a4",
	"KeyItem_TavernBlueprint":                  "bcd71fdd76d64e443b7b47364271b044",
	"KeyItem_Tower3_Key":                       "6cdb3cdb6dd53bf488486c7fa7f6bb34",
	"KeyItem_Valve_A":                          "aed455e0a258631408f2694e1de9aea2",
	"KeyItem_Valve_B":                          "f39ff4369129dde46a0e1fb61dca33ba",
	"KeyItem_VialOfTime":                       "375a19f5e47b951419795eaf409f3169",
	"KeyItem_WaterGateKey":                     "e554a0e60158d6a45a6fbaa76b7a149d",
	"KeyItem_WheelsCharacter_Archer":           "eab7dd1ce97e5f549a124d6508121943",
	"KeyItem_WheelsCharacter_Assassin":         "b29f7387520ec284aadf210a3d96eeef",
	"KeyItem_WheelsCharacter_Engineer":         "1ffdc826f25d33f418925e7a9838e3e1",
	"KeyItem_WheelsCharacter_Mage":             "d7f92ecb9e4da7b418070285c25d86e1",
	"KeyItem_WheelsCharacter_Priest":           "0fba7ae2d8a1d2d4aa49a2c9a6fb61e7",
	"KeyItem_WheelsCharacter_Warrior":          "e972fad3d8d63a745bdfc1dc7dc6d2f7",
	"KeyItem_WheelsRank_Bronze":                "a81551d5aa1d0fc419c2023113b5c0ab",
	"KeyItem_WheelsRank_Copper":                "76241bd9c19934344a8274665fb67f2b",
	"KeyItem_WheelsRank_Diamond":               "56ca0aa8b72609d45a65481a6290ee75",
	"KeyItem_WheelsRank_Gold":                  "b5e8130725d015140a492ef72e660cd3",
	"KeyItem_WheelsRank_Platinum":              "f959b0aa9e4fd9649a096875b81ebe82",
	"KeyItem_WheelsRank_Silver":                "e024e3aebc5d1424ea1d69be9df5d4cc",
	"KeyItem_WheelsTable":                      "2b0d434789480b1439e5458f158e5043",
	"KeyItem_WindKey":                          "24632686b928dbc42b744f96d59a6cf0",
	"KeyItem_WizardLab_BlueCrystal":            "7072b9fc59fa699458b7acf5597d5d97",
	"KeyItem_WizardLab_GreenCrystal":           "37ed1b808bebec1458cbb90a2e2021d5",
	"KeyItem_YellowFlame":                      "64bf3ab125f071e4785b7a00150ac1b7",
	"KeyItem_YellowPearl":                      "56ddec906232705469ab9a0a52fea8f2",
	"KybersteelBlade":                          "0dddb9e8063bbdd4fb724929ee784f38",
	"KybersteelDaggers":                        "e24926f361bf385478653d34ac9f6a41",
	"LeafCape":                                 "b441ba29ad2257445a55095e6cb1d537",
	"LeechingThorn":                            "933db0df85333b341a7d58da22f3b39c",
	"LuanaStaff":                               "95ac264461a94a0458a14a39954e3afc",
	"LucentShard":                              "92e2af189aebd9949a662314b01ab847",
	"MageKnightArmor":                          "1b92e304b4f82144eb3e123ccb755b2c",
	"MagicPocket":                              "8c32a9ec62778cc4f8cef577c6d80812",
	"MapleCork":                                "8f50c130484e7c44a8d90860eaaa2806",
	"MinersSmock":                              "f23fec51c068c00418db6127c54fcc8e",
	"MooncradleBoyLid":                         "0f0053be4fa1bf84db338a626d751eb2",
	"MoonstoneBracelet":                        "4441ac030d9882445867b6ee06fbe941",
	"NanoInjector":                             "8c4cbe75847cc6249b3bd79cb5a29e8c",
	"NeobsidianStaff":                          "d25d22b957a9c5c478e188e1f03f7107",
	"NinjaSpirit":                              "1d744837c9ee072498a3e668104325ac",
	"OakenArmor":                               "ebb0e8958a73d394da97e174d0b5b018",
	"ObsidianLid":                              "c16988af55e565545b978150228fc5e7",
	"OrnateBo":                                 "c82873a6208c95241834faa4a0c90321",
	"OsseousStaff":                             "3e2210133b9ad0940bddde38c647e3e7",
	"PearlescentApron":                         "bd7a12ffa698146418723ed43e6a5eea",
	"PhantomDaggers":                           "3f851aff158a63042bd188b378bc3d81",
	"PhosphoriteLid":                           "8df0767e67aa4e34584a5066469765de",
	"PirateGarb":                               "0626cb583af926649b435bcf63c101a7",
	"PlasmaBlade":                              "301554cfa6770af4d9e0791f01488999",
	"PlasmaDaggers":                            "1ca6171b638ffdb49bda2f4cfcb2e564",
	"PliantshellVest":                          "7fdba9db0aa4cbd4e8fa3315f94876ab",
	"PowerBelt":                                "154461019876b7741bbd74980276c852",
	"ReapersMercy":                             "427eaeae77b247442a8ec3e014542890",
	"RecipeUnlock_BasicSalad":                  "3ad1eaff8549fe94c897ac387f8ae4c9",
	"RecipeUnlock_BerryJam":                    "bb98188ba554ed240a3161762390017f",
	"RecipeUnlock_Bouillabaisse":               "04901995730d6e8459b705872897f088",
	"RecipeUnlock_Braise":                      "3088f0f4cd968e34fa3781eb9933ddf8",
	"RecipeUnlock_ChampionOmelette":            "3e0d11751c5fcf847ba5adbcbe4e751e",
	"RecipeUnlock_Chaudree":                    "3dafda053c9fcb0439e0d5719cc11c8f",
	"RecipeUnlock_Croustade":                   "44abbdb24e6269e4781d1d4e4ec3bef3",
	"RecipeUnlock_FishPie":                     "f5241ef7a0fa1a04ba780e73ac23ea8d",
	"RecipeUnlock_GourmetBurger":               "acfbbff667ad7ad47a95d82351a64648",
	"RecipeUnlock_HeartyStew":                  "11e59219302f6b1479a5492650982272",
	"RecipeUnlock_HerbedFilet":                 "19e478ef186577e489f95767465a1a84",
	"RecipeUnlock_Lasagna":                     "c576cca46c0189d458f53feca4fb131a",
	"RecipeUnlock_LegendaryFeast":              "06ed69ffa96524b47a68fd2fc63e8fd7",
	"RecipeUnlock_MushroomScramble":            "8b102534541d1f24e9f958a5041b139c",
	"RecipeUnlock_MushroomSoup":                "fe44b430ac413ec4f970e9e908841c55",
	"RecipeUnlock_PainDore":                    "88fd9a7fcfbd0854dbc95a58128b09c2",
	"RecipeUnlock_Papillotte":                  "32ea2a86f22b90f4989ee64eb06c58a8",
	"RecipeUnlock_Parfait":                     "168fbde19e968eb418b8053c5814637b",
	"RecipeUnlock_PeachStrudel":                "c203b6eef768b63449d485b7d5779723",
	"RecipeUnlock_Poutine":                     "e5cf696cec8c0d5419ce05ed66a8a7c4",
	"RecipeUnlock_PuddingChomeur":              "d3931ad465684074e8fd82c32f7498b6",
	"RecipeUnlock_RoastSandwich":               "212f14bab84c08745bbc35b36daa7c77",
	"RecipeUnlock_Sashimi":                     "30bdce2e73ebcb140929cad623a54ea2",
	"RecipeUnlock_SurfAndTurfTataki":           "e44fdfcaf1b80d64b9b9e35ab29bddd7",
	"RecipeUnlock_TomatoClub":                  "64f77efd09e519d4999ffb01b9ff328f",
	"RecipeUnlock_YakitoriShrimp":              "254124e5f00a4734a9802bd36d84b622",
	"Relic_AdamantShard":                       "4133b72ae404b374987e2b434c7f5c10",
	"Relic_AmuletOfStorytelling":               "a91e6b011845d77418d3bae4766a8a9d",
	"Relic_ArtfulGambit":                       "884bf88d04075264c98ab588ae5221cf",
	"Relic_DoubleEdge":                         "a153f84abd9ac3b4ab7746c1d43095f2",
	"Relic_DubiousDare":                        "5969aba2037e09b46823584da7ee0d15",
	"Relic_ExtraPockets":                       "4e0db461b8b133c4ab2536bc1016cf93",
	"Relic_Fishing_FishingLineHP":              "a8c2b79eb9a4bb84ba5876ddb96ec55b",
	"Relic_Fishing_ReelingSpeed":               "662aa1ede20e4a14db1e29e258893a6c",
	"Relic_Fishing_StaminaDepletionMultiplier": "45ab00b468451b949ac17163040925fa",
	"Relic_GoldenTooth":                        "57597d27d25e6f74fb87c572b2b171d2",
	"Relic_GuardianAura":                       "def407b542a5c3d458a8c1fa59815693",
	"Relic_KnowledgeTome":                      "31de888ea125ddf458c85998a8958ef4",
	"Relic_PirateParrot":                       "e388991e8f7c5934993153ef7e50232f",
	"Relic_SalientSails":                       "1554ef53341beea43ab50edbe869f560",
	"Relic_SequentFlare":                       "1b0313fe821ba7c419b7b443416aa784",
	"Relic_SixthSense":                         "f2e2a73117e6d044d8b0ced0304293d1",
	"Relic_TrueStrikePendant":                  "c1962220eb589a642aa1a5856ef650d4",
	"RevenantArmor":                            "a0890c10ae319b0409d43f08af673ffd",
	"RockLid":                                  "7694b5b801204a74c888d67a49f06d42",
	"RosewoodCork":                             "c2d85fc1508398e4a8c4db3e12594978",
	"SalixCork":                                "2a8606f2bf7f5224cadb8ae2c1d1b531",
	"ScrimshawedBlade":                         "7ce9f696d3089434fbff10c7653d0026",
	"SeraiWeapon":                              "6dfc4e7a1624a9c4eaaf2ae75c336b5c",
	"ShimmeringBlade":                          "10e93ab756357f142b3c6ef3ec7a7c4b",
	"ShimmeringDaggers":                        "b883d3f8ffbc78040ade7dc4675ac1c6",
	"ShimmeringShard":                          "71ff97ab95cbcd84985e62255cbca323",
	"ShimmeringStaff":                          "f7d49514f7bfca34b942d95722b76a32",
	"ShroomyDaggers":                           "aa8b7c8001ca94d4eaa65d1ffb58a5e2",
	"SignetOfClarity":                          "62dcbc88129046140a17fb2790ad258b",
	"SilverBlade":                              "71cfc6d93b292d3499c472b73e9daae1",
	"SkyArmor":                                 "e1e3c71bb3b7e034684d195c2fa5968c",
	"Snack_BasicSalad":                         "68c337d503ebc7e4a837052ed38452b5",
	"Snack_BerryJam":                           "74a5e5d26b56b7e429c36d1acb84a120",
	"Snack_Bouillabaisse":                      "f2868459715d3df45ad1da473d197ac6",
	"Snack_Braise":                             "512b3f049d35cbd4eb4648aa5a1105f6",
	"Snack_ChampionOmelette":                   "5608bed7407aae34ba3012feba387b00",
	"Snack_Chaudree":                           "71853a3bd516511428ea6d23bc7eb34f",
	"Snack_Croustade":                          "46bfb5ae7593f8f4bb870c9644635a99",
	"Snack_FishPie":                            "6e613ca39c27bff49ae0da1773c6ab03",
	"Snack_GourmetBurger":                      "918caccd92d8f7540929427a743d1f15",
	"Snack_HeartyStew":                         "a4a1c78380553e74bb92899ddcd62440",
	"Snack_HerbedFilet":                        "88bc64e502aab364f800ff8b94427f5f",
	"Snack_Lasagna":                            "e8908ed6c2bd60f4bb4042067baa2a8c",
	"Snack_LegendaryFeast":                     "425a2ecc6c4b87c4d89735500c6c9d95",
	"Snack_MushroomScramble":                   "c1866d6de70d4834b951c06d4ae23306",
	"Snack_MushroomSoup":                       "df724719b2fbf6e40a85e8f9bc4ccae2",
	"Snack_PainDore":                           "f6b47783588bed64e9fa44dba59b4a49",
	"Snack_Papillotte":                         "9151230a300ed934bbd8d6c1c659fc34",
	"Snack_Parfait":                            "fceb00c496ecb5844b14022ba450de53",
	"Snack_PeachStrudel":                       "d508421fae4fe5549a21d767a5d7d10c",
	"Snack_Poutine":                            "8af2d2fccb35a0f43a965bbdd7a993f1",
	"Snack_PuddingChomeur":                     "52004597d9485634dbd4fca16b151c89",
	"Snack_RoastSandwich":                      "520e9f55dc3432a498ec389a59d7401f",
	"Snack_Sashimi":                            "92dbbdececf32284eb6868f3529ff7ac",
	"Snack_SurfAndTurfTataki":                  "b504e699b3af5ab4faa0b252ff7d49f6",
	"Snack_TomatoClub":                         "1aafd2f9435698349a63a99837e9104e",
	"Snack_YakitoriShrimp":                     "547cb5586279b80489ace061c33eb861",
	"SolenSword":                               "8f96ab39454c54641812c57f7b332481",
	"SolsticeMageRing":                         "c7eb103c76a21974c844159ab0f5a0d2",
	"SolsticeSash":                             "076aaeb73b8283748accfb24f68a5c64",
	"SparkmeshArmor":                           "ccc69fb007cbda342844f25126c90377",
	"SparkmeshCape":                            "fe4a8a4cada2d4a4999403d31f73a50a",
	"SpectralCape":                             "d2fd56a9405f9c04fb303795c7840f2f",
	"SquireSword":                              "4a1710ba97ae350428f18704e36fe234",
	"StarShards":                               "a27614e2379ef9e4dac1950a51b3f71d",
	"StoryArtifact_CerulanExpedition":          "a7eb75ef484df8748a4c507fba097b85",
	"StoryArtifact_ClockworkAndKidEngineers":   "9fffcbe75bd0a61439e3546edd2d1049",
	"StoryArtifact_Estristae":                  "027715b8b6eb986459da52f290a22c45",
	"StoryArtifact_LucentShroudNight":          "2cbaec690b20378448407f18f53c7607",
	"StoryArtifact_MooncradleAndEldermist":     "a079a093d27333e4e99cd0b4abe3b6a1",
	"StoryArtifact_NomadsAndSea":               "6086a4552abd9ab4dbd76f1cfb4b6812",
	"StoryArtifact_SkyGiantAndKhukkar":         "bcedb2e46cfcb9a45a9736062dbd6e47",
	"StoryArtifact_SleeperAndMolekins":         "c7e3009a90c46164e86fd8fb5d08cbce",
	"StoryArtifact_ThreeSisters":               "f65753c0374254346afc37b1f75cd0ee",
	"StoryArtifact_VampireRose":                "5c4863eb4f266574e937fb34e3031ed4",
	"SturdyCog":                                "68d99c8b95dbf7c41a00d562b41b289a",
	"TatteredCape":                             "ecf26467374cebc4b812538e7fbe44a4",
	"TealAmberStaff":                           "e27094f36cb7bb140b614b89fde60550",
	"TestIngredient":                           "8c9604711530463408f53774a8c44177",
	"ThalassicCloak":                           "0e08751170c68ca4faae2b08ea913275",
	"TrainingStaff":                            "40b7062ac812c5d47bb1ff0df4987e8e",
	"TrainingSword":                            "e3098c0169021924a97713b57a009928",
	"TruesilverDaggers":                        "0d86cee64cf8be44985fcee7a34c49f2",
	"ValuableItem_AdamantiteOre":               "77a0a1cac957b4b4d8cfbb1ee9b2548c",
	"ValuableItem_AlumniToken":                 "c067bbcbb9deb85488d779cf334e50db",
	"ValuableItem_ObsidianIngot":               "4717dc86cf98f2d4794b40e910b63e61",
	"ValuableItem_ObsidianOre":                 "7a9b2938fabc5434da21134b18b4e0ee",
	"ValuableItem_SapphireIngot":               "79b159a1b2b69834a96cd56d5e02058c",
	"ValuableItem_SapphireOre":                 "c43421b626574174e9b5156141213250",
	"ValuableItem_ShinyPearl":                  "7337dc21759feae4a92aba8200c42898",
	"ValuableItem_TealAmberOre":                "33e568f23e2581d448041ac97fb8358d",
	"Vespertine_Hortence_Shop":                 "c3253cabfb65df143bb4a1252efb6094",
	"VitricSimulacrum":                         "ebe89a4a81e46c245bd98a337df06eb8",
	"VolcanicArmor":                            "0c8b9c021791a734892aaafde3b847b6",
	"WalnutCork":                               "c3b22a46f99faba498bfbc7519cce88c",
	"WireplateArmor":                           "67e51219a3a7ea14fa14e9eb4e8643e4",
	"WitheredCork":                             "441bec8771714944eb32ff53c082f8da",
}

var CONCH = map[string]string{
	"ConchID_AirElementalSkyland (1)":    "98298d6cac529ac42a210924d16e4c9a",
	"ConchID_Autumnhills (1)":            "81055d3fef7e90b4ba23999618478509",
	"ConchID_BambooCreek (1)":            "cfd69c969cbe59a419949529145a2220",
	"ConchID_Brisk (1)":                  "ce991cc8c461c8e45b84aaac2c811d77",
	"ConchID_Brisk (2)":                  "0433e4300245109439327f722ca4e44a",
	"ConchID_Brisk (3)":                  "73663fef4cae0264c954bdbd14eda34c",
	"ConchID_Brisk (4)":                  "75ca925bbf6d7a94d9ec074096a39a35",
	"ConchID_Brisk (5)":                  "96678b90b5463004f9df3db6ebb144ab",
	"ConchID_Brisk (6)":                  "cbbe4f5f1a822904da6afd52695f3cad",
	"ConchID_BriskNew (1)":               "b5639ec82dba9f14b8eab2fe829d9a77",
	"ConchID_CeruleanExpanse (1)":        "a7f4bf29bd40ee941abb1553a242e397",
	"ConchID_ClockworkCastle (1)":        "a63e7b32a1a866e499b94a75627f47f0",
	"ConchID_CoralCascades (1)":          "205096bb3a9b11a4aad9e2d0add85fb3",
	"ConchID_CoralCascades (2)":          "dad0f9d1cd7023e45b7b94b288839622",
	"ConchID_Crypt (1)":                  "2df759a3259f1be4e835ae3f5da39d14",
	"ConchID_CursedWood (1)":             "1454d1631fd972f439c00e13956be9e8",
	"ConchID_Docarri (1)":                "af260b24e01d35a4da225b5731166e46",
	"ConchID_Docarri (2)":                "012a4ef102d6717489dc3d1b985a67ee",
	"ConchID_Docarri (3)":                "ad97a0348e5f7b042bf2ba14b356527d",
	"ConchID_Docks (1)":                  "aa83c1c230750354e95cc7a4f2d0f738",
	"ConchID_ElderMistTrial (1)":         "6a6b4b3a7f2b8a1449af2fd1842af1d6",
	"ConchID_Factory (1)":                "542cac20cc67be444ac4d1e2e97e53c7",
	"ConchID_FishingDongeon (1)":         "c136ab125b46ff742a8f8012d09ae14b",
	"ConchID_FloodedGraveyard (1)":       "bdd808850f85c994f8c5692fc79e017b",
	"ConchID_ForbiddenCavern (1)":        "46569470ab5012b45b9e47a36ed5f4e8",
	"ConchID_GlacialPeak (1)":            "8b30eac742165884f8c6fa2dd27ae233",
	"ConchID_HalfSunkenTower (1)":        "aaadb686e5968444d928d49829885172",
	"ConchID_HauntedMansion (1)":         "661bf2ac3a07e7c429668be568ff70c1",
	"ConchID_JunglePath (1)":             "a6f8cf5b36d27ff449b83547ddecd9aa",
	"ConchID_KilnMountain (1)":           "4fe86276999a7f546832590cfcc371db",
	"ConchID_Lucent (1)":                 "aa4f942f4bf114246b31567d3adcb379",
	"ConchID_Lucent (2)":                 "b37a45b075d050f4cb04dd64b0bba56b",
	"ConchID_Mirth (1)":                  "6df198ddca1d2434c904f195766d6445",
	"ConchID_Mirth (2)":                  "f9245b24bb17b7f4d85c9411cffb0ac3",
	"ConchID_Mooncradle (1)":             "07a7b3fec78502e4cb8df7631792a233",
	"ConchID_Mooncradle (2)":             "1edeead6636d07b4da6e89fd9961d0cd",
	"ConchID_Moorlands (1)":              "4b94adf4f083a824b9eb4bfc7053f08a",
	"ConchID_Moorlands (2)":              "8f92a7ce30f380445bb1e77fe428e6fe",
	"ConchID_MossyCache (1)":             "ceff4d54c9fab35499f7c8c2a0dd3f89",
	"ConchID_MountainTrail (1)":          "18d92899f70a10248845d34ef582966c",
	"ConchID_NecroLair (1)":              "d600027e89127fb4da3e2e89bc404622",
	"ConchID_Outpost (1)":                "77fdfbfbb38a34d42a7ce99407cb47f2",
	"ConchID_Outpost (2)":                "cb755b4973e52a14ba92437c84f84e8b",
	"ConchID_Repine (1)":                 "874c6aba4d04d3f48a51135ac6bdbdc8",
	"ConchID_Repine (2)":                 "874662dd90976274b8b826122c7405aa",
	"ConchID_Repine (3)":                 "d03dc856fbc4ecf4aae4538ed9f9949c",
	"ConchID_SacredGrove (1)":            "868efdff1f7e0544993f7833b3ab98f1",
	"ConchID_SacrosanctTemple (1)":       "49161a708ab13b2439fb8f10dfe4ccc0",
	"ConchID_SkyGiantVillage (1)":        "8f701dbb72eadad4d89baa8fd7535059",
	"ConchID_SkyGiantVillage (2)":        "acbba75484d4e8343856a7a1f89df39c",
	"ConchID_Skybase (1)":                "c44c69e01c64236409fc4e4aaa9e4d2b",
	"ConchID_SleeperIslandYeetGolem (1)": "39acb7edaa21bf3499e8e6809d90ecc5",
	"ConchID_SongShroomMarsh (1)":        "e75afe9135293404e91a55f541bff715",
	"ConchID_SunkenRuinsBoss (1)":        "bac4c3b66c8a66442acc50e7ec83c29b",
	"ConchID_TheQueenThrone (1)":         "2968c6b089c9da24c9be20c1822e3370",
	"ConchID_TormentPeak (1)":            "d11a7de0ed9b8964299a799442dd82d9",
	"ConchID_WaterTemple (1)":            "3447183c44062ed439e3fa921903ba7b",
	"ConchID_WindMines (1)":              "f5ae2813305f0f240acd361d04d59f82",
	"ConchID_Wizlab (1)":                 "acbf7d8e96065004483610a3b8939555",
	"ConchID_Wizlab (2)":                 "d0677b0430c0561418dac8a3df0be22b",
}

var PIRATE_SONGS = map[string]string{
	"PirateSong_10_ElderMistTrials":  "3272244d4e67c28469e7f7e8bfd4e36f",
	"PirateSong_11_Mooncradle":       "ceedf99c2494ce64ebb1e7048315110b",
	"PirateSong_12_Miniboss":         "75edb60f84f6d1144b8d9573bd783d2f",
	"PirateSong_13_MountainTrail":    "d05a654682a3f4341bef0a2bb5f7dfdc",
	"PirateSong_14_CursedWoods":      "b4ad40ec302314f4599c2d96ad183106",
	"PirateSong_15_Ferryman":         "98fe40247dbf3504bb78f1ef31cac444",
	"PirateSong_16_Lucent":           "12d2b9c304443da4b90b53ff8bf30c0d",
	"PirateSong_17_NecromancerLair":  "1dabd3d6a2718054bb7cd8478681336d",
	"PirateSong_18_Docarri":          "3fc306d900b04844f9ed74308b5d30a7",
	"PirateSong_19_JunglePath":       "49bfa384c40ba934f88e458ddd04d1fa",
	"PirateSong_1_Garl":              "0a87fda86471d004ea7664d747ebbf2e",
	"PirateSong_20_OracleOfTides":    "ace046d371d6b114eb463a53f80c6e44",
	"PirateSong_21_WatcherIsland":    "05c068781fcb82e4da8e186179c2fbcc",
	"PirateSong_22_CursedVespertine": "ef2880e4dcaec5947b9c27c181856acc",
	"PirateSong_23_Stormcaller":      "1189b48c91dfa4540a66717a7a83d82c",
	"PirateSong_24_Crypt":            "ff428bd1166556c4ab8e11e388f48148",
	"PirateSong_25_AcolyteBoss":      "f500740ef56291b4fa80527262c38876",
	"PirateSong_26_BabyGorillas":     "904da597aefc9294da0118e1f73b7fef",
	"PirateSong_27_GlacialPeak":      "decdd99448f24fc46b7f9b9128d14f1c",
	"PirateSong_28_WaterTemple":      "99fe2ce3b44a4b84fa9f8e046aa6c788",
	"PirateSong_29_AutumnHills":      "22e52346334b461468d2ab7efa0df031",
	"PirateSong_2_Battle":            "6f9c49155b12f1442bc0bbec2e888e70",
	"PirateSong_30_CaelAndTheKids":   "69486e5bcce1a024094d9657157329b9",
	"PirateSong_31_ClockworkCastle":  "35f52d5fd307c0842a5050be650bab5e",
	"PirateSong_32_SongshroomMarsh":  "a45ced77543404648a8e55199a816064",
	"PirateSong_33_AirSkylands":      "ca09e30d4f0547847b34f3a67af30180",
	"PirateSong_34_AutumnHillsBoss":  "7e3f0c5cbfe641546a41099d1354b6c8",
	"PirateSong_35_Factory":          "757d67440d985364c8f359a87d80b160",
	"PirateSong_36_LostOnesHamlet":   "5aa8cb4d7f4d2d348bc2ddd2352415a7",
	"PirateSong_37_SkyBase":          "1770a1f28eebcef40b6ce00081b0d677",
	"PirateSong_3_Molekin":           "adccd3c5726cdd54c9623a8c4a8900a8",
	"PirateSong_4_Moorlands":         "3db56f85d4a1d43498a6c95332fb457a",
	"PirateSong_5_Brisk":             "b34da424af540214ca68a8180724aff5",
	"PirateSong_6_Encounter":         "df1a43f65bcdf0c488c5a9196cc01570",
	"PirateSong_7_SleeperIsland":     "d231be2a0b9f2bc4197f8a6f286160a7",
	"PirateSong_8_Teaks":             "075931239f328ab4b99e4233c3e553d8",
	"PirateSong_9_WindTunnels":       "859c3d5e3a4c2894b87723aaf36f5863",
}
