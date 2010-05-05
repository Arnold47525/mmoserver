/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_RADIALMENU_ENUMS_H
#define ANH_ZONESERVER_RADIALMENU_ENUMS_H


//=============================================================================

enum RadialAction
{
	radAction_Default		= 1,
	radAction_2				= 2,
	radAction_ObjCallback	= 3
};

//=============================================================================

enum RadialIdentifier
{
	radId_Unknown					= 0,
	radId_combatTarget				= 1,
	radId_combatUntarget			= 2,
	radId_combatAttack				= 3,
	radId_combatPeace				= 4,
	radId_combatDuel				= 5,
	radId_combatDeathBlow			= 6,
	radId_examine					= 7,
	radId_tradeStart				= 8,
	radId_tradeAccept				= 9,
	radId_itemPickup				= 10,
	radId_itemEquip					= 11,
	radId_itemUnequip				= 12,
	radId_itemDrop					= 13,
	radId_itemDestroy				= 14,
	radId_itemToken					= 15,
	radId_itemOpen					= 16,
	radId_itemOpenNewWindow			= 17,
	radId_itemActivate				= 18,
	radId_itemDeactivate			= 19,
	radId_itemUse					= 20,
	radId_itemUseSelf				= 21,
	radId_itemUseOther				= 22,
	radId_itemSit					= 23,
	radId_itemMail					= 24,
	radId_converseStart				= 25,
	radId_converseRespond			= 26,
	radId_converseResponse			= 27,
	radId_converseStop				= 28,
	radId_craftOptions				= 29,
	radId_craftStart				= 30,
	radId_craftHopperInput			= 31,
	radId_craftHopperOutput			= 32,
	radId_missionTerminalList		= 33,
	radId_missionDetails			= 34,
	radId_loot						= 35,
	radId_lootAll					= 36,
	radId_groupInvite				= 37,
	radId_groupJoin					= 38,
	radId_groupLeave				= 39,
	radId_groupKick					= 40,
	radId_groupDisband				= 41,
	radId_groupDecline				= 42,
	radId_extractObject				= 43,
	radId_petCall					= 44,
	radId_terminalAuctionUse		= 45,
	radId_creatureFollow			= 46,
	radId_creatureStopFollow		= 47,
	radId_split						= 48,
	radId_imagedesign				= 49,
	radId_setName					= 50,
	radId_itemRotate				= 51,
	radId_itemRotateRight			= 52,
	radId_itemRotateLeft			= 53,
	radId_itemMove					= 54,
	radId_itemMoveForward			= 55,
	radId_ItemMoveBack				= 56,
	radId_itemMoveUp				= 57,
	radId_itemMoveDown				= 58,
	radId_petStore					= 59,
	radId_VehicleGenerate			= 60,
	radId_VehicleStore				= 61,
	radId_missionAbort				= 62,
	radId_missionEndDuty			= 63,
	radId_shipManageComponents		= 64,
	radId_waypointAutopilot			= 65,
	radId_programDroid				= 66,
	radId_serverDivider				= 67,
	radId_serverMenu1				= 68,
	radId_serverMenu2				= 69,
	radId_serverMenu3				= 70,
	radId_serverMenu4				= 71,
	radId_serverMenu5				= 72,
	radId_serverMenu6				= 73,
	radId_serverMenu7				= 74,
	radId_serverMenu8				= 75,
	radId_serverMenu9				= 76,
	radId_serverMenu10				= 77,
	radId_serverHarvesterManage		= 78,
	radId_serverHouseManage			= 79,
	radId_serverFactionHallManage	= 80,
	radId_serverHue					= 81,
	radId_serverObserve				= 82,
	radId_serverStopObserving		= 83,
	radId_serverTravelOptions		= 84,
	radId_serverBazaarOptions		= 85,
	radId_serverShippingOptions		= 86,
	radId_serverHealWound			= 87,
	radId_serverHealWoundHealth		= 88,
	radId_serverHealWoundAction		= 89,
	radId_serverHealWoundStrength	= 90,
	radId_serverHealWoundConst		= 91,
	radId_serverHealWoundQuickness	= 92,
	radId_serverHealWoundStamina	= 93,
	radId_serverHealDamage			= 94,
	radId_serverHealState			= 95,
	radId_serverHealStateStunned	= 96,
	radId_serverHealStateBlinded	= 97,
	radId_serverHealStateDizzy		= 98,
	radId_serverHealStateIntim		= 99,
	radId_serverHealEnhance			= 100,
	radId_serverHealEnhanceHealth	= 101,
	radId_serverHealEnhanceAction	= 102,
	radId_serverHealEnhanceStrangth	= 103,
	radId_serverHealEnhanceConst	= 104,
	radId_serverHealEnhanceQuickness= 105,
	radId_serverHealEnhanceStamina	= 106,
	radId_serverHealFirstAid		= 107,
	radId_serverHealCurePoison		= 108,
	radId_serverHealCureDisease		= 109,
	radId_serverHealApplyPoison		= 110,
	radId_serverHealApplyDisease	= 111,
	radId_serverHarvestCorpse		= 112,
	radId_serverPerformanceListen	= 113,
	radId_serverPerformanceWatch	= 114,
	radId_serverPerformanceListenStop	= 115,
	radId_serverPerformanceWatchStop	= 116,
	radId_serverTerminalPermissions	= 117,
	radId_serverTerminalManagement	= 118,
	radId_serverTerminalPermissionsEnter	= 119,
	radId_serverTerminalPermissionsBanned	= 120,
	radId_serverTerminalPermissionsAdmin	= 121,
	radId_serverTerminalPermissionVendor	= 122,
	radId_serverTerminalPermissionsHopper	= 123,
	radId_serverTerminalManagementStatus	= 124,
	radId_serverTerminalManagementPrivacy	= 125,
	radId_serverTerminalManagementTransfer	= 126,
	radId_serverTerminalManagementResidence	= 127,
	radId_serverTerminalManagementDestroy	= 128,
	radId_serverTerminalManagementPay		= 129,
	radId_serverTerminalCreateVendor		= 130,
	radId_serverGiveVendorMaintenance		= 131,
	radId_serverItemOptions					= 132,
	radId_serverSurveyToolRange				= 133,
	radId_serverSurveyToolResolution		= 134,
	radId_serverSurveyToolClass				= 135,
	radId_serverProbeDroidTrackTarget		= 136,
	radId_serverProbeDroidFindTarget		= 137,
	radId_serverProbeDroidActivate			= 138,
	radId_serverProbeDroidBuy				= 139,
	radId_serverTeach						= 140,
	radId_petCommand						= 141,
	radId_petFollow							= 142,
	radId_petStay							= 143,
	radId_petGuard							= 144,
	radId_petFriend							= 145,
	radId_petAttack							= 146,
	radId_petPatrol							= 147,
	radId_petGetPatrolPoint					= 148,
	radId_petClearPatrolPoint		 		= 149,
	radId_petAssumeFormation1				= 150,
	radId_petAssumeFormation2				= 151,
	radId_petTransfer						= 152,
	radId_petRelease						= 153,
	radId_petTrick1							= 154,
	radId_petTrick2							= 155,
	radId_petTrick3							= 156,
	radId_petTrick4							= 157,
	radId_petGroup							= 158,
	radId_petTame							= 159,
	radId_petFeed							= 160,
	radId_petSpecialAttackOne				= 161,
	radId_petSpecialAttackTwo				= 162,
	radId_petRangedAttack					= 163,
	radId_diceRoll							= 164, //Reused for HarvestMeat
	radId_diceTwoFace						= 165, //Reused for HarvestHide
	radId_diceThreeFace						= 166, //Reused for HarvestBone
	radId_diceFourFace						= 167, //Reused for Milk Me
	radId_diceFiveFace						= 168,
	radId_diceSixFace						= 169,
	radId_diceSevenFace						= 170,
	radId_diceEightFace						= 171,
	radId_diceCountOne						= 172,
	radId_diceCountTwo						= 173,
	radId_diceCountThree					= 174,
	radId_diceCountFour						= 175,
	radId_createBallot						= 176,
	radId_vote								= 177,
	radId_bombingRun						= 178,
	radId_selfDestruct						= 179,
	radId_thirtySec							= 180,
	radId_fifteenSec						= 181,
	radId_serverCampDisband					= 182,
	radId_serverCampAssumeOwnership			= 183,
	radId_serverProbeDroidProram			= 184,
	radId_serverGuildCreate					= 185,
	radId_serverGuildInfo					= 186,
	radId_serverGuildMembers				= 187,
	radId_serverGuildSponsored				= 188,
	radId_serverGuildEnemies				= 189,
	radId_serverGuildSponsor				= 190,
	radId_serverGuildDisband				= 191,
	radId_serverGuildNameChange				= 192,
	radId_serverGuildGuildManagement		= 193,
	radId_serverGuildMemberManagement		= 194,
	radId_serverManfHopperInput				= 195,
	radId_serverManfHopperOutput			= 196,
	radId_serverManfStationSchematic		= 197,
	radId_elevatorUp						= 198,
	radId_elevatorDown						= 199,
	radId_serverPetOpen						= 200,
	radId_serverPetDpad						= 201,
	radId_serverMedToolDiagnose				= 202,
	radId_serverMedToolTendWound			= 203,
	radId_serverMedToolTendDamage			= 204,
	radId_serverPetMount					= 205,
	radId_serverPetDismount					= 206,
	radId_serverPetTrainMount				= 207,
	radId_serverVehicleEnter				= 208,
	radId_serverVehicleExit					= 209,
	radId_openNaviCompDpad					= 210,
	radId_initNavicompDpad					= 211,
	radId_cityStatus						= 212,
	radId_cityCitizens						= 213,
	radId_cityStructures					= 214,
	radId_cityTreasury						= 215,
	radId_cityManagement					= 216,
	radId_cityName							= 217,
	radId_cityMilitia						= 218,
	radId_cityTaxes							= 219,
	radId_cityTreasuryDeposit				= 220,
	radId_cityTreasuryWithdraw				= 221,
	radId_cityRegister						= 222,
	radId_cityRank							= 223,
	radId_cityAdmin1						= 224,
	radId_cityAdmin2						= 225,
	radId_cityAdmin3						= 226,
	radId_cityAdmin4						= 227,
	radId_cityAdmin5						= 228,
	radId_cityAdmin6						= 229,
	radId_memoryChipProgram					= 230,
	radId_memoryChipTransfer				= 231,
	radId_memoryChipAnalyze					= 232,
	radId_equipDroidOnChip					= 233,
	radId_bankJoin							= 234,
	radId_bankQuit							= 235,
	radId_bankDepositAll					= 236,
	radId_bankWithdrawAll					= 237,
	radId_bankTransfer						= 238,
	radId_bankItems							= 239,
	radId_fireworkshowAdd					= 240,
	radId_fireworkshowRemove				= 241,
	radId_fireworkshowModify				= 242,
	radId_fireworkshowReorder				= 243,
	radId_fireworkshowData					= 244,
	radId_operateHarvester					= 245,
	radId_payMaintenance					= 246,
	radId_depositPower						= 247,
	radId_StructureStatus					= 248,
	radId_StructureOptions					= 249,
	radId_StartManufacture					= 250,
	radId_ListIngredients					= 251,
	radId_StopManufacture					= 252
};

#endif

