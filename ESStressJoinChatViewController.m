//
//  ESStressJoinChatViewController.m
//  StressAdiumPlugin
//
//  Created by Alexey Yesipenko on 5/21/13.
//  Copyright (c) 2013 Alexey Yesipenko. All rights reserved.
//

#import "ESStressJoinChatViewController.h"

@implementation ESStressJoinChatViewController

- (void)joinChatWithAccount:(AIAccount *)inAccount
{
    NSString *channel = @"StressChat";
	NSMutableDictionary	*chatCreationInfo;
    
    if ([channel length]<1) {
        return;
    }
    chatCreationInfo = [NSMutableDictionary dictionaryWithObject:channel
                                                          forKey:@"room"];

    [self doJoinChatWithName:@"StressChat"
                   onAccount:inAccount
            chatCreationInfo:chatCreationInfo
            invitingContacts:nil
       withInvitationMessage:nil];
}

@end
