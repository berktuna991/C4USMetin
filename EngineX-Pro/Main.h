


#pragma once
class Main :public IAbstractModuleBase, public Singleton<Main>
{
private:

	DWORD lastTimeRefreshItemList = 0;
	D3DVECTOR  lastPosition = D3DVECTOR{ 0, 0, 0 };
	DWORD lastTimeBackToPosition = 0;
	DWORD lastMiniMHRotation = 0;
	DWORD lastTimeAttackEnable = 0;
	DWORD lastWaitHackEnable = 0;
	DWORD lastWaitHackSkillDelay = 0;
	DWORD lastTimeUpdateIcons = 0;
	bool playerUsingHorse = false;
	bool autoReviveNeedWait = false;
	DWORD lastMiniMHMoveSpeed = 0;
	DWORD lastMiniMHAttackSpeed = 0;
	bool canAttack = false;


	DWORD lastTimeStonesArrowShow = 0;

	DirectTexture texture_Skill_0;
	DirectTexture texture_Skill_1;
	DirectTexture texture_Skill_2;
	DirectTexture texture_Skill_3;
	DirectTexture texture_Skill_4;
	DirectTexture texture_Skill_5;
	DirectTexture texture_Skill_None;

	void  SetJobRaceTextures(int job, int race)
	{

		texture_Skill_None = MainForm::skill_none;
		if (job == 0)
		{
			texture_Skill_0 = texture_Skill_None;
			texture_Skill_1 = texture_Skill_None;
			texture_Skill_2 = texture_Skill_None;
			texture_Skill_3 = texture_Skill_None;
			texture_Skill_4 = texture_Skill_None;
			texture_Skill_5 = texture_Skill_None;
			return;
		}
		else
		{
		}
		if (race == 0 || race == 4)
		{
			if (job == 1)
			{

				texture_Skill_0 = MainForm::warrior_b_0;
				texture_Skill_1 = MainForm::warrior_b_1;
				texture_Skill_2 = MainForm::warrior_b_2;
				texture_Skill_3 = MainForm::warrior_b_3;
				texture_Skill_4 = MainForm::warrior_b_4;
				texture_Skill_5 = MainForm::warrior_b_5;
				return;
			}
			if (job == 2)
			{

				texture_Skill_0 = MainForm::warrior_m_0;
				texture_Skill_1 = MainForm::warrior_m_1;
				texture_Skill_2 = MainForm::warrior_m_2;
				texture_Skill_3 = MainForm::warrior_m_3;
				texture_Skill_4 = MainForm::warrior_m_4;
				texture_Skill_5 = MainForm::warrior_m_5;
				return;
			}
		}

		if (race == 1 || race == 5)
		{
			if (job == 1)
			{
				texture_Skill_0 = MainForm::ninja_d_0;
				texture_Skill_1 = MainForm::ninja_d_1;
				texture_Skill_2 = MainForm::ninja_d_2;
				texture_Skill_3 = MainForm::ninja_d_3;
				texture_Skill_4 = MainForm::ninja_d_4;
				texture_Skill_5 = MainForm::ninja_d_5;
				return;
			}
			if (job == 2)
			{
				texture_Skill_0 = MainForm::ninja_a_0;
				texture_Skill_1 = MainForm::ninja_a_1;
				texture_Skill_2 = MainForm::ninja_a_2;
				texture_Skill_3 = MainForm::ninja_a_3;
				texture_Skill_4 = MainForm::ninja_a_4;
				texture_Skill_5 = MainForm::ninja_a_5;
				return;
			}
		}

		if (race == 2 || race == 6)
		{
			if (job == 1)
			{
				texture_Skill_0 = MainForm::sura_w_0;
				texture_Skill_1 = MainForm::sura_w_1;
				texture_Skill_2 = MainForm::sura_w_2;
				texture_Skill_3 = MainForm::sura_w_3;
				texture_Skill_4 = MainForm::sura_w_4;
				texture_Skill_5 = MainForm::sura_w_5;
				return;
			}
			if (job == 2)
			{
				texture_Skill_0 = MainForm::sura_b_0;
				texture_Skill_1 = MainForm::sura_b_1;
				texture_Skill_2 = MainForm::sura_b_2;
				texture_Skill_3 = MainForm::sura_b_3;
				texture_Skill_4 = MainForm::sura_b_4;
				texture_Skill_5 = MainForm::sura_b_6;
				return;
			}
		}

		if (race == 3 || race == 7)
		{
			if (job == 1)
			{
				texture_Skill_0 = MainForm::shaman_d_0;
				texture_Skill_1 = MainForm::shaman_d_1;
				texture_Skill_2 = MainForm::shaman_d_2;
				texture_Skill_3 = MainForm::shaman_d_3;
				texture_Skill_4 = MainForm::shaman_d_4;
				texture_Skill_5 = MainForm::shaman_d_5;
				return;
			}
			if (job == 2)
			{
				texture_Skill_0 = MainForm::shaman_h_0;
				texture_Skill_1 = MainForm::shaman_h_1;
				texture_Skill_2 = MainForm::shaman_h_2;
				texture_Skill_3 = MainForm::shaman_h_3;
				texture_Skill_4 = MainForm::shaman_h_4;
				texture_Skill_5 = MainForm::shaman_h_5;
				return;
			}
		}
	}


public:


