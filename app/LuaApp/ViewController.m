//
//  ViewController.m
//  WebViewTest-iOS
//
//  Created by wuyoujian on 2018/4/13.
//  Copyright © 2018年 AI. All rights reserved.
//

#import "ViewController.h"
#import "WMLuaRunner.h"
#import <Lua/Lua.hpp>


@interface ViewController ()
@property (nonatomic, strong) LuaState *luaState;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = UIColor.whiteColor;
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSURL *url = [NSURL fileURLWithPath:[mainBundle pathForResource:@"main" ofType:@"lua" inDirectory:@"luascript"]];
    NSString *luaScript = [NSString stringWithContentsOfURL:url encoding:NSUTF8StringEncoding error:nil];
    
    
    LuaState *luaState = [self luaState];
    @autoreleasepool {
        NSError *error;
        if (![luaState runChunk:luaScript
                        rvalues:nil
                        options:0
                          error:&error])
        {
            NSLog(@"%@", error);
            return;
        }
    }
    
    [luaState collectGarbage];

    UIButton *button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button setClipsToBounds:YES];
    [button.layer setCornerRadius:4.0];
    [button.layer setBorderColor:UIColor.grayColor.CGColor];
    [button.layer setBorderWidth:0.5];
    [button setTitle:@"运行Lua" forState:UIControlStateNormal];
    
    [button setFrame:CGRectMake(60, 100, 120, 40)];
    [button addTarget:self action:@selector(buttonAction:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
}

- (LuaState *)luaState {
    if (!_luaState) {
        _luaState = [LuaState new];
    }
    return _luaState;
}


- (void)buttonAction:(UIButton*)sender {
    
    LuaState *luaState = [self luaState];
    [luaState runFunctionNamed:@"addButton" arguments:@[self] rvalues:nil options:0 error:nil];
    
//    [[WMLuaRunner getInstance] runLua:luaScript];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
