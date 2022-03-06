//
//  IMService.h
//
//  Copyright (c) 2001 Apple Computer, Inc. All rights reserved.
//

/*! @header
    @discussion The IMService API provides a way to integrate a variety of data about a user's iChat connections into your
				application. It provides information on which services the user is connected to (AIM, Jabber, or Bonjour), their online
				screen names, their lists of acquaintances, their current status on a given service (away, idle, available), idle
				times, and other presence-specific details. The API also provides notifications to update your applications when
				a user's status, information, status images, or service connections have changed.
				
				A variety of status notifications related to the user's status and preferences are posted by the 
				IMService custom notification center. See "Notifications" for more information. 
*/

// This API has now moved to IMCore/IMService.h
#import <IMCore/IMService.h>