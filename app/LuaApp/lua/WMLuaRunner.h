//
//  WMLuaRunner.h
//  LuaApp
//
//  Created by youjian on 2024/1/12.
//  Copyright © 2024 AI. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WMLuaRunner : NSObject

+ (instancetype)getInstance;

- (void)runLua:(NSString *)luaScript;

@end

NS_ASSUME_NONNULL_END
