//
//  floodfill.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__floodfill__
#define __SanGuoYingJie__floodfill__

#include <stdio.h>

template <class UserState> class FloodFillSearch
{
    UserState m_UserStart;
    unsigned m_Limited;
    
public:
    
    void SetStartStates(UserState &Start, unsigned limited)
    {
        m_UserStart = Start;
        m_Limited = limited;
    }
    
    void SearchStep(float x, float y)
    {
        
        if (m_UserStart.isValid(x - 1, y) &&
            ( m_UserStart.GoalDistanceEstimate(m_UserStart) <= m_Limited )
            ) {
            SearchStep(x-1, y);
        }
        
        if (m_UserStart.isValid(x, y - 1) &&
            ( m_UserStart.GoalDistanceEstimate(m_UserStart) <= m_Limited )
            ) {
            SearchStep(x, y-1);
        }
        
        if (m_UserStart.isValid(x + 1, y) &&
            ( m_UserStart.GoalDistanceEstimate(m_UserStart) <= m_Limited )
            ) {
            SearchStep(x+1, y);
        }
        
        if (m_UserStart.isValid(x, y + 1) &&
            ( m_UserStart.GoalDistanceEstimate(m_UserStart) <= m_Limited )
            ) {
            SearchStep(x, y+1);
        }
    }
};

#endif /* defined(__SanGuoYingJie__floodfill__) */
