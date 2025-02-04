////////////////////////////////////////////////////////////////////////////////
//
//  MILLENIUM-STUDIO
//  Copyright 2016 Millenium-studio SARL
//  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "PetBattleAbilityEffect.h"
#include "PetBattle.h"
#include "ScriptMgr.h"
//#include "GameTables.h"

#define MAX_PETBATTLE_EFFECT_TYPES 235

static const uint32 FailFlags = PETBATTLE_EVENT_FLAG_MISS | PETBATTLE_EVENT_FLAG_BLOCKED | PETBATTLE_EVENT_FLAG_DODGE | PETBATTLE_EVENT_FLAG_REFLECT | PETBATTLE_EVENT_FLAG_IMMUNE;

struct PetBattleAbilityEffectHandler
{
    bool (PetBattleAbilityEffect::*Handle)();
    PetBattleAbilityImplicitTarget ImplicitTarget;
};

static PetBattleAbilityEffectHandler Handlers[MAX_PETBATTLE_EFFECT_TYPES] =
{
    /* EFFECT 0   */{nullptr,                                                         PETBATTLE_TARGET_NONE},
    /* EFFECT 1   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 2   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 3   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 4   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 5   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 6   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 7   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 8   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 9   */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 10  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 11  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 12  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 13  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 14  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 15  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 16  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 17  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 18  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 19  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 20  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 21  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 22  */{&PetBattleAbilityEffect::HandleDummy,                      PETBATTLE_TARGET_CASTER}, // Dummy
    /* EFFECT 23  */{&PetBattleAbilityEffect::HandleHeal,                       PETBATTLE_TARGET_CASTER},
    /* EFFECT 24  */{&PetBattleAbilityEffect::HandleDamage,                     PETBATTLE_TARGET_TARGET},
    /* EFFECT 25  */{&PetBattleAbilityEffect::HandleCatch,                      PETBATTLE_TARGET_TARGET},
    /* EFFECT 26  */{&PetBattleAbilityEffect::HandlePositiveAura,               PETBATTLE_TARGET_CASTER},
    /* EFFECT 27  */{&PetBattleAbilityEffect::HandleRampingDamage,              PETBATTLE_TARGET_TARGET},
    /* EFFECT 28  */{&PetBattleAbilityEffect::HandleCancellableAura,            PETBATTLE_TARGET_CASTER},
    /* EFFECT 29  */{&PetBattleAbilityEffect::HandleStateDamage,                PETBATTLE_TARGET_TARGET},
    /* EFFECT 30  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 31  */{&PetBattleAbilityEffect::HandleSetState,                   PETBATTLE_TARGET_CASTER},
    /* EFFECT 32  */{&PetBattleAbilityEffect::HandleHealPercentDealt,           PETBATTLE_TARGET_CASTER},
    /* EFFECT 33  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 34  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 35  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 36  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 37  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 38  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 39  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 40  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 41  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 42  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 43  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 44  */{&PetBattleAbilityEffect::HandleHealLastHitTaken,           PETBATTLE_TARGET_CASTER},
    /* EFFECT 45  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 46  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 47  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 48  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 49  */{&PetBattleAbilityEffect::HandleRemoveAura,                 PETBATTLE_TARGET_CASTER},
    /* EFFECT 50  */{&PetBattleAbilityEffect::HandleNegativeAura,               PETBATTLE_TARGET_TARGET},
    /* EFFECT 51  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 52  */{&PetBattleAbilityEffect::HandleControlAura,                PETBATTLE_TARGET_TARGET},
    /* EFFECT 53  */{&PetBattleAbilityEffect::HandleHealPercent,                PETBATTLE_TARGET_CASTER},
    /* EFFECT 54  */{&PetBattleAbilityEffect::HandlePeriodicTrigger,            PETBATTLE_TARGET_TARGET},
    /* EFFECT 55  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 56  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 57  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 58  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 59  */{&PetBattleAbilityEffect::HandleWitchingDamage,             PETBATTLE_TARGET_TARGET},
    /* EFFECT 60  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 61  */{&PetBattleAbilityEffect::HandleHealCasterPercentNotState,  PETBATTLE_TARGET_CASTER_TEAM_UNCONDITIONAL},
    /* EFFECT 62  */{&PetBattleAbilityEffect::HandleDamagePercent,              PETBATTLE_TARGET_TARGET},
    /* EFFECT 63  */{&PetBattleAbilityEffect::HandlePeriodicPositiveTrigger,    PETBATTLE_TARGET_CASTER},
    /* EFFECT 64  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 65  */{&PetBattleAbilityEffect::HandleDamageStateBonus,           PETBATTLE_TARGET_TARGET},
    /* EFFECT 66  */{&PetBattleAbilityEffect::HandleDamageRuthless,             PETBATTLE_TARGET_TARGET},
    /* EFFECT 67  */{&PetBattleAbilityEffect::HandleEqualizeLife,               PETBATTLE_TARGET_TARGET},
    /* EFFECT 68  */{&PetBattleAbilityEffect::HandleDamageCasterPercent,        PETBATTLE_TARGET_CASTER},
    /* EFFECT 69  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 70  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 71  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 72  */{&PetBattleAbilityEffect::HandleHealToggleAura,             PETBATTLE_TARGET_CASTER},
    /* EFFECT 73  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 74  */{&PetBattleAbilityEffect::HandleInitialization,             PETBATTLE_TARGET_CASTER},
    /* EFFECT 75  */{&PetBattleAbilityEffect::HandleDamageToggleAura,           PETBATTLE_TARGET_TARGET},
    /* EFFECT 76  */{&PetBattleAbilityEffect::HandleDamageToggleAura,           PETBATTLE_TARGET_TARGET},
    /* EFFECT 77  */{&PetBattleAbilityEffect::HandleDamageToggleAura,           PETBATTLE_TARGET_TARGET},
    /* EFFECT 78  */{&PetBattleAbilityEffect::HandleHealStateToggleAura,        PETBATTLE_TARGET_CASTER},
    /* EFFECT 79  */{&PetBattleAbilityEffect::HandleModState,                   PETBATTLE_TARGET_CASTER},
    /* EFFECT 80  */{&PetBattleAbilityEffect::HandleWeatherAura,                PETBATTLE_TARGET_ALL},
    /* EFFECT 81  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 82  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 83  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 84  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 85  */{&PetBattleAbilityEffect::HandleResetState,                 PETBATTLE_TARGET_ALL},
    /* EFFECT 86  */{&PetBattleAbilityEffect::HandleDamageAuraToggleAura,       PETBATTLE_TARGET_TARGET},
    /* EFFECT 87  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 88  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 89  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 90  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 91  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 92  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 93  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 94  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 95  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 96  */{&PetBattleAbilityEffect::HandleDamageHitState,             PETBATTLE_TARGET_TARGET},
    /* EFFECT 97  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 98  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 99  */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 100 */{&PetBattleAbilityEffect::HandleHealPetType,                PETBATTLE_TARGET_CASTER},
    /* EFFECT 101 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 102 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 103 */{&PetBattleAbilityEffect::HandleExtraAttackIfMoreFaster,    PETBATTLE_TARGET_TARGET},
    /* EFFECT 104 */{&PetBattleAbilityEffect::HandleHealState,                  PETBATTLE_TARGET_CASTER},
    /* EFFECT 105 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 106 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 107 */{&PetBattleAbilityEffect::HandleSwap,                       PETBATTLE_TARGET_TARGET},
    /* EFFECT 108 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 109 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 110 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 111 */{&PetBattleAbilityEffect::HandleResurect,                   PETBATTLE_TARGET_CASTER},
    /* EFFECT 112 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 113 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 114 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 115 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 116 */{&PetBattleAbilityEffect::HandleUpdatePriority,             PETBATTLE_TARGET_CASTER},
    /* EFFECT 117 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 118 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 119 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 120 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 121 */{&PetBattleAbilityEffect::HandleHealthConsume,              PETBATTLE_TARGET_CASTER},
    /* EFFECT 122 */{nullptr,                                                         PETBATTLE_TARGET_NONE}, // Clone
    /* EFFECT 123 */{nullptr,                                                         PETBATTLE_TARGET_NONE}, // Clone
    /* EFFECT 124 */{nullptr,                                                         PETBATTLE_TARGET_NONE}, // Clone
    /* EFFECT 125 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 126 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 127 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 128 */{&PetBattleAbilityEffect::HandleSetHealthPercent,           PETBATTLE_TARGET_TARGET},
    /* EFFECT 129 */{&PetBattleAbilityEffect::HandleLockActiveAbility,          PETBATTLE_TARGET_TARGET},
    /* EFFECT 130 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 131 */{&PetBattleAbilityEffect::HandleAuraIfCasterFaster,         PETBATTLE_TARGET_TARGET},
    /* EFFECT 132 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 133 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 134 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 135 */{&PetBattleAbilityEffect::HandleKill,                       PETBATTLE_TARGET_CASTER},
    /* EFFECT 136 */{&PetBattleAbilityEffect::HandleCleansing,                  PETBATTLE_TARGET_CASTER},
    /* EFFECT 137 */{&PetBattleAbilityEffect::HandleAuraState,                  PETBATTLE_TARGET_CASTER},
    /* EFFECT 138 */{&PetBattleAbilityEffect::HandleChangeCasterState,          PETBATTLE_TARGET_TARGET},
    /* EFFECT 139 */{&PetBattleAbilityEffect::HandleSwapLow,                    PETBATTLE_TARGET_TARGET},
    /* EFFECT 140 */{&PetBattleAbilityEffect::HandleResetAuraDuration,          PETBATTLE_TARGET_TARGET},
    /* EFFECT 141 */{&PetBattleAbilityEffect::HandleSplittedDamage,             PETBATTLE_TARGET_TARGET_TEAM},
    /* EFFECT 142 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 143 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 144 */{nullptr,                                                         PETBATTLE_TARGET_NONE}, // Dummy select dead target
    /* EFFECT 145 */{&PetBattleAbilityEffect::HandleSwapHigh,                   PETBATTLE_TARGET_TARGET},
    /* EFFECT 146 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 147 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 148 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 149 */{&PetBattleAbilityEffect::HandleDamageNonLetal,             PETBATTLE_TARGET_TARGET},
    /* EFFECT 150 */{&PetBattleAbilityEffect::HandleRedirectionAura,            PETBATTLE_TARGET_CASTER},
    /* EFFECT 151 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 152 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 153 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 154 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 155 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 156 */{&PetBattleAbilityEffect::HandleCheckState,                 PETBATTLE_TARGET_TARGET},
    /* EFFECT 157 */{&PetBattleAbilityEffect::HandleCheckState,                 PETBATTLE_TARGET_CASTER},
    /* EFFECT 158 */{&PetBattleAbilityEffect::HandleStopChainFailure,           PETBATTLE_TARGET_CASTER},
    /* EFFECT 159 */{nullptr,                                                         PETBATTLE_TARGET_NONE}, // Dummy select next target?
    /* EFFECT 160 */{&PetBattleAbilityEffect::HandleExtraAttackIfLessFaster,    PETBATTLE_TARGET_TARGET},
    /* EFFECT 161 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 162 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 163 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 164 */{&PetBattleAbilityEffect::HandleExtraAttack,                PETBATTLE_TARGET_TARGET},
    /* EFFECT 165 */{&PetBattleAbilityEffect::HandleTryRevive,                  PETBATTLE_TARGET_CASTER},
    /* EFFECT 166 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 167 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 168 */{&PetBattleAbilityEffect::HandleNegativeAura,               PETBATTLE_TARGET_TARGET},
    /* EFFECT 169 */{&PetBattleAbilityEffect::HandleStateDamage,                PETBATTLE_TARGET_HEAD},
    /* EFFECT 170 */{&PetBattleAbilityEffect::HandleWeatherDamage,              PETBATTLE_TARGET_TARGET},
    /* EFFECT 171 */{&PetBattleAbilityEffect::HandleHealOnSpecificWeather,      PETBATTLE_TARGET_CASTER},
    /* EFFECT 172 */{&PetBattleAbilityEffect::HandleAuraCondAccuracyState,      PETBATTLE_TARGET_TARGET},
    /* EFFECT 173 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 174 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 175 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 176 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 177 */{&PetBattleAbilityEffect::HandleCheckState,                 PETBATTLE_TARGET_TARGET},
    /* EFFECT 178 */{&PetBattleAbilityEffect::HandlePowerlessAura,              PETBATTLE_TARGET_TARGET},
    /* EFFECT 179 */{&PetBattleAbilityEffect::HandleDamage,                     PETBATTLE_TARGET_TARGET},
    /* EFFECT 180 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 181 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 182 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 183 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 184 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 185 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 186 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 187 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 188 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 189 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 190 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 191 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 192 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 193 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 194 */{&PetBattleAbilityEffect::HandleCheckFailure,               PETBATTLE_TARGET_CASTER},
    /* EFFECT 195 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 196 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 197 */{&PetBattleAbilityEffect::HandleDamagePercentTaken,         PETBATTLE_TARGET_TARGET},
    /* EFFECT 198 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 199 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 200 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 201 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 202 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 203 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 204 */{&PetBattleAbilityEffect::HandleDamagePercentTaken,         PETBATTLE_TARGET_TARGET},
    /* EFFECT 205 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 206 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 207 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 208 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 209 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 210 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 211 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 212 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 213 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 214 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 215 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 216 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 217 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 218 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 219 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 220 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 221 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 222 */{&PetBattleAbilityEffect::HandleDamageRange,                PETBATTLE_TARGET_TARGET},
    /* EFFECT 223 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 224 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 225 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 226 */{&PetBattleAbilityEffect::HandleDamageWithBonus,            PETBATTLE_TARGET_NONE},
    /* EFFECT 227 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 228 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 229 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 230 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 231 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 232 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 233 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE},
    /* EFFECT 234 */{&PetBattleAbilityEffect::HandleNull,                       PETBATTLE_TARGET_NONE}
};

