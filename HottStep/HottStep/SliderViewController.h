//
//  SliderViewController.h
//  HottStep
//
//  Created by Stacey Mulcahy on 8/25/12.
//  Copyright (c) 2012 Stacey Mulcahy. All rights reserved.
//

#import <UIKit/UIKit.h>
@class OSCManager, OSCInPort, OSCOutPort;

@interface SliderViewController : UIView

{
    NSString *sendingToIP;
	int sendingToPort;
	int receivingOnPort;
	
	BOOL slidingFlag;
	UILabel *sliderLabel;
	UILabel *sendingInfoLabel;
	UILabel *receivingInfoLabel;
	UILabel *receivingDataLabel;
	
	OSCManager *manager;
	OSCInPort *inPort;
	OSCOutPort *outPort;
    

}

@property (strong, nonatomic) NSString *sliderId;


- (void)sendOSCMessage:(float)floatMessage label:(NSString*)label;
-(void)turnItemOn:(BOOL) isOn;
-(NSString *) getMyWifiIP;
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;


@end
