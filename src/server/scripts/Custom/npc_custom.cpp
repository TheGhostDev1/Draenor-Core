////////////////////////////////////////////////////////////////////////////////
//
// Project-Hellscream https://hellscream.org
// Copyright (C) 2018-2020 Project-Hellscream-6.2
// Discord https://discord.gg/CWCF3C9
//
////////////////////////////////////////////////////////////////////////////////

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "GameObjectAI.h"
#include "NPCHandler.h"
#include "Vehicle.h"
#include "Common.h"
#include "ObjectMgr.h"
#include "World.h"
#include "PetAI.h"
#include "PassiveAI.h"
#include "CombatAI.h"
#include "GameEventMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"
#include "SpellAuras.h"
#include "Vehicle.h"
#include "Player.h"
#include "SpellScript.h"
#include "MapManager.h"
#include "Chat.h"

/// ????? - Hellscream Beta Teleporter
/// No SQL commit with this script, must stay in Beta.
/*
INSERT INTO `creature_template` (`entry`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `femaleName`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_req`, `faction`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_fly`, `scale`, `rank`, `dmgschool`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `baseVariance`, `rangeVariance`, `unit_class`, `unit_flags`, `unit_flags2`, `unit_flags3`, `dynamicflags`, `WorldEffectID`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `TrackingQuestID`, `VignetteID`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `BuildVerified`) VALUES('4050924','0','0','18720','0','0','0','Hellscream Teleporter','','Help Test All Content','','0','100','100','6','0','35','1','0','1','1.14286','1.14286','1','0','0','1','0','0','1','1','1','518','0','0','0','0','0','0','0','0','0','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','1','0','0','0','npc_hellscream_teleporter','1');
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `content_loc9`, `content_loc10`) VALUES (124097, 'Visit the Hellscream Teleporter to debug the new content!', NULL, 'Visit the Hellscream Teleporter to debug the new content!', 'Visit the Hellscream Teleporter to debug the new content!', NULL, NULL, 'Visit the Hellscream Teleporter to debug the new content!', NULL, 'Visit the Hellscream Teleporter to debug the new content!', NULL, NULL);
*/
class npc_hellscream_teleporter : public CreatureScript
{
    public:
        npc_hellscream_teleporter() : CreatureScript("npc_hellscream_teleporter")
        {
        }

        enum eActions
        {
			SelectWodstart = 1001,
			SelectBloodmaulslagmines = 1002,
			SelectIrondocks = 1003,
			SelectAuchindoun = 1004,
			SelectSkyreach = 1005,
			SelectGrimraildepot = 1006,
			SelectShadowmoonburialgrounds = 1007,
			SelectEverbloom = 1008,
			SelectUpperblackrockspire = 1009,
			SelectHighmaul = 1010,
			SelectBlackrock = 1011,
			SelectHFC      = 1012,
            SelectRukhmar     = 1013,
            SelectTarlna      = 1014,
            SelectDrov        = 1015,
			SelectKazz        = 1016,
			TpAloneWodstart = 1017,
			TpGroupWodstart = 1018,
			TpAloneBloodmaulslagmines = 1019,
			TpGroupBloodmaulslagmines = 1020,
			TpAloneIrondocks = 1021,
			TpGroupIrondocks = 1022,
			TpAloneAuchindoun = 1023,
			TpGroupAuchindoun = 1024,
			TpAloneSkyreach = 1025,
			TpGroupSkyreach = 1026,
			TpAloneGrimraildepot = 1027,
			TpGroupGrimraildepot = 1028,
			TpAloneShadowmoonburialgrounds = 1029,
			TpGroupShadowmoonburialgrounds = 1030,
			TpAloneEverbloom = 1031,
			TpGroupEverbloom = 1032,
			TpAloneUpperblackrockspire = 1033,
			TpGroupUpperblackrockspire = 1034,
			TpAloneHighmaul = 1035,
			TpGroupHighmaul = 1036,
			TpAloneBlackrock = 1037,
			TpGroupBlackrock = 1038,
			TpAloneHFC = 1039,
			TpGroupHFC = 1040,
            TpAloneRukhmar    = 1041,
            TpGroupRukhmar    = 1042,
            TpAloneTarlna     = 1043,
            TpGroupTarlna     = 1044,
            TpAloneDrov       = 1045,
            TpGroupDrov       = 1046,
			TpAloneKazz       = 1047,
			TpGroupKazz       = 1048,

        };

        enum Destinations
        {
			DestinationWodstart = 1,
			DestinationBloodmaulslagmines = 2,
			DestinationIrondocks = 3,
			DestinationAuchindoun = 4,
			DestinationSkyreach = 5,
			DestinationGrimraildepot = 6,
			DestinationShadowmoonburialgrounds = 7,
			DestinationEverbloom = 8,
			DestinationUpperblackrockspire = 9,
			DestinationHighmaul = 10,
			DestinationBlackRockFoundry = 11,
			DestinationHFC = 12,
            DestinationRukhmar          = 13,
            DestinationTarlna           = 14,
            DestinationDrov             = 15,
			DestinationKazz             = 16
            
        };

        void TeleportPlayer(Player* p_Player, uint8 p_Destination)
        {
            switch (p_Destination)
            {
			case Destinations::DestinationWodstart:
				p_Player->TeleportTo(1, -8452.49f, -4202.24f, -211.992f, 4.38f);
				break;
                case Destinations::DestinationBloodmaulslagmines:
                    p_Player->TeleportTo(1175, 1829.37f, -245.757f, 255.727f, 46.1094f);
                    break;
				case Destinations::DestinationIrondocks:
					p_Player->TeleportTo(1195, 6746.09f, -545.04f, 4.89f, 4.8989f);
					break;
				case Destinations::DestinationAuchindoun:
					p_Player->TeleportTo(1182, 1483.99f, 2953.26f, 35.2387f, 0.0275292f);
					break;
				case Destinations::DestinationGrimraildepot:
					p_Player->TeleportTo(1208, 1737.59f, 1681.19f, 7.6742f, 3.082f);
					break;
				case Destinations::DestinationSkyreach:
					p_Player->TeleportTo(1209, 1232.46f, 1743.71f, 177.169f, 331.58f);
					break;
				case Destinations::DestinationShadowmoonburialgrounds:
					p_Player->TeleportTo(1176, 1774.28f, 213.331f, 304.917f, 4.69119f);
					break;
				case Destinations::DestinationEverbloom:
					p_Player->TeleportTo(1279, 454.855f, 1350.13f, 117.067f, 0.966836f);
					break;
				case Destinations::DestinationUpperblackrockspire:
					p_Player->TeleportTo(1358, 120.472f, -319.104f, 70.9541f, 6.2642f);
					break;
				case Destinations::DestinationRukhmar:
					p_Player->TeleportTo(1116, 167.2388f, 2655.39f, 68.58f, 4.105f);
					break;
                case Destinations::DestinationTarlna:
                    p_Player->TeleportTo(1116, 4918.54f, 1292.16f, 120.28f, 4.018f);
                    break;
                case Destinations::DestinationDrov:
                    p_Player->TeleportTo(1116, 7330.3f, 1455.87f, 81.76f, 6.08f);
                    break;
				case Destinations::DestinationKazz:
					p_Player->TeleportTo(1464, 5122.14f, -814.783f, 329.13f, 0.759337f);
					break;
                case Destinations::DestinationHighmaul:
					p_Player->TeleportTo(1228, 3486.48f, 7603.32f, 10.4853f, 4.0252f);
                    break;
                case Destinations::DestinationBlackRockFoundry:
					p_Player->TeleportTo(1205, 131.172f, 3429.48f, 319.829f, 0.00135f);
                    break;
				case Destinations::DestinationHFC:
					p_Player->TeleportTo(1448, 3980.45f, -782.131f, 36.5177f, 1.74766f);
					break;
            }
        }

