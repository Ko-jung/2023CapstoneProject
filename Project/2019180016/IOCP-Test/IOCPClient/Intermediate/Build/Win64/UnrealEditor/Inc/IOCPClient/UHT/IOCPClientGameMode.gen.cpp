// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "IOCPClient/IOCPClientGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeIOCPClientGameMode() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	IOCPCLIENT_API UClass* Z_Construct_UClass_AIOCPClientGameMode();
	IOCPCLIENT_API UClass* Z_Construct_UClass_AIOCPClientGameMode_NoRegister();
	UPackage* Z_Construct_UPackage__Script_IOCPClient();
// End Cross Module References
	void AIOCPClientGameMode::StaticRegisterNativesAIOCPClientGameMode()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AIOCPClientGameMode);
	UClass* Z_Construct_UClass_AIOCPClientGameMode_NoRegister()
	{
		return AIOCPClientGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AIOCPClientGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AIOCPClientGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_IOCPClient,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AIOCPClientGameMode_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AIOCPClientGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "IOCPClientGameMode.h" },
		{ "ModuleRelativePath", "IOCPClientGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AIOCPClientGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AIOCPClientGameMode>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AIOCPClientGameMode_Statics::ClassParams = {
		&AIOCPClientGameMode::StaticClass,
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
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AIOCPClientGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AIOCPClientGameMode_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AIOCPClientGameMode()
	{
		if (!Z_Registration_Info_UClass_AIOCPClientGameMode.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AIOCPClientGameMode.OuterSingleton, Z_Construct_UClass_AIOCPClientGameMode_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AIOCPClientGameMode.OuterSingleton;
	}
	template<> IOCPCLIENT_API UClass* StaticClass<AIOCPClientGameMode>()
	{
		return AIOCPClientGameMode::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AIOCPClientGameMode);
	AIOCPClientGameMode::~AIOCPClientGameMode() {}
	struct Z_CompiledInDeferFile_FID_IOCPClient_Source_IOCPClient_IOCPClientGameMode_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_IOCPClient_Source_IOCPClient_IOCPClientGameMode_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AIOCPClientGameMode, AIOCPClientGameMode::StaticClass, TEXT("AIOCPClientGameMode"), &Z_Registration_Info_UClass_AIOCPClientGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AIOCPClientGameMode), 523048543U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_IOCPClient_Source_IOCPClient_IOCPClientGameMode_h_1743471619(TEXT("/Script/IOCPClient"),
		Z_CompiledInDeferFile_FID_IOCPClient_Source_IOCPClient_IOCPClientGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_IOCPClient_Source_IOCPClient_IOCPClientGameMode_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