	void OnStart()
	{
		Settings::GLOBAL_SWITCH = true;
		playerUsingHorse = GameFunctionsCustom::PlayerIsMountingHorse();
		lastPosition = GameFunctionsCustom::PlayerGetPixelPosition();
	}

	void OnStop()
	{
		Settings::GLOBAL_SWITCH = false;
		GameFunctions::PlayerSetAttackKeyState(false);
		autoReviveNeedWait = false;
		playerUsingHorse = false;
	}

	void OnUpdate()
	{

		if (GameFunctionsCustom::PlayerIsInstance())
		{
			SetJobRaceTextures(GameFunctions::NetworkStreamGetMainActorSkillGroup(), GameFunctions::PlayerGetRace());
		}
		else
		{
			SetJobRaceTextures(0, 0);
		}
		if (Settings::GLOBAL_SWITCH)
		{
			if (GameFunctionsCustom::PlayerIsInstance())
			{

				Potions();

				Other();
				if (Revive())
				{
					return;
				}
				if ((GetTickCount() - lastTimeBackToPosition) > 1200 && GameFunctionsCustom::PlayerGetDistance(lastPosition) > 200 && !playerUsingHorse && Settings::MiniMHAttackEnable)
				{
					GameFunctionsCustom::LookAtDestPixelPosition(lastPosition);
					GameFunctionsCustom::PlayerMoveToDestPixelPositionDirection(lastPosition);

					lastTimeBackToPosition = GetTickCount();
				}
				if (Settings::MiniMHAttackStopAttackNoMobDistance)
				{
					canAttack = IsAttackMobDistance();
				}
				else
				{

				}




				Skill();
				WaitHack();
				if (Settings::MiniMHAttackEnable)
				{
					GameFunctions::PlayerSetAttackKeyState(canAttack);
				}
				

			}
			else
			{


			}
		}

		else
		{


		}
	}