uint32 PetBattleAbilityEffect::GetActiveOpponent()
{
    return PetBattleInstance->Teams[!PetBattleInstance->Pets[Caster]->TeamID]->ActivePetID;
}

int32 PetBattleAbilityEffect::GetPetType()
{
    if (BattlePetAbilityTurnEntry const* abilityTurn = sBattlePetAbilityTurnStore.LookupEntry(EffectInfo->abilityTurnId))
        if (BattlePetAbilityEntry const* ability = sBattlePetAbilityStore.LookupEntry(abilityTurn->abilityId))
            return ability->petType == BATTLEPET_PETTYPE_ALL ? BATTLEPET_PETTYPE_HUMANOID : ability->petType;

    return BATTLEPET_PETTYPE_HUMANOID;
}

bool PetBattleAbilityEffect::Damage(uint32 target, int32 damage, bool cantBeAvoidBlockedDodged)
{
    if (!(Flags & FailFlags) && damage <= 0)
        Flags |= PETBATTLE_EVENT_FLAG_MISS;

    if (!(Flags & FailFlags) && !cantBeAvoidBlockedDodged)
    {
        for (uint32 petID = 0; petID < (MAX_PETBATTLE_SLOTS * MAX_PETBATTLE_TEAM); ++petID)
        {
            if (!PetBattleInstance->Pets[petID])
                continue;

            if (GetState(petID, BATTLEPET_STATE_Mechanic_IsWall))
            {
                if (PetBattleInstance->Pets[petID]->TeamID == PetBattleInstance->Pets[Caster]->TeamID && !GetState(petID, BATTLEPET_STATE_Special_BlockedFriendlyMode))
                    continue;

                int32 blockedAttackCount = GetState(petID, BATTLEPET_STATE_Special_BlockedAttackCount);

                if (blockedAttackCount > 0)
                {
                    blockedAttackCount -= 1;

                    SetState(petID, BATTLEPET_STATE_Special_BlockedAttackCount, blockedAttackCount);

                    Flags |= PETBATTLE_EVENT_FLAG_BLOCKED;

                    if (!blockedAttackCount)
                        if (auto aura = GetAura(petID, GetState(petID, BATTLEPET_STATE_Special_ObjectRedirectionAuraID)))
                            aura->Expire(PetBattleInstance);

                    break;
                }
            }
        }
    }

    if (Flags & FailFlags)
    {
        damage = 0;

        if (ReportFailAsImmune)
            Flags = (Flags & ~FailFlags) | PETBATTLE_EVENT_FLAG_IMMUNE;
    }

    /// Passive: aquatic
    if (GetState(target, BATTLEPET_STATE_Passive_Aquatic) && (Flags & PETBATTLE_EVENT_FLAG_PERIODIC))
        damage /= 2;

    /// Passive: magic
    if (GetState(target, BATTLEPET_STATE_Passive_Magic))
        if (damage * 100 / GetMaxHealth(target) >= 35)
            damage = CalculatePct(GetMaxHealth(target), 35);

    int32 health = PetBattleInstance->Pets[target]->Health;
    health -= damage;

    if (health <= 0 && PetBattleInstance->Pets[target]->Health <= 0)
        return damage > 0;

    SetHealth(target, health);

    if (damage > 0)
    {
        PetBattleInstance->SetPetState(Caster, Caster, EffectInfo->id, BATTLEPET_STATE_Condition_DidDamageThisRound, 1);
        PetBattleInstance->SetPetState(Caster, target, EffectInfo->id, BATTLEPET_STATE_Condition_WasDamagedThisTurn, 1);
        PetBattleInstance->SetPetState(Caster, target, EffectInfo->id, BATTLEPET_STATE_Last_HitTaken, damage);
        PetBattleInstance->SetPetState(Caster, Caster, EffectInfo->id, BATTLEPET_STATE_Last_HitDealt, damage);
    }

    if (!IsTriggered)
    {
        for (auto& aura : PetBattleInstance->PetAuras)
        {
            if (aura->Expired)
                continue;

            /// Can't self-proc, avoid deadloop
            if (AbilityID == aura->AbilityID)
                continue;

            if (aura->CasterPetID == Caster)
                PetBattleInstance->Cast(aura->CasterPetID, aura->AbilityID, 0, PETBATTLE_ABILITY_TURN0_PROC_ON_DAMAGE_DEALT, PETBATTLE_CAST_TRIGGER_ALL);
            else if (aura->CasterPetID == target)
                PetBattleInstance->Cast(aura->CasterPetID, aura->AbilityID, 0, PETBATTLE_ABILITY_TURN0_PROC_ON_DAMAGE_TAKEN, PETBATTLE_CAST_TRIGGER_ALL);
        }
    }

    return damage > 0;
}