        void TeleportGroup(Player* p_Player, uint8 p_Destination)
        {
            std::list<Unit*> l_PlayerList;
            p_Player->GetPartyMembers(l_PlayerList);

            for (Unit* l_GroupMember : l_PlayerList)
            {
                if (l_GroupMember->IsPlayer())
                {
                    switch (p_Destination)
                    {
					case Destinations::DestinationWodstart:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationWodstart);
						break;
					case Destinations::DestinationBloodmaulslagmines:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationBloodmaulslagmines);
						break;
					case Destinations::DestinationIrondocks:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationIrondocks);
						break;
					case Destinations::DestinationAuchindoun:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationAuchindoun);
						break;
					case Destinations::DestinationGrimraildepot:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationGrimraildepot);
						break;
					case Destinations::DestinationSkyreach:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationSkyreach);
						break;
					case Destinations::DestinationShadowmoonburialgrounds:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationShadowmoonburialgrounds);
						break;
					case Destinations::DestinationEverbloom:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationEverbloom);
						break;
					case Destinations::DestinationUpperblackrockspire:
						TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationUpperblackrockspire);
						break;
                        case Destinations::DestinationRukhmar:
                            TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationRukhmar);
                            break;
                        case Destinations::DestinationTarlna:
                            TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationTarlna);
                            break;
                        case Destinations::DestinationDrov:
                            TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationDrov);
                            break;
						case Destinations::DestinationKazz:
							TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationKazz);
							break;
                        case Destinations::DestinationHighmaul:
							TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationHighmaul);
                            break;
                        case Destinations::DestinationBlackRockFoundry:
							TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationBlackRockFoundry);
                            break;
						case Destinations::DestinationHFC:
							TeleportPlayer(l_GroupMember->ToPlayer(), Destinations::DestinationHFC);
							break;

                    }
                }
            }
        }

        bool OnGossipHello(Player* p_Player, Creature* p_Creature) override
        {
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Intro] Warlords of Draenor, please.", GOSSIP_SENDER_MAIN, eActions::SelectWodstart);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Bloodmaul Slag Mines, please.", GOSSIP_SENDER_MAIN, eActions::SelectBloodmaulslagmines);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Iron Docks, please.", GOSSIP_SENDER_MAIN, eActions::SelectIrondocks);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Auchindoun, please.", GOSSIP_SENDER_MAIN, eActions::SelectAuchindoun);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Grimrail Depot, please.", GOSSIP_SENDER_MAIN, eActions::SelectGrimraildepot);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Skyreach, please.", GOSSIP_SENDER_MAIN, eActions::SelectSkyreach);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Shadowmoon Burial Grounds, please.", GOSSIP_SENDER_MAIN, eActions::SelectShadowmoonburialgrounds);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] The Everbloom, please.", GOSSIP_SENDER_MAIN, eActions::SelectEverbloom);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Dungeon] Upper Blackrock Spire, please.", GOSSIP_SENDER_MAIN, eActions::SelectUpperblackrockspire);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Raid] Highmaul, please.", GOSSIP_SENDER_MAIN, eActions::SelectHighmaul);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Raid] Blackrock Foundry, please.", GOSSIP_SENDER_MAIN, eActions::SelectBlackrock);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[Raid] Hellfire Citadel, please.", GOSSIP_SENDER_MAIN, eActions::SelectHFC);
            p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[World Boss] Rukhmar, please.", GOSSIP_SENDER_MAIN, eActions::SelectRukhmar);
            p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[World Boss] Tarlna, please.", GOSSIP_SENDER_MAIN, eActions::SelectTarlna);
            p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[World Boss] Drov, please.", GOSSIP_SENDER_MAIN, eActions::SelectDrov);
			p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "[World Boss] Supreme Lord Kazzak, please.", GOSSIP_SENDER_MAIN, eActions::SelectKazz);
            p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* p_Player, Creature* p_Creature, uint32 /*p_Sender*/, uint32 p_Action) override
        {
            p_Player->PlayerTalkClass->ClearMenus();
            p_Player->PlayerTalkClass->SendCloseGossip();

            switch (p_Action)
            {
			case eActions::SelectWodstart:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to teleport to Tanaris alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneWodstart);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to teleport to Tanaris with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupWodstart);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectBloodmaulslagmines:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Bloodmaul Slag Mines alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneBloodmaulslagmines);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Bloodmaul Slag Mines with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupBloodmaulslagmines);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectIrondocks:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Iron Docks alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneIrondocks);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Iron Docks with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupIrondocks);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectAuchindoun:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Auchindoun alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneAuchindoun);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Auchindoun with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupAuchindoun);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectGrimraildepot:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Grimrail Depot alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneGrimraildepot);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Grimrail Depot with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupGrimraildepot);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectSkyreach:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Skyreach alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneSkyreach);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Skyreach with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupSkyreach);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectShadowmoonburialgrounds:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Shadowmoon Burial Grounds alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneShadowmoonburialgrounds);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Shadowmoon Burial Grounds with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupShadowmoonburialgrounds);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectEverbloom:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test The Everbloom alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneEverbloom);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight The Everbloom with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupEverbloom);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
			case eActions::SelectUpperblackrockspire:
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Upper Blackrock Spire alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneUpperblackrockspire);
				p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Upper Blackrock Spire with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupUpperblackrockspire);
				p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
				break;
                case eActions::SelectRukhmar:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Rukhmar alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneRukhmar);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Rukhmar with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupRukhmar);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectTarlna:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Tarlna alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneTarlna);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Tarlna with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupTarlna);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectDrov:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Drov alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneDrov);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Drov with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupDrov);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
				case eActions::SelectKazz:
					p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Supreme Lord Kazzak alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneKazz);
					p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Supreme Lord Kazzak with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupKazz);
					p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
					break;
                case eActions::SelectHighmaul:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Highmaul alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneHighmaul);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Highmaul with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupHighmaul);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectBlackrock:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Blackrock Foundry alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneBlackrock);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Blackrock Foundry with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupBlackrock);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
				case eActions::SelectHFC:
					p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to test Hellfire Citadel alone.", GOSSIP_SENDER_MAIN, eActions::TpAloneHFC);
					p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I want to fight Hellfire Citadel with my group.", GOSSIP_SENDER_MAIN, eActions::TpGroupHFC);
					p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
					break;
				case eActions::TpAloneWodstart:
					TeleportPlayer(p_Player, Destinations::DestinationWodstart);
					break;
				case eActions::TpAloneBloodmaulslagmines:
					TeleportPlayer(p_Player, Destinations::DestinationBloodmaulslagmines);
					break;
				case eActions::TpGroupBloodmaulslagmines:
					TeleportGroup(p_Player, Destinations::DestinationBloodmaulslagmines);
					break;
				case eActions::TpAloneIrondocks:
					TeleportPlayer(p_Player, Destinations::DestinationIrondocks);
					break;
				case eActions::TpGroupIrondocks:
					TeleportGroup(p_Player, Destinations::DestinationIrondocks);
					break;
				case eActions::TpAloneAuchindoun:
					TeleportPlayer(p_Player, Destinations::DestinationAuchindoun);
					break;
				case eActions::TpGroupAuchindoun:
					TeleportGroup(p_Player, Destinations::DestinationAuchindoun);
					break;
				case eActions::TpAloneGrimraildepot:
					TeleportPlayer(p_Player, Destinations::DestinationGrimraildepot);
					break;
				case eActions::TpGroupGrimraildepot:
					TeleportGroup(p_Player, Destinations::DestinationGrimraildepot);
					break;
				case eActions::TpAloneSkyreach:
					TeleportPlayer(p_Player, Destinations::DestinationSkyreach);
					break;
				case eActions::TpGroupSkyreach:
					TeleportGroup(p_Player, Destinations::DestinationSkyreach);
					break;
				case eActions::TpAloneShadowmoonburialgrounds:
					TeleportPlayer(p_Player, Destinations::DestinationShadowmoonburialgrounds);
					break;
				case eActions::TpGroupShadowmoonburialgrounds:
					TeleportGroup(p_Player, Destinations::DestinationShadowmoonburialgrounds);
					break;
				case eActions::TpAloneEverbloom:
					TeleportPlayer(p_Player, Destinations::DestinationEverbloom);
					break;
				case eActions::TpGroupEverbloom:
					TeleportGroup(p_Player, Destinations::DestinationEverbloom);
					break;
				case eActions::TpAloneUpperblackrockspire:
					TeleportPlayer(p_Player, Destinations::DestinationUpperblackrockspire);
					break;
				case eActions::TpGroupUpperblackrockspire:
					TeleportGroup(p_Player, Destinations::DestinationUpperblackrockspire);
					break;
                case eActions::TpAloneRukhmar:
                    TeleportPlayer(p_Player, Destinations::DestinationRukhmar);
                    break;
                case eActions::TpGroupRukhmar:
                    TeleportGroup(p_Player, Destinations::DestinationRukhmar);
                    break;
                case eActions::TpAloneTarlna:
                    TeleportPlayer(p_Player, Destinations::DestinationTarlna);
                    break;
                case eActions::TpGroupTarlna:
                    TeleportGroup(p_Player, Destinations::DestinationTarlna);
                    break;
                case eActions::TpAloneDrov:
                    TeleportPlayer(p_Player, Destinations::DestinationDrov);
                    break;
                case eActions::TpGroupDrov:
                    TeleportGroup(p_Player, Destinations::DestinationDrov);
                    break;
				case eActions::TpAloneKazz:
					TeleportPlayer(p_Player, Destinations::DestinationKazz);
					break;
				case eActions::TpGroupKazz:
					TeleportGroup(p_Player, Destinations::DestinationKazz);
					break;
                case eActions::TpAloneHighmaul:
                    TeleportPlayer(p_Player, Destinations::DestinationHighmaul);
                    break;
                case eActions::TpGroupHighmaul:
                    TeleportGroup(p_Player, Destinations::DestinationHighmaul);
                    break;
                case eActions::TpAloneBlackrock:
                    TeleportPlayer(p_Player, Destinations::DestinationBlackRockFoundry);
                    break;
                case eActions::TpGroupBlackrock:
                    TeleportGroup(p_Player, Destinations::DestinationBlackRockFoundry);
                    break;
				case eActions::TpAloneHFC:
					TeleportPlayer(p_Player, Destinations::DestinationHFC);
					break;
				case eActions::TpGroupHFC:
					TeleportGroup(p_Player, Destinations::DestinationHFC);
					break;
                default:
                    break;
            }

            return true;
        }

        struct npc_hellscream_teleporterAI : public ScriptedAI
        {
            npc_hellscream_teleporterAI(Creature* creature) : ScriptedAI(creature)
            {
                m_YellTimer = 300 * IN_MILLISECONDS;
            }

            uint32 m_YellTimer;

            void UpdateAI(uint32 const p_Diff) override
            {
                if (m_YellTimer)
                {
                    if (m_YellTimer <= p_Diff)
                    {
                        
                        me->YellToZone(124097, LANG_UNIVERSAL, 0);
                        m_YellTimer = 300 * IN_MILLISECONDS;
                    }
                    else
                        m_YellTimer -= p_Diff;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_hellscream_teleporterAI(creature);
        }
};

enum eHighmaulDests
{
    DestinationKargath,
    DestinationButcher,
    DestinationBrackenspore,
    DestinationTectus,
    DestinationTwinOgron,
    DestinationKoragh,
    DestinationMargok,
    MaxHighmaulDests
};

Position const g_HighmaulDests[eHighmaulDests::MaxHighmaulDests] =
{
    { 3475.60f, 7590.64f, 55.30f, 4.062f }, ///< Kargath
    { 3698.73f, 7601.06f, 30.03f, 1.178f }, ///< Butcher
    { 3983.92f, 7742.95f, 5.009f, 0.019f }, ///< Brackenspore
    { 3492.97f, 7907.10f, 68.40f, 0.679f }, ///< Tectus
    { 3923.18f, 8310.01f, 322.1f, 0.836f }, ///< Twin Ogron
    { 3864.26f, 8554.24f, 367.6f, 0.903f }, ///< Ko'ragh
    { 4067.41f, 8582.56f, 572.6f, 3.084f }  ///< Imperator Mar'gok
};

/// This class is used to activate tests for Highmaul
class HighmaulTestEnable : public BasicEvent
{
    enum eHighmaulData
    {
        TestsActivated = 1
    };

    public:
        HighmaulTestEnable(uint64 p_Guid) : BasicEvent(), m_Guid(p_Guid) { }
        virtual ~HighmaulTestEnable() {}

        virtual bool Execute(uint64 /*p_EndTime*/, uint32 /*p_Time*/)
        {
            if (Player* l_Player = HashMapHolder<Player>::Find(m_Guid))
            {
                if (InstanceScript* l_Highmaul = l_Player->GetInstanceScript())
                {
                    if (l_Highmaul->GetData(eHighmaulData::TestsActivated))
                        return false;

                    l_Highmaul->SetData(eHighmaulData::TestsActivated, true);
                }
            }

            return true;
        }

        virtual void Abort(uint64 /*p_EndTime*/) { }

    private:
        uint64 m_Guid;
};

class npc_pve_tests_manager : public CreatureScript
{
    public:
        npc_pve_tests_manager() : CreatureScript("npc_pve_tests_manager") { }

        enum eActions
        {
            /// Gossip select
            /// Highmaul
            SelectHighmaul      = 1000,
            SelectKargath       = 1001,
            SelectButcher       = 1002,
            SelectBrackenspore  = 1003,
            SelectTectus        = 1004,
            SelectTwinOgron     = 1005,
            SelectKoragh        = 1006,
            SelectMargok        = 1007,
            /// Blackrock Foundry
            SelectBlackrock     = 1008,
            SelectBRFAlone      = 1009,
            SelectBRFGroup      = 1010,
            /// Boss select
            /// Highmaul
            KargathGroup        = 10001,
            ButcherGroup        = 10002,
            BrackensporeGroup   = 10003,
            TectusGroup         = 10004,
            TwinOgronGroup      = 10005,
            KoraghGroup         = 10006,
            MargokGroup         = 10007
        };

        enum eData
        {
            HighmaulMapID = 1228
        };

        bool OnGossipHello(Player* p_Player, Creature* p_Creature) override
        {
            p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to do some tests in Highmaul.", GOSSIP_SENDER_MAIN, eActions::SelectHighmaul);
            p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to do some tests in Blackrock Foundry.", GOSSIP_SENDER_MAIN, eActions::SelectBlackrock);
            p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* p_Player, Creature* p_Creature, uint32 /*p_Sender*/, uint32 p_Action) override
        {
            p_Player->PlayerTalkClass->ClearMenus();
            p_Player->PlayerTalkClass->SendCloseGossip();

            if (!p_Creature->IsAIEnabled)
                return true;

            npc_pve_tests_manager::npc_pve_tests_managerAI* l_AI = CAST_AI(npc_pve_tests_manager::npc_pve_tests_managerAI, p_Creature->GetAI());
            if (l_AI == nullptr)
                return true;

            switch (p_Action)
            {
                case eActions::SelectHighmaul:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against Kargath Bladefist.", GOSSIP_SENDER_MAIN, eActions::SelectKargath);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against The Butcher.", GOSSIP_SENDER_MAIN, eActions::SelectButcher);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against Brackenspore.", GOSSIP_SENDER_MAIN, eActions::SelectBrackenspore);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against Tectus.", GOSSIP_SENDER_MAIN, eActions::SelectTectus);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against the Twin Ogron.", GOSSIP_SENDER_MAIN, eActions::SelectTwinOgron);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against Ko'ragh.", GOSSIP_SENDER_MAIN, eActions::SelectKoragh);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight against Imperator Mar'gok.", GOSSIP_SENDER_MAIN, eActions::SelectMargok);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectKargath:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight Kargath Bladefist with my group.", GOSSIP_SENDER_MAIN, eActions::KargathGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectButcher:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight The Butcher with my group.", GOSSIP_SENDER_MAIN, eActions::ButcherGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectBrackenspore:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight Brackenspore with my group.", GOSSIP_SENDER_MAIN, eActions::BrackensporeGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectTectus:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight Tectus with my group.", GOSSIP_SENDER_MAIN, eActions::TectusGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectTwinOgron:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight the Twin Ogron with my group.", GOSSIP_SENDER_MAIN, eActions::TwinOgronGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectKoragh:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight Ko'ragh with my group.", GOSSIP_SENDER_MAIN, eActions::KoraghGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectMargok:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to fight Imperator Mar'gok with my group.", GOSSIP_SENDER_MAIN, eActions::MargokGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::SelectBlackrock:
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to be teleported to Blackrock Foundry alone.", GOSSIP_SENDER_MAIN, eActions::SelectBRFAlone);
                    p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, "I want to be teleported to Blackrock Foundry with my group.", GOSSIP_SENDER_MAIN, eActions::SelectBRFGroup);
                    p_Player->SEND_GOSSIP_MENU(1, p_Creature->GetGUID());
                    break;
                case eActions::KargathGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationKargath);
                    break;
                case eActions::ButcherGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationButcher);
                    break;
                case eActions::BrackensporeGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationBrackenspore);
                    break;
                case eActions::TectusGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationTectus);
                    break;
                case eActions::TwinOgronGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationTwinOgron);
                    break;
                case eActions::KoraghGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationKoragh);
                    break;
                case eActions::MargokGroup:
                    l_AI->TeleportGroup(p_Player, eHighmaulDests::DestinationMargok);
                    break;
                case eActions::SelectBRFAlone:
                    p_Player->TeleportTo(1116, 8084.64f, 855.51f, 34.3623f, 6.037f);
                    break;
                case eActions::SelectBRFGroup:
                    l_AI->TeleportGroup(p_Player, 8084.64f, 855.51f, 34.3623f, 6.037f);
                    break;
                default:
                    break;
            }

            return true;
        }

        struct npc_pve_tests_managerAI : public ScriptedAI
        {
            npc_pve_tests_managerAI(Creature* p_Creature) : ScriptedAI(p_Creature)
            {
                m_YellTimer = 300 * IN_MILLISECONDS;
            }

            uint32 m_YellTimer;

            void UpdateAI(uint32 const p_Diff) override
            {
                if (m_YellTimer)
                {
                    if (m_YellTimer <= p_Diff)
                    {
                        /// "Hey $N, come to me in your faction capital, to access fastly our last testable content ! Newest raids, boss, get directly teleported to the destination you are looking for."
                        me->YellToZone(TrinityStrings::WarnRaidTests, LANG_UNIVERSAL, 0);
                        m_YellTimer = 300 * IN_MILLISECONDS;
                    }
                    else
                        m_YellTimer -= p_Diff;
                }
            }

            void TeleportPlayer(Player* p_Player, uint8 p_Destination)
            {
                if (p_Destination >= eHighmaulDests::MaxHighmaulDests)
                    return;

                /// This will prevent players to be re-teleported depending on bosses states
                p_Player->BeginSummon();
                p_Player->TeleportTo(eData::HighmaulMapID, g_HighmaulDests[p_Destination]);

                p_Player->m_Events.AddEvent(new HighmaulTestEnable(p_Player->GetGUID()), 3 * TimeConstants::IN_MILLISECONDS);
            }

            void TeleportGroup(Player* p_Player, uint8 p_Destination)
            {
                if (p_Player->GetGroup() == nullptr)
                {
                    me->MonsterSay("Sorry, but you must be in a raid group to test this boss.", LANG_UNIVERSAL, 0);
                    return;
                }

                std::list<Unit*> l_PlayerList;
                p_Player->GetRaidMembers(l_PlayerList);

                for (Unit* l_GroupMember : l_PlayerList)
                {
                    if (l_GroupMember->GetTypeId() == TypeID::TYPEID_PLAYER)
                        TeleportPlayer(l_GroupMember->ToPlayer(), p_Destination);
                }
            }

            void TeleportGroup(Player* p_Player, float p_X, float p_Y, float p_Z, float p_O)
            {
                if (p_Player->GetGroup() == nullptr)
                {
                    me->MonsterSay("Sorry, but you must be in a raid group to test this boss.", LANG_UNIVERSAL, 0);
                    return;
                }

                std::list<Unit*> l_PlayerList;
                p_Player->GetRaidMembers(l_PlayerList);

                for (Unit* l_GroupMember : l_PlayerList)
                {
                    if (l_GroupMember->GetTypeId() == TypeID::TYPEID_PLAYER)
                        l_GroupMember->ToPlayer()->TeleportTo(1116, p_X, p_Y, p_Z, p_O);
                }
            }
        };

        CreatureAI* GetAI(Creature* p_Creature) const override
        {
            return new npc_pve_tests_managerAI(p_Creature);
        }
};

