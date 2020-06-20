#pragma once
class MainDungs : public IAbstractModuleBase, public Singleton<MainDungs>
{
private:
	enum DungeonType
	{
		DT = 0,
	};
public:
	int Phase = 0;
	string MapName = "";

	int Floor2Step = 0;
	vector<D3DVECTOR> Floor2Positions;
	int Floor5Step = 0;
	vector<D3DVECTOR> Floor5Positions;

	void DemonTowerStart()
	{
		if (Phase == 0) {
			if (MapName == "metin2_map_deviltower") {
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
				Phase = 1;
			}
			else {
				DWORD DemonTowerGuard = GameFunctionsCustom::GetCloseObjectByVnum(20348);
				if (!DemonTowerGuard)
				{
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Brak NPC!");
					return;
				}
				GameFunctions::NetworkStreamSendOnClickPacket(DemonTowerGuard);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				GameFunctions::NetworkStreamSendScriptAnswerPacket(0);
				Phase = 1;
				Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 1!");
			}
		}
	}

	void OnStart()
	{
		Floor2Positions = {
			D3DVECTOR{13629, 38768, 0}, D3DVECTOR{16983, 37937, 0}, D3DVECTOR{20189, 39168, 0},
			D3DVECTOR{21150, 42453, 0}, D3DVECTOR{20071, 45562, 0}, D3DVECTOR{17547, 46444, 0},
			D3DVECTOR{14887, 46372, 0}, D3DVECTOR{12801, 45006, 0}, D3DVECTOR{11794, 42202, 0},
			D3DVECTOR{12082, 39900, 0}, D3DVECTOR{13664, 38678, 0}
		};
		Floor5Positions = {
			D3DVECTOR{40550, 39705, 0}, D3DVECTOR{41592, 40065, 0}, D3DVECTOR{42419, 41539, 0},
			D3DVECTOR{42347, 43409, 0}, D3DVECTOR{40765, 44955, 0}, D3DVECTOR{38320, 44847, 0},
			D3DVECTOR{37062, 43013, 0}, D3DVECTOR{37278, 41144, 0}, D3DVECTOR{38680, 40317, 0},
			D3DVECTOR{40442, 39705, 0}
		};
		Settings::DUNGEON_BOT = true;
		D3DVECTOR CharPos;
		GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
		LONG GlobalX = CharPos.x;
		LONG GlobalY = CharPos.y;
		GameFunctions::BackgroundLocalPositionToGlobalPosition(GlobalX, GlobalY);
		MapName = GetStr((DWORD)GameFunctions::BackgroundGlobalPositionToMapInfo(GlobalX, GlobalY)->name);
		Logger::Add(Logger::MAIN, true, Logger::WHITE, MapName.c_str());
		switch (Settings::DUNGEON_TYPE) {
		case DungeonType::DT:
			DemonTowerStart();
			break;
		}
	}

	void OnStop()
	{
		Settings::DUNGEON_BOT = false;
		MapName = "";
		Floor2Step = 0;
		Floor5Step = 0;

	}

	static void RestartDT()
	{
		MainDungs::Instance().DemonTowerStart();
	}

