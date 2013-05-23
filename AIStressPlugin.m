//
//  AIStressPlugin.m
//  StressAdiumPlugin
//
//  Created by Alexey Yesipenko on 5/21/13.
//  Copyright (c) 2013 Alexey Yesipenko. All rights reserved.
//

#import "AIStressPlugin.h"
#import "ESStressService.h"

@implementation AIStressPlugin

extern void purple_init_stress_plugin();

- (void)installPlugin
{
    purple_init_stress_plugin();
    [ESStressService registerService];
}

- (void)uninstallPlugin
{
}

- (void)installLibpurplePlugin
{
}

- (void)loadLibpurplePlugin
{
}

- (NSString *)pluginAuthor
{
	return @"Alexey Yesipenko <alex7y@gmail.com>";
}

-(NSString *)pluginVersion
{
	return @"0.1";
}

-(NSString *)pluginDescription
{
	return @"Stress";
}

@end
