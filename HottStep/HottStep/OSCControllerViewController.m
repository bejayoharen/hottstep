//
//  OSCControllerViewController.m
//  HottStep
//
//  Created by Stacey Mulcahy on 8/25/12.
//  Copyright (c) 2012 Stacey Mulcahy. All rights reserved.
//

#import "OSCControllerViewController.h"
#import "SliderViewController.h"

@interface OSCControllerViewController ()

@end

@implementation OSCControllerViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
   // NSInteger *newWidth = 16 *100;// should declare teh width of the item
    mainView = [[AnimationMainView alloc]initWithFrame:CGRectMake(0,0,700,480)];
    [self.view addSubview: mainView];
    [mainView release];
    
    
    //[self.view addSubview:slider];
	// Do any additional setup after loading the view, typically from a nib.
}

-(void)animateViews
{
    // can i animate the items
    
    // check if the item is out of view if it is, 
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
