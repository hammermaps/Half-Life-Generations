/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   This source code contains proprietary and confidential information of
*   Valve LLC and its suppliers.  Access to this code is restricted to
*   persons who have executed a written SDK license with Valve.  Any access,
*   use or distribution of this code by or to any unlicensed person is illegal.
*
****/
#ifndef GAME_SERVER_ENTITIES_NPCS_CDEADOTIS_H
#define GAME_SERVER_ENTITIES_NPCS_CDEADOTIS_H

class CDeadOtis : public CBaseMonster
{
public:
	using BaseClass = CBaseMonster;
	
	void Spawn() override;
	void Precache() override;
	int Classify() override;

	void KeyValue(KeyValueData* pkvd) override;

	int m_iPose; // which sequence to display
	
	static char* m_szPoses[5];
};

#endif //GAME_SERVER_ENTITIES_NPCS_CDEADOTIS_H
