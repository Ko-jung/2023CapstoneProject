// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum class COMP_OP : int8
{
	// Default
	OP_RECV,
	OP_SEND,
	OP_ACCEPT,

	// Lobby
	OP_STARTMATCHING,
	OP_CANCLEMATCHING,
	OP_CONNECTTOGAMESERVER,

	// Select
	OP_STARTGAME,
	OP_SELECTWEAPONINFO,
	OP_SETTIMER,

	//Main
	OP_POSITION,
	OP_PLAYERPOSITION,
	OP_DAMAGEDPLAYER,
	OP_CHANGEDPLAYERHP,
	OP_CHANGEDPLAYERSTATE,
	OP_SPAWNOBJECT,
	OP_PLAYERJOIN,
	OP_DISCONNECT,
	OP_TILEDROP,
	OP_SPAWNITEM,
	OP_CHANGEANIMMONTAGE,
};
