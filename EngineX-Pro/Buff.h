
#pragma once
class Buff : public IAbstractModuleBase, public Singleton<Buff>
{

	class TargetBuff
	{

	public:
		TargetBuff(string targetName, DWORD  targetVid)
		{
			this->targetName = targetName;
			this->targetVid = targetVid;
		}
		DWORD lastTimeBuff_1 = 0;
		DWORD lastTimeBuff_2 = 0;
		DWORD lastTimeBuff_3 = 0;
		string targetName = "";
		DWORD targetVid = 0;
		bool guiLineIsSelected = false;
	};



private:
	map<DWORD , std::shared_ptr<TargetBuff>> targetList;
	
	DWORD selectedTargetLine=0;
	
	DirectTexture textureSkill_1;
	DirectTexture textureSkill_2;
	DirectTexture textureSkill_3;


	void  SetJobRaceTextures(int job, int race)
	{
		if (!GameFunctionsCustom::PlayerIsInstance())
		{
			job = 0;
			race = 0;
		}
		if (job == 0)
		{
			textureSkill_1 = MainForm::skill_none;
			textureSkill_2 = MainForm::skill_none;
			textureSkill_3 = MainForm::skill_none;
			return;
		}
		else
		{

		}
		if (race == 0 || race == 4)
		{
			if (job == 1)
			{

				textureSkill_1 = MainForm::skill_none;
				textureSkill_2 = MainForm::skill_none;
				textureSkill_3 = MainForm::skill_none;
			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::skill_none;
				textureSkill_2 = MainForm::skill_none;
				textureSkill_3 = MainForm::skill_none;
			}
		}

		if (race == 1 || race == 5)
		{
			if (job == 1)
			{
				textureSkill_1 = MainForm::skill_none;
				textureSkill_2 = MainForm::skill_none;
				textureSkill_3 = MainForm::skill_none;
			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::skill_none;
				textureSkill_2 = MainForm::skill_none;
				textureSkill_3 = MainForm::skill_none;
			}
		}

		if (race == 2 || race == 6)
		{
			if (job == 1)
			{
				textureSkill_1 = MainForm::skill_none;
				textureSkill_2 = MainForm::skill_none;
				textureSkill_3 = MainForm::skill_none;

			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::skill_none;
				textureSkill_2 = MainForm::skill_none;
				textureSkill_3 = MainForm::skill_none;
			}
		}

		if (race == 3 || race == 7)
		{
			if (job == 1)
			{
				textureSkill_1 = MainForm::shaman_d_3;
				textureSkill_2 = MainForm::shaman_d_4;
				textureSkill_3 = MainForm::shaman_d_5;
			}
			if (job == 2)
			{
				textureSkill_1 = MainForm::shaman_h_3;
				textureSkill_2 = MainForm::shaman_h_4;
				textureSkill_3 = MainForm::shaman_h_5;
			}
		}
	}

public:
	virtual void OnStart()
	{
		
		
	}


	virtual void OnStop()
	{
		
	}

