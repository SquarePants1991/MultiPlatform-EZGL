//
//  NSObjectHolder.h
//  metal
//
//  Created by wang yang on 2017/6/22.
//  Copyright © 2017年 wang yang. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ELRetain(obj) [NSObjectHolder retain: obj]
#define ELRelease(obj) [NSObjectHolder release: obj]

@interface NSObjectHolder : NSObject
// NSObject under impl_Metal can be managed by ELMetalAdapter
+ (void)retain:(NSObject *)object;
+ (void)release:(NSObject *)object;
@end
