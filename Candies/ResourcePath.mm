#import "ResourcePath.h"
#import <Foundation/Foundation.h>

std::string getResourcePath(const std::string& filename)
{
    return [[[NSBundle mainBundle] resourcePath] UTF8String] + ("/" + filename);
}