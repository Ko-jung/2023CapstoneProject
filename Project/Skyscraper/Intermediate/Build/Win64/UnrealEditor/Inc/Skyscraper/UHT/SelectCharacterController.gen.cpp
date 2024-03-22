// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SelectCharacter/Core/SelectCharacterController.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSelectCharacterController() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASelectCharacterController();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASelectCharacterController_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_USelectCharacter_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_USelectDetail_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(ASelectCharacterController::execSetDetailWidgetVisibility)
	{
		P_GET_UBOOL(Z_Param_bVisible);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetDetailWidgetVisibility(Z_Param_bVisible);
		P_NATIVE_END;
	}
	void ASelectCharacterController::StaticRegisterNativesASelectCharacterController()
	{
		UClass* Class = ASelectCharacterController::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "SetDetailWidgetVisibility", &ASelectCharacterController::execSetDetailWidgetVisibility },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics
	{
		struct SelectCharacterController_eventSetDetailWidgetVisibility_Parms
		{
			bool bVisible;
		};
		static void NewProp_bVisible_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bVisible;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::NewProp_bVisible_SetBit(void* Obj)
	{
		((SelectCharacterController_eventSetDetailWidgetVisibility_Parms*)Obj)->bVisible = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::NewProp_bVisible = { "bVisible", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SelectCharacterController_eventSetDetailWidgetVisibility_Parms), &Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::NewProp_bVisible_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::NewProp_bVisible,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/Core/SelectCharacterController.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_ASelectCharacterController, nullptr, "SetDetailWidgetVisibility", nullptr, nullptr, Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::SelectCharacterController_eventSetDetailWidgetVisibility_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x40020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::SelectCharacterController_eventSetDetailWidgetVisibility_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASelectCharacterController);
	UClass* Z_Construct_UClass_ASelectCharacterController_NoRegister()
	{
		return ASelectCharacterController::StaticClass();
	}
	struct Z_Construct_UClass_ASelectCharacterController_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterSelectionWidget_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_CharacterSelectionWidget;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SelectDetailWidget_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPtrPropertyParams NewProp_SelectDetailWidget;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterSelectionWidgetClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_CharacterSelectionWidgetClass;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SelectDetailWidgetClass_MetaData[];
#endif
		static const UECodeGen_Private::FClassPropertyParams NewProp_SelectDetailWidgetClass;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASelectCharacterController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_ASelectCharacterController_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_ASelectCharacterController_SetDetailWidgetVisibility, "SetDetailWidgetVisibility" }, // 87967370
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASelectCharacterController_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "SelectCharacter/Core/SelectCharacterController.h" },
		{ "ModuleRelativePath", "SelectCharacter/Core/SelectCharacterController.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/Core/SelectCharacterController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidget = { "CharacterSelectionWidget", nullptr, (EPropertyFlags)0x0044000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASelectCharacterController, CharacterSelectionWidget), Z_Construct_UClass_USelectCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidget_MetaData), Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidget_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidget_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/Core/SelectCharacterController.h" },
	};
#endif
	const UECodeGen_Private::FObjectPtrPropertyParams Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidget = { "SelectDetailWidget", nullptr, (EPropertyFlags)0x0044000000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASelectCharacterController, SelectDetailWidget), Z_Construct_UClass_USelectDetail_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidget_MetaData), Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidget_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidgetClass_MetaData[] = {
		{ "ModuleRelativePath", "SelectCharacter/Core/SelectCharacterController.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidgetClass = { "CharacterSelectionWidgetClass", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASelectCharacterController, CharacterSelectionWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_USelectCharacter_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidgetClass_MetaData), Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidgetClass_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidgetClass_MetaData[] = {
		{ "ModuleRelativePath", "SelectCharacter/Core/SelectCharacterController.h" },
	};
#endif
	const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidgetClass = { "SelectDetailWidgetClass", nullptr, (EPropertyFlags)0x0044000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASelectCharacterController, SelectDetailWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_USelectDetail_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidgetClass_MetaData), Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidgetClass_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASelectCharacterController_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidget,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidget,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_CharacterSelectionWidgetClass,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASelectCharacterController_Statics::NewProp_SelectDetailWidgetClass,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASelectCharacterController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASelectCharacterController>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASelectCharacterController_Statics::ClassParams = {
		&ASelectCharacterController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_ASelectCharacterController_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::PropPointers),
		0,
		0x009002A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::Class_MetaDataParams), Z_Construct_UClass_ASelectCharacterController_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASelectCharacterController_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_ASelectCharacterController()
	{
		if (!Z_Registration_Info_UClass_ASelectCharacterController.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASelectCharacterController.OuterSingleton, Z_Construct_UClass_ASelectCharacterController_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASelectCharacterController.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<ASelectCharacterController>()
	{
		return ASelectCharacterController::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASelectCharacterController);
	ASelectCharacterController::~ASelectCharacterController() {}
	struct Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_Core_SelectCharacterController_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_Core_SelectCharacterController_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASelectCharacterController, ASelectCharacterController::StaticClass, TEXT("ASelectCharacterController"), &Z_Registration_Info_UClass_ASelectCharacterController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASelectCharacterController), 1201818307U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_Core_SelectCharacterController_h_2546214166(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_Core_SelectCharacterController_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_Core_SelectCharacterController_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
