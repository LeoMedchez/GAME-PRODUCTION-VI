#include "BaseGM.h"
#include "BasePC.h"
#include "BaseHUD.h"

ABaseGM::ABaseGM()
	:Super()
{
	PlayerControllerClass = ABasePC::StaticClass();

	HUDClass = ABaseHUD::StaticClass();
}
