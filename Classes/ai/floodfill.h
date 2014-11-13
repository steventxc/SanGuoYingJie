//
//  floodfill.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__floodfill__
#define __SanGuoYingJie__floodfill__

#include <vector>

using namespace std;

template <class UserState> class FloodFillSearch
{
public:
    
    void SetupWithStartStates(UserState &Start, unsigned limited)
    {
        m_Start = Start;
        m_Limited = limited;
        
        SearchStep(m_Start);
    }
    
    vector<UserState> getResultSet()
    {
        return m_ResultList;
    }
    
    
protected:
    
    void SearchStep(UserState userNode)
    {
        // from back to head.
        for (int i = m_ResultList.size()-1; i>=0; i--) {
            if( userNode.IsSameState( m_ResultList[i] ) )
            {
                return;
            }
        }
        

        m_ResultList.push_back( userNode );
        
        const int x = userNode.x;
        const int y = userNode.y;
        
        
        UserState node(x-1, y);
        
        if (node.isValid() &&
            ( node.GoalDistanceEstimate(m_Start) <= m_Limited )
            ) {
                SearchStep(node);
        }
        
        
        node = UserState(x, y-1);
        
        if (node.isValid() &&
            ( node.GoalDistanceEstimate(m_Start) <= m_Limited )
            ) {
            SearchStep(node);
        }
        
        
        node = UserState(x+1, y);
        
        if (userNode.isValid() &&
            ( userNode.GoalDistanceEstimate(m_Start) <= m_Limited )
            ) {
            SearchStep(node);
        }

        
        node = UserState(x, y+1);
        
        if (userNode.isValid() &&
            (userNode.GoalDistanceEstimate(m_Start) <= m_Limited )
            ) {
            SearchStep(node);
        }

    }
    
    
private:
    
    UserState m_Start;
    unsigned m_Limited;
    vector<UserState> m_ResultList;
    
};

#endif /* defined(__SanGuoYingJie__floodfill__) */