	void UpdateDT()
	{
		switch (Phase) 
		{
			case 1: {
				D3DVECTOR CharPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
				bool Floor2 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 16431, 41912, 0 }, 8000);
				if (Floor2)
				{
					Phase = 2;
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 2!");
					DelayActions::Clear();
					return;
				}

				DWORD MetinTwardosci = GameFunctionsCustom::GetCloseObjectByVnum(8015);
				if (!MetinTwardosci)
				{
					return;
				}
				D3DVECTOR MetinPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(MetinTwardosci), &MetinPos);
				vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, MetinPos);
				int i = 0;
				for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
				{
					bool InDistance = MathExtension::PointInCircle(CharPos, MetinPos, 400);
					if (!InDistance)
					{
						DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
					}
					i++;
				}
				break;
			}
			case 2: {
				D3DVECTOR CharPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
				bool Floor3 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 17807, 18682, 0 }, 8000);
				if (Floor3)
				{
					Phase = 3;
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 3!");
					DelayActions::Clear();
					return;
				}

				bool InDistance = MathExtension::PointInCircle(CharPos, Floor2Positions[Floor2Step], 400);
				if (InDistance)
				{
					Floor2Step++;
				}
				if (Floor2Step == Floor2Positions.size())
				{
					reverse(Floor2Positions.begin(), Floor2Positions.end());
					Floor2Step = 0;
				}
				if (!InDistance)
				{
					vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, Floor2Positions[Floor2Step]);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
					{
						bool InDistance = MathExtension::PointInCircle(CharPos, Floor2Positions[Floor2Step], 400);
						if (!InDistance)
						{
							DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
						}
						i++;
					}
				}
				break;
			}
			case 3: {
				Floor2Step = 0;
				D3DVECTOR CharPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
				bool Floor4 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 39402, 65544, 0 }, 6500);
				if (Floor4)
				{
					Phase = 4;
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 4!");
					DelayActions::Clear();
					return;
				}

				DWORD KrolDemonow = GameFunctionsCustom::GetCloseObjectByVnum(1091);
				if (!KrolDemonow)
				{
					return;
				}
				D3DVECTOR MobPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(KrolDemonow), &MobPos);
				vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, MobPos);
				int i = 0;
				for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
				{
					bool InDistance = MathExtension::PointInCircle(CharPos, MobPos, 400);
					if (!InDistance)
					{
						DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
					}
					i++;
				}
				break;
			}
			case 4: {
				D3DVECTOR CharPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
				bool Floor5 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 39572, 42738, 0 }, 6500);
				if (Floor5)
				{
					Phase = 5;
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 5!");
					DelayActions::Clear();
					return;
				}

				DWORD Metin = GameFunctionsCustom::GetCloseObject(OBJECT_STONE);
				if (!Metin)
				{
					return;
				}
				D3DVECTOR MetinPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(Metin), &MetinPos);
				vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, MetinPos);
				int i = 0;
				for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
				{
					bool InDistance = MathExtension::PointInCircle(CharPos, MetinPos, 400);
					if (!InDistance)
					{
						DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
					}
					i++;
				}
				break;
			}
			case 5: {
				D3DVECTOR CharPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
				bool Floor6 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 39855, 19264, 0 }, 6500);
				if (Floor6)
				{
					Phase = 6;
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 6!");
					DelayActions::Clear();
					return;
				}
				//Przeciaganie pieczeci
				int kamien_slot = GameFunctionsCustom::FindItemSlotInInventory(50084);
				if (kamien_slot != -1) {
					DWORD Pieczec = GameFunctionsCustom::GetCloseObjectByVnum(20073);
					if (Pieczec)
					{
						D3DVECTOR MetinPos;
						GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(Pieczec), &MetinPos);
						vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, MetinPos);
						int i = 0;
						for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
						{
							bool InDistance = MathExtension::PointInCircle(CharPos, MetinPos, 400);
							if (!InDistance)
							{
								DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
							}
							else {
								GameFunctions::NetworkStreamSendGiveItemPacket(Pieczec, TItemPos{INVENTORY, (WORD)kamien_slot}, 1);
							}
							i++;
						}
					}
				}
				//Bicie
				bool InDistance = MathExtension::PointInCircle(CharPos, Floor5Positions[Floor5Step], 400);
				if (InDistance)
				{
					Floor5Step++;
				}
				if (Floor5Step == Floor5Positions.size())
				{
					reverse(Floor5Positions.begin(), Floor5Positions.end());
					Floor5Step = 0;
				}
				if (!InDistance)
				{
					vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, Floor5Positions[Floor5Step]);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
					{
						bool InDistance = MathExtension::PointInCircle(CharPos, Floor5Positions[Floor5Step], 400);
						if (!InDistance)
						{
							DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
						}
						i++;
					}
				}
				break;
			}
			case 6: {
				Floor5Step = 0;
				D3DVECTOR CharPos;
				GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::PlayerNEW_GetMainActorPtr(), &CharPos);
				bool Floor7 = MathExtension::PointInCircle(CharPos, D3DVECTOR{ 0, 0, 0 }, 6500);
				if (Floor7)
				{
					Phase = 7;
					Logger::Add(Logger::MAIN, true, Logger::WHITE, "Pietro 7!");
					DelayActions::Clear();
					return;
				}

				DWORD ElitKrolDemonow = GameFunctionsCustom::GetCloseObjectByVnum(1092);
				if (ElitKrolDemonow)
				{
					D3DVECTOR MobPos;
					GameFunctions::InstanceBaseNEW_GetPixelPosition(GameFunctions::CharacterManagerGetInstancePtr(ElitKrolDemonow), &MobPos);
					vector< D3DVECTOR> gf = MiscExtension::DivideTwoPointsByDistance(400, CharPos, MobPos);
					int i = 0;
					for (vector< D3DVECTOR>::iterator it = gf.begin(); it != gf.end(); ++it)
					{
						bool InDistance = MathExtension::PointInCircle(CharPos, MobPos, 400);
						if (!InDistance)
						{
							DelayActions::AppendBlock(false, 34 * (i + 1), &GameFunctionsCustom::Teleport, D3DVECTOR{ it->x, it->y, it->z });
						}
						i++;
					}
					return;
				}
				else {
					DWORD Kowal1 = GameFunctionsCustom::GetCloseObjectByVnum(20074);
					DWORD Kowal2 = GameFunctionsCustom::GetCloseObjectByVnum(20075);
					DWORD Kowal3 = GameFunctionsCustom::GetCloseObjectByVnum(20076);
					if (Kowal1 != 0 || Kowal2 != 0 || Kowal3 != 0) {
						int lastSlot = GameFunctionsCustom::GetCharSlotByName(GameFunctions::PlayerGetName());
						if (lastSlot != -1)
						{
							GameFunctions::NetworkStreamConnectGameServer(lastSlot);
						}
						Phase = 0;
						DelayActions::AppendBlock(false, 5000, &RestartDT);
					}
				}
				break;
			}
			case 7: {

				break;
			}
		}
	}

	void OnUpdate()
	{
		if (Settings::DUNGEON_BOT) 
		{
			if (GameFunctionsCustom::PlayerIsInstance()) {
				switch (Settings::DUNGEON_TYPE) {
				case DungeonType::DT:
					UpdateDT();
					break;
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
		ImGui::BeginChild("DungBot", ImVec2(645, 110), true);
		if (ImGui::Checkbox("On/Off", &Settings::DUNGEON_BOT)) {
			if (Settings::DUNGEON_BOT == true)
			{
				OnStart();
			}
			else
			{
				OnStop();
			}
		}
		ImGui::RadioButton("VIDGAR DT", &Settings::DUNGEON_TYPE, 0);
		ImGui::EndChild();
		ImGui::PopStyleVar();
	}
};