bool PetBattleAbilityEffect::Heal(uint32 target, int32 heal)
{
    int32 health = PetBattleInstance->Pets[target]->Health;
    int32 maxHealth = PetBattleInstance->Pets[target]->GetMaxHealth();

    if (health + heal > maxHealth)
        heal = maxHealth - health;

    if (heal <= 0)
    {
        heal = 0;
        Flags |= PETBATTLE_EVENT_FLAG_MISS;
    }

    if (Flags & FailFlags)
    {
        heal = 0;

        if (ReportFailAsImmune)
            Flags = (Flags & ~FailFlags) | PETBATTLE_EVENT_FLAG_IMMUNE;
    }

    health += heal;

    SetHealth(target, health);

    if (!IsTriggered)
    {
        for (auto& aura : PetBattleInstance->PetAuras)
        {
            if (aura->Expired)
                continue;

            if (aura->CasterPetID == Caster)
                PetBattleInstance->Cast(aura->CasterPetID, aura->AbilityID, 0, PETBATTLE_ABILITY_TURN0_PROC_ON_HEAL_DEALT, PETBATTLE_CAST_TRIGGER_ALL);
            else if (aura->CasterPetID == target)
                PetBattleInstance->Cast(aura->CasterPetID, aura->AbilityID, 0, PETBATTLE_ABILITY_TURN0_PROC_ON_HEAL_TAKEN, PETBATTLE_CAST_TRIGGER_ALL);
        }
    }

    return heal > 0;
}

void PetBattleAbilityEffect::ModState(uint32 target, uint32 stateID, int32 modValue, bool isApply)
{
    SetState(target, stateID, PetBattleInstance->Pets[target]->States[stateID] + (isApply ? modValue : -modValue));
}

int32 PetBattleAbilityEffect::CalculateDamage(int32 damage)
{
    /// Modifiers
    damage += GetState(Caster, BATTLEPET_STATE_Add_FlatDamageDealt);
    damage += GetState(Target, BATTLEPET_STATE_Add_FlatDamageTaken);

    /// Power
    int32 modPct = CalculatePct(GetState(Caster, BATTLEPET_STATE_Stat_Power), 5);

    /// Mod Dealt / Taken
    modPct += GetState(Caster, BATTLEPET_STATE_Mod_DamageDealtPercent);
    modPct += GetState(Target, BATTLEPET_STATE_Mod_DamageTakenPercent);

    /// Pet type damage mod
    int32 abilityPetType = GetPetType();
    uint32 targetPetType = BATTLEPET_PETTYPE_HUMANOID;

    if (BattlePetSpeciesEntry const* targetSpeciesInfo = sBattlePetSpeciesStore.LookupEntry(PetBattleInstance->Pets[Target]->Species))
        targetPetType = targetSpeciesInfo->type;

    int32 modPetTypeDamagePercent = -100;

    if (GtBattlePetTypeDamageModEntry const* DamageModInfo = sGtBattlePetTypeDamageModStore.LookupEntry(targetPetType * NUM_BATTLEPET_PETTYPES + abilityPetType))
        modPetTypeDamagePercent += DamageModInfo->mod * 100;

   /* if (auto const& damageModInfo = sBattlePetTypeDamageModTable.GetRow(abilityPetType + 1))
    {
        switch (targetPetType)
        {
            case BATTLEPET_PETTYPE_HUMANOID:
                modPetTypeDamagePercent += damageModInfo->Humanoid * 100;
                break;
            case BATTLEPET_PETTYPE_DRAGONKIN:
                modPetTypeDamagePercent += damageModInfo->Dragonkin * 100;
                break;
            case BATTLEPET_PETTYPE_FLYING:
                modPetTypeDamagePercent += damageModInfo->Flying * 100;
                break;
            case BATTLEPET_PETTYPE_UNDEAD:
                modPetTypeDamagePercent += damageModInfo->Undead * 100;
                break;
            case BATTLEPET_PETTYPE_CRITTER:
                modPetTypeDamagePercent += damageModInfo->Critter * 100;
                break;
            case BATTLEPET_PETTYPE_MAGIC:
                modPetTypeDamagePercent += damageModInfo->Magic * 100;
                break;
            case BATTLEPET_PETTYPE_ELEMENTAL:
                modPetTypeDamagePercent += damageModInfo->Elemental * 100;
                break;
            case BATTLEPET_PETTYPE_BEAST:
                modPetTypeDamagePercent += damageModInfo->Beast * 100;
                break;
            case BATTLEPET_PETTYPE_AQUATIC:
                modPetTypeDamagePercent += damageModInfo->Aquatic * 100;
                break;
            case BATTLEPET_PETTYPE_MECHANICAL:
                modPetTypeDamagePercent += damageModInfo->Mechanical * 100;
                break;
            default:
                break;
        }
    }*/

    if (GetState(Caster, BATTLEPET_STATE_Mod_PetType_ID) == abilityPetType)
        modPetTypeDamagePercent += GetState(Caster, BATTLEPET_STATE_Mod_PetTypeDamageDealtPercent);

    if (GetState(Target, BATTLEPET_STATE_Mod_PetType_ID) == abilityPetType)
        modPetTypeDamagePercent += GetState(Target, BATTLEPET_STATE_Mod_PetTypeDamageTakenPercent);

    if (modPetTypeDamagePercent > 0)
        Flags |= PETBATTLE_EVENT_FLAG_STRONG;
    else if (modPetTypeDamagePercent < 0)
        Flags |= PETBATTLE_EVENT_FLAG_WEAK;

    // Critical
    if (roll_chance_i(GetState(Target, BATTLEPET_STATE_Stat_CritChance)))
    {
        modPct += 100;
        Flags |= PETBATTLE_EVENT_FLAG_CRITICAL;
    }

    // Passive: beast
    if (GetState(Caster, BATTLEPET_STATE_Passive_Beast))
        if (GetHealth(Caster) * 100 / GetMaxHealth(Caster) < 50)
            modPetTypeDamagePercent += 25;

    // Calculate result
    damage += int32(CalculatePct(damage, modPct));
    damage += int32(CalculatePct(damage, modPetTypeDamagePercent));

    // Passive: magic
    if (GetState(Target, BATTLEPET_STATE_Passive_Magic))
        if (damage * 100 / GetMaxHealth(Target) >= 35)
            damage = CalculatePct(GetMaxHealth(Target), 35);

    return damage;
}

int32 PetBattleAbilityEffect::CalculateHeal(int32 heal)
{
    // Add power
    int32 modPct = CalculatePct(GetState(Caster, BATTLEPET_STATE_Stat_Power), 5);

    // Modifiers Dealt / Taken
    modPct += GetState(Caster, BATTLEPET_STATE_Mod_HealingDealtPercent);
    modPct += GetState(Target, BATTLEPET_STATE_Mod_HealingTakenPercent);

    return heal + CalculatePct(heal, modPct);
}

