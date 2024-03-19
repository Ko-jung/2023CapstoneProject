// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SelectCharacter/UI/MeleeWeaponDetail.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMeleeWeaponDetail() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMeleeWeaponDetail();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMeleeWeaponDetail_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UImage_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(UMeleeWeaponDetail::execOnClickGreatSwordButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickGreatSwordButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMeleeWeaponDetail::execOnClickKatanaButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickKatanaButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UMeleeWeaponDetail::execOnClickDaggerButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickDaggerButton();
		P_NATIVE_END;
	}
	void UMeleeWeaponDetail::StaticRegisterNativesUMeleeWeaponDetail()
	{
		UClass* Class = UMeleeWeaponDetail::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnClickDaggerButton", &UMeleeWeaponDetail::execOnClickDaggerButton },
			{ "OnClickGreatSwordButton", &UMeleeWeaponDetail::execOnClickGreatSwordButton },
			{ "OnClickKatanaButton", &UMeleeWeaponDetail::execOnClickKatanaButton },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMeleeWeaponDetail, nullptr, "OnClickDaggerButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMeleeWeaponDetail, nullptr, "OnClickGreatSwordButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UMeleeWeaponDetail, nullptr, "OnClickKatanaButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMeleeWeaponDetail);
	UClass* Z_Construct_UClass_UMeleeWeaponDetail_NoRegister()
	{
		return UMeleeWeaponDetail::StaticClass();
	}
	struct Z_Construct_UClass_UMeleeWeaponDetail_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DaggerImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DaggerImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_KatanaImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_KatanaImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GreatSwordImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GreatSwordImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DaggerSelectButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_DaggerSelectButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_KatanaSelectButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_KatanaSelectButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GreatSwordButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GreatSwordButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeleeSwitcher_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MeleeSwitcher;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UMeleeWeaponDetail_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UMeleeWeaponDetail_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UMeleeWeaponDetail_OnClickDaggerButton, "OnClickDaggerButton" }, // 1663591078
		{ &Z_Construct_UFunction_UMeleeWeaponDetail_OnClickGreatSwordButton, "OnClickGreatSwordButton" }, // 2681659235
		{ &Z_Construct_UFunction_UMeleeWeaponDetail_OnClickKatanaButton, "OnClickKatanaButton" }, // 212042894
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerImage_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerImage = { "DaggerImage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, DaggerImage), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerImage_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaImage_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaImage = { "KatanaImage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, KatanaImage), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaImage_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordImage_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordImage = { "GreatSwordImage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, GreatSwordImage), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordImage_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerSelectButton_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xb0 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xb0 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerSelectButton = { "DaggerSelectButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, DaggerSelectButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerSelectButton_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerSelectButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaSelectButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaSelectButton = { "KatanaSelectButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, KatanaSelectButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaSelectButton_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaSelectButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordButton = { "GreatSwordButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, GreatSwordButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordButton_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_MeleeSwitcher_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/MeleeWeaponDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_MeleeSwitcher = { "MeleeSwitcher", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UMeleeWeaponDetail, MeleeSwitcher), Z_Construct_UClass_UWidgetSwitcher_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_MeleeSwitcher_MetaData), Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_MeleeSwitcher_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UMeleeWeaponDetail_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_DaggerSelectButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_KatanaSelectButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_GreatSwordButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UMeleeWeaponDetail_Statics::NewProp_MeleeSwitcher,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UMeleeWeaponDetail_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMeleeWeaponDetail>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UMeleeWeaponDetail_Statics::ClassParams = {
		&UMeleeWeaponDetail::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UMeleeWeaponDetail_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::Class_MetaDataParams), Z_Construct_UClass_UMeleeWeaponDetail_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMeleeWeaponDetail_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UMeleeWeaponDetail()
	{
		if (!Z_Registration_Info_UClass_UMeleeWeaponDetail.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMeleeWeaponDetail.OuterSingleton, Z_Construct_UClass_UMeleeWeaponDetail_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UMeleeWeaponDetail.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<UMeleeWeaponDetail>()
	{
		return UMeleeWeaponDetail::StaticClass();
	}
	UMeleeWeaponDetail::UMeleeWeaponDetail(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UMeleeWeaponDetail);
	UMeleeWeaponDetail::~UMeleeWeaponDetail() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_MeleeWeaponDetail_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_MeleeWeaponDetail_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UMeleeWeaponDetail, UMeleeWeaponDetail::StaticClass, TEXT("UMeleeWeaponDetail"), &Z_Registration_Info_UClass_UMeleeWeaponDetail, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMeleeWeaponDetail), 2618369612U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_MeleeWeaponDetail_h_3707912177(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_MeleeWeaponDetail_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_MeleeWeaponDetail_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
