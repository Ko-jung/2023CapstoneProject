// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SelectCharacter/UI/SelectDetail.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSelectDetail() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_USelectDetail();
	SKYSCRAPER_API UClass* Z_Construct_UClass_USelectDetail_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(USelectDetail::execOnClickGoToLastButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickGoToLastButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USelectDetail::execOnClickRangeDetailButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickRangeDetailButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USelectDetail::execOnClickMeleeDetailButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickMeleeDetailButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(USelectDetail::execOnClickCharacterDetailButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickCharacterDetailButton();
		P_NATIVE_END;
	}
	void USelectDetail::StaticRegisterNativesUSelectDetail()
	{
		UClass* Class = USelectDetail::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnClickCharacterDetailButton", &USelectDetail::execOnClickCharacterDetailButton },
			{ "OnClickGoToLastButton", &USelectDetail::execOnClickGoToLastButton },
			{ "OnClickMeleeDetailButton", &USelectDetail::execOnClickMeleeDetailButton },
			{ "OnClickRangeDetailButton", &USelectDetail::execOnClickRangeDetailButton },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USelectDetail, nullptr, "OnClickCharacterDetailButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USelectDetail, nullptr, "OnClickGoToLastButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USelectDetail, nullptr, "OnClickMeleeDetailButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USelectDetail, nullptr, "OnClickRangeDetailButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USelectDetail);
	UClass* Z_Construct_UClass_USelectDetail_NoRegister()
	{
		return USelectDetail::StaticClass();
	}
	struct Z_Construct_UClass_USelectDetail_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterDetailButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CharacterDetailButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeleeDetailButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MeleeDetailButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RangeDetailButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RangeDetailButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GoToLastButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GoToLastButton;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Buttons_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Buttons_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Buttons;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DetailSwitcher_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DetailSwitcher;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USelectDetail_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_USelectDetail_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USelectDetail_OnClickCharacterDetailButton, "OnClickCharacterDetailButton" }, // 3531654586
		{ &Z_Construct_UFunction_USelectDetail_OnClickGoToLastButton, "OnClickGoToLastButton" }, // 3020870921
		{ &Z_Construct_UFunction_USelectDetail_OnClickMeleeDetailButton, "OnClickMeleeDetailButton" }, // 3078880650
		{ &Z_Construct_UFunction_USelectDetail_OnClickRangeDetailButton, "OnClickRangeDetailButton" }, // 3264205477
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SelectCharacter/UI/SelectDetail.h" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::NewProp_CharacterDetailButton_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xb0 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xb0 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_CharacterDetailButton = { "CharacterDetailButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USelectDetail, CharacterDetailButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::NewProp_CharacterDetailButton_MetaData), Z_Construct_UClass_USelectDetail_Statics::NewProp_CharacterDetailButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::NewProp_MeleeDetailButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_MeleeDetailButton = { "MeleeDetailButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USelectDetail, MeleeDetailButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::NewProp_MeleeDetailButton_MetaData), Z_Construct_UClass_USelectDetail_Statics::NewProp_MeleeDetailButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::NewProp_RangeDetailButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_RangeDetailButton = { "RangeDetailButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USelectDetail, RangeDetailButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::NewProp_RangeDetailButton_MetaData), Z_Construct_UClass_USelectDetail_Statics::NewProp_RangeDetailButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::NewProp_GoToLastButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_GoToLastButton = { "GoToLastButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USelectDetail, GoToLastButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::NewProp_GoToLastButton_MetaData), Z_Construct_UClass_USelectDetail_Statics::NewProp_GoToLastButton_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons_Inner = { "Buttons", nullptr, (EPropertyFlags)0x0000000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons_MetaData[] = {
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons = { "Buttons", nullptr, (EPropertyFlags)0x0040008000000008, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USelectDetail, Buttons), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons_MetaData), Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectDetail_Statics::NewProp_DetailSwitcher_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectDetail_Statics::NewProp_DetailSwitcher = { "DetailSwitcher", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USelectDetail, DetailSwitcher), Z_Construct_UClass_UWidgetSwitcher_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::NewProp_DetailSwitcher_MetaData), Z_Construct_UClass_USelectDetail_Statics::NewProp_DetailSwitcher_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USelectDetail_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_CharacterDetailButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_MeleeDetailButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_RangeDetailButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_GoToLastButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_Buttons,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectDetail_Statics::NewProp_DetailSwitcher,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USelectDetail_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USelectDetail>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USelectDetail_Statics::ClassParams = {
		&USelectDetail::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USelectDetail_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::Class_MetaDataParams), Z_Construct_UClass_USelectDetail_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USelectDetail_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_USelectDetail()
	{
		if (!Z_Registration_Info_UClass_USelectDetail.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USelectDetail.OuterSingleton, Z_Construct_UClass_USelectDetail_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USelectDetail.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<USelectDetail>()
	{
		return USelectDetail::StaticClass();
	}
	USelectDetail::USelectDetail(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USelectDetail);
	USelectDetail::~USelectDetail() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectDetail_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectDetail_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USelectDetail, USelectDetail::StaticClass, TEXT("USelectDetail"), &Z_Registration_Info_UClass_USelectDetail, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USelectDetail), 1089330827U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectDetail_h_458869429(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectDetail_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectDetail_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
