#pragma once

#include "DialogueNodeType.generated.h"

UENUM()
enum class EDialogueNodeType
{
	Unknown,
	Start,
	Dialogue,
	End,
	Return
};