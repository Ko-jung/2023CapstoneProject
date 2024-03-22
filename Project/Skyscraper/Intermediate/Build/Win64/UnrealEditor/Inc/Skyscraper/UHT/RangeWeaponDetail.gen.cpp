// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SelectCharacter/UI/RangeWeaponDetail.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRangeWeaponDetail() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_URangeWeaponDetail();
	SKYSCRAPER_API UClass* Z_Construct_UClass_URangeWeaponDetail_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UImage_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UMG_API UClass* Z_Construct_UClass_UWidgetSwitcher_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(URangeWeaponDetail::execOnClickRPGSelectButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickRPGSelectButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URangeWeaponDetail::execOnClickRifleSelectButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickRifleSelectButton();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(URangeWeaponDetail::execOnClickSMGSelectButton)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->OnClickSMGSelectButton();
		P_NATIVE_END;
	}
	void URangeWeaponDetail::StaticRegisterNativesURangeWeaponDetail()
	{
		UClass* Class = URangeWeaponDetail::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "OnClickRifleSelectButton", &URangeWeaponDetail::execOnClickRifleSelectButton },
			{ "OnClickRPGSelectButton", &URangeWeaponDetail::execOnClickRPGSelectButton },
			{ "OnClickSMGSelectButton", &URangeWeaponDetail::execOnClickSMGSelectButton },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URangeWeaponDetail, nullptr, "OnClickRifleSelectButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URangeWeaponDetail, nullptr, "OnClickRPGSelectButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_URangeWeaponDetail, nullptr, "OnClickSMGSelectButton", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton_Statics::Function_MetaDataParams), Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(URangeWeaponDetail);
	UClass* Z_Construct_UClass_URangeWeaponDetail_NoRegister()
	{
		return URangeWeaponDetail::StaticClass();
	}
	struct Z_Construct_UClass_URangeWeaponDetail_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SMGImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SMGImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RifleImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RifleImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RPGImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RPGImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SMGSelectButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SMGSelectButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RifleSelectButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RifleSelectButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RPGSelectButton_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RPGSelectButton;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RangeSwitcher_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RangeSwitcher;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_URangeWeaponDetail_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_URangeWeaponDetail_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_URangeWeaponDetail_OnClickRifleSelectButton, "OnClickRifleSelectButton" }, // 4203678011
		{ &Z_Construct_UFunction_URangeWeaponDetail_OnClickRPGSelectButton, "OnClickRPGSelectButton" }, // 2683279268
		{ &Z_Construct_UFunction_URangeWeaponDetail_OnClickSMGSelectButton, "OnClickSMGSelectButton" }, // 1072209022
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGImage_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xcc\xb9\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGImage = { "SMGImage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, SMGImage), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGImage_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleImage_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleImage = { "RifleImage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, RifleImage), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleImage_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGImage_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGImage = { "RPGImage", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, RPGImage), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGImage_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGImage_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGSelectButton_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xb0 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xc6\xb0 \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGSelectButton = { "SMGSelectButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, SMGSelectButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGSelectButton_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGSelectButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleSelectButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleSelectButton = { "RifleSelectButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, RifleSelectButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleSelectButton_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleSelectButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGSelectButton_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGSelectButton = { "RPGSelectButton", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, RPGSelectButton), Z_Construct_UClass_UButton_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGSelectButton_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGSelectButton_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RangeSwitcher_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/RangeWeaponDetail.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xc5\xb8\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd \xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd\xef\xbf\xbd" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RangeSwitcher = { "RangeSwitcher", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(URangeWeaponDetail, RangeSwitcher), Z_Construct_UClass_UWidgetSwitcher_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RangeSwitcher_MetaData), Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RangeSwitcher_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_URangeWeaponDetail_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_SMGSelectButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RifleSelectButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RPGSelectButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_URangeWeaponDetail_Statics::NewProp_RangeSwitcher,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_URangeWeaponDetail_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<URangeWeaponDetail>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_URangeWeaponDetail_Statics::ClassParams = {
		&URangeWeaponDetail::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_URangeWeaponDetail_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::Class_MetaDataParams), Z_Construct_UClass_URangeWeaponDetail_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_URangeWeaponDetail_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_URangeWeaponDetail()
	{
		if (!Z_Registration_Info_UClass_URangeWeaponDetail.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_URangeWeaponDetail.OuterSingleton, Z_Construct_UClass_URangeWeaponDetail_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_URangeWeaponDetail.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<URangeWeaponDetail>()
	{
		return URangeWeaponDetail::StaticClass();
	}
	URangeWeaponDetail::URangeWeaponDetail(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(URangeWeaponDetail);
	URangeWeaponDetail::~URangeWeaponDetail() {}
	struct Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_RangeWeaponDetail_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_RangeWeaponDetail_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_URangeWeaponDetail, URangeWeaponDetail::StaticClass, TEXT("URangeWeaponDetail"), &Z_Registration_Info_UClass_URangeWeaponDetail, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(URangeWeaponDetail), 3860805376U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_RangeWeaponDetail_h_2365976936(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_RangeWeaponDetail_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_RangeWeaponDetail_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
