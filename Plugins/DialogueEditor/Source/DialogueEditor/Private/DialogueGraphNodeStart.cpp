


#include "DialogueGraphNodeStart.h"

UEdGraphPin* UDialogueGraphNodeStart::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Outputs");
	FName SubCategory = TEXT("StartPin");

	UEdGraphPin* Pin = CreatePin(
		Direction, 
		Category, 
		Name
	);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}