int32 PetBattleAbilityEffect::CalculateHit(int32 accuracy)
{
    // Add stat
    accuracy += GetState(Caster, BATTLEPET_STATE_Stat_Accuracy);
    accuracy -= GetState(Target, BATTLEPET_STATE_Stat_Dodge);

    // Calculate
    if (accuracy < 100 && !roll_chance_i(accuracy))
        Flags |= PETBATTLE_EVENT_FLAG_MISS;

    if (Caster != Target && GetState(Target, BATTLEPET_STATE_untargettable))
        Flags |= PETBATTLE_EVENT_FLAG_MISS;

    return accuracy;
}

bool PetBattleAbilityEffect::SetState(uint32 target, uint32 stateID, int32 value)
{
    /// Passive : Critter
    if (GetState(target, BATTLEPET_STATE_Passive_Critter))
    {
        switch (stateID)
        {
            case BATTLEPET_STATE_Mechanic_IsStunned:
            case BATTLEPET_STATE_Mechanic_IsWebbed:
            case BATTLEPET_STATE_turnLock:
                Flags |= PETBATTLE_EVENT_FLAG_IMMUNE;
                break;
            default:
                break;
        }
    }

    if (!(Flags & FailFlags))
        PetBattleInstance->Pets[target]->States[stateID] = value;

    if (BattlePetStateEntry const* petStateEntry = sBattlePetStateStore.LookupEntry(stateID))
        if (petStateEntry->flags)
        {
            PetBattleEvent battleEvent(PETBATTLE_EVENT_SET_STATE, Caster, Flags, EffectInfo->id, PetBattleInstance->RoundTurn++, 0, 1);
            battleEvent.UpdateState(target, stateID, PetBattleInstance->Pets[target]->States[stateID]);
            PetBattleInstance->RoundEvents.push_back(battleEvent);
        }

    return !(Flags & FailFlags);
}

int32 PetBattleAbilityEffect::GetState(uint32 target, uint32 stateID)
{
    return PetBattleInstance->Pets[target]->States[stateID];
}

int32 PetBattleAbilityEffect::GetHealth(uint32 target)
{
    return PetBattleInstance->Pets[target]->Health;
}

int32 PetBattleAbilityEffect::GetSpeed(uint32 target)
{
    return PetBattleInstance->Pets[target]->GetSpeed();
}

int32 PetBattleAbilityEffect::GetMaxHealth(uint32 target)
{
    return PetBattleInstance->Pets[target]->GetMaxHealth();
}

bool PetBattleAbilityEffect::SetHealth(uint32 target, int32 value)
{
    int32 maxHealth = GetMaxHealth(target);

    if (value > maxHealth)
        value = maxHealth;

    if (!(Flags & FailFlags) && value == PetBattleInstance->Pets[target]->Health)
        Flags |= PETBATTLE_EVENT_FLAG_MISS;

    if (!(Flags & FailFlags))
    {
        if (value <= 0 && !GetAura(target, 284))    ///< Buff : Suvival http://www.wowhead.com/petability=283/survival
        {
            Flags |= PETBATTLE_EVENT_FLAG_UNK_KILL;

            if (!GetState(target, BATTLEPET_STATE_Is_Dead))
                PetBattleInstance->SetPetState(Caster, target, EffectInfo->id, BATTLEPET_STATE_Internal_HealthBeforeInstakill, PetBattleInstance->Pets[target]->Health);
        }
        else if (value <= 0 && GetAura(target, 284))    ///< Buff : Suvival http://www.wowhead.com/petability=283/survival
            value = 1;

        PetBattleInstance->Pets[target]->Health = value;
    }

    PetBattleEvent battleEvent(PETBATTLE_EVENT_SET_HEALTH, Caster, Flags, EffectInfo->id, PetBattleInstance->RoundTurn++, 0, 1);
    battleEvent.UpdateHealth(target, PetBattleInstance->Pets[target]->Health);

    PetBattleInstance->RoundEvents.push_back(battleEvent);

    if (!(Flags & FailFlags) && PetBattleInstance->Pets[target]->Health <= 0 && !GetState(target, BATTLEPET_STATE_Is_Dead) && !GetState(target, BATTLEPET_STATE_unkillable))
        Kill(target);

    return !(Flags & FailFlags);
}

void PetBattleAbilityEffect::Trigger(uint32 target, uint32 abilityID)
{
    PetBattleEvent battleEvent(PETBATTLE_EVENT_SET_HEALTH, Caster, Flags, EffectInfo->id, PetBattleInstance->RoundTurn++, 0, 1);

    battleEvent.Trigger(target, abilityID);

    PetBattleInstance->RoundEvents.push_back(battleEvent);

    PetBattleInstance->Cast(Caster, abilityID, 0, PETBATTLE_ABILITY_TURN0_PROC_ON_NONE, PETBATTLE_CAST_TRIGGER_NONE);
}

PetBattleAura* PetBattleAbilityEffect::GetAura(uint32 target, uint32 abilityID)
{
    for (auto aura : PetBattleInstance->PetAuras)
        if (!aura->Expired && aura->TargetPetID == target && aura->AbilityID == abilityID)
            return aura;

    return nullptr;
}

void PetBattleAbilityEffect::Kill(uint32 target)
{
    if (Flags & FailFlags)
    {
        // TC_LOG_DEBUG(LOG_FILTER_BATTLEPET, "PetBattleAbilityEffect::Kill BATTLEPET_STATE_Is_Dead");
        SetState(target, BATTLEPET_STATE_Is_Dead, 1);
        return;
    }

    PetBattleInstance->Kill(Caster, target, EffectInfo->id, false, Flags);

    /// Passive: mechanical
    if (GetState(target, BATTLEPET_STATE_Passive_Mechanical))
    {
        Trigger(target, 723);
        SetState(target, BATTLEPET_STATE_Passive_Mechanical, 0);
        return;
    }

    /// Passive: undead
    if (GetState(target, BATTLEPET_STATE_Passive_Undead))
    {
        Trigger(target, 242);
        SetState(target, BATTLEPET_STATE_Passive_Undead, 0);
        return;
    }

    // TC_LOG_DEBUG(LOG_FILTER_BATTLEPET, "PetBattleAbilityEffect::Kill BATTLEPET_STATE_Special_ConsumedCorpse");

    // SetState(target, BATTLEPET_STATE_Special_ConsumedCorpse, 1);

    PetBattleInstance->PetXDied.push_back(target);
    PetBattleInstance->Kill(Caster, target, EffectInfo->id);

    StopChain = true;
}

bool PetBattleAbilityEffect::AddTarget(uint32 target)
{
    if (!PetBattleInstance->Pets[target])
        return false;

    if (!PetBattleInstance->Pets[target]->IsAlive())
        return false;

    Targets.push_back(target);
    return true;
}

