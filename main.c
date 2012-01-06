#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>


int main (int argc, const char * argv[]) {
	CFDataRef data;
	
	io_service_t platformExpert = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("IOPlatformExpertDevice"));
	if (platformExpert)
	{
		data = IORegistryEntryCreateCFProperty(platformExpert,
											   CFStringCreateWithCString(
																		 NULL,
																		 argv[1],
																		 kCFStringEncodingUTF8),
											   kCFAllocatorDefault, 0);
	}
	
	IOObjectRelease(platformExpert);
	CFIndex bufferLength = CFDataGetLength(data);  
	UInt8 *buffer = malloc(bufferLength);
	CFDataGetBytes(data, CFRangeMake(0,bufferLength), (UInt8*) buffer);
	CFStringRef string = CFStringCreateWithBytes(kCFAllocatorDefault,
												 buffer,
												 bufferLength,
												 kCFStringEncodingUTF8,
												 TRUE);
	CFShow(string);
	return 0;
	
}