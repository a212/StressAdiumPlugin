//
//  ESPurpleStressAccount.m
//  StressAdiumPlugin
//
//  Created by Alexey Yesipenko on 5/21/13.
//  Copyright (c) 2013 Alexey Yesipenko. All rights reserved.
//

#import "ESPurpleStressAccount.h"

@implementation ESPurpleStressAccount

- (const char*)protocolPlugin
{
	return "prpl-avy-stress";
}

- (BOOL)connectivityBasedOnNetworkReachability
{
    return FALSE;
}

@end