bool PetBattleAbilityEffect::AddTarget(PetBattleAbilityImplicitTarget /*target*/)
{
    PetBattleTeam* battleTeam;
    switch (Handlers[EffectInfo->effect].ImplicitTarget)
    {
        case PETBATTLE_TARGET_CASTER:
            return AddTarget(Caster);
        case PETBATTLE_TARGET_TARGET:
            return AddTarget(GetActiveOpponent());
        case PETBATTLE_TARGET_CASTER_TEAM:
            battleTeam = PetBattleInstance->Teams[PetBattleInstance->Pets[Caster]->TeamID];
            for (size_t slot = 0; slot < battleTeam->TeamPetCount; ++slot)
                AddTarget(battleTeam->TeamPets[slot]->ID);
            return true;
        case PETBATTLE_TARGET_CASTER_TEAM_0:
            battleTeam = PetBattleInstance->Teams[PetBattleInstance->Pets[Caster]->TeamID];
            if (battleTeam->TeamPetCount <= 1)
                return AddTarget(battleTeam->TeamPets[0]->ID);
            return false;
        case PETBATTLE_TARGET_CASTER_TEAM_1:
            battleTeam = PetBattleInstance->Teams[PetBattleInstance->Pets[Caster]->TeamID];
            if (battleTeam->TeamPetCount <= 2)
                return AddTarget(battleTeam->TeamPets[1]->ID);
            return false;
        case PETBATTLE_TARGET_CASTER_TEAM_2:
            battleTeam = PetBattleInstance->Teams[PetBattleInstance->Pets[Caster]->TeamID];
            if (battleTeam->TeamPetCount <= 3)
                return AddTarget(battleTeam->TeamPets[2]->ID);
            return false;
        case PETBATTLE_TARGET_TARGET_TEAM:
            battleTeam = PetBattleInstance->Teams[!PetBattleInstance->Pets[Caster]->TeamID];
            for (auto slot = 0; slot < battleTeam->TeamPetCount; ++slot)
                return AddTarget(battleTeam->TeamPets[slot]->ID);
            return true;
        case PETBATTLE_TARGET_TARGET_TEAM_0:
            battleTeam = PetBattleInstance->Teams[!PetBattleInstance->Pets[Caster]->TeamID];
            if (battleTeam->TeamPetCount <= 1)
                return AddTarget(battleTeam->TeamPets[PETBATTLE_TEAM_1]->ID);
            return false;
        case PETBATTLE_TARGET_TARGET_TEAM_1:
            battleTeam = PetBattleInstance->Teams[!PetBattleInstance->Pets[Caster]->TeamID];
            if (battleTeam->TeamPetCount <= 2)
                return AddTarget(battleTeam->TeamPets[1]->ID);
            return false;
        case PETBATTLE_TARGET_TARGET_TEAM_2:
            battleTeam = PetBattleInstance->Teams[!PetBattleInstance->Pets[Caster]->TeamID];
            if (battleTeam->TeamPetCount <= 3)
                return AddTarget(battleTeam->TeamPets[2]->ID);
            return false;
        case PETBATTLE_TARGET_ALL:
            for (size_t slot = 0; slot < MAX_PETBATTLE_TEAM * MAX_PETBATTLE_SLOTS; ++slot)
                AddTarget(slot);
            return true;
        case PETBATTLE_TARGET_CASTER_TEAM_UNCONDITIONAL:
            battleTeam = PetBattleInstance->Teams[PetBattleInstance->Pets[Caster]->TeamID];
            for (size_t slot = 0; slot < battleTeam->TeamPetCount; ++slot)
                if (PetBattleInstance->Pets[slot])
                    Targets.push_back(battleTeam->TeamPets[slot]->ID);
            return true;
        case PETBATTLE_TARGET_HEAD:
            return AddTarget(Caster) || AddTarget(GetActiveOpponent());
        default:
            return false;
    }
}

bool PetBattleAbilityEffect::AddAura(uint32 target, int32 duration, int32 maxAllowed)
{
    return PetBattleInstance->AddAura(Caster, target, EffectInfo->triggerAbility, duration, maxAllowed, EffectInfo->id, Flags);
}

void PetBattleAbilityEffect::SelectTargets()
{
    if (EffectInfo->effect > MAX_PETBATTLE_EFFECT_TYPES)
        //TC_LOG_ERROR(LOG_FILTER_BATTLEPET, "Function: %s; Line: %u EffectInfo->effect > MAX_PETBATTLE_EFFECT_TYPES; effect: %u", __FUNCTION__, __LINE__, EffectInfo->effect);

    Targets.clear();
    AddTarget(Handlers[EffectInfo->effect].ImplicitTarget);
}

bool PetBattleAbilityEffect::Execute()
{
    if (!Handlers[EffectInfo->effect].Handle)
        return false;

    if (Targets.empty())
        return false;

    StopChain = false;
    bool result = true;

    for (auto target : Targets)
    {
        Target = target;
        Flags = 0;

        if (PetBattleInstance->Pets[Caster]->TeamID != PetBattleInstance->Pets[Target]->TeamID && PetBattleInstance->Pets[Target]->States[BATTLEPET_STATE_untargettable])
            Flags |= PETBATTLE_EVENT_FLAG_DODGE;

        auto _result = (this->*Handlers[EffectInfo->effect].Handle)();
        result &= _result;
        if (result)
            break;
    }

    return result;
}

bool PetBattleAbilityEffect::HandleDummy()
{
    return true;
}

bool PetBattleAbilityEffect::HandleDamage()
{
    CalculateHit(EffectInfo->prop[1]);

    if (EffectInfo->prop[2])
        Flags |= PETBATTLE_EVENT_FLAG_PERIODIC;

    return Damage(Target, CalculateDamage(EffectInfo->prop[0]), EffectInfo->prop[2]);
}

bool PetBattleAbilityEffect::HandleWitchingDamage()
{
    CalculateHit(EffectInfo->prop[1]);

    /// Witching
    int32 damage = EffectInfo->prop[0];
    int32 casterHealPct = (GetHealth(Caster) * 100) / GetMaxHealth(Caster);

    if (EffectInfo->prop[2] && casterHealPct < EffectInfo->prop[2])
        damage *= 2;
    else if (GetHealth(Target) > GetHealth(Caster))                     ///< http://fr.wowhead.com/petability=253/repliquer
        damage *= 2;

    return Damage(Target, CalculateDamage(damage));
}

bool PetBattleAbilityEffect::HandleStateDamage()
{
    /// In some case, proc only if caster state prop[2] is on
    if (EffectInfo->prop[2] != 0 && !GetState(Caster, EffectInfo->prop[2]))
        return false;

    if (EffectInfo->prop[4])
        Flags |= PETBATTLE_EVENT_FLAG_PERIODIC;

    CalculateHit(EffectInfo->prop[1]);
    int32 damage = CalculateDamage(EffectInfo->prop[0]);

    /// Double base damage is the state in Prop[3] is on
    if (EffectInfo->prop[3] != 0 && GetState(Target, EffectInfo->prop[3]) == 1)
        damage *= 2;

    return Damage(Target, damage);
}

bool PetBattleAbilityEffect::HandleSetState()
{
    return SetState(Target, EffectInfo->prop[0], EffectInfo->prop[1]);
}

bool PetBattleAbilityEffect::HandleStopChainFailure()
{
    if (AbilityTurn->ChainFailure)
        StopChain = true;

    return true;
}

bool PetBattleAbilityEffect::HandleHealPercentDealt()
{
    // Chain Failure
    if (EffectInfo->prop[2] && AbilityTurn->ChainFailure)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    // Recovery
    int32 heal = CalculatePct(GetState(Caster, BATTLEPET_STATE_Last_HitDealt), EffectInfo->prop[0]);
    int32 modPct = 0;

    // Modifiers Dealt / Taken
    modPct += GetState(Caster, BATTLEPET_STATE_Mod_HealingDealtPercent);
    modPct += GetState(Target, BATTLEPET_STATE_Mod_HealingTakenPercent);

    return Heal(Target, heal + CalculatePct(heal, modPct));
}