	virtual void OnUpdate()
	{
		SetJobRaceTextures(GameFunctions::NetworkStreamGetMainActorSkillGroup(), GameFunctions::PlayerGetRace());
		if (Settings::BUFF_ENABLE)
		{
			if (!GameFunctions::NetworkStreamGetMainActorSkillGroup())
			{
				return;
			}
			if (GameFunctions::PlayerGetRace() == 3 || GameFunctions::PlayerGetRace() == 7)
			{
				
			}
			else
			{
				return;
			}
			if (Settings::BUFF_ENABLE)
			{
				if(DynamicTimer::CheckAutoSet("Skill", 500))
				{
					if (Settings::BUFF_SKILL_1)
					{
						if (DynamicTimer::Check("BuffBotSkill1Time", Settings::BUFF_SKILL_1_TIME * 100))
						{
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if ((GetTickCount() - itor->second.get()->lastTimeBuff_1) > 30000)
								{
									if (GameFunctionsCustom::PlayerGetCharacterDistance(itor->first) < 10000)
									{
										DWORD targetVID = GameFunctionsCustom::GetCharacterVidByName(itor->second.get()->targetName.c_str());
										if (targetVID)
										{
											GameFunctions::PlayerSetTarget(itor->second.get()->targetVid);
											GameFunctionsCustom::UseSkillSlot(4);
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											DynamicTimer::SetTick("BuffBotSkill1Time");
											continue;
										}

										else
										{
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											continue;
										}


									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}



						}
					}


					if (Settings::BUFF_SKILL_2)
					{
						if (DynamicTimer::Check("BuffBotSkill2Time", Settings::BUFF_SKILL_2_TIME * 100))
						{
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if (GetTickCount() - itor->second.get()->lastTimeBuff_2 > 30000)
								{
									if (GameFunctionsCustom::PlayerGetCharacterDistance(itor->first) < 10000)
									{
										DWORD targetVID = GameFunctionsCustom::GetCharacterVidByName(itor->second.get()->targetName.c_str());
										if (targetVID)
										{
											GameFunctions::PlayerSetTarget(itor->second.get()->targetVid);
											GameFunctionsCustom::UseSkillSlot(5);
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											DynamicTimer::SetTick("BuffBotSkill2Time");
											continue;
										}

										else
										{
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											continue;
										}


									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}



						}
					}


					if (Settings::BUFF_SKILL_3)
					{
						if (DynamicTimer::Check("BuffBotSkill3Time", Settings::BUFF_SKILL_3_TIME * 100))
						{
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if (GetTickCount() - itor->second.get()->lastTimeBuff_3 > 30000)
								{
									if (GameFunctionsCustom::PlayerGetCharacterDistance(itor->first) < 10000)
									{
										DWORD targetVID = GameFunctionsCustom::GetCharacterVidByName(itor->second.get()->targetName.c_str());
										if (targetVID)
										{
											GameFunctions::PlayerSetTarget(itor->second.get()->targetVid);
											GameFunctionsCustom::UseSkillSlot(6);
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											DynamicTimer::SetTick("BuffBotSkill3Time");
											continue;
										}

										else
										{
											itor->second.get()->lastTimeBuff_3 = GetTickCount();
											continue;
										}


									}
									else
									{
										continue;
									}
								}
								else
								{
									continue;
								}
							}



						}
					}
				}
				
			}
		}
	}

	void OnRender()
	{
	}

	void OnMenu()
	{

		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
		ImGui::SetNextWindowBgAlpha(0.75f);
		ImGui::BeginChild("BuffSkillsBorder", ImVec2(645, 430), true);
		ImGui::Checkbox("Buff Enable", &Settings::BUFF_ENABLE);
		ImGui::IconButton2(&Settings::BUFF_SKILL_1, "Skill 1", textureSkill_1, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::PushItemWidth(150);  ImGui::InputFloat("Skill 1 Time", &Settings::BUFF_SKILL_3_TIME, 0.100, 1);
		ImGui::IconButton2(&Settings::BUFF_SKILL_2, "Skill 2", textureSkill_2, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::PushItemWidth(150);  ImGui::InputFloat("Skill 2 Time", &Settings::BUFF_SKILL_3_TIME, 0.100, 1);
		ImGui::IconButton2(&Settings::BUFF_SKILL_3, "Skill 3", textureSkill_3, MainForm::skill_on, MainForm::skill_off, ImVec2(32, 32));
		ImGui::SameLine();
		ImGui::PushItemWidth(150);  ImGui::InputFloat("Skill 3 Time", &Settings::BUFF_SKILL_3_TIME, 0.100, 1);

		
		ImGui::BeginChild("BuffTargetList", ImVec2(190, 240), true);
		
		for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
		{
			
			if (ImGui::Selectable(itor->second.get()->targetName.c_str(), itor->second.get()->guiLineIsSelected))
			{
				selectedTargetLine = itor->first;
			}
			else
			{
				
			}


			if (itor->first == selectedTargetLine)
			{
				itor->second.get()->guiLineIsSelected = true;
			}
			else
			{
				itor->second.get()->guiLineIsSelected = false;
			}
		}
	
		ImGui::EndChild();
		ImGui::SameLine();
		if (ImGui::Button("Add"))
		{
			if (!Settings::BUFF_ENABLE)
			{

				DWORD targetVID = GameFunctions::PlayerGetTargetVID();
				if (targetVID)
				{
					int  targetType = GameFunctionsCustom::InstanceGetInstanceTypeByVID(targetVID);
					if (targetType == TYPE_PC)
					{
						string targetName = GameFunctionsCustom::InstanceGetNameStringByVID(GameFunctions::PlayerGetTargetVID());
						if (targetName != GameFunctionsCustom::PlayerGetNameString())
						{
							bool isExistInMap = false;
							for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
							{
								if (itor->second.get()->targetName == targetName)
								{
									isExistInMap = true;
								}

							}
							if (!isExistInMap)
							{
								DWORD emptyLastKey = 0;

								for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
								{

									emptyLastKey = itor->first;
								}
								emptyLastKey++;


								targetList.insert(std::make_pair(emptyLastKey, shared_ptr<TargetBuff >(new TargetBuff(targetName, targetVID))));
							}

						}

					}



				}
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			if (!Settings::BUFF_ENABLE)
			{
				DWORD key = 0;
				for (map<DWORD, std::shared_ptr<TargetBuff>>::iterator itor = targetList.begin(); itor != targetList.end(); itor++)
				{
					if (itor->second.get()->guiLineIsSelected)
					{

						key = itor->first;
					}

				}
				targetList.erase(key);
			}
			
		}
		
		
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}

};
