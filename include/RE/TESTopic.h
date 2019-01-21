#pragma once

#include "f4se/GameFormComponents.h"  // TESFullName
#include "f4se/GameForms.h"  // TESForm


namespace RE
{
	class TESTopicInfo;


	class TESTopic :
		public TESForm,		// 00
		public TESFullName	// 20
	{
	public:
		virtual ~TESTopic();	// 00


		// members
		UInt64			unk30;		// 30
		UInt64			unk38;		// 38
		UInt64			unk40;		// 40
		UInt64			unk48;		// 48
		TESTopicInfo**	infoTopics;	// 50
		UInt64			unk58;		// 58
		UInt32			infoCount;	// 60 - TIFC
		UInt32			unk64;		// 60
		UInt64			unk68;		// 68
		UInt64			unk70;		// 70
	};
}
