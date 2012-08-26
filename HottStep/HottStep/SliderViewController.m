//
//  SliderViewController.m
//  HottStep
//
//  Created by Stacey Mulcahy on 8/25/12.
//  Copyright (c) 2012 Stacey Mulcahy. All rights reserved.
//

#import "SliderViewController.h"
#import"Background.h"

#import "VVOSC.h"

#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>

@implementation SliderViewController

{
    Background *bg;
    UIImageView *lightIndicator;
    UIImage *offLight;
    UIImage *onLight;
}
///slider id for the item
@synthesize sliderId=_sliderId;


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        
        bg = [[Background alloc]initWithFrame:CGRectMake(0,30,26,290)];
        
        [bg setBackgroundColor:[UIColor blackColor]];
        
        onLight = [UIImage imageNamed:@"onimage.png"];
        offLight =[UIImage imageNamed:@"offlight.png"];
        
        [self addSubview:bg];
        [self setBackgroundColor:[UIColor darkGrayColor]];

        lightIndicator = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 100, 30)];
        lightIndicator.image = offLight;
        sliderLabel = [[UILabel alloc]initWithFrame:CGRectMake(0,280,100,30)];
        sliderLabel.backgroundColor = [UIColor whiteColor];
      
        [self addSubview:sliderLabel];
        [self addSubview:lightIndicator];
        [lightIndicator release];
        [bg release];
        [sliderLabel release];
        [self initOSC];
        
    }
    return self;
}

-(void)initOSC
{
    // OSC
	manager = [[OSCManager alloc] init];
	[manager setDelegate:self];
	
	// sending, the IP & Port you want to send to
	//sendingToIP = @"202.175.157.76";
    sendingToIP = @"192.168.1.80";
	sendingToPort = 12345;
	outPort = [manager createNewOutputToAddress:sendingToIP atPort:sendingToPort];
    
	OSCMessage *ip = [OSCMessage createWithAddress:@"/ip"];
	[ip addString:[self getMyWifiIP]];
	[outPort sendThisPacket:[OSCPacket createWithContent:ip]];
	
	OSCMessage *uniqueID = [OSCMessage createWithAddress:@"/unique"];
	[uniqueID addString:[[UIDevice currentDevice] uniqueIdentifier]];
	[outPort sendThisPacket:[OSCPacket createWithContent:uniqueID]];
	
	
	// receiving
	receivingOnPort = 51234;
	//inPort = [manager createNewInput]; // default at port 1234
	inPort = [manager createNewInputForPort:receivingOnPort];
	
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
   
    if(bg.hidden == YES)
    {
        [bg setHidden:NO];
    }
    // we need to store the position here
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSLog(@"touches moved");
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint location = [touch locationInView:touch.view];
    CGPoint pastLocation = [touch previousLocationInView:self]; //previous touch
 
    [bg drawTheSlider:location.y];

    NSMutableString *labelString =[[NSMutableString alloc] init];
    [labelString appendString:@"/fuck/"];
    [labelString appendString:sliderLabel.text];
    [self sendOSCMessage:287-location.y label:labelString];
    [labelString release];
    
    // need to draw something here to show how big this item should be 
    
    
    
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    NSUInteger numTaps = [[touches anyObject] tapCount];
    if(numTaps == 2)
    {
        [bg setHidden:YES];
        
    }
   
}

// TO DO IMPLEMENT THIS

/*
-(NSNumber *)normalize:(NSInteger *)value minimum:(double *)min maximum:(double *)max
{
 
    // 
  // return ((value-min)/(max-min));
    
}
 
 */

-(void)turnItemOn:(BOOL)isOn
{
    if(isOn == YES)
    {
        // do this shit
        lightIndicator.image = onLight;
    }else
    {
        //not on do this shit
        lightIndicator.image = offLight;
    }
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/
// called by delegate on message
- (void) receivedOSCMessage:(OSCMessage *)m	{
	
	NSString *address = [m address];
	OSCValue *value = [m value];
	NSString *message;
    
	if ([address isEqualToString:@"/mouseX"]) {
		message = [NSString stringWithFormat:@"mouseX: %i", [value intValue]];
		NSString *txt = [NSString stringWithFormat:@"%i", [value intValue]];
		[receivingDataLabel performSelectorOnMainThread:@selector(setText:) withObject:txt waitUntilDone:NO];
		
	} else if ([address isEqualToString:@"/mouseY"]) {
		message = [NSString stringWithFormat:@"mouseY: %i", [value intValue]];
	} else if ([address isEqualToString:@"/floatArray"]) {
		message = [NSString stringWithFormat:@"floatArray: %f", [value floatValue]];
	}
	
	NSLog(@"%@: %@", address, value);
}


-(void)setSliderId:(NSString *)sliderId
{
    _sliderId = sliderId;
    sliderLabel.text = _sliderId;
    NSLog(@"oh man");
    [self setNeedsDisplay];
}
- (void)sendOSCMessage:(float)floatMessage label:(NSString*)label {
	OSCMessage *msg = [OSCMessage createWithAddress:label];
	[msg addFloat:floatMessage];
	[outPort sendThisPacket:[OSCPacket createWithContent:msg]];
}

-(NSString *) getMyWifiIP {
	BOOL success;
	struct ifaddrs * addrs;
	const struct ifaddrs * cursor;
	
	success = getifaddrs(&addrs) == 0;
	if (success) {
		cursor = addrs;
		while (cursor != NULL) {
			if (cursor->ifa_addr->sa_family == AF_INET && (cursor->ifa_flags & IFF_LOOPBACK) == 0) // this second test keeps from picking up the loopback address
			{
				NSString *name = [NSString stringWithUTF8String:cursor->ifa_name];
				if ([name isEqualToString:@"en0"]) { // found the WiFi adapter
					return [NSString stringWithUTF8String:inet_ntoa(((struct sockaddr_in *)cursor->ifa_addr)->sin_addr)];
				}
			}
			
			cursor = cursor->ifa_next;
		}
		freeifaddrs(addrs);
	}
	return NULL;
}



@end
