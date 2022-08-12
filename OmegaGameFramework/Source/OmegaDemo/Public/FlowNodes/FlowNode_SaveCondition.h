// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "UObject/Object.h"
#include "FlowNode_SaveCondition.generated.h"

/**
 * 
 */
UCLASS()
class OMEGADEMO_API UFlowNode_SaveCondition : public UFlowNode
{
	GENERATED_BODY()

public:
public:

	UFlowNode_SaveCondition();
	
	UPROPERTY(EditAnywhere, Category="Choice")
	FSaveCon
	UPROPERTY(EditAnywhere, Category="Choice")
	TSubclassOf<AOmegaLinearChoiceInstance> InstanceClass = AOmegaLinearChoiceInstance::StaticClass();

	UPROPERTY()
	AOmegaLinearChoiceInstance* ChoiceInst;
	UFUNCTION()
	void LocalChoiceSelect(UOmegaLinearChoice* Choice, int32 Index);

	
	virtual bool CanUserAddOutput() const override;
	virtual void ExecuteInput(const FName& PinName) override;
};
