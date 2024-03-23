// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SelectCharacter/UI/CharacterPickState.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCharacterPickState() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_UCharacterPickState();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UCharacterPickState_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(UCharacterPickState::execGoToDetail)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GoToDetail();
		P_NATIVE_END;
	}
	void UCharacterPickState::StaticRegisterNativesUCharacterPickState()
	{
		UClass* Class = UCharacterPickState::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GoToDetail", &UCharacterPickState::execGoToDetail },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCharacterPickState_GoToDetail_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCharacterPickState_GoToDetail_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCharacterPickState_GoToDetail_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCharacterPickState, nullptr, "GoToDetail", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCharacterPickState_GoToDetail_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCharacterPickState_GoToDetail_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UCharacterPickState_GoToDetail()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCharacterPickState_GoToDetail_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCharacterPickState);
	UClass* Z_Construct_UClass_UCharacterPickState_NoRegister()
	{
		return UCharacterPickState::StaticClass();
	}
	struct Z_Construct_UClass_UCharacterPickState_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MyCharacterButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MyCharacterButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MyMeleeButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MyMeleeButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MyRangeButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MyRangeButton;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCharacterPickState_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UCharacterPickState_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCharacterPickState_GoToDetail, "GoToDetail" }, // 3155773255
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SelectCharacter/UI/CharacterPickState.h" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyCharacterButton_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Border variable\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Border variable" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyCharacterButton = { "MyCharacterButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, MyCharacterButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyCharacterButton_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyCharacterButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyMeleeButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyMeleeButton = { "MyMeleeButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, MyMeleeButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyMeleeButton_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyMeleeButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyRangeButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyRangeButton = { "MyRangeButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, MyRangeButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyRangeButton_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyRangeButton_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCharacterPickState_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyCharacterButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyMeleeButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyRangeButton,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCharacterPickState_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCharacterPickState>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCharacterPickState_Statics::ClassParams = {
		&UCharacterPickState::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UCharacterPickState_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::Class_MetaDataParams), Z_Construct_UClass_UCharacterPickState_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UCharacterPickState()
	{
		if (!Z_Registration_Info_UClass_UCharacterPickState.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCharacterPickState.OuterSingleton, Z_Construct_UClass_UCharacterPickState_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCharacterPickState.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<UCharacterPickState>()
	{
		return UCharacterPickState::StaticClass();
	}
	UCharacterPickState::UCharacterPickState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCharacterPickState);
	UCharacterPickState::~UCharacterPickState() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCharacterPickState, UCharacterPickState::StaticClass, TEXT("UCharacterPickState"), &Z_Registration_Info_UClass_UCharacterPickState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCharacterPickState), 1809154862U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_3274836635(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