	void OnRender()
	{

#ifdef BZDETY
		DWORD pCInstanceBaseGetGraphicThingInstanceRef = Globals::hEntryBaseAddress + 0x59A70;
		typedef DWORD* (__thiscall* tCInstanceBaseGetGraphicThingInstanceRef)(void* This);
		tCInstanceBaseGetGraphicThingInstanceRef CInstanceBaseGetGraphicThingInstanceRef = (tCInstanceBaseGetGraphicThingInstanceRef)pCInstanceBaseGetGraphicThingInstanceRef;

		DWORD pCGraphicThingInstanceGetBoundingSphere = Globals::hEntryBaseAddress + 0x47f360;
		typedef bool(__thiscall* tCGraphicThingInstanceGetBoundingSphere)(void* This, D3DXVECTOR3& v3Center, float& fRadius);
		tCGraphicThingInstanceGetBoundingSphere CGraphicThingInstanceGetBoundingSphere = (tCGraphicThingInstanceGetBoundingSphere)pCGraphicThingInstanceGetBoundingSphere;


		//if (GameFunctions::PlayerNEW_GetMainActorPtr() == NULL)
		//	return;

		//DWORD* GraphicThing = CInstanceBaseGetGraphicThingInstanceRef(GameFunctions::PlayerNEW_GetMainActorPtr());
		//D3DXVECTOR3 Position;
		//float r;
		//CGraphicThingInstanceGetBoundingSphere(GraphicThing, Position, r);
		//D3DCOLOR color = D3DCOLOR_RGBA((int)(Settings::renderwh_color.x * 255.0f),
		//(int)(Settings::renderwh_color.y * 255.0f),
		//(int)(Settings::renderwh_color.z * 255.0f),
		//(int)(Settings::renderwh_color.w * 255.0f));
		//CRender::RenderSphere(Device::ms_lpSphereMesh, Position.x, Position.y, Position.z, Settings::MiniMHWaitHackDistanceValue, D3DFILL_SOLID, color);

		//Render WH
		if (!Settings::renderwh)
			return;

		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE, Settings::MiniMHWaitHackDistanceValue);
		if (objectList.size() > 0)
		{
			for (auto itor = objectList.begin(); itor != objectList.end(); itor++)
			{
				if (itor->second == GameFunctions::PlayerNEW_GetMainActorPtr())
					continue;
				DWORD* GraphicThing = CInstanceBaseGetGraphicThingInstanceRef(itor->second);
				D3DXVECTOR3 Position;
				float r;
				CGraphicThingInstanceGetBoundingSphere(GraphicThing, Position, r);
				//RenderSphere(Device::ms_lpSphereMesh, Position.x, Position.y, Position.z, r, D3DFILL_WIREFRAME, D3DCOLOR_RGBA(255, 0, 0, 125));
				D3DCOLOR color = D3DCOLOR_RGBA((int)(Settings::renderwh_color.x * 255.0f),
					(int)(Settings::renderwh_color.y * 255.0f),
					(int)(Settings::renderwh_color.z * 255.0f),
					(int)(Settings::renderwh_color.w * 255.0f));
				//CRender::RenderBox(Device::ms_lpCylinderMesh, Position.x, Position.y, Position.z, r, D3DFILL_SOLID, color);
				CRender::RenderSphere(Device::ms_lpSphereMesh, Position.x, Position.y, Position.z, r, D3DFILL_WIREFRAME, color);
			}
		}
#endif
	}

	void OnMenu()
	{

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("MHUsager", ImVec2(645, 110), true);
		ImGui::Checkbox("HP Potion           ", &Settings::MiniMHUseRedPotion); ImGui::SameLine();
		ImGui::PushItemWidth(150); ImGui::SliderInt("Speed(ms)            ", &Settings::MiniMHUseRedPotionSpeed, 1, 1000); ImGui::SameLine();
		ImGui::PushItemWidth(150); ImGui::SliderInt("Below % HP", &Settings::MiniMHUseRedPotionValue, 1, 100);


		ImGui::Checkbox("MP Potion           ", &Settings::MiniMHUseBluePotion); ImGui::SameLine();
		ImGui::PushItemWidth(150); ImGui::SliderInt("Speed(ms)            ", &Settings::MiniMHUseRedPotionSpeed, 1, 1000); ImGui::SameLine();
		ImGui::PushItemWidth(150); ImGui::SliderInt("Below % MP", &Settings::MiniMHUseBluePotionValue, 1, 100);


		ImGui::Checkbox("Auto Revive        ", &Settings::MiniMHAutoRevive); ImGui::SameLine();
		ImGui::SliderInt("Resume Attack After HP %", &Settings::MiniMHAutoReviveHpPercentValue, 1, 100);
		ImGui::EndChild();
		ImGui::PopStyleVar();/* ImGui::SameLine();*/
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);

		ImGui::BeginChild("AtakBorder", ImVec2(645, 80), true);
		if (ImGui::Checkbox("Auto Attack   ", &Settings::MiniMHAttackEnable))
		{
			lastPosition = GameFunctionsCustom::PlayerGetPixelPosition();
			canAttack = Settings::MiniMHAttackEnable;
			if (!Settings::MiniMHAttackEnable)
			{
				GameFunctions::PlayerSetAttackKeyState(canAttack);
			}
		}
		ImGui::SameLine();
		ImGui::Checkbox("Mob Detect         ", &Settings::MiniMHAttackStopAttackNoMobDistance); ImGui::SameLine();
		if (ImGui::Checkbox("Rotation", &Settings::MiniMHRotation))
		{
			canAttack = true;
		}
		ImGui::SameLine();
		ImGui::PushItemWidth(200); ImGui::SliderInt("Rotation Frequency", &Settings::MiniMHRotationValue, 1, 100);



		ImGui::Checkbox("Wallhack Mob", &Settings::MainWallHackMob); ImGui::SameLine();
		ImGui::Checkbox("Wallhack Object", &Settings::MainWallHackObject); ImGui::SameLine();
		ImGui::Checkbox("Wallhack Terrain", &Settings::MainWallHackTerrain); ImGui::SameLine();


		ImGui::Checkbox("NOK", &Settings::MiniMHNOK); ImGui::SameLine();
		ImGui::Checkbox("NOP", &Settings::MiniMHNOP);
		ImGui::EndChild();
		ImGui::PopStyleVar(); /*ImGui::SameLine();*/

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("SkillsBorder", ImVec2(645, 75), true);
		ImGui::IconButton2(&Settings::MAIN_SKILL_1, "Skill 1", texture_Skill_0, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_2, "Skill 2", texture_Skill_1, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_3, "Skill 3", texture_Skill_2, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_4, "Skill 4", texture_Skill_3, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_5, "Skill 5", texture_Skill_4, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::IconButton2(&Settings::MAIN_SKILL_6, "Skill 6", texture_Skill_5, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::EndChild();
		ImGui::PopStyleVar();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("WHBorder", ImVec2(315, 230), true);
		ImGui::Checkbox("WaitHack", &Settings::MiniMHWaitHackEnable);
		ImGui::Checkbox("Detect Player", &Settings::MiniMHWaitHackDetect);

		ImGui::RadioButton("Standard", &Settings::MiniMHWaitHackOneTarget, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Target", &Settings::MiniMHWaitHackOneTarget, 1);
		ImGui::PushItemWidth(100); ImGui::InputInt("Time(ms)", &Settings::MiniMHWaitHackTime, 5, 100);
		ImGui::Checkbox("Range", &Settings::MiniMHWaitHackSwordRange); ImGui::SameLine();
		ImGui::PushItemWidth(100); ImGui::InputInt("Attack Distance", &Settings::MiniMHWaitHackDistanceValue, 100, 1000);
		ImGui::RadioButton("Sword", &Settings::MiniMHWaitHackType, 0); ImGui::SameLine();
		ImGui::RadioButton("Bow", &Settings::MiniMHWaitHackType, 1);

#ifdef DEVELOPER_MODE
		ImGui::RadioButton("Skill", &Settings::MiniMHWaitHackType, 2);
		ImGui::InputInt("Skill Number", &Settings::MiniMHSkillNumber, 1, 111);
		ImGui::InputInt("Skill Time", &Settings::MiniMHWaitHackSkillDelay, 1, 10);
#endif	
		ImGui::EndChild();
		ImGui::PopStyleVar();
#ifdef BZDETY
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("RenderWH", ImVec2(150, 60), true);
		ImGui::ColorEdit4("##RenderWH", (float*)&Settings::renderwh_color, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoInputs); ImGui::SameLine();
		ImGui::Checkbox("Render WH", &Settings::renderwh);
		ImGui::EndChild();
		ImGui::PopStyleVar();
#endif






		ImGui::SameLine();

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("OtherBorder", ImVec2(315, 230), true);

		
		ImGui::Checkbox("Detect Stones", &Settings::MainInfoStonesViewportShow);

		ImGui::Hotkey(Settings::HotkeyTime, "Boost         ", &Settings::BoostKey);
		ImGui::Hotkey(Settings::HotkeyTime, "Relog         ", &Settings::RelogKey);
		ImGui::Hotkey(Settings::HotkeyTime, "MH Switch", &Settings::OnOffMH);
		ImGui::Hotkey(Settings::HotkeyTime, "Hide UI      ", &Settings::HideUI);
		
		ImGui::PushItemWidth(100); ImGui::InputInt("Boost Distance", &Settings::BoostSpeed3, 5, 100);



		ImGui::EndChild();
		ImGui::PopStyleVar();
	}
private:
	bool Revive()
	{
		if (GameFunctionsCustom::PlayerIsDead() && Settings::MiniMHAutoRevive && /*!autoReviveNeedWait &&*/ DynamicTimer::CheckAutoSet("PlayerRevive", 1000))
		{
			GameFunctionsCustom::PlayerRevive();
			autoReviveNeedWait = true;
			return true;

		}
		else if (!GameFunctionsCustom::PlayerIsDead() && !Settings::MiniMHAutoRevive )
		{
			return false;
		}
		else if (GameFunctionsCustom::GetHpProcentageStatus() < Settings::MiniMHAutoReviveHpPercentValue && Settings::MiniMHAutoRevive && autoReviveNeedWait)
		{
			return true;
		}
		else if (GameFunctionsCustom::GetHpProcentageStatus() > Settings::MiniMHAutoReviveHpPercentValue && Settings::MiniMHAutoRevive && autoReviveNeedWait)
		{
			if (playerUsingHorse)
			{
				GameFunctionsCustom::MountHorse();
			}
			autoReviveNeedWait = false;
			return false;
		}
		else if ( !Settings::MiniMHAutoRevive && autoReviveNeedWait)
		{
			autoReviveNeedWait = false;
			return false;
		}
		else
		{
			return true;
		}
	}
	bool IsAttackMobDistance()
	{
		if (((GetTickCount() - lastTimeAttackEnable) > 500))
		{

			if (GameFunctionsCustom::GetObjectListCount(OBJECT_MOB, 300) == 0)
			{

				return false;
			}
			else
			{
				return true;
			}



			lastTimeAttackEnable = GetTickCount();
		}

		else
		{
			return false;
		}


	}

	void Skill()
	{

		if (Settings::MAIN_SKILL_1)
		{
			if (!GameFunctions::PlayerIsSkillActive(1) && !GameFunctions::PlayerIsSkillCoolTime(1))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 1);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 1);
				}
			}

		}
		if (Settings::MAIN_SKILL_2)
		{
			if (!GameFunctions::PlayerIsSkillActive(2) && !GameFunctions::PlayerIsSkillCoolTime(2))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 2);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 2);
				}
			}

		}
		if (Settings::MAIN_SKILL_3)
		{
			if (!GameFunctions::PlayerIsSkillActive(3) && !GameFunctions::PlayerIsSkillCoolTime(3))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 3);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 3);
				}
			}

		}
		if (Settings::MAIN_SKILL_4)
		{
			if (!GameFunctions::PlayerIsSkillActive(4) && !GameFunctions::PlayerIsSkillCoolTime(4))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 4);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 4);
				}
			}

		}
		if (Settings::MAIN_SKILL_5)
		{
			if (!GameFunctions::PlayerIsSkillActive(5) && !GameFunctions::PlayerIsSkillCoolTime(5))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 5);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 5);
				}
			}

		}
		if (Settings::MAIN_SKILL_6)
		{
			if (!GameFunctions::PlayerIsSkillActive(6) && !GameFunctions::PlayerIsSkillCoolTime(6))
			{
				if (playerUsingHorse)
				{
					DelayActions::AppendBlockUnique(true, 700, "Skill", &GameFunctionsCustom::UseSkillSlot, 6);
				}
				else
				{
					DelayActions::AppendBlockUnique(true, 300, "Skill", &GameFunctionsCustom::UseSkillSlot, 6);
				}
			}

		}


	}
	void SwordWH()
	{
		D3DVECTOR oldPosition;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE, Settings::MiniMHWaitHackDistanceValue);
		for (auto itor = objectList.begin(); itor != objectList.end(); itor++)
		{
			DWORD vid = itor->first;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
			DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
			GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);
			if (Settings::MiniMHWaitHackSwordRange)
			{
				GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, 0, 0, 0);
			}
			GameFunctions::NetworkStreamSendAttackPacket(0, vid);
			/*GameFunctionsCustom::NetworkStreamSendAttackPacket(0, vid);*/

			if (Settings::MiniMHWaitHackSwordRange)
			{
				GameFunctions::NetworkStreamSendCharacterStatePacket(oldPosition, 0, 0, 0);
			}
		}
	}

	void BowWH()
	{
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE, Settings::MiniMHWaitHackDistanceValue);
		for (auto itor = objectList.begin(); itor != objectList.end(); itor++)
		{
			DWORD vid = itor->first;
			GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);
			GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
			/*GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, 35, 133, 0);*/
		}
		if (objectList.size())
		{
			GameFunctions::NetworkStreamSendShootPacket(0);
		}
		
	}
