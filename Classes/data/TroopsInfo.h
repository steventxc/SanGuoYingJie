//
//  TroopsInfo.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__TroopsInfo__
#define __SanGuoYingJie__TroopsInfo__

#include <stdio.h>

class TroopsInfo
{
public:
    
    enum class TroopsType
    {
        INFANTRY,
        CAVALRY,
        ARCHER,
    };
    
public:
    /**
     *
     */
   static unsigned getTerrainsWithType(TroopsType type);
    
private:
    TroopsInfo(){}
};

#endif /* defined(__SanGuoYingJie__TroopsInfo__) */