bool PetBattleAbilityEffect::HandleHeal()
{
    CalculateHit(EffectInfo->prop[1]);

    return Heal(Caster, CalculateHeal(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleCatch()
{
    int32 chance = EffectInfo->prop[0] + (GetState(Target, BATTLEPET_STATE_Internal_CaptureBoost) * EffectInfo->prop[1]);

    bool success = roll_chance_i(chance);

    PetBattleEvent event(PETBATTLE_EVENT_CATCH, Caster, success ? 0 : PETBATTLE_EVENT_FLAG_MISS, EffectInfo->id, PetBattleInstance->RoundTurn++, 0, 1);
    event.UpdateSpeed(Target, success ? 1 : 0);
    PetBattleInstance->RoundEvents.push_back(event);
    PetBattleInstance->RoundPetSpeedUpdate.emplace_back(Target, 0);

    if (success)
        PetBattleInstance->Catch(Caster, Target, EffectInfo->id);
    else
        ModState(Target, BATTLEPET_STATE_Internal_CaptureBoost, 1);

    return success;
}

bool PetBattleAbilityEffect::HandlePeriodicTrigger()
{
    // Chain Failure
    if (EffectInfo->prop[0] && AbilityTurn->ChainFailure)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], EffectInfo->prop[3]);
}

bool PetBattleAbilityEffect::HandleRampingDamage()
{
    CalculateHit(EffectInfo->prop[1]);

    int32 baseDamage = EffectInfo->prop[0];
    int32 damageIncrementPerUse = EffectInfo->prop[2];
    int32 maxDamage = EffectInfo->prop[3];

    if (GetState(Caster, BATTLEPET_STATE_Ramping_DamageID) != AbilityID)
    {
        SetState(Caster, BATTLEPET_STATE_Ramping_DamageID, AbilityID);
        SetState(Caster, BATTLEPET_STATE_Ramping_DamageUses, 0);
    }

    int32 bonusDamage = damageIncrementPerUse * GetState(Caster, BATTLEPET_STATE_Ramping_DamageUses);
    if ((baseDamage + bonusDamage) >= maxDamage)
    {
        bonusDamage = maxDamage - baseDamage;

        if (EffectInfo->prop[4]) ///< StateToTriggerMaxPoints
            SetState(Target, EffectInfo->prop[4], 1);
    }

    ModState(Caster, BATTLEPET_STATE_Ramping_DamageUses, 1);

    return Damage(Target, CalculateDamage(baseDamage + bonusDamage));
}

bool PetBattleAbilityEffect::HandleHealLastHitTaken()
{
    CalculateHit(EffectInfo->prop[1]);

    // Recovery
    int32 heal = CalculatePct(GetState(Caster, BATTLEPET_STATE_Last_HitTaken), EffectInfo->prop[0]);
    int32 modPct = 0;

    // Modifiers Dealt / Taken
    modPct += GetState(Caster, BATTLEPET_STATE_Mod_HealingDealtPercent);
    modPct += GetState(Target, BATTLEPET_STATE_Mod_HealingTakenPercent);

    return Heal(Target, heal + CalculatePct(heal, modPct));
}

bool PetBattleAbilityEffect::HandleRemoveAura()
{
    /// Data for this effect are unknown so we assume 100% unaura
    ///CalculateHit(EffectInfo->prop[0]);
    ///
    ///if (!(Flags & FailFlags))
    ///{
    ///    for (auto itr = PetBattleInstance->PetAuras.begin(); itr != PetBattleInstance->PetAuras.end(); itr++)
    ///    {
    ///        if (!(*itr)->Expired && (*itr)->TargetPetID == Target && (*itr)->AbilityID == AbilityID)
    ///        {
    ///            /// Make aura expired
    ///            (*itr)->Expire(PetBattleInstance);
    ///        }
    ///    }
    ///}
    ///
    ///return !(Flags & FailFlags);

    CalculateHit(100);
    return true;
}

bool PetBattleAbilityEffect::HandleModState()
{
    assert(EffectInfo->prop[0] < NUM_BATTLEPET_STATES);

    /// Min check
    if (GetState(Caster, EffectInfo->prop[0]) < EffectInfo->prop[2])
        return false;

    /// Max check
    if (GetState(Caster, EffectInfo->prop[0]) > EffectInfo->prop[3])
        return false;

    ModState(Target, EffectInfo->prop[0], EffectInfo->prop[1]);

    return true;
}

bool PetBattleAbilityEffect::HandlePositiveAura()
{
    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleHealPetType()
{
    /// Handle only first effect of this type
    /// Don't know how to handle it properly
    /// http://wowhead.com/petability=533
    /// http://wowhead.com/petability=922
    if (EffectInfo->effectIndex != 2)
        return true;

    CalculateHit(EffectInfo->prop[1]);

    int32 modPct = CalculatePct(GetState(Caster, BATTLEPET_STATE_Stat_Power), 5);
    modPct += GetState(Caster, BATTLEPET_STATE_Mod_HealingDealtPercent);

    BattlePetSpeciesEntry const* battlePetSpeciesEntry = sBattlePetSpeciesStore.LookupEntry(PetBattleInstance->Pets[Caster]->Species);
    int32 casterType = 0;
    if (battlePetSpeciesEntry)
        casterType = battlePetSpeciesEntry->type;

    uint32 team = PetBattleInstance->Pets[Caster]->TeamID;

    for (const auto& currentPet : PetBattleInstance->Pets)
    {
        if (currentPet && currentPet->TeamID == team)
        {
            battlePetSpeciesEntry = sBattlePetSpeciesStore.LookupEntry(currentPet->Species);
            if (battlePetSpeciesEntry && battlePetSpeciesEntry->type == casterType)
            {
                auto heal = (EffectInfo->prop[0] / 2) + CalculatePct((EffectInfo->prop[0] / 2), modPct + GetState(currentPet->ID, BATTLEPET_STATE_Mod_HealingTakenPercent));
                Heal(currentPet->ID, heal);
            }
        }
    }

    return Heal(Target, CalculateHeal(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleExtraAttackIfMoreFaster()
{
    if (PetBattleInstance->RoundFirstTeamCasting != PetBattleInstance->Pets[Caster]->TeamID)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    return Damage(Target, CalculateDamage(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleHealState()
{
    if (EffectInfo->prop[3] && !GetState(Target, EffectInfo->prop[3]))
        return false;

    CalculateHit(EffectInfo->prop[1]);

    return Heal(Target, CalculateHeal(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleSplittedDamage()
{
    CalculateHit(EffectInfo->prop[1]);
    int32 damage = CalculateDamage(EffectInfo->prop[0] / Targets.size());
    return Damage(Target, damage);
}

bool PetBattleAbilityEffect::HandleDamageNonLetal()
{
    CalculateHit(EffectInfo->prop[1]);

    int32 damage = CalculateDamage(EffectInfo->prop[0]);

    if (damage >= GetHealth(Target))
        damage = GetHealth(Target) - 1;

    return Damage(Target, damage);
}

bool PetBattleAbilityEffect::HandleExtraAttackIfLessFaster()
{
    if (PetBattleInstance->RoundFirstTeamCasting == PetBattleInstance->Pets[Caster]->TeamID)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    return Damage(Target, CalculateDamage(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleHealOnSpecificWeather()
{
    int32 l_RequiredState = EffectInfo->prop[2];

    if (l_RequiredState && !GetState(Caster, l_RequiredState))
        return false;

    CalculateHit(EffectInfo->prop[1]);

    int32 healBase = EffectInfo->prop[0];
    int32 healBonusOnStateID = EffectInfo->prop[3];

    if (healBonusOnStateID && GetState(Caster, healBonusOnStateID))
        healBase *= 2;

    return Heal(Target, CalculateHeal(healBase));
}

bool PetBattleAbilityEffect::HandleWeatherAura()
{
    // Chain Failure
    if (EffectInfo->prop[3] && AbilityTurn->ChainFailure)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    if (!(Flags & FailFlags) && PetBattleInstance->WeatherAbilityId)
        for (auto& aura : PetBattleInstance->PetAuras)
            if (!aura->Expired && aura->AbilityID == PetBattleInstance->WeatherAbilityId)
                aura->Expire(PetBattleInstance);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleAuraCondAccuracyState()
{
    // Chain Failure
    if (EffectInfo->prop[4] && AbilityTurn->ChainFailure)
        return false;

    // Accuracy
    int32 accuracy = EffectInfo->prop[5];
    if ((!EffectInfo->prop[1] || GetState(Caster, EffectInfo->prop[1]) != EffectInfo->prop[0]) && (!EffectInfo->prop[3] || GetState(Target, EffectInfo->prop[3]) != EffectInfo->prop[0]))
        accuracy = 100;

    CalculateHit(accuracy);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleCheckState()
{
    if (GetState(Target, EffectInfo->prop[0]) != EffectInfo->prop[1])
        StopChain = true;

    return true;
}

bool PetBattleAbilityEffect::HandleCancellableAura()
{
    // Accuracy
    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleWeatherDamage()
{
    // weatherState
    if (!GetState(Target, EffectInfo->prop[2]))
        return false;

    // Accuracy
    CalculateHit(EffectInfo->prop[1]);

    // Periodic
    if (EffectInfo->prop[4])
        Flags |= PETBATTLE_EVENT_FLAG_PERIODIC;

    // Damage
    return Damage(Target, CalculateDamage(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleNegativeAura()
{
    // Chain Failure
    if (EffectInfo->prop[0] && AbilityTurn->ChainFailure)
        return false;

    // Accuracy
    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], EffectInfo->prop[3]);
}

bool PetBattleAbilityEffect::HandlePeriodicPositiveTrigger()
{
    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleControlAura()
{
    // Chain Failure
    if (EffectInfo->prop[0] && AbilityTurn->ChainFailure)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandlePowerlessAura()
{
    if (EffectInfo->prop[5])
        ReportFailAsImmune = true;

    // Chain Failure
    if (EffectInfo->prop[4] && AbilityTurn->ChainFailure)
    {
        if (ReportFailAsImmune)
            Flags |= PETBATTLE_EVENT_FLAG_IMMUNE;
        else
            return false;
    }

    // State
    if (EffectInfo->prop[3] && GetState(Target, EffectInfo->prop[3]) == EffectInfo->prop[0])
    {
        if (ReportFailAsImmune)
            Flags |= PETBATTLE_EVENT_FLAG_IMMUNE;
        else
            return false;
    }

    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleHealPercent()
{
    CalculateHit(EffectInfo->prop[1]);

    /// No sure if all ability should not use spell power on this effect
    /// Passive humanoid http://wowhead.com/petability=726
    if (AbilityID == 726)
    {
        int32 modPct = 1;
        int32 heal = CalculatePct(GetMaxHealth(Target), EffectInfo->prop[0]);

        /// Modifiers Dealt / Taken
        modPct += GetState(Caster, BATTLEPET_STATE_Mod_HealingDealtPercent);
        modPct += GetState(Target, BATTLEPET_STATE_Mod_HealingTakenPercent);

        return heal + CalculatePct(heal, modPct);
    }

    // Recovery
    int32 heal = CalculateHeal(CalculatePct(GetMaxHealth(Target), EffectInfo->prop[0]));

    return Heal(Target, heal);
}

bool PetBattleAbilityEffect::HandleExtraAttack()
{
    CalculateHit(EffectInfo->prop[1]);

    if (EffectInfo->prop[2])
        Flags |= PETBATTLE_EVENT_FLAG_PERIODIC;

    bool result = !(Flags & FailFlags);
    if (result)
        Damage(Target, CalculateDamage(EffectInfo->prop[0]));

    return result;
}

bool PetBattleAbilityEffect::HandleHealCasterPercentNotState()
{
    if (EffectInfo->prop[2] && !GetState(Caster, EffectInfo->prop[2]))
        return false;

    if (EffectInfo->prop[3] && !GetState(Target, EffectInfo->prop[3]))
        return false;

    // It's caster who need to be heal
    Target = Caster;

    CalculateHit(EffectInfo->prop[1]);

    int32 heal = CalculateHeal(CalculatePct(GetMaxHealth(Target), EffectInfo->prop[0]));
    return Heal(Target, heal);
}

bool PetBattleAbilityEffect::HandleDamagePercent()
{
    CalculateHit(EffectInfo->prop[1]);

    if (EffectInfo->prop[2])
        Flags |= PETBATTLE_EVENT_FLAG_PERIODIC;

    int32 damage = CalculateDamage(CalculatePct(GetMaxHealth(Target), EffectInfo->prop[0]));
    return Damage(Target, damage);
}

bool PetBattleAbilityEffect::HandleDamageStateBonus()
{
    CalculateHit(EffectInfo->prop[1]);

    int32 damage = EffectInfo->prop[0];
    if (EffectInfo->prop[3] && GetState(Target, EffectInfo->prop[3]) == EffectInfo->prop[4])
        damage += EffectInfo->prop[2];

    return Damage(Target, CalculateDamage(damage));
}

bool PetBattleAbilityEffect::HandleDamageRuthless()
{
    CalculateHit(EffectInfo->prop[1]);

    int32 damage = EffectInfo->prop[0];
    int32 targetHealthPct = (GetHealth(Target) * 100) / GetMaxHealth(Target);

    if (targetHealthPct < 25)
        damage += CalculatePct(damage, EffectInfo->prop[2]);

    return Damage(Target, CalculateDamage(damage));
}

bool PetBattleAbilityEffect::HandleEqualizeLife()
{
    CalculateHit(EffectInfo->prop[0]);
    if (Flags & FailFlags)
        return SetHealth(Caster, GetHealth(Caster));

    int32 life = (GetHealth(Caster) + GetHealth(Target)) / 2;
    SetHealth(Caster, life);
    SetHealth(Target, life);
    return true;
}

bool PetBattleAbilityEffect::HandleDamageCasterPercent()
{
    if (EffectInfo->prop[2])
        Target = GetActiveOpponent();

    CalculateHit(EffectInfo->prop[1]);

    int32 damage = CalculateDamage(CalculatePct(GetMaxHealth(Caster), EffectInfo->prop[0]));
    return Damage(Target, damage, true);
}

bool PetBattleAbilityEffect::HandleHealToggleAura()
{
    CalculateHit(EffectInfo->prop[1]);
    if (Flags & FailFlags)
        return SetHealth(Target, GetHealth(Target));

    if (PetBattleAura* aura = GetAura(Target, EffectInfo->triggerAbility))
    {
        aura->Expire(PetBattleInstance);

        // Heal
        return Heal(Target, CalculateHeal(EffectInfo->prop[0]));
    }
    // No aura, add it
    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleInitialization()
{
    SetState(Target, BATTLEPET_STATE_Internal_InitialHealth, GetHealth(Target));
    SetState(Target, BATTLEPET_STATE_Internal_InitialLevel, PetBattleInstance->Pets[Target]->Level);
    SetState(Target, BATTLEPET_STATE_Stat_CritChance, 5);

    uint32 petType = BATTLEPET_PETTYPE_HUMANOID;
    if (BattlePetSpeciesEntry const* targetSpeciesInfo = sBattlePetSpeciesStore.LookupEntry(PetBattleInstance->Pets[Target]->Species))
        petType = targetSpeciesInfo->type;

    static const uint32 petTypePassiveState[NUM_BATTLEPET_PETTYPES] =
    {
        /*BATTLEPET_PETTYPE_HUMANOID*/      BATTLEPET_STATE_Passive_Humanoid,
        /*BATTLEPET_PETTYPE_DRAGONKIN*/     BATTLEPET_STATE_Passive_Dragon,
        /*BATTLEPET_PETTYPE_FLYING*/        BATTLEPET_STATE_Passive_Flying,
        /*BATTLEPET_PETTYPE_UNDEAD*/        BATTLEPET_STATE_Passive_Undead,
        /*BATTLEPET_PETTYPE_CRITTER*/       BATTLEPET_STATE_Passive_Critter,
        /*BATTLEPET_PETTYPE_MAGIC*/         BATTLEPET_STATE_Passive_Magic,
        /*BATTLEPET_PETTYPE_ELEMENTAL*/     BATTLEPET_STATE_Passive_Elemental,
        /*BATTLEPET_PETTYPE_BEAST*/         BATTLEPET_STATE_Passive_Beast,
        /*BATTLEPET_PETTYPE_AQUATIC*/       BATTLEPET_STATE_Passive_Aquatic,
        /*BATTLEPET_PETTYPE_MECHANICAL*/    BATTLEPET_STATE_Passive_Mechanical,
    };

    SetState(Target, petTypePassiveState[petType], 1);

    return true;
}

bool PetBattleAbilityEffect::HandleResurect()
{
    SetHealth(Target, CalculatePct(GetMaxHealth(Target), EffectInfo->prop[0]));
    SetState(Target, BATTLEPET_STATE_Is_Dead, 0);
    return true;
}

bool PetBattleAbilityEffect::HandleKill()
{
    /// @TODO Figure out what to do with prop[1] & prop[3]
    CalculateHit(EffectInfo->prop[0]);

    int32 immuneStateCondition = EffectInfo->prop[2];

    if (!immuneStateCondition || !GetState(GetActiveOpponent(), immuneStateCondition))
        Kill(GetActiveOpponent());

    if (!immuneStateCondition || !GetState(Caster, immuneStateCondition))
        Kill(Caster);

    return !(Flags & FailFlags);
}

bool PetBattleAbilityEffect::HandleDamageToggleAura()
{
    CalculateHit(EffectInfo->prop[1]);
    if (Flags & FailFlags)
        return SetHealth(Target, GetHealth(Target));

    if (PetBattleAura* aura = GetAura(Caster, EffectInfo->triggerAbility))
    {
        aura->Expire(PetBattleInstance);

        // Damage
        return Damage(Target, CalculateDamage(EffectInfo->prop[0]));
    }
    // No aura, add it
    return AddAura(Caster, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleHealStateToggleAura()
{
    if (PetBattleAura* aura = GetAura(Caster, EffectInfo->triggerAbility))
    {
        aura->Expire(PetBattleInstance);

        // Heal
        int32 stateValue = std::min(GetState(Caster, EffectInfo->prop[1]), int32(EffectInfo->prop[2]));
        int32 heal = EffectInfo->prop[0] + EffectInfo->prop[3] * stateValue;
        return Heal(Target, CalculateHeal(heal));
    }
    // No aura, add it
    return AddAura(Caster, 0, 0);
}

bool PetBattleAbilityEffect::HandleResetState()
{
    return SetState(Target, EffectInfo->prop[0], 0);
}

bool PetBattleAbilityEffect::HandleDamageHitState()
{
    if ((!EffectInfo->prop[2] || !GetState(Caster, EffectInfo->prop[2])) && (!EffectInfo->prop[3] || !GetState(Target, EffectInfo->prop[3])))
        CalculateHit(EffectInfo->prop[1]);
    else
        CalculateHit(200);

    return Damage(Target, CalculateDamage(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleDamageAuraToggleAura()
{
    // Aura is applied independently of damages and cannot miss
    if (PetBattleAura* aura = GetAura(Target, EffectInfo->prop[3]))
    {
        aura->Expire(PetBattleInstance);
        AddAura(Target, EffectInfo->prop[4], 0);
    }
    else
        PetBattleInstance->AddAura(Caster, Target, EffectInfo->prop[3], EffectInfo->prop[2], 0, EffectInfo->id, Flags);

    CalculateHit(EffectInfo->prop[1]);

    return Damage(Target, CalculateDamage(EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleHealthConsume()
{
    int32 healthConsumePct = EffectInfo->prop[0];

    /// Hotfix for http://wowhead.com/petability=758
    if (AbilityID == 758)
        healthConsumePct = 50;

    return SetHealth(Target, GetHealth(Target) - CalculatePct(GetMaxHealth(Target), healthConsumePct));
}

bool PetBattleAbilityEffect::HandleSwap()
{
    CalculateHit(EffectInfo->prop[0]);
    if (Flags & FailFlags)
        return false;

    auto availablesPets = PetBattleInstance->Teams[PetBattleInstance->Pets[Target]->TeamID]->GetAvailablesPets();
    auto iter = std::find(availablesPets.begin(), availablesPets.end(), Target);
    if (iter != availablesPets.end())
        availablesPets.erase(iter);

    if (availablesPets.empty())
        return false;

    PetBattleInstance->SwapPet(PetBattleInstance->Pets[Target]->TeamID, availablesPets[rand() % availablesPets.size()]);
    return true;
}

bool PetBattleAbilityEffect::HandleUpdatePriority()
{
    PetBattleInstance->RoundFirstTeamCasting = PetBattleInstance->GetFirstAttackingTeam();
    return true;
}

bool PetBattleAbilityEffect::HandleSetHealthPercent()
{
    return SetHealth(Target, CalculatePct(GetMaxHealth(Target), EffectInfo->prop[0]));
}

bool PetBattleAbilityEffect::HandleLockActiveAbility()
{
    std::shared_ptr<BattlePetInstance> target = PetBattleInstance->Pets[Target];
    uint32 activeAbilityId = PetBattleInstance->Teams[target->TeamID]->ActiveAbilityId;

    uint32 abilitySlot;
    for (abilitySlot = 0; abilitySlot < MAX_PETBATTLE_ABILITIES; ++abilitySlot)
        if (target->Abilities[abilitySlot] == activeAbilityId)
            break;

    if (abilitySlot == MAX_PETBATTLE_ABILITIES)
        return false;

    target->Cooldowns[abilitySlot] = EffectInfo->prop[0];
    return true;
}

bool PetBattleAbilityEffect::HandleAuraIfCasterFaster()
{
    if (EffectInfo->prop[0] && AbilityTurn->ChainFailure)
        return false;

    if (PetBattleInstance->RoundFirstTeamCasting != PetBattleInstance->Pets[Caster]->TeamID)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleCleansing()
{
    //TODO: implement prop 0: DontMiss

    for (auto aura : PetBattleInstance->PetAuras)
        if (!aura->Expired && aura->TargetPetID == Target)
            aura->Expire(PetBattleInstance);

    return true;
}

bool PetBattleAbilityEffect::HandleAuraState()
{
    if (EffectInfo->prop[5] && AbilityTurn->ChainFailure)
        return false;

    if (EffectInfo->prop[0] && GetState(Caster, EffectInfo->prop[0]) != EffectInfo->prop[1])
        return false;

    if (EffectInfo->prop[3] && GetState(Caster, EffectInfo->prop[3]) != EffectInfo->prop[4])
        return false;

    return AddAura(Target, EffectInfo->prop[2], 0);
}

bool PetBattleAbilityEffect::HandleChangeCasterState()
{
    if (EffectInfo->prop[4] && GetState(Target, EffectInfo->prop[4]) == EffectInfo->prop[5])
        return false;

    int32 value = GetState(Caster, EffectInfo->prop[0]);
    if (value < EffectInfo->prop[2] || value > EffectInfo->prop[3])
        return false;

    ModState(Caster, EffectInfo->prop[0], EffectInfo->prop[1]);

    return true;
}

bool PetBattleAbilityEffect::HandleSwapLow()
{
    CalculateHit(EffectInfo->prop[0]);
    if (Flags & FailFlags)
        return false;

    auto availablesPets = PetBattleInstance->Teams[PetBattleInstance->Pets[Target]->TeamID]->GetAvailablesPets();
    auto iter = std::find(availablesPets.begin(), availablesPets.end(), Target);
    if (iter != availablesPets.end())
        availablesPets.erase(iter);

    if (availablesPets.empty())
        return false;

    std::sort(availablesPets.begin(), availablesPets.end(), [this](uint32 i, uint32 j)
    {
        return GetHealth(i) < GetHealth(j);
    });

    PetBattleInstance->SwapPet(PetBattleInstance->Pets[Target]->TeamID, availablesPets.front());
    return true;
}

bool PetBattleAbilityEffect::HandleResetAuraDuration()
{
    for (auto aura : PetBattleInstance->PetAuras)
        if (!aura->Expired && aura->TargetPetID == Target && aura->AbilityID == EffectInfo->triggerAbility)
            aura->Duration = EffectInfo->prop[0];
    return true;
}

bool PetBattleAbilityEffect::HandleSwapHigh()
{
    CalculateHit(EffectInfo->prop[0]);
    if (Flags & FailFlags)
        return false;

    auto availablesPets = PetBattleInstance->Teams[PetBattleInstance->Pets[Target]->TeamID]->GetAvailablesPets();
    auto iter = std::find(availablesPets.begin(), availablesPets.end(), Target);
    if (iter != availablesPets.end())
        availablesPets.erase(iter);

    if (availablesPets.empty())
        return false;

    std::sort(availablesPets.begin(), availablesPets.end(), [this](uint32 i, uint32 j)
    {
        return GetHealth(i) < GetHealth(j);
    });

    PetBattleInstance->SwapPet(PetBattleInstance->Pets[Target]->TeamID, availablesPets.back());
    return true;
}

bool PetBattleAbilityEffect::HandleRedirectionAura()
{
    if (EffectInfo->prop[0] && AbilityTurn->ChainFailure)
        return false;

    CalculateHit(EffectInfo->prop[1]);

    // remove all wall auras
    if (uint32 wallAuraId = GetState(Target, BATTLEPET_STATE_Special_ObjectRedirectionAuraID))
        if (PetBattleAura* aura = GetAura(Target, wallAuraId))
            aura->Expire(PetBattleInstance);

    return AddAura(Target, 0, 0);
}

bool PetBattleAbilityEffect::HandleCheckFailure()
{
    if (!AbilityTurn->ChainFailure)
        StopChain = true;

    return true;
}

bool PetBattleAbilityEffect::HandleTryRevive()
{
    if (GetHealth(Target) <= 0)
        return false;

    if (EffectInfo->prop[1] && GetState(Caster, EffectInfo->prop[1]))
        Flags |= PETBATTLE_EVENT_FLAG_IMMUNE;

    if (EffectInfo->prop[2] && GetState(Target, EffectInfo->prop[2]))
        Flags |= PETBATTLE_EVENT_FLAG_IMMUNE;

    CalculateHit(EffectInfo->prop[0]);

    return SetState(Target, BATTLEPET_STATE_Is_Dead, 0);
}

bool PetBattleAbilityEffect::HandleDamagePercentTaken()
{
    CalculateHit(EffectInfo->prop[1]);

    int32 damage = CalculateDamage(CalculatePct(GetState(Caster, BATTLEPET_STATE_Last_HitTaken), EffectInfo->prop[0]));
    return Damage(Target, damage);
}

bool PetBattleAbilityEffect::HandleDamageRange()
{
    CalculateHit(EffectInfo->prop[1]);

    int32 baseDamage = urand(EffectInfo->prop[0], EffectInfo->prop[2]);

    return Damage(Target, CalculateDamage(baseDamage));
}

bool PetBattleAbilityEffect::HandleDamageWithBonus()
{
    CalculateHit(EffectInfo->prop[1]);

    uint32 damage = CalculateDamage(EffectInfo->prop[0]);

    if (EffectInfo->prop[3] && GetState(Caster, EffectInfo->prop[3]))
        damage += CalculateDamage(EffectInfo->prop[2]);

    return Damage(Target, damage);
}