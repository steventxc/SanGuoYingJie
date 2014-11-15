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
    
    class MapNode
    {
    public:
        int step;
        
        MapNode() :
            step(0)
        {
        }
        
        UserState m_UserState;
    };
    
public:
    
    void SetupWithStartStates(UserState &Start, unsigned limited)
    {
        m_Start = new MapNode();
        m_Start->m_UserState = Start;
        
        m_Limited = limited;
        
        SearchStep(m_Start);
    }
    
    vector<UserState*> getResultSet()
    {
        vector<UserState*> _results;
        
        for (result_iter = m_ResultList.begin(); result_iter != m_ResultList.end(); ++result_iter)
        {
            _results.push_back( &((*result_iter)->m_UserState) );
        }
        
        return _results;
    }
    
    void FreeSolutionNodes()
    {
        for (result_iter = m_ResultList.begin(); result_iter!=m_ResultList.end(); result_iter++)
        {
            delete (*result_iter);
        }
        
        m_ResultList.clear();
    }
    
protected:
    
    void SearchStep(MapNode *userNode)
    {
        
        const int step = userNode->step;
        
        for (result_iter = m_ResultList.begin(); result_iter != m_ResultList.end(); result_iter++) {
            if ( userNode->m_UserState.IsSameState( (*result_iter)->m_UserState ) ) {
                
                // we use new node which have less step value
                // instead of the one which add before.
                if (step < (*result_iter)->step ) {
                    m_ResultList.erase(result_iter);
                    
                    break;
                }
                else {
                    return;
                }
            }
        }
        

        m_ResultList.push_back( userNode );
        
        const int x = userNode->m_UserState.x;
        const int y = userNode->m_UserState.y;
        
        
        
        UserState node(x-1, y);
        
        if (node.isValid() &&
            ( step <= m_Limited )
            ) {
            
            auto _node = new MapNode;
            _node->m_UserState = node;
            _node->step = step + node.GetCost(node);
            SearchStep(_node);
        }
        
        
        node = UserState(x, y-1);
        
        if (node.isValid() &&
            (step <= m_Limited )
            ) {
            
            auto _node = new MapNode;
            _node->m_UserState = node;
            _node->step = step + node.GetCost(node);
            SearchStep(_node);
        }
        
        
        node = UserState(x+1, y);
        
        if (node.isValid() &&
            ( step <= m_Limited )
            ) {
            
            auto _node = new MapNode;
            _node->m_UserState = node;
            _node->step = step + node.GetCost(node);
            SearchStep(_node);
        }

        
        node = UserState(x, y+1);
        
        if (node.isValid() &&
            ( step <= m_Limited )
            ) {

            auto _node = new MapNode;
            _node->m_UserState = node;
            _node->step = step + node.GetCost(node);
            SearchStep(_node);
        }

    }
    
    
private:
    
    MapNode *m_Start;
    unsigned m_Limited;
    vector<MapNode *> m_ResultList;
    typename vector<MapNode*>::iterator result_iter;
    
};

#endif /* defined(__SanGuoYingJie__floodfill__) */
