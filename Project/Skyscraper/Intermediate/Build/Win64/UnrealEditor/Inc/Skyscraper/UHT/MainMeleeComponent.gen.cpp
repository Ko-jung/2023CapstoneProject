// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/MainGame/Component/MainMeleeComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainMeleeComponent() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASkyscraperCharacter_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMainMeleeComponent();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMainMeleeComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(UMainMeleeComponent::execOnBlendOutMeleeAttack)
	{
		P_GET_OBJECT(UAnimMontage,Z_Param_Montage);
		P_GET_UBOOL(Z_Param_bInterrupted);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnBlendOutMeleeAttack(Z_Param_Montage,Z_Param_bInterrupted);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainMeleeComponent::execCreateAttackArea)
	{
		P_GET_STRUCT(FVector,Z_Param_vHitSize);
		P_GET_PROPERTY(FFloatProperty,Z_Param_fStiffnessTime);
		P_GET_PROPERTY(FFloatProperty,Z_Param_fBaseDamage);
		P_GET_UBOOL(Z_Param_bDoDown);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CreateAttackArea(Z_Param_vHitSize,Z_Param_fStiffnessTime,Z_Param_fBaseDamage,Z_Param_bDoDown);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainMeleeComponent::execAttack)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Attack();
		P_NATIVE_END;
	}
	void UMainMeleeComponent::StaticRegisterNativesUMainMeleeComponent()
	{
		UClass* Class = UMainMeleeComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "Attack", &UMainMeleeComponent::execAttack },
			{ "CreateAttackArea", &UMainMeleeComponent::execCreateAttackArea },
			{ "OnBlendOutMeleeAttack", &UMainMeleeComponent::execOnBlendOutMeleeAttack },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMainMeleeComponent_Attack_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainMeleeComponent_Attack_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Do attack action by anim montage anim notify\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Do attack action by anim montage anim notify" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainMeleeComponent_Attack_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainMeleeComponent, nullptr, "Attack", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_Attack_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainMeleeComponent_Attack_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMainMeleeComponent_Attack()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainMeleeComponent_Attack_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics
	{
		struct MainMeleeComponent_eventCreateAttackArea_Parms
		{
			FVector vHitSize;
			float fStiffnessTime;
			float fBaseDamage;
			bool bDoDown;
		};
		static const UECodeGen_Private::FStructPropertyParams NewProp_vHitSize;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_fStiffnessTime;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_fBaseDamage;
		static void NewProp_bDoDown_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bDoDown;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_vHitSize = { "vHitSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainMeleeComponent_eventCreateAttackArea_Parms, vHitSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_fStiffnessTime = { "fStiffnessTime", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainMeleeComponent_eventCreateAttackArea_Parms, fStiffnessTime), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_fBaseDamage = { "fBaseDamage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainMeleeComponent_eventCreateAttackArea_Parms, fBaseDamage), METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_bDoDown_SetBit(void* Obj)
	{
		((MainMeleeComponent_eventCreateAttackArea_Parms*)Obj)->bDoDown = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_bDoDown = { "bDoDown", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MainMeleeComponent_eventCreateAttackArea_Parms), &Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_bDoDown_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_vHitSize,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_fStiffnessTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_fBaseDamage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::NewProp_bDoDown,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "//TODO: Refactoring for team not damaged\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "TODO: Refactoring for team not damaged" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainMeleeComponent, nullptr, "CreateAttackArea", nullptr, nullptr, Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::MainMeleeComponent_eventCreateAttackArea_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04820401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::MainMeleeComponent_eventCreateAttackArea_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics
	{
		struct MainMeleeComponent_eventOnBlendOutMeleeAttack_Parms
		{
			UAnimMontage* Montage;
			bool bInterrupted;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Montage;
		static void NewProp_bInterrupted_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bInterrupted;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::NewProp_Montage = { "Montage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainMeleeComponent_eventOnBlendOutMeleeAttack_Parms, Montage), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::NewProp_bInterrupted_SetBit(void* Obj)
	{
		((MainMeleeComponent_eventOnBlendOutMeleeAttack_Parms*)Obj)->bInterrupted = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::NewProp_bInterrupted = { "bInterrupted", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MainMeleeComponent_eventOnBlendOutMeleeAttack_Parms), &Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::NewProp_bInterrupted_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::NewProp_Montage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::NewProp_bInterrupted,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == On Blend Out attack montage\n// To link delegate (OnMontageBlendingOut);\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== On Blend Out attack montage\nTo link delegate (OnMontageBlendingOut);" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainMeleeComponent, nullptr, "OnBlendOutMeleeAttack", nullptr, nullptr, Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::MainMeleeComponent_eventOnBlendOutMeleeAttack_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::MainMeleeComponent_eventOnBlendOutMeleeAttack_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMainMeleeComponent);
	UClass* Z_Construct_UClass_UMainMeleeComponent_NoRegister()
	{
		return UMainMeleeComponent::StaticClass();
	}
	struct Z_Construct_UClass_UMainMeleeComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MeleeComboAnimMontage_ValueProp;
		static const UECodeGen_Private::FIntPropertyParams NewProp_MeleeComboAnimMontage_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeleeComboAnimMontage_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_MeleeComboAnimMontage;
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackTime_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AttackTime_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_AttackTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AnimationMovementDistance_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_AnimationMovementDistance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeleeComboCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MeleeComboCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CanAttack_MetaData[];
#endif
		static void NewProp_CanAttack_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_CanAttack;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastAttackClickTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_LastAttackClickTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnerAnimInstance_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwnerAnimInstance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnerCharacter_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwnerCharacter;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMainMeleeComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UMainMeleeComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMainMeleeComponent_Attack, "Attack" }, // 3375881145
		{ &Z_Construct_UFunction_UMainMeleeComponent_CreateAttackArea, "CreateAttackArea" }, // 3994937880
		{ &Z_Construct_UFunction_UMainMeleeComponent_OnBlendOutMeleeAttack, "OnBlendOutMeleeAttack" }, // 1574295209
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "MainGame/Component/MainMeleeComponent.h" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_ValueProp = { "MeleeComboAnimMontage", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_Key_KeyProp = { "MeleeComboAnimMontage_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_MetaData[] = {
		{ "Category", "Components" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage = { "MeleeComboAnimMontage", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, MeleeComboAnimMontage), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_MetaData) };
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime_Inner = { "AttackTime", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime_MetaData[] = {
		{ "Category", "AnimMontage" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime = { "AttackTime", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, AttackTime), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AnimationMovementDistance_MetaData[] = {
		{ "Category", "MotionWarping" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AnimationMovementDistance = { "AnimationMovementDistance", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, AnimationMovementDistance), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AnimationMovementDistance_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AnimationMovementDistance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboCount_MetaData[] = {
		{ "Category", "ComboSystem" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboCount = { "MeleeComboCount", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, MeleeComboCount), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboCount_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboCount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack_MetaData[] = {
		{ "Category", "ComboSystem" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	void Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack_SetBit(void* Obj)
	{
		((UMainMeleeComponent*)Obj)->CanAttack = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack = { "CanAttack", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UMainMeleeComponent), &Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_LastAttackClickTime_MetaData[] = {
		{ "Category", "ComboSystem" },
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_LastAttackClickTime = { "LastAttackClickTime", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, LastAttackClickTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_LastAttackClickTime_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_LastAttackClickTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerAnimInstance_MetaData[] = {
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerAnimInstance = { "OwnerAnimInstance", nullptr, (EPropertyFlags)0x0040000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, OwnerAnimInstance), Z_Construct_UClass_UAnimInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerAnimInstance_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerAnimInstance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerCharacter_MetaData[] = {
		{ "ModuleRelativePath", "MainGame/Component/MainMeleeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerCharacter = { "OwnerCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainMeleeComponent, OwnerCharacter), Z_Construct_UClass_ASkyscraperCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerCharacter_MetaData), Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerCharacter_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMainMeleeComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboAnimMontage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AttackTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_AnimationMovementDistance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_MeleeComboCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_CanAttack,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_LastAttackClickTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerAnimInstance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainMeleeComponent_Statics::NewProp_OwnerCharacter,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMainMeleeComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMainMeleeComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMainMeleeComponent_Statics::ClassParams = {
		&UMainMeleeComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UMainMeleeComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UMainMeleeComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainMeleeComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UMainMeleeComponent()
	{
		if (!Z_Registration_Info_UClass_UMainMeleeComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMainMeleeComponent.OuterSingleton, Z_Construct_UClass_UMainMeleeComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMainMeleeComponent.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<UMainMeleeComponent>()
	{
		return UMainMeleeComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMainMeleeComponent);
	UMainMeleeComponent::~UMainMeleeComponent() {}
	struct Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_MainGame_Component_MainMeleeComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_MainGame_Component_MainMeleeComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMainMeleeComponent, UMainMeleeComponent::StaticClass, TEXT("UMainMeleeComponent"), &Z_Registration_Info_UClass_UMainMeleeComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMainMeleeComponent), 2089258191U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_MainGame_Component_MainMeleeComponent_h_4130544270(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_MainGame_Component_MainMeleeComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_MainGame_Component_MainMeleeComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