public:
	void ResetSkillTimer()
	{
		lastWaitHackSkillDelay = 0;
	}
private:
#ifdef DEVELOPER_MODE
	void SkillWH() 
	{
		D3DVECTOR oldPosition;
		D3DVECTOR newPosition;
		map<DWORD, DWORD*> objectList = GameFunctionsCustom::GetObjectList(OBJECT_MOB | OBJECT_BOSS | OBJECT_STONE, Settings::MiniMHWaitHackDistanceValue);
		if (objectList.size() > 0)
		{
			for (auto itor = objectList.begin(); itor != objectList.end(); itor++)
			{
				DWORD vid = itor->first;

				if ((GetTickCount() - Main::lastWaitHackSkillDelay) > Settings::MiniMHWaitHackSkillDelay * 1000)
				{
					GameFunctions::NetworkStreamSendUseSkillPacket(Settings::MiniMHSkillNumber, vid);
					Main::lastWaitHackSkillDelay = GetTickCount();
				}
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &oldPosition);
				GameFunctions::InstanceBaseNEW_GetPixelPosition(itor->second, &newPosition);
				if (Settings::MiniMHWaitHackSwordRange)
				{
					vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(1500, oldPosition, newPosition);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
					{
						bool InDistance = MathExtension::PointInCircle(oldPosition, newPosition, 800);
						if (!InDistance)
						{
							//DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
							GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
							//DelayActions::AppendBlock(false, 10 * (i + 1), &GameFunctions::NetworkStreamSendCharacterStatePacket, D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						}
						i++;			
					}
					//GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, 0, 0, 0);
				}
				GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
				if (Settings::MiniMHWaitHackSwordRange)
				{
					GameFunctions::NetworkStreamSendShootPacket(Settings::MiniMHSkillNumber);
					vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(1500, newPosition, oldPosition);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
					{
						bool InDistance = MathExtension::PointInCircle(newPosition, oldPosition, 800);
						if (!InDistance)
						{
							//DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
							GameFunctions::NetworkStreamSendCharacterStatePacket(D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
							//DelayActions::AppendBlock(false, 10 * (i + 1), &GameFunctions::NetworkStreamSendCharacterStatePacket, D3DVECTOR{ it->x, it->y, it->z }, 0, 0, 0);
						}
						i++;
					}
					//GameFunctions::NetworkStreamSendCharacterStatePacket(oldPosition, 0, 0, 0);
				}

			}
			if (!Settings::MiniMHWaitHackSwordRange)
			{
				GameFunctions::NetworkStreamSendShootPacket(Settings::MiniMHSkillNumber);
			}
		}

	}
#endif
	void Target()
	{
		DWORD vid = GameFunctions::PlayerGetTargetVID();
		if (vid != 0)
		{
			D3DVECTOR oldPosition;
			D3DVECTOR newPosition;
			DWORD* pTargetInstance = GameFunctions::CharacterManagerGetInstancePtr(vid);
			DWORD* pCharInstance = GameFunctions::CharacterManagerGetInstancePtr(GameFunctions::PlayerGetMainCharacterIndex());
			if (pTargetInstance != 0 && pCharInstance != 0)
			{
				if (Settings::MiniMHWaitHackSwordRange)
				{
					GameFunctions::NetworkStreamSendCharacterStatePacket(newPosition, 0, 0, 0);
				}

				switch (Settings::MiniMHWaitHackType)
				{
				case 0:
					GameFunctions::NetworkStreamSendAttackPacket(0, vid);
					/*GameFunctionsCustom::NetworkStreamSendAttackPacket(0, vid);*/
					break;
				case 1:
					GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ newPosition.x, newPosition.y, newPosition.z });
					GameFunctions::NetworkStreamSendShootPacket(0);
				case 2:
					if ((GetTickCount() - Main::lastWaitHackSkillDelay) > (Settings::MiniMHWaitHackSkillDelay * 1000))
					{
						GameFunctions::NetworkStreamSendUseSkillPacket(Settings::MiniMHSkillNumber, vid);
						Main::lastWaitHackSkillDelay = GetTickCount();
					}
					for (int i = 0; i < 50; i++) {
						GameFunctions::NetworkStreamSendAddFlyTargetingPacket(vid, D3DVECTOR{ 0,0,0 });
						GameFunctions::NetworkStreamSendShootPacket(Settings::MiniMHSkillNumber);
					}
					break;
				}
				if (Settings::MiniMHWaitHackSwordRange)
				{
					GameFunctions::NetworkStreamSendCharacterStatePacket(oldPosition, 0, 0, 0);
				}

			}
		}
	}


	void WaitHack()
	{
		if (((GetTickCount() - lastWaitHackEnable) > Settings::MiniMHWaitHackTime) && Settings::MiniMHWaitHackEnable)
		{

			if (Settings::MiniMHWaitHackDetect && GameFunctionsCustom::DetectPlayer(Settings::DETECT_PLAYER_WHITE_LIST_NAMES))
			{
				return;
			}
			if (Settings::MiniMHWaitHackOneTarget == 1)
			{
				Target();
			}
			else
			{
				switch (Settings::MiniMHWaitHackType)
				{
				case 0:
					SwordWH();
					break;
				case 1:
					BowWH();
					break;
#ifdef DEVELOPER_MODE
				case 2:
					SkillWH();
					break;
#endif
				}
			}
			lastWaitHackEnable = GetTickCount();
		}
	}



	void Other()
	{

		if (Settings::MiniMHNOP)
		{

			GameFunctions::InstanceBase__SetAffect(GameFunctions::PlayerNEW_GetMainActorPtr(), 16, true);
		}

		if (((GetTickCount() - lastMiniMHRotation) > (MiscExtension::RandomInt(500, 8000))) && Settings::MiniMHRotation)
		{
			if (MiscExtension::RandomInt(0, 100) < Settings::MiniMHRotationValue)
			{

				/*GameFunctionsCustom::SetDirection((MiscExtension::Random(0, 7)));*/
				GameFunctions::InstanceSetRotation(GameFunctions::PlayerNEW_GetMainActorPtr(),MiscExtension::RandomInt(0, 360));
				


			}
			lastMiniMHRotation = GetTickCount();
		}
		if ((GetTickCount() - lastTimeStonesArrowShow) > 4000 && Settings::MainInfoStonesViewportShow)
		{
			DWORD vid = GameFunctionsCustom::GetCloseObject(OBJECT_STONE);
			if (vid > 0)
			{
				GameFunctionsCustom::PlayerShowTargetArrow(vid, 3);

				lastTimeStonesArrowShow = GetTickCount();
			}

		}

	}


	void MPPotion() {
		int slot = GameFunctionsCustom::FindItemSlotInInventory(27004);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27005);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27006);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
