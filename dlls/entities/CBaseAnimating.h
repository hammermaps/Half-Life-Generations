/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef GAME_SERVER_CBASEANIMATING_H
#define GAME_SERVER_CBASEANIMATING_H

class CBaseAnimating : public CBaseDelay
{
public:
	using BaseClass = CBaseDelay;

	int Save(CSave& save) override;
	int Restore(CRestore& restore) override;

	static TYPEDESCRIPTION m_SaveData[];

	// Basic Monster Animation functions
	float StudioFrameAdvance(float flInterval = 0.0); // accumulate animation frame time from last time called until now
	int GetSequenceFlags() const;
	int LookupActivity(int activity);
	int LookupActivityHeaviest(int activity);
	int LookupSequence(const char* label);
	void ResetSequenceInfo();
	void DispatchAnimEvents(float flFutureInterval = 0.1);
	// Handle events that have happend since last time called up until X seconds into the future
	virtual void HandleAnimEvent(MonsterEvent_t* pEvent) { return; }
	
	float SetBoneController(int iController, float flValue);
	void InitBoneControllers();
	float SetBlending(int iBlender, float flValue);
	void GetBonePosition(int iBone, Vector& origin, Vector& angles);
	int FindTransition(int iEndingSequence, int iGoalSequence, int* piDir);
	void GetAttachment(int iAttachment, Vector& origin, Vector& angles);
	void SetBodygroup(int iGroup, int iValue);
	int GetBodygroup(int iGroup);

	//LRC
	int GetBoneCount();
	void SetBones(float (*data)[3], int datasize);

	int ExtractBbox(int sequence, float* mins, float* maxs);
	void SetSequenceBox();

	// animation needs
	float m_flFrameRate; // computed FPS for current sequence
	float m_flGroundSpeed; // computed linear movement rate for current sequence
	float m_flLastEventCheck; // last time the event list was checked
	bool m_fSequenceFinished; // flag set when StudioAdvanceFrame moves across a frame boundry
	bool m_fSequenceLoops; // true if the sequence loops
};

#endif //GAME_SERVER_CBASEANIMATING_H
