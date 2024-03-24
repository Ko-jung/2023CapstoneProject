// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Skyscraper/MainGame/Actor/Character/EnemyCharacter.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyCharacter() {}
// Cross Module References
	SKYSCRAPER_API UClass* Z_Construct_UClass_AEnemyCharacter();
	SKYSCRAPER_API UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_ASkyscraperCharacter();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UMainRangeComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_Skyscraper();
// End Cross Module References
	DEFINE_FUNCTION(AEnemyCharacter::execFirePer1Sec)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FirePer1Sec();
		P_NATIVE_END;
	}
	void AEnemyCharacter::StaticRegisterNativesAEnemyCharacter()
	{
		UClass* Class = AEnemyCharacter::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FirePer1Sec", &AEnemyCharacter::execFirePer1Sec },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "MainGame/Actor/Character/EnemyCharacter.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_AEnemyCharacter, nullptr, "FirePer1Sec", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00040401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec_Statics::Function_MetaDataParams), Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyCharacter);
	UClass* Z_Construct_UClass_AEnemyCharacter_NoRegister()
	{
		return AEnemyCharacter::StaticClass();
	}
	struct Z_Construct_UClass_AEnemyCharacter_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RangeComponent_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RangeComponent;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEnemyCharacter_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ASkyscraperCharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Skyscraper,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_AEnemyCharacter_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_AEnemyCharacter_FirePer1Sec, "FirePer1Sec" }, // 1968820927
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "MainGame/Actor/Character/EnemyCharacter.h" },
		{ "ModuleRelativePath", "MainGame/Actor/Character/EnemyCharacter.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_RangeComponent_MetaData[] = {
		{ "Category", "Component" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "MainGame/Actor/Character/EnemyCharacter.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_RangeComponent = { "RangeComponent", nullptr, (EPropertyFlags)0x00100000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AEnemyCharacter, RangeComponent), Z_Construct_UClass_UMainRangeComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_RangeComponent_MetaData), Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_RangeComponent_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEnemyCharacter_Statics::NewProp_RangeComponent,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEnemyCharacter_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyCharacter>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyCharacter_Statics::ClassParams = {
		&AEnemyCharacter::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyCharacter_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyCharacter_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_AEnemyCharacter()
	{
		if (!Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton, Z_Construct_UClass_AEnemyCharacter_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AEnemyCharacter.OuterSingleton;
	}
	template<> SKYSCRAPER_API UClass* StaticClass<AEnemyCharacter>()
	{
		return AEnemyCharacter::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyCharacter);
	AEnemyCharacter::~AEnemyCharacter() {}
	struct Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Actor_Character_EnemyCharacter_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Actor_Character_EnemyCharacter_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyCharacter, AEnemyCharacter::StaticClass, TEXT("AEnemyCharacter"), &Z_Registration_Info_UClass_AEnemyCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyCharacter), 2703424570U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Actor_Character_EnemyCharacter_h_434422717(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Actor_Character_EnemyCharacter_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_MainGame_Actor_Character_EnemyCharacter_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
