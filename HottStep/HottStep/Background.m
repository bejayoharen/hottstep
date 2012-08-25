//
//  Background.m
//  HottStep
//
//  Created by Stacey Mulcahy on 8/25/12.
//  Copyright (c) 2012 Stacey Mulcahy. All rights reserved.
//

#import "Background.h"

@implementation Background

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}
-(void)drawTheSlider:(NSInteger)height
{
    [self setFrame:CGRectMake(self.frame.origin.x,0,self.frame.size.width,height)];
    [self setNeedsDisplay];    
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
