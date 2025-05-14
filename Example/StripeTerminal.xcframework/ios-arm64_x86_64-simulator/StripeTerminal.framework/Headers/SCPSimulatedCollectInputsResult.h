#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The supported behaviors for simulating skipping inputs
 */
typedef NS_ENUM(NSInteger, SCPSimulatedCollectInputsSkipBehavior) {
    /**
     Don't skip any of the inputs.
     */
    SCPSimulatedCollectInputsSkipBehaviorNone,
    /**
     Skip all of the non-required inputs.
     */
    SCPSimulatedCollectInputsSkipBehaviorAll
} NS_SWIFT_NAME(SimulatedCollectInputsSkipBehavior);

/**
 Simulated collect inputs result objects can be used with the shared
 `SCPSimulatorConfiguration` to simulate different input collection results.
 */
NS_SWIFT_NAME(SimulatedCollectInputsResult)
@interface SCPSimulatedCollectInputsResult : NSObject
@end

/**
 Simulate a successful collect inputs

 Based on the input type, the SDK returns a predefined value. The predefined values are:
 - selection -> (value of first option)
 - signature -> (a valid SVG image string)
 - email -> "someone@example.com"
 - phone -> "+15555551234"
 - text -> "Jane Doe"
 - numeric -> "2907981236"

 If any toggles are specified, their default value is selected and returned.
 */
NS_SWIFT_NAME(SimulatedCollectInputsResultSucceeded)
@interface SCPSimulatedCollectInputsResultSucceeded : SCPSimulatedCollectInputsResult

/**
 The skip behavior to use while simulating a successful input collection.
 */
@property (nonatomic, assign) SCPSimulatedCollectInputsSkipBehavior simulatedCollectInputsSkipBehavior;

/**
 Initializes a new instance of the `SCPSimulatedCollectInputsResultSucceeded` class with the provided
 skip behavior.

 @param skipBehavior The skip behavior to use while simulating input collection.
 */
- (instancetype)initWithSimulatedCollectInputsSkipBehavior:(SCPSimulatedCollectInputsSkipBehavior)skipBehavior;

/**
 You cannot instantiate this class without specifying a skip behavior
 */
+ (instancetype)new NS_UNAVAILABLE;

/**
 You cannot instantiate this class without specifying a skip behavior
 */
- (instancetype)init NS_UNAVAILABLE;
@end

/**
 Simulate a collect inputs where collection times out
 */
NS_SWIFT_NAME(SimulatedCollectInputsResultTimeout)
@interface SCPSimulatedCollectInputsResultTimeout : SCPSimulatedCollectInputsResult
@end

NS_ASSUME_NONNULL_END
