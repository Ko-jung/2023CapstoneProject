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
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UCharacterPickState();
	SKYSCRAPER_API UClass* Z_Construct_UClass_UCharacterPickState_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UButton_NoRegister();
	UMG_API UClass* Z_Construct_UClass_UImage_NoRegister();
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
	DEFINE_FUNCTION(UCharacterPickState::execSelectInfoUpdate)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SelectInfoUpdate();
		P_NATIVE_END;
	}
	void UCharacterPickState::StaticRegisterNativesUCharacterPickState()
	{
		UClass* Class = UCharacterPickState::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GoToDetail", &UCharacterPickState::execGoToDetail },
			{ "SelectInfoUpdate", &UCharacterPickState::execSelectInfoUpdate },
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
	struct Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCharacterPickState, nullptr, "SelectInfoUpdate", nullptr, nullptr, nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate_Statics::Function_MetaDataParams), Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate_Statics::Function_MetaDataParams) };
	UFunction* Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate_Statics::FuncParams);
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
		static const UECodeGen_Private::FObjectPropertyParams NewProp_CharacterImages_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CharacterImages_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_CharacterImages;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_MeleeImages_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeleeImages_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_MeleeImages;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_RangeImages_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_RangeImages_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_RangeImages;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_QuestionImages_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_QuestionImages;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyCharacter0_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyCharacter0;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyMelee0_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyMelee0;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyRange0_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyRange0;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyCharacter1_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyCharacter1;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyMelee1_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyMelee1;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyRange1_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyRange1;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyCharacter2_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyCharacter2;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyMelee2_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyMelee2;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FriendlyRange2_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_FriendlyRange2;
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
		{ &Z_Construct_UFunction_UCharacterPickState_SelectInfoUpdate, "SelectInfoUpdate" }, // 3110321835
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages_Inner = { "CharacterImages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages_MetaData[] = {
		{ "Category", "SelectedImage" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages = { "CharacterImages", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, CharacterImages), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages_Inner = { "MeleeImages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages_MetaData[] = {
		{ "Category", "SelectedImage" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages = { "MeleeImages", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, MeleeImages), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages_MetaData) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages_Inner = { "RangeImages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(0, nullptr) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages_MetaData[] = {
		{ "Category", "SelectedImage" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages = { "RangeImages", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, RangeImages), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_QuestionImages_MetaData[] = {
		{ "Category", "SelectedImage" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_QuestionImages = { "QuestionImages", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, QuestionImages), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_QuestionImages_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_QuestionImages_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter0_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter0 = { "FriendlyCharacter0", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyCharacter0), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter0_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter0_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee0_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee0 = { "FriendlyMelee0", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyMelee0), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee0_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee0_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange0_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange0 = { "FriendlyRange0", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyRange0), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange0_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange0_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter1_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter1 = { "FriendlyCharacter1", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyCharacter1), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter1_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter1_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee1_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee1 = { "FriendlyMelee1", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyMelee1), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee1_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee1_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange1_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange1 = { "FriendlyRange1", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyRange1), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange1_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange1_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter2_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter2 = { "FriendlyCharacter2", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyCharacter2), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter2_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter2_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee2_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee2 = { "FriendlyMelee2", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyMelee2), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee2_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee2_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange2_MetaData[] = {
		{ "BindWidget", "" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SelectCharacter/UI/CharacterPickState.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange2 = { "FriendlyRange2", nullptr, (EPropertyFlags)0x0010000000080008, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UCharacterPickState, FriendlyRange2), Z_Construct_UClass_UImage_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange2_MetaData), Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange2_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCharacterPickState_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyCharacterButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyMeleeButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MyRangeButton,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_CharacterImages,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_MeleeImages,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_RangeImages,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_QuestionImages,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter0,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee0,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange0,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter1,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee1,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange1,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyCharacter2,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyMelee2,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCharacterPickState_Statics::NewProp_FriendlyRange2,
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
		{ Z_Construct_UClass_UCharacterPickState, UCharacterPickState::StaticClass, TEXT("UCharacterPickState"), &Z_Registration_Info_UClass_UCharacterPickState, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCharacterPickState), 653676989U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_982795676(TEXT("/Script/Skyscraper"),
		Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_2023CapstoneProject_Project_Skyscraper_Source_Skyscraper_SelectCharacter_UI_CharacterPickState_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
