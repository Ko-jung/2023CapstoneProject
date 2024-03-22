// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "NetworkGameMode.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SKYSCRAPER_NetworkGameMode_generated_h
#error "NetworkGameMode.generated.h already included, missing '#pragma once' in NetworkGameMode.h"
#endif
#define SKYSCRAPER_NetworkGameMode_generated_h

#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_SPARSE_DATA
#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS
#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_ACCESSORS
#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesANetworkGameMode(); \
	friend struct Z_Construct_UClass_ANetworkGameMode_Statics; \
public: \
	DECLARE_CLASS(ANetworkGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Skyscraper"), NO_API) \
	DECLARE_SERIALIZER(ANetworkGameMode)


#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ANetworkGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ANetworkGameMode(ANetworkGameMode&&); \
	NO_API ANetworkGameMode(const ANetworkGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ANetworkGameMode); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ANetworkGameMode); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ANetworkGameMode) \
	NO_API virtual ~ANetworkGameMode();


#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_22_PROLOG
#define FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_SPARSE_DATA \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_EDITOR_ONLY_SPARSE_DATA_PROPERTY_ACCESSORS \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_ACCESSORS \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_INCLASS_NO_PURE_DECLS \
	FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h_25_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SKYSCRAPER_API UClass* StaticClass<class ANetworkGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Skyscraper_Source_Skyscraper_NetworkGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