/// Warlords of draenor intro? - NPC
class npc_hellscream_booster : public CreatureScript
{
    public:
        npc_hellscream_booster() : CreatureScript("npc_hellscream_booster") { }

        enum eOptions
        {
            LevelUp,
            FullEquipment
        };

        enum eItems
        {
            HexweaveBag                     = 114821,
            TomeOfTheClearMind              = 79249,
            ReinsOfTheIllidariFelstalker    = 118515
        };

        enum eMenuIDs
        {
            MenuBaseLevel   = 179317,
            MenuBaseStuff   = 179318,
            MenuUnable      = 179319
        };

        enum eTalks
        {
            TalkSpec,
            TalkError,
            TalkNoSpace,
            TalkStuffOK,
            TalkLevelOK
        };

        enum eVisual
        {
            MountID = 29344
        };

        bool OnGossipHello(Player* p_Player, Creature* p_Creature) override
        {
           // if (!p_Player->GetSession()->HasServiceFlags(ServiceFlags::Season2Gold) &&
           //    !p_Player->GetSession()->HasServiceFlags(ServiceFlags::Season2Item))
            {
                p_Player->PlayerTalkClass->ClearMenus();
                p_Player->SEND_GOSSIP_MENU(eMenuIDs::MenuUnable, p_Creature->GetGUID());
               
                p_Player->ADD_GOSSIP_ITEM_DB(eMenuIDs::MenuBaseLevel, 0, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                p_Player->SEND_GOSSIP_MENU(eMenuIDs::MenuBaseLevel, p_Creature->GetGUID());
                
            }

            return true;
        }

        struct npc_hellscream_boosterAI : public ScriptedAI
        {
            npc_hellscream_boosterAI(Creature* p_Creature) : ScriptedAI(p_Creature) { }

            void Reset() override
            {
                me->SetUInt32Value(EUnitFields::UNIT_FIELD_MOUNT_DISPLAY_ID, eVisual::MountID);

                me->SetReactState(ReactStates::REACT_PASSIVE);
            }

            void sGossipSelect(Player* p_Player, uint32 /*p_MenuID*/, uint32 /*p_Action*/) override
            {
              //  if (p_Player->GetSession()->HasServiceFlags(ServiceFlags::Season2Gold))
                {
                    /// Player doesn't have enough space
                    if (p_Player->GetBagsFreeSlots() < 6)
                    {
                        Talk(eTalks::TalkNoSpace, p_Player->GetGUID());
                        p_Player->PlayerTalkClass->SendCloseGossip();
                        return;
                    }

                    p_Player->GiveLevel(MAX_LEVEL);
                    p_Player->ModifyMoney(100000 * MoneyConstants::GOLD);
					p_Player->TeleportTo(1, -8452.49f, -4202.24f, -211.992f, 4.38f);

                    p_Player->AddItem(eItems::HexweaveBag, 4);
                    p_Player->AddItem(eItems::TomeOfTheClearMind, 200);
                    p_Player->AddItem(eItems::ReinsOfTheIllidariFelstalker, 1);

                    //p_Player->GetSession()->UnsetServiceFlags(ServiceFlags::Season2Gold);
                    Talk(eTalks::TalkLevelOK, p_Player->GetGUID());
					Talk(eTalks::TalkStuffOK, p_Player->GetGUID());
					p_Player->PlayerTalkClass->SendCloseGossip();
                }
				{
                    if (!p_Player->GetSpecializationId())
                    {
                        Talk(eTalks::TalkSpec, p_Player->GetGUID());
                        p_Player->PlayerTalkClass->SendCloseGossip();
                        return;
                    }

                    if (!GiveFullPvPEquipment(p_Player))
                    {
                        p_Player->PlayerTalkClass->SendCloseGossip();
                        return;
                    }

                    //p_Player->GetSession()->UnsetServiceFlags(ServiceFlags::Season2Item);
                    //Talk(eTalks::TalkStuffOK, p_Player->GetGUID());
                }

                p_Player->PlayerTalkClass->SendCloseGossip();
            }

            bool GiveFullPvPEquipment(Player* p_Player)
            {
                LootStore& l_LootStore = LootTemplates_Creature;
                LootTemplate const* l_LootTemplate = l_LootStore.GetLootFor(me->GetCreatureTemplate()->lootid);
                if (l_LootTemplate == nullptr)
                {
                    Talk(eTalks::TalkError, p_Player->GetGUID());
                    return false;
                }

                std::list<ItemTemplate const*>      l_LootTable;
                std::vector<std::vector<uint32>>    l_Items;
                std::set<uint32>                    l_ItemsToAdd;

                l_LootTemplate->FillAutoAssignationLoot(l_LootTable, p_Player, false);

                uint32 l_SpecID     = p_Player->GetSpecializationId();
                uint32 l_ItemCount  = 0;

                l_Items.resize(InventoryType::MAX_INVTYPE);

                /// Fill possible equipment for each slots
                for (uint8 l_Iter = 0; l_Iter < InventoryType::MAX_INVTYPE; ++l_Iter)
                {
                    l_Items[l_Iter].clear();

                    for (ItemTemplate const* l_Template : l_LootTable)
                    {
                        if (l_Template->InventoryType != l_Iter)
                            continue;

                        if (p_Player->CanUseItem(l_Template) != InventoryResult::EQUIP_ERR_OK)
                            continue;

                        if (!l_Template->HasSpec((SpecIndex)l_SpecID, p_Player->getLevel()))
                            continue;

                        l_Items[l_Iter].push_back(l_Template->ItemId);
                    }

                    std::random_shuffle(l_Items[l_Iter].begin(), l_Items[l_Iter].end());
                }

                for (uint8 l_Iter = 0; l_Iter < InventoryType::MAX_INVTYPE; ++l_Iter)
                {
                    uint8 l_Count = 1;

                    switch (l_Iter)
                    {
                        case InventoryType::INVTYPE_FINGER:
                        case InventoryType::INVTYPE_TRINKET:
                        case InventoryType::INVTYPE_WEAPON:
                            l_Count++;
                            break;
                        default:
                            break;
                    }

                    for (uint32 l_Item : l_Items[l_Iter])
                    {
                        if (!l_Count)
                            break;

                        if (l_ItemsToAdd.find(l_Item) != l_ItemsToAdd.end())
                            continue;

                        l_ItemsToAdd.insert(l_Item);
                        --l_Count;
                        ++l_ItemCount;
                    }
                }

                /// Player doesn't have enough space
                if (p_Player->GetBagsFreeSlots() < l_ItemCount)
                {
                    Talk(eTalks::TalkNoSpace, p_Player->GetGUID());
                    return false;
                }

                for (uint32 l_Item : l_ItemsToAdd)
                    p_Player->AddItem(l_Item, 1);

                return true;
            }
        };

        CreatureAI* GetAI(Creature* p_Creature) const override
        {
            return new npc_hellscream_boosterAI(p_Creature);
        }
}; 

class npc_fun_gold_vendor : public CreatureScript
{
    public:
        npc_fun_gold_vendor() : CreatureScript("npc_fun_gold_vendor") { }
    
