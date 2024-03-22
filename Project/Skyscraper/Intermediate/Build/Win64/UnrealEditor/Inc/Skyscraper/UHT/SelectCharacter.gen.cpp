// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/SelectCharacter/UI/SelectCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSelectCharacter() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_USelectCharacter();
	SKYSCRAPER_API UClass* Z_Construct_UClass_USelectCharacter_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UUserWidget();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	void USelectCharacter::StaticRegisterNativesUSelectCharacter()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USelectCharacter);
	UClass* Z_Construct_UClass_USelectCharacter_NoRegister()
	{
		return USelectCharacter::StaticClass();
	}
	struct Z_Construct_UClass_USelectCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USelectCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UUserWidget,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USelectCharacter_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectCharacter_Statics::Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "SelectCharacter/UI/SelectCharacter.h" },
		{ "ModuleRelativePath", "SelectCharacter/UI/SelectCharacter.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USelectCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USelectCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USelectCharacter_Statics::ClassParams = {
		&USelectCharacter::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x00B010A0u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USelectCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_USelectCharacter_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_USelectCharacter()
	{
		if (!Z_Registration_Info_UClass_USelectCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USelectCharacter.OuterSingleton, Z_Construct_UClass_USelectCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USelectCharacter.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<USelectCharacter>()
	{
		return USelectCharacter::StaticClass();
	}
	USelectCharacter::USelectCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USelectCharacter);
	USelectCharacter::~USelectCharacter() {}
	struct Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USelectCharacter, USelectCharacter::StaticClass, TEXT("USelectCharacter"), &Z_Registration_Info_UClass_USelectCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USelectCharacter), 3658239514U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectCharacter_h_1614550076(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Skyscraper_Source_Skyscraper_SelectCharacter_UI_SelectCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
