// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Network/NetProxy.h"

#include "Debug/XDLog.h"
#include "Kismet/GameplayStatics.h"




UNetProxy::UNetProxy() :Super()
{
	

	bIsInit = false;


}

void UNetProxy::Init()
{
	bool bSucceed = K2_Init();

	OnInit(bSucceed);
}

void UNetProxy::OnInit()
{
	XDLOG(Warning, TEXT("Net Proxy Initialization Failed, Socket Type : %s"),SocketType);
}

bool IsInit()const
{
	return bIsInit;
}