        bool OnGossipHello(Player* p_Player, Creature* p_Creature) override
        {
            p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Give me 50 000 golds! ", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            p_Player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, p_Creature->GetGUID());
            return true;
        }
        
        struct npc_fun_gold_vendorAI : public ScriptedAI
        {
            npc_fun_gold_vendorAI(Creature* p_Creature) : ScriptedAI(p_Creature) { }
            
            void sGossipSelect(Player* p_Player, uint32 p_MenuID, uint32 p_Action) override
            {
                p_Player->ModifyMoney(50000 * MoneyConstants::GOLD);
                p_Player->PlayerTalkClass->SendCloseGossip();
            }
        };

        CreatureAI * GetAI(Creature* p_Creature) const override
        {
            return new npc_fun_gold_vendorAI(p_Creature);
        }
};

class npc_fun_transmo_vendor : public CreatureScript
{
    public:
        npc_fun_transmo_vendor() 
            : CreatureScript("npc_fun_transmo_vendor") 
        { 
        }
    
        /// Called when a player opens a gossip dialog with the creature.
        /// @p_Player   : Source player instance
        /// @p_Creature : Target creature instance
        bool OnGossipHello(Player* p_Player, Creature* p_Creature) override
        {
            static const uint8 l_VendorClass[] = {
                CLASS_DEATH_KNIGHT,
                CLASS_DRUID,
                CLASS_HUNTER,
                CLASS_MAGE,
                CLASS_MONK,
                CLASS_PALADIN,
                CLASS_PRIEST,
                CLASS_ROGUE,
                CLASS_SHAMAN,
                CLASS_WARLOCK,
                CLASS_WARRIOR,
            };

            uint8 l_ClassOffset = p_Creature->GetEntry() - 900003;

            if ((l_ClassOffset >= 0 && l_ClassOffset < sizeof(l_VendorClass) && l_VendorClass[l_ClassOffset] == p_Player->getClass()) || p_Player->isGameMaster())
            {
                p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvP Transmog", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                p_Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "PvE Transmog", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            }

            p_Player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, p_Creature->GetGUID());
            return true;
        }
        /// Called when a player selects a gossip item in the creature's gossip menu.
        /// @p_Player   : Source player instance
        /// @p_Creature : Target creature instance
        /// @p_Sender   : Sender menu
        /// @p_Action   : Action
        virtual bool OnGossipSelect(Player* p_Player, Creature* p_Creature, uint32 p_Sender, uint32 p_Action)
        {
            p_Player->PlayerTalkClass->SendCloseGossip();
            p_Player->GetSession()->SendListInventory(p_Creature->GetGUID(), p_Action == (GOSSIP_ACTION_INFO_DEF + 2), true);
            return false;
        }

};

class npc_legendary_transmogrificator : public CreatureScript
{
    public:
        npc_legendary_transmogrificator() : CreatureScript("npc_legendary_transmogrificator") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (player->getLevel() < 19)
            {
                player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                return true;
            }

