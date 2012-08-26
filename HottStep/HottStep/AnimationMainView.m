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
        currentIndex = 0;
        totalNumber = 16;
        [self initializeView];
    
       
        // Initialization code
    }
    return self;
}

-(void) initializeView
{
    
    
    for(int i = 0;i<17;i++)
    {
        
        SliderViewController *slider = [[SliderViewController alloc] initWithFrame:CGRectMake(i*28, 0, 100, 480)];
        [sliders addObject:slider];
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

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    
    NSLog(@"stacey");
}


-(void)updateData
{
    NSLog(@"Update the data");
    currentIndex++;
    NSLog(@"current index @%i",currentIndex);
    if(currentIndex == totalNumber)
    {
        currentIndex = 1;
    }
    self.frame = CGRectMake(0,0,self.frame.size.width,self.frame.size.height);
    for(int i=0;i<7;i++)
    {
        NSInteger *position = i+currentIndex;
        //SliderViewController * s = [sliders objectAtIndex:i];
        [[self.subviews objectAtIndex:i]setSliderId:[NSString stringWithFormat:@"%d",position]];
      
     NSLog(@"current index @%i",position);
        //[s setSliderId:@"FUCK @%",position];
        //[s setSliderId:[NSString stringWithFormat:@"%d",position]];
    }
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
