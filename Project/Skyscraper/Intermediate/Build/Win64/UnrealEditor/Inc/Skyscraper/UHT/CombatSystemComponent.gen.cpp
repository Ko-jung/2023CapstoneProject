// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/MainGame/Component/Combat/CombatSystemComponent.h"
#include "InputActionValue.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCombatSystemComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction_NoRegister();
	ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext_NoRegister();
	ENHANCEDINPUT_API UScriptStruct* Z_Construct_UScriptStruct_FInputActionValue();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASkyscraperCharacter_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UCombatSystemComponent();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UCombatSystemComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(UCombatSystemComponent::execLockOn)
	{
		P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->LockOn(Z_Param_Out_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCombatSystemComponent::execSwapToRangeWeapon)
	{
		P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SwapToRangeWeapon(Z_Param_Out_Value);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCombatSystemComponent::execSwapToMeleeWeapon)
	{
		P_GET_STRUCT_REF(FInputActionValue,Z_Param_Out_Value);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SwapToMeleeWeapon(Z_Param_Out_Value);
		P_NATIVE_END;
	}
	void UCombatSystemComponent::StaticRegisterNativesUCombatSystemComponent()
	{
		UClass* Class = UCombatSystemComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "LockOn", &UCombatSystemComponent::execLockOn },
			{ "SwapToMeleeWeapon", &UCombatSystemComponent::execSwapToMeleeWeapon },
			{ "SwapToRangeWeapon", &UCombatSystemComponent::execSwapToRangeWeapon },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics
	{
		struct CombatSystemComponent_eventLockOn_Parms
		{
			FInputActionValue Value;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatSystemComponent_eventLockOn_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::NewProp_Value_MetaData), Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::NewProp_Value_MetaData) }; // 1693336646
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCombatSystemComponent, nullptr, "LockOn", nullptr, nullptr, Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::CombatSystemComponent_eventLockOn_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::CombatSystemComponent_eventLockOn_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCombatSystemComponent_LockOn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatSystemComponent_LockOn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics
	{
		struct CombatSystemComponent_eventSwapToMeleeWeapon_Parms
		{
			FInputActionValue Value;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatSystemComponent_eventSwapToMeleeWeapon_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::NewProp_Value_MetaData), Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::NewProp_Value_MetaData) }; // 1693336646
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Input action function\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Input action function" },
#endif
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCombatSystemComponent, nullptr, "SwapToMeleeWeapon", nullptr, nullptr, Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::CombatSystemComponent_eventSwapToMeleeWeapon_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::CombatSystemComponent_eventSwapToMeleeWeapon_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics
	{
		struct CombatSystemComponent_eventSwapToRangeWeapon_Parms
		{
			FInputActionValue Value;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::NewProp_Value_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(CombatSystemComponent_eventSwapToRangeWeapon_Parms, Value), Z_Construct_UScriptStruct_FInputActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::NewProp_Value_MetaData), Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::NewProp_Value_MetaData) }; // 1693336646
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::NewProp_Value,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCombatSystemComponent, nullptr, "SwapToRangeWeapon", nullptr, nullptr, Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::PropPointers), sizeof(Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::CombatSystemComponent_eventSwapToRangeWeapon_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::CombatSystemComponent_eventSwapToRangeWeapon_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCombatSystemComponent);
	UClass* Z_Construct_UClass_UCombatSystemComponent_NoRegister()
	{
		return UCombatSystemComponent::StaticClass();
	}
	struct Z_Construct_UClass_UCombatSystemComponent_Statics
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
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MainWeaponComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MainWeaponComponent;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IMC_CombatSystem_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IMC_CombatSystem;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IA_MeleeWeaponSelect_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IA_MeleeWeaponSelect;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IA_RangeWeaponSelect_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IA_RangeWeaponSelect;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IA_LockOn_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_IA_LockOn;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCombatSystemComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UCombatSystemComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatSystemComponent_LockOn, "LockOn" }, // 2018703687
		{ &Z_Construct_UFunction_UCombatSystemComponent_SwapToMeleeWeapon, "SwapToMeleeWeapon" }, // 198326990
		{ &Z_Construct_UFunction_UCombatSystemComponent_SwapToRangeWeapon, "SwapToRangeWeapon" }, // 1893469014
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_OwnerCharacter_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Owner Character\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Owner Character" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_OwnerCharacter = { "OwnerCharacter", nullptr, (EPropertyFlags)0x0020080000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCombatSystemComponent, OwnerCharacter), Z_Construct_UClass_ASkyscraperCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_OwnerCharacter_MetaData), Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_OwnerCharacter_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_MainWeaponComponent_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Weapon Component Variable\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Weapon Component Variable" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_MainWeaponComponent = { "MainWeaponComponent", nullptr, (EPropertyFlags)0x0020080000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCombatSystemComponent, MainWeaponComponent), Z_Construct_UClass_UActorComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_MainWeaponComponent_MetaData), Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_MainWeaponComponent_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IMC_CombatSystem_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Input Action And Input Mapping Context\n" },
#endif
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Input Action And Input Mapping Context" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IMC_CombatSystem = { "IMC_CombatSystem", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCombatSystemComponent, IMC_CombatSystem), Z_Construct_UClass_UInputMappingContext_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IMC_CombatSystem_MetaData), Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IMC_CombatSystem_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_MeleeWeaponSelect_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_MeleeWeaponSelect = { "IA_MeleeWeaponSelect", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCombatSystemComponent, IA_MeleeWeaponSelect), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_MeleeWeaponSelect_MetaData), Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_MeleeWeaponSelect_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_RangeWeaponSelect_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_RangeWeaponSelect = { "IA_RangeWeaponSelect", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCombatSystemComponent, IA_RangeWeaponSelect), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_RangeWeaponSelect_MetaData), Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_RangeWeaponSelect_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_LockOn_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Input" },
		{ "ModuleRelativePath", "MainGame/Component/Combat/CombatSystemComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_LockOn = { "IA_LockOn", nullptr, (EPropertyFlags)0x0040000000000015, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCombatSystemComponent, IA_LockOn), Z_Construct_UClass_UInputAction_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_LockOn_MetaData), Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_LockOn_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCombatSystemComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_OwnerCharacter,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_MainWeaponComponent,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IMC_CombatSystem,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_MeleeWeaponSelect,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_RangeWeaponSelect,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCombatSystemComponent_Statics::NewProp_IA_LockOn,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCombatSystemComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCombatSystemComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCombatSystemComponent_Statics::ClassParams = {
		&UCombatSystemComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCombatSystemComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UCombatSystemComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCombatSystemComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UCombatSystemComponent()
	{
		if (!Z_Registration_Info_UClass_UCombatSystemComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatSystemComponent.OuterSingleton, Z_Construct_UClass_UCombatSystemComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCombatSystemComponent.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<UCombatSystemComponent>()
	{
		return UCombatSystemComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCombatSystemComponent);
	UCombatSystemComponent::~UCombatSystemComponent() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_CombatSystemComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_CombatSystemComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCombatSystemComponent, UCombatSystemComponent::StaticClass, TEXT("UCombatSystemComponent"), &Z_Registration_Info_UClass_UCombatSystemComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatSystemComponent), 2148073826U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_CombatSystemComponent_h_152110666(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_CombatSystemComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Component_Combat_CombatSystemComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
