// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/MainGame/Widget/Health/HealthBar.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHealthBar() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_UHealthBar();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UHealthBar_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UProgressBar_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	void UHealthBar::StaticRegisterNativesUHealthBar()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHealthBar);
	UClass* Z_Construct_UClass_UHealthBar_NoRegister()
	{
		return UHealthBar::StaticClass();
	}
	struct Z_Construct_UClass_UHealthBar_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_HealthBar_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_HealthBar;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHealthBar_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthBar_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHealthBar_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "MainGame/Widget/Health/HealthBar.h" },
		{ "ModuleRelativePath", "MainGame/Widget/Health/HealthBar.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHealthBar_Statics::NewProp_HealthBar_MetaData[] = {
		{ "BindWidget", "" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// == Border variable\n" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainGame/Widget/Health/HealthBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "== Border variable" },
#endif
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UHealthBar_Statics::NewProp_HealthBar = { "HealthBar", nullptr, (EPropertyFlags)0x0040000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHealthBar, HealthBar), Z_Construct_UClass_UProgressBar_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthBar_Statics::NewProp_HealthBar_MetaData), Z_Construct_UClass_UHealthBar_Statics::NewProp_HealthBar_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHealthBar_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHealthBar_Statics::NewProp_HealthBar,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHealthBar_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHealthBar>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UHealthBar_Statics::ClassParams = {
		&UHealthBar::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UHealthBar_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UHealthBar_Statics::PropPointers),
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthBar_Statics::Class_MetaDataParams), Z_Construct_UClass_UHealthBar_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHealthBar_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UHealthBar()
	{
		if (!Z_Registration_Info_UClass_UHealthBar.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHealthBar.OuterSingleton, Z_Construct_UClass_UHealthBar_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UHealthBar.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<UHealthBar>()
	{
		return UHealthBar::StaticClass();
	}
	UHealthBar::UHealthBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHealthBar);
	UHealthBar::~UHealthBar() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Widget_Health_HealthBar_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Widget_Health_HealthBar_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UHealthBar, UHealthBar::StaticClass, TEXT("UHealthBar"), &Z_Registration_Info_UClass_UHealthBar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHealthBar), 2534663179U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Widget_Health_HealthBar_h_2066226621(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Widget_Health_HealthBar_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Widget_Health_HealthBar_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
