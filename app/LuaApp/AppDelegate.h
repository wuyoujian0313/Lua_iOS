//
//  AppDelegate.h
//  WebViewTest-iOS
//
//  Created by wuyoujian on 2018/4/13.
//  Copyright © 2018年 AI. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface Person : NSObject<NSSecureCoding>
@property(nonatomic,strong)NSString* name;
@property(nonatomic,assign)NSInteger age;

+ (id)deepCopyOfObject:(id)object;
@end

@interface AppDelegate : UIResponder <UIApplicationDelegate>
@property (strong, nonatomic) UIWindow *window;

+ (AppDelegate*)shareMyApplication;
@end

