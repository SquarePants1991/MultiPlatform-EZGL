//
//  NSObjectHolder.m
//  metal
//
//  Created by wang yang on 2017/6/22.
//  Copyright © 2017年 wang yang. All rights reserved.
//

#import "NSObjectHolder.h"
#import <objc/runtime.h>

const void *kManagedObjects;

@implementation NSObjectHolder
+ (void)retain:(NSObject *)object {
    id obj = objc_getAssociatedObject(self, &kManagedObjects);
    if (obj == nil) {
        obj = [NSMutableArray new];
        objc_setAssociatedObject(self, &kManagedObjects, obj, OBJC_ASSOCIATION_RETAIN);
    }
    [obj addObject:object];
}

+ (void)release:(NSObject *)object {
    id obj = objc_getAssociatedObject(self, &kManagedObjects);
    if (obj != nil) {
        [obj removeObject:object];
    }
}
@end
