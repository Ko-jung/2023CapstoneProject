// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SkyscraperGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSkyscraperGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASkyscraperGameMode();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASkyscraperGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	void ASkyscraperGameMode::StaticRegisterNativesASkyscraperGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASkyscraperGameMode);
	UClass* Z_Construct_UClass_ASkyscraperGameMode_NoRegister()
	{
		return ASkyscraperGameMode::StaticClass();
	}
	struct Z_Construct_UClass_ASkyscraperGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASkyscraperGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASkyscraperGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASkyscraperGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "SkyscraperGameMode.h" },
		{ "ModuleRelativePath", "SkyscraperGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASkyscraperGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASkyscraperGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_ASkyscraperGameMode_Statics::ClassParams = {
		&ASkyscraperGameMode::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008802ACu,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASkyscraperGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASkyscraperGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_ASkyscraperGameMode()
	{
		if (!Z_Registration_Info_UClass_ASkyscraperGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASkyscraperGameMode.OuterSingleton, Z_Construct_UClass_ASkyscraperGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_ASkyscraperGameMode.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<ASkyscraperGameMode>()
	{
		return ASkyscraperGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASkyscraperGameMode);
	ASkyscraperGameMode::~ASkyscraperGameMode() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SkyscraperGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SkyscraperGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_ASkyscraperGameMode, ASkyscraperGameMode::StaticClass, TEXT("ASkyscraperGameMode"), &Z_Registration_Info_UClass_ASkyscraperGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASkyscraperGameMode), 1805268391U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SkyscraperGameMode_h_2112293794(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SkyscraperGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SkyscraperGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
