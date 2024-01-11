//
//  ViewController.m
//  WebViewTest-iOS
//
//  Created by wuyoujian on 2018/4/13.
//  Copyright © 2018年 AI. All rights reserved.
//

#import "ViewController.h"
#import <WebKit/WebKit.h>


@interface ViewController ()
@property (nonatomic,strong) WKWebView  *wkWebView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [self layoutWebView];
}

- (void)layoutWebView {
    WKWebViewConfiguration *config = [[WKWebViewConfiguration alloc] init];
    //通过默认的构造器来创建对象
    WKWebView *wkWebView = [[WKWebView alloc] initWithFrame:self.view.bounds configuration:config];
    self.wkWebView = wkWebView;
    [self.view addSubview:wkWebView];
    
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSURL *url = [NSURL fileURLWithPath:[mainBundle pathForResource:@"index" ofType:@"html" inDirectory:@"html"]];
    NSURLRequest *request = [NSURLRequest requestWithURL:url cachePolicy:NSURLRequestReloadIgnoringCacheData timeoutInterval:30.0];
    [_wkWebView loadRequest:request];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



@end
