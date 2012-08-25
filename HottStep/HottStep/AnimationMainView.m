//
//  AnimationMainView.m
//  HottStep
//
//  Created by Stacey Mulcahy on 8/25/12.
//  Copyright (c) 2012 Stacey Mulcahy. All rights reserved.
//

#import "AnimationMainView.h"
#import "SliderViewController.h";

@implementation AnimationMainView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self initializeView];
        // Initialization code
    }
    return self;
}

-(void) initializeView
{
    
    
    for(int i = 0;i<7;i++)
    {
        
        SliderViewController *slider = [[SliderViewController alloc] initWithFrame:CGRectMake(i*100, 0, 100, 480)];
        [slider setSliderId:[NSString stringWithFormat:@"%d",i]];
        [self addSubview:slider];
        [slider release];
        
    }
    //[self animateTheView];
         

}

-(void)animateTheView
{
    
    [UIView setAnimationDelegate:self];
    // [UIView setAnimationDidStopSelector:@selector(myAnimationStopped:finished:context:)];
    [UIView animateWithDuration:1 delay:0.0 options:nil
                     animations:^{
                         self.frame = CGRectMake(self.frame.origin.x-100,self.frame.origin.y, self.frame.size.width, self.frame.size.height);
                     }
                     completion:^(BOOL finished) {
                         [self updateData];
                     }];
    

}


-(void)updateData
{
    NSLog(@"Update the data");
    [self animateTheView];
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