            WorldSession* session = player->GetSession();
            for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_TABARD; slot++) // EQUIPMENT_SLOT_END
            {
                if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                {
                    uint32 quality = newItem->GetTemplate()->Quality;
                    if (quality == ITEM_QUALITY_UNCOMMON || quality == ITEM_QUALITY_RARE || quality == ITEM_QUALITY_EPIC || quality == ITEM_QUALITY_HEIRLOOM || quality == ITEM_QUALITY_LEGENDARY)
                    {
                        if (const char* slotName = GetSlotName(slot, session))
                            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, slotName, EQUIPMENT_SLOT_END, slot);
                    }
                }
            }
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, session->GetTrinityString(LANG_OPTION_REMOVE_ALL), EQUIPMENT_SLOT_END+2, 0, session->GetTrinityString(LANG_POPUP_REMOVE_ALL), 0, false);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, session->GetTrinityString(LANG_OPTION_UPDATE_MENU), EQUIPMENT_SLOT_END+1, 0);
            player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 uiAction)
        {
            WorldSession* session = player->GetSession();
            player->PlayerTalkClass->ClearMenus();
            switch(sender)
            {
                case EQUIPMENT_SLOT_END: // Show items you can use
                {
                    if (Item* oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, uiAction))
                    {
                        uint32 lowGUID = player->GetGUIDLow();
                        _items[lowGUID].clear();
                        uint32 limit = 0;
                        for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; i++)
                        {
                            if (limit > 30)
                                break;
                            if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                            {
                                uint32 display = newItem->GetTemplate()->DisplayInfoID;

                                if (Item::CanTransmogrifyItemWithItem(oldItem->GetTemplate(), newItem->GetTemplate()))
                                {
                                    if (_items[lowGUID].find(display) == _items[lowGUID].end())
                                    {
                                        limit++;
                                        _items[lowGUID][display] = newItem;
                                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, GetItemName(newItem, session), uiAction, display, session->GetTrinityString(LANG_POPUP_TRANSMOGRIFY)+GetItemName(newItem, session), GetFakePrice(oldItem), false);
                                    }
                                }
                            }
                        }

                        for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
                        {
                            if (Bag* bag = player->GetBagByPos(i))
                            {
                                for (uint32 j = 0; j < bag->GetBagSize(); j++)
                                {
                                    if (limit > 30)
                                        break;
                                    if (Item* newItem = player->GetItemByPos(i, j))
                                    {
                                        uint32 display = newItem->GetTemplate()->DisplayInfoID;
                                        if (Item::CanTransmogrifyItemWithItem(oldItem->GetTemplate(), newItem->GetTemplate()))
                                        {
                                            if (_items[lowGUID].find(display) == _items[lowGUID].end())
                                            {
                                                limit++;
                                                _items[lowGUID][display] = newItem;
                                                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, GetItemName(newItem, session), uiAction, display, session->GetTrinityString(LANG_POPUP_TRANSMOGRIFY)+GetItemName(newItem, session), GetFakePrice(oldItem), false);
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        char popup[250];
                        snprintf(popup, 250, session->GetTrinityString(LANG_POPUP_REMOVE_ONE), GetSlotName(uiAction, session));
                        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_INTERACT_1, session->GetTrinityString(LANG_OPTION_REMOVE_ONE), EQUIPMENT_SLOT_END+3, uiAction, popup, 0, false);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TALK, session->GetTrinityString(LANG_OPTION_BACK), EQUIPMENT_SLOT_END+1, 0);
                        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
                    }
                    else
                        OnGossipHello(player, creature);

                    break;
                }
                case EQUIPMENT_SLOT_END+1: // Back
                {
                    OnGossipHello(player, creature);

                    break;
                }
                case EQUIPMENT_SLOT_END+2: // Remove Transmogrifications
                {
                    bool removed = false;
                    for (uint8 Slot = EQUIPMENT_SLOT_START; Slot < EQUIPMENT_SLOT_END; Slot++)
                    {
                        if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, Slot))
                        {
                            if (newItem->GetModifier(eItemModifiers::TransmogItemID) != 0 && !removed)
                            {
                                newItem->SetModifier(eItemModifiers::TransmogItemID, 0);
                                player->SetVisibleItemSlot(uiAction, newItem);

                                removed = true;
                            }
                        }
                    }
                    if (removed)
                    {
                        ChatHandler(session).PSendSysMessage(session->GetTrinityString(LANG_REM_TRANSMOGRIFICATIONS_ITEMS));
                        player->PlayDirectSound(3337);
                    }
                    else
                        session->SendNotification(session->GetTrinityString(LANG_ERR_NO_TRANSMOGRIFICATIONS));

                    OnGossipHello(player, creature);

                    break;
                }
                case EQUIPMENT_SLOT_END+3: // Remove Transmogrification from single item
                {
                    if (Item* newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, uiAction))
                    {
                        if (newItem->GetModifier(eItemModifiers::TransmogItemID) != 0)
                        {
                            newItem->SetModifier(eItemModifiers::TransmogItemID, 0);
                            player->SetVisibleItemSlot(uiAction, newItem);

                            ChatHandler(session).PSendSysMessage(session->GetTrinityString(LANG_REM_TRANSMOGRIFICATION_ITEM), GetSlotName(uiAction, session));
                            player->PlayDirectSound(3337);
                        }
                        else
                            session->SendNotification(session->GetTrinityString(LANG_ERR_NO_TRANSMOGRIFICATION), GetSlotName(uiAction, session));
                    }

                    OnGossipSelect(player, creature, EQUIPMENT_SLOT_END, uiAction);

                    break;
                }
                default: // Transmogrify
                {
                    uint32 lowGUID = player->GetGUIDLow();
                    if (Item* oldItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, sender))
                    {
                        if (_items[lowGUID].find(uiAction) != _items[lowGUID].end() && _items[lowGUID][uiAction]->IsInWorld())
                        {
                            Item* newItem = _items[lowGUID][uiAction];
                            if (newItem->GetOwnerGUID() == player->GetGUID() && (newItem->IsInBag() || newItem->GetBagSlot() == INVENTORY_SLOT_BAG_0) 
                                && Item::CanTransmogrifyItemWithItem(oldItem->GetTemplate(), newItem->GetTemplate()))
                            {
                                player->ModifyMoney(-1*GetFakePrice(oldItem)); // take cost

                                oldItem->SetModifier(eItemModifiers::TransmogItemID, newItem->GetEntry());
                                player->SetVisibleItemSlot(sender, oldItem);

                                oldItem->UpdatePlayedTime(player);

                                oldItem->SetOwnerGUID(player->GetGUID());
                                oldItem->SetNotRefundable(player);
                                oldItem->ClearSoulboundTradeable(player);

                                if (newItem != nullptr)
                                {
                                    if (newItem->GetTemplate()->Bonding == BIND_WHEN_EQUIPED || newItem->GetTemplate()->Bonding == BIND_WHEN_USE)
                                        newItem->SetBinding(true);

                                    newItem->SetOwnerGUID(player->GetGUID());
                                    newItem->SetNotRefundable(player);
                                    newItem->ClearSoulboundTradeable(player);
                                    newItem->SetState(ITEM_CHANGED, player);
                                }

                                oldItem->SetState(ITEM_CHANGED, player);

                                player->PlayDirectSound(3337);

                                ChatHandler(session).PSendSysMessage(session->GetTrinityString(LANG_ITEM_TRANSMOGRIFIED), GetSlotName(sender, session));
                            }
                            else
                                session->SendNotification(session->GetTrinityString(LANG_ERR_NO_ITEM_SUITABLE));
                        }
                        else
                            session->SendNotification(session->GetTrinityString(LANG_ERR_NO_ITEM_EXISTS));
                    }
                    else
                        session->SendNotification(session->GetTrinityString(LANG_ERR_EQUIP_SLOT_EMPTY));

                    _items[lowGUID].clear();
                    OnGossipSelect(player, creature, EQUIPMENT_SLOT_END, sender);

                    break;
                }
            }
            return true;
        }

    private:
        std::map<uint64, std::map<uint32, Item*> > _items; // _items[lowGUID][DISPLAY] = item

        const char * GetSlotName(uint8 slot, WorldSession* session)
        {
            switch(slot)
            {
                case EQUIPMENT_SLOT_HEAD      : return session->GetTrinityString(LANG_SLOT_NAME_HEAD);
                case EQUIPMENT_SLOT_SHOULDERS : return session->GetTrinityString(LANG_SLOT_NAME_SHOULDERS);
                case EQUIPMENT_SLOT_BODY      : return session->GetTrinityString(LANG_SLOT_NAME_BODY);
                case EQUIPMENT_SLOT_CHEST     : return session->GetTrinityString(LANG_SLOT_NAME_CHEST);
                case EQUIPMENT_SLOT_WAIST     : return session->GetTrinityString(LANG_SLOT_NAME_WAIST);
                case EQUIPMENT_SLOT_LEGS      : return session->GetTrinityString(LANG_SLOT_NAME_LEGS);
                case EQUIPMENT_SLOT_FEET      : return session->GetTrinityString(LANG_SLOT_NAME_FEET);
                case EQUIPMENT_SLOT_WRISTS    : return session->GetTrinityString(LANG_SLOT_NAME_WRISTS);
                case EQUIPMENT_SLOT_HANDS     : return session->GetTrinityString(LANG_SLOT_NAME_HANDS);
                case EQUIPMENT_SLOT_BACK      : return session->GetTrinityString(LANG_SLOT_NAME_BACK);
                case EQUIPMENT_SLOT_MAINHAND  : return session->GetTrinityString(LANG_SLOT_NAME_MAINHAND);
                case EQUIPMENT_SLOT_OFFHAND   : return session->GetTrinityString(LANG_SLOT_NAME_OFFHAND);
                case EQUIPMENT_SLOT_RANGED    : return session->GetTrinityString(LANG_SLOT_NAME_RANGED);
                case EQUIPMENT_SLOT_TABARD    : return session->GetTrinityString(LANG_SLOT_NAME_TABARD);
                default: return NULL;
            }
        }

        std::string GetItemName(Item* item, WorldSession* session)
        {
            std::string name = item->GetTemplate()->Name1->Get(session->GetSessionDbLocaleIndex());
            return name;
        }

        int32 GetFakePrice(Item* item)
        {
            return item->GetTemplate()->ItemLevel * 12.5f * GOLD;
        }
};


