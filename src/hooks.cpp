#include "hooks.h"

namespace HookLineAndSinker
{
	typedef void(ScreenshotMessageSig)(void*, const char*, const char*, bool);
	REL::Relocation<ScreenshotMessageSig> OriginalFunction;

	void HookedShowHUDMessage(void*, const char*, const char*, bool)
	{
		return;
	}

	void RegisterHooks(F4SE::Trampoline& trampoline) {
		REL::Relocation<ScreenshotMessageSig> screenshotTaken{ REL::ID(919230), 0xCA };     // screenshot taken
		REL::Relocation<ScreenshotMessageSig> copiedToClipboard{ REL::ID(919230), 0x137 };  // copied to clipboard
		OriginalFunction = trampoline.write_call<5>(screenshotTaken.address(), &HookedShowHUDMessage);
		OriginalFunction = trampoline.write_call<5>(copiedToClipboard.address(), &HookedShowHUDMessage);
	}
}
