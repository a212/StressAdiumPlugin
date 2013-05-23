//
//  ESStressService.m
//  StressAdiumPlugin
//
//  Created by Alexey Yesipenko on 5/21/13.
//  Copyright (c) 2013 Alexey Yesipenko. All rights reserved.
//

#import "ESStressService.h"
#import "ESPurpleStressAccount.h"
#import "ESStressJoinChatViewController.h"

#import <Adium/AISharedAdium.h>
#import <Adium/AIStatusControllerProtocol.h>
#import <AIUtilities/AIStringUtilities.h>
#import <AIUtilities/AIImageAdditions.h>

@implementation ESStressService

- (Class)accountClass {
	return [ESPurpleStressAccount class];
}

//Service Description
- (NSString *)serviceCodeUniqueID {
	return @"libpurple-stress";
}
- (NSString *)serviceID{
	return @"Stress";
}
- (NSString *)serviceClass {
	return @"Stress";
}
- (NSString *)shortDescription {
	return @"Stress";
}
- (NSString *)longDescription {
	return @"Stress";
}

- (NSCharacterSet *)allowedCharacters {
    NSMutableCharacterSet *allowed = [NSMutableCharacterSet alphanumericCharacterSet];
    [allowed formUnionWithCharacterSet:[NSCharacterSet  punctuationCharacterSet]];
    return allowed;
}

- (NSUInteger)allowedLength {
	return 64;
}

- (BOOL)caseSensitive {
	return NO;
}

- (BOOL)supportsPassword {
	return NO;
}

- (AIServiceImportance)serviceImportance {
	return AIServicePrimary;
}

- (NSString *)userNameLabel {
    return AILocalizedString(@"Nick", nil); // Sign-in name
}

- (void)registerStatuses {
#define ADDSTATUS(name, type) \
[adium.statusController registerStatus:name \
withDescription:[adium.statusController localizedDescriptionForCoreStatusName:name] \
ofType:type forService:self]
    
    ADDSTATUS(STATUS_NAME_AVAILABLE, AIAvailableStatusType);
    ADDSTATUS(STATUS_NAME_OFFLINE, AIOfflineStatusType);
}

- (NSImage *)defaultServiceIconOfType:(AIServiceIconType)iconType
{
    if ((iconType == AIServiceIconSmall) || (iconType == AIServiceIconList)) {
        return [NSImage imageNamed:@"stress_small" forClass:[self class] loadLazily:YES];
    } else {
        return [NSImage imageNamed:@"stress" forClass:[self class] loadLazily:YES];
    }
}

- (NSString *)pathForDefaultServiceIconOfType:(AIServiceIconType)iconType
{
    if ((iconType == AIServiceIconSmall) || (iconType == AIServiceIconList)) {
		return [[NSBundle bundleForClass:[self class]] pathForImageResource:@"stress_small"];
	}
	return [[NSBundle bundleForClass:[self class]] pathForImageResource:@"stress"];
}

- (BOOL)canCreateGroupChats
{
    return YES;
}

- (DCJoinChatViewController *)joinChatView
{
    return [ESStressJoinChatViewController joinChatView];
}
@end
