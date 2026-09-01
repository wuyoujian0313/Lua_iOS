//
//  AppDelegate.m
//  WebViewTest-iOS
//
//  Created by wuyoujian on 2018/4/13.
//  Copyright © 2018年 AI. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import <objc/runtime.h>


@implementation Person

+ (BOOL)supportsSecureCoding {
    return YES;
}


+ (id)deepCopyOfObject:(id)object {
    NSError *err;
    NSData *d = [NSKeyedArchiver archivedDataWithRootObject:object requiringSecureCoding:YES error:&err];
    id obj = [NSKeyedUnarchiver unarchivedObjectOfClass:[Person class] fromData:d error:&err];
    return obj;
}

- (nonnull id)copyWithZone:(nullable NSZone *)zone {
    Person *model = [[[self class] allocWithZone:zone] init];
    model.name = [NSString stringWithUTF8String:self.name.UTF8String];
//    model.age = self.age;
//    unsigned int count = 0;
//    objc_property_t *properties = class_copyPropertyList([self class], &count);
//    for (int i = 0; i<count; i++) {
//        objc_property_t property = properties[i];
//        const char *name = property_getName(property);
//        NSString *propertyName = [NSString stringWithUTF8String:name];
//        id value = [[self valueForKey:propertyName] copy];
//        if (value) {
//            [model setValue:value forKey:propertyName];
//        }
//    }
//    free(properties);
    return model;
}

- (void)encodeWithCoder:(NSCoder *)coder {
    [coder encodeObject:_name forKey:@"name"];
    [coder encodeObject:@(_age) forKey:@"age"];
}
- (id)initWithCoder:(NSCoder *)coder {
    if (self = [super init]) {
        _name = [coder decodeObjectForKey:@"name"];
        _age = [[coder decodeObjectForKey:@"age"] integerValue];
    }
    return self;
}


@end

@interface AppDelegate ()
@end

@implementation AppDelegate

+ (AppDelegate*)shareMyApplication {
    return (AppDelegate*)[UIApplication sharedApplication].delegate;
}

- (void)layoutMainPage {
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    ViewController *mainVC = [[ViewController alloc] init];
    self.window.rootViewController = mainVC;
    [_window makeKeyAndVisible];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    [self layoutMainPage];
    
    Person *p1 = [[Person alloc] init];
    p1.name = [NSString stringWithFormat:@"%@",@"wuyj"];
//    p1.age = 30;
    
    Person *p2 = [Person deepCopyOfObject:p1];
    
    NSLog(@"%@,%@",p1,p2);
    
    int fire = 90;
    int dur = 15;
    int gap = 60;
    int loop = dur + gap;
    
    int num = (60-90) / loop;
    
    NSArray *arr = @[@1,@2,@3,@4];
    
    for (NSNumber*n in arr) {
        NSLog(@"-----:%d",n.intValue);
        break;
    }
    
    
    NSMutableArray *array = [NSMutableArray arrayWithObjects:[NSNumber numberWithInt:3],[NSNumber numberWithInt:1],[NSNumber numberWithInt:2], nil];
    [array sortUsingComparator:^NSComparisonResult(id obj1, id obj2) {
        if ([obj1 integerValue] > [obj2 integerValue]) {
            return NSOrderedAscending;
        }
        
        return NSOrderedDescending;
    }];
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