/// Boris <Loyalty Point> - 250000
class npc_loyalty_point : public CreatureScript
{
public:
    npc_loyalty_point() : CreatureScript("npc_loyalty_point") { }

    enum eMenuIDs
    {
        GiveLoyaltyPoint = 92007,
        AlreadyEarnPoint = 92008
    };

    bool OnGossipHello(Player* p_Player, Creature* p_Creature) override
    {
        if (!p_Player)
            return false;

        WorldSession* l_Session = p_Player->GetSession();
        time_t l_NowTime = time(nullptr);

        time_t l_LastClaimTime = l_Session->GetLastClaim();

        auto l_Time = localtime(&l_NowTime);
        struct tm l_Now = *l_Time;
        auto l_LastClaim = localtime(&l_LastClaimTime);

        /// If now is a different day than the last event reset day, then clear event history
        if (l_LastClaim->tm_year != l_Now.tm_year || l_LastClaim->tm_mday != l_Now.tm_mday || l_LastClaim->tm_mon != l_Now.tm_mon)
        {
            uint32 l_Points = 5;

            if (l_Session->GetLastBan() < (time(nullptr) - (MONTH * 6)))
                l_Points += 2;

            if (l_Session->HaveAlreadyPurchasePoints())
                l_Points += 1;

            if (l_Session->IsEmailValidated())
                l_Points += 1;

            if (l_Session->GetActivityDays() > 13)
                l_Points += 1;

            if (l_Session->GetActivityDays() > 59)
                l_Points += 1;

            if (l_Session->GetActivityDays() > 179)
                l_Points += 1;

            if (l_Session->GetActivityDays() > 359)
                l_Points += 1;

            l_Session->AddLoyaltyPoints(l_Points, "NPC Daily reward");
            l_Session->SetLastClaim(time(nullptr));

            PreparedStatement* l_Statement = LoginDatabase.GetPreparedStatement(LOGIN_REP_ACC_LOYALTY);
            l_Statement->setUInt32(0, l_Session->GetAccountId());
            l_Statement->setUInt32(1, l_Session->GetLastClaim());
            l_Statement->setUInt32(2, l_Session->GetLastEventReset());
            LoginDatabase.Execute(l_Statement);

            p_Player->PlayerTalkClass->ClearMenus();
            p_Player->SEND_GOSSIP_MENU(eMenuIDs::GiveLoyaltyPoint, p_Creature->GetGUID());
            return true;
        }

        p_Player->SEND_GOSSIP_MENU(eMenuIDs::AlreadyEarnPoint, p_Creature->GetGUID());
        return true;
    }
};

#ifndef __clang_analyzer__
void AddSC_npc_custom()
{
    new npc_hellscream_teleporter();
    new npc_pve_tests_manager();
    new npc_hellscream_booster();
    new npc_fun_gold_vendor();
    new npc_fun_transmo_vendor();
    new npc_legendary_transmogrificator();
    new npc_loyalty_point();
}
#endif