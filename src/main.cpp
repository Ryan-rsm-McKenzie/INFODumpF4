#include "f4se/GameData.h"  // DataHandler
#include "f4se/PluginAPI.h"  // PluginHandle, F4SEInterface, PluginInfo
#include "f4se_common/f4se_version.h"  // RUNTIME_VERSION

#include <ShlObj.h>  // CSIDL_MYDOCUMENTS

#include "version.h"  // INFODUMPF4_VERSION_VERSTRING

#include "RE/TESTopic.h"  // TESTopic
#include "RE/TESTopicInfo.h"  // TESTopicInfo


static PluginHandle				g_pluginHandle = kPluginHandle_Invalid;
static F4SEMessagingInterface*	g_messaging = 0;


void MessageHandler(F4SEMessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
	case F4SEMessagingInterface::kMessage_GameDataReady:
		if (a_msg->data) {
			DataHandler* dataHandler = *g_dataHandler;
			RE::TESTopic* topic = 0;
			for (UInt32 i = 0; i < dataHandler->arrDIAL.count; ++i) {
				topic = (RE::TESTopic*)dataHandler->arrDIAL[i];
				_MESSAGE("DIAL: %08X", topic->formID);
				for (UInt32 i = 0; i < topic->infoCount; ++i) {
					_MESSAGE("INFO: %08X", topic->infoTopics[i]->formID);
				}
			}
		}
		break;
	}
}


extern "C" {
	bool F4SEPlugin_Query(const F4SEInterface* a_f4se, PluginInfo* a_info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4\\F4SE\\INFODumpF4.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_DebugMessage);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		a_info->infoVersion = PluginInfo::kInfoVersion;
		a_info->name = "INFODumpF4";
		a_info->version = INFODUMPF4_VERSION_MAJOR;

		g_pluginHandle = a_f4se->GetPluginHandle();

		if (a_f4se->isEditor) {
			_FATALERROR("[FATAL ERROR] Loaded in editor, marking as incompatible!\n");
			return false;
		}

		if (a_f4se->runtimeVersion != RUNTIME_VERSION_1_10_120) {
			_FATALERROR("[FATAL ERROR] Unsupported runtime version %08X!\n", a_f4se->runtimeVersion);
			return false;
		}

		return true;
	}


	bool F4SEPlugin_Load(const F4SEInterface* a_f4se)
	{
		g_messaging = (F4SEMessagingInterface*)a_f4se->QueryInterface(kInterface_Messaging);
		if (!g_messaging->RegisterListener(g_pluginHandle, "F4SE", MessageHandler)) {
			_FATALERROR("[FATAL ERROR] Messaging interface registration failed!\n");
			return false;
		}

		return true;
	}
};
