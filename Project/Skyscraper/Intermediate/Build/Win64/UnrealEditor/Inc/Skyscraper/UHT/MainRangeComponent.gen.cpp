// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/MainGame/Component/Combat/Range/MainRangeComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMainRangeComponent() {}
// Cross Module References
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FRotator();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UAnimInstance_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAnimMontage_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASkyscraperCharacter_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMainRangeComponent();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMainRangeComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(UMainRangeComponent::execCanFire)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->CanFire();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainRangeComponent::execPlayReloadAnim)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->PlayReloadAnim();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainRangeComponent::execBulletReloading)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->BulletReloading();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainRangeComponent::execEnemyFire)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_fBaseDamage);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->EnemyFire(Z_Param_fBaseDamage);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainRangeComponent::execFire)
	{
		P_GET_PROPERTY(FFloatProperty,Z_Param_fBaseDamage);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->Fire(Z_Param_fBaseDamage);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMainRangeComponent::execPlayFireAnim)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->PlayFireAnim();
		P_NATIVE_END;
	}
	void UMainRangeComponent::StaticRegisterNativesUMainRangeComponent()
	{
		UClass* Class = UMainRangeComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "BulletReloading", &UMainRangeComponent::execBulletReloading },
			{ "CanFire", &UMainRangeComponent::execCanFire },
			{ "EnemyFire", &UMainRangeComponent::execEnemyFire },
			{ "Fire", &UMainRangeComponent::execFire },
			{ "PlayFireAnim", &UMainRangeComponent::execPlayFireAnim },
			{ "PlayReloadAnim", &UMainRangeComponent::execPlayReloadAnim },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMainRangeComponent_BulletReloading_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainRangeComponent_BulletReloading_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainRangeComponent_BulletReloading_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainRangeComponent, nullptr, "BulletReloading", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_BulletReloading_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainRangeComponent_BulletReloading_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMainRangeComponent_BulletReloading()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainRangeComponent_BulletReloading_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics
	{
		struct MainRangeComponent_eventCanFire_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((MainRangeComponent_eventCanFire_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(MainRangeComponent_eventCanFire_Parms), &Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainRangeComponent, nullptr, "CanFire", nullptr, nullptr, Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::MainRangeComponent_eventCanFire_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::MainRangeComponent_eventCanFire_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UMainRangeComponent_CanFire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainRangeComponent_CanFire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics
	{
		struct MainRangeComponent_eventEnemyFire_Parms
		{
			float fBaseDamage;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_fBaseDamage;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::NewProp_fBaseDamage = { "fBaseDamage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainRangeComponent_eventEnemyFire_Parms, fBaseDamage), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::NewProp_fBaseDamage,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainRangeComponent, nullptr, "EnemyFire", nullptr, nullptr, Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::MainRangeComponent_eventEnemyFire_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::MainRangeComponent_eventEnemyFire_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UMainRangeComponent_EnemyFire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainRangeComponent_EnemyFire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainRangeComponent_Fire_Statics
	{
		struct MainRangeComponent_eventFire_Parms
		{
			float fBaseDamage;
		};
		static const UECodeGen_Private::FFloatPropertyParams NewProp_fBaseDamage;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::NewProp_fBaseDamage = { "fBaseDamage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(MainRangeComponent_eventFire_Parms, fBaseDamage), METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::NewProp_fBaseDamage,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainRangeComponent, nullptr, "Fire", nullptr, nullptr, Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::PropPointers), sizeof(Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::MainRangeComponent_eventFire_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::MainRangeComponent_eventFire_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UMainRangeComponent_Fire()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainRangeComponent_Fire_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainRangeComponent, nullptr, "PlayFireAnim", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMainRangeComponent, nullptr, "PlayReloadAnim", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMainRangeComponent);
	UClass* Z_Construct_UClass_UMainRangeComponent_NoRegister()
	{
		return UMainRangeComponent::StaticClass();
	}
	struct Z_Construct_UClass_UMainRangeComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnerCharacter_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwnerCharacter;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentFireCoolTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentFireCoolTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FireMaxCoolTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_FireMaxCoolTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentReloadCoolTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentReloadCoolTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReloadMaxCoolTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ReloadMaxCoolTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReloadSpeedTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_ReloadSpeedTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CurrentBulletCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentBulletCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_BulletMaxCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_BulletMaxCount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RecoilAboveAmount_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RecoilAboveAmount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RecoilBesideAmount_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RecoilBesideAmount;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RecoilTime_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RecoilTime;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RecoilTargetRot_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_RecoilTargetRot;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RecoilSpeed_MetaData[];
#endif
		static const UECodeGen_Private::FFloatPropertyParams NewProp_RecoilSpeed;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OwnerAnimInstance_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_OwnerAnimInstance;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AM_Fire_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_AM_Fire;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AM_Reload_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_AM_Reload;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IMC_RangeInput_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IMC_RangeInput;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IA_Fire_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IA_Fire;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IA_Reload_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IA_Reload;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMainRangeComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UMainRangeComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMainRangeComponent_BulletReloading, "BulletReloading" }, // 1943298676
		{ &Z_Construct_UFunction_UMainRangeComponent_CanFire, "CanFire" }, // 77920913
		{ &Z_Construct_UFunction_UMainRangeComponent_EnemyFire, "EnemyFire" }, // 1365291990
		{ &Z_Construct_UFunction_UMainRangeComponent_Fire, "Fire" }, // 907041525
		{ &Z_Construct_UFunction_UMainRangeComponent_PlayFireAnim, "PlayFireAnim" }, // 3339285894
		{ &Z_Construct_UFunction_UMainRangeComponent_PlayReloadAnim, "PlayReloadAnim" }, // 1194829875
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "BlueprintType", "true" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerCharacter_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Owner Character Variable\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Owner Character Variable" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerCharacter = { "OwnerCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, OwnerCharacter), Z_Construct_UClass_ASkyscraperCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerCharacter_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerCharacter_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentFireCoolTime_MetaData[] = {
		{ "Category", "Fire" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == MainRange Variable\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== MainRange Variable" },
#endif
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentFireCoolTime = { "CurrentFireCoolTime", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, CurrentFireCoolTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentFireCoolTime_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentFireCoolTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_FireMaxCoolTime_MetaData[] = {
		{ "Category", "Fire" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_FireMaxCoolTime = { "FireMaxCoolTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, FireMaxCoolTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_FireMaxCoolTime_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_FireMaxCoolTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentReloadCoolTime_MetaData[] = {
		{ "Category", "Reload" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentReloadCoolTime = { "CurrentReloadCoolTime", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, CurrentReloadCoolTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentReloadCoolTime_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentReloadCoolTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadMaxCoolTime_MetaData[] = {
		{ "Category", "Reload" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadMaxCoolTime = { "ReloadMaxCoolTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, ReloadMaxCoolTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadMaxCoolTime_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadMaxCoolTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadSpeedTime_MetaData[] = {
		{ "Category", "Reload" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadSpeedTime = { "ReloadSpeedTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, ReloadSpeedTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadSpeedTime_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadSpeedTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentBulletCount_MetaData[] = {
		{ "Category", "Bullet" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentBulletCount = { "CurrentBulletCount", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, CurrentBulletCount), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentBulletCount_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentBulletCount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_BulletMaxCount_MetaData[] = {
		{ "Category", "Bullet" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_BulletMaxCount = { "BulletMaxCount", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, BulletMaxCount), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_BulletMaxCount_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_BulletMaxCount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilAboveAmount_MetaData[] = {
		{ "Category", "Recoil" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilAboveAmount = { "RecoilAboveAmount", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, RecoilAboveAmount), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilAboveAmount_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilAboveAmount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilBesideAmount_MetaData[] = {
		{ "Category", "Recoil" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilBesideAmount = { "RecoilBesideAmount", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, RecoilBesideAmount), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilBesideAmount_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilBesideAmount_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTime_MetaData[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTime = { "RecoilTime", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, RecoilTime), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTime_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTime_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTargetRot_MetaData[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTargetRot = { "RecoilTargetRot", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, RecoilTargetRot), Z_Construct_UScriptStruct_FRotator, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTargetRot_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTargetRot_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilSpeed_MetaData[] = {
		{ "Category", "Recoil" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilSpeed = { "RecoilSpeed", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, RecoilSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilSpeed_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilSpeed_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerAnimInstance_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Anim Variable\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Anim Variable" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerAnimInstance = { "OwnerAnimInstance", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, OwnerAnimInstance), Z_Construct_UClass_UAnimInstance_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerAnimInstance_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerAnimInstance_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Fire_MetaData[] = {
		{ "Category", "AnimMontage" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Fire = { "AM_Fire", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, AM_Fire), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Fire_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Fire_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Reload_MetaData[] = {
		{ "Category", "AnimMontage" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Reload = { "AM_Reload", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, AM_Reload), Z_Construct_UClass_UAnimMontage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Reload_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Reload_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IMC_RangeInput_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Input Action And Input Mapping Context\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Input Action And Input Mapping Context" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IMC_RangeInput = { "IMC_RangeInput", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, IMC_RangeInput), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IMC_RangeInput_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IMC_RangeInput_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Fire_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Fire = { "IA_Fire", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, IA_Fire), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Fire_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Fire_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Reload_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/Range/MainRangeComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Reload = { "IA_Reload", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMainRangeComponent, IA_Reload), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Reload_MetaData), Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Reload_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMainRangeComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerCharacter,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentFireCoolTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_FireMaxCoolTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentReloadCoolTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadMaxCoolTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_ReloadSpeedTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_CurrentBulletCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_BulletMaxCount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilAboveAmount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilBesideAmount,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTime,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilTargetRot,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_RecoilSpeed,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_OwnerAnimInstance,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Fire,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_AM_Reload,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IMC_RangeInput,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Fire,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMainRangeComponent_Statics::NewProp_IA_Reload,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMainRangeComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMainRangeComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMainRangeComponent_Statics::ClassParams = {
		&UMainRangeComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UMainRangeComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UMainRangeComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMainRangeComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UMainRangeComponent()
	{
		if (!Z_Registration_Info_UClass_UMainRangeComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMainRangeComponent.OuterSingleton, Z_Construct_UClass_UMainRangeComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMainRangeComponent.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<UMainRangeComponent>()
	{
		return UMainRangeComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMainRangeComponent);
	UMainRangeComponent::~UMainRangeComponent() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_Range_MainRangeComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_Range_MainRangeComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMainRangeComponent, UMainRangeComponent::StaticClass, TEXT("UMainRangeComponent"), &Z_Registration_Info_UClass_UMainRangeComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMainRangeComponent), 3682072647U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_Range_MainRangeComponent_h_2768402129(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_Range_MainRangeComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_Range_MainRangeComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