#ifdef METINPL
		slot = GameFunctionsCustom::FindItemSlotInInventory(27008);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
#endif
	}
	void Potions()
	{
		if (Settings::MiniMHUseRedPotion)
		{
			if (GameFunctionsCustom::GetHpProcentageStatus() < Settings::MiniMHUseRedPotionValue)
			{
				if (DynamicTimer::CheckAutoSet("HPPotion", Settings::MiniMHUseRedPotionSpeed))
				{
					HPPotion();
				}

			}
		}
		if (Settings::MiniMHUseBluePotion)
		{
			if (GameFunctionsCustom::GetMpProcentageStatus() < Settings::MiniMHUseBluePotionValue)
			{
				if (DynamicTimer::CheckAutoSet("MPPotion", Settings::MiniMHUseBluePotionSpeed))
				{
					MPPotion();
				}
			}
		}
	}
	void HPPotion() 
	{
		int slot = GameFunctionsCustom::FindItemSlotInInventory(27001);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27002);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
		slot = GameFunctionsCustom::FindItemSlotInInventory(27003);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
#ifdef METINPL
		slot = GameFunctionsCustom::FindItemSlotInInventory(27007);
		if (slot != -1)
		{
			GameFunctions::NetworkStreamSendItemUsePacket(TItemPos(INVENTORY, slot));
			return;
		}
#endif
	}












};

