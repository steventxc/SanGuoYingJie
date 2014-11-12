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
    
    class Node
    {
    public:
        
        bool isVisited;
        
        Node() : isVisited( false ) { }
        
        UserState m_UserState;
    };
    
    
public:
    
    void SetStartStates(UserState &Start, unsigned limited)
    {
        m_Start = new Node;
        m_Start->m_UserState = Start;
        
        m_Limited = limited;
        
    }
    
    void startSearch()
    {
        SearchStep(m_Start);
    }
    
    vector<UserState> getResultSet()
    {
        vector<UserState> result;
        
        typename vector<Node *>::iterator iter;
        for (iter = m_ValidList.begin(); iter != m_ValidList.end(); iter ++) {
            result.push_back( (*iter)->m_UserState );
        }
        
        return result;
    }
    
    
    Node * createNode( UserState &State )
    {
        Node *node = new Node();
        
        if( node )
        {
            node->m_UserState = State;
            return node;
        }
        
        delete node;
        
        return nullptr;
    }
    
    void destroyNode(Node *node)
    {
        delete node;
    }
    
protected:
    
    void SearchStep(Node* node)
    {
        //        if (! node->m_UserState.IsSameState(m_Start->m_UserState)) {
        node->isVisited = true;
        m_ValidList.push_back( node );
        //        }
        
        const int x = node->m_UserState.x;
        const int y = node->m_UserState.y;
        
        if (!node->isVisited &&
            node->m_UserState.isValid() &&
            ( node->m_UserState.GoalDistanceEstimate(m_Start->m_UserState) <= m_Limited )
            ) {
            
            auto n = node->m_UserState.getNode(this, x-1, y);
            if (n) {
                SearchStep(n);
            }
            
        }
        
        if (!node->isVisited &&
            node->m_UserState.isValid() &&
            ( node->m_UserState.GoalDistanceEstimate(m_Start->m_UserState) <= m_Limited )
            ) {
            
            auto n = node->m_UserState.getNode(this, x, y-1);
            if (n) {
                SearchStep(n);
            }
            
        }
        
        if (!node->isVisited &&
            node->m_UserState.isValid() &&
            ( node->m_UserState.GoalDistanceEstimate(m_Start->m_UserState) <= m_Limited )
            ) {
            
            auto n = node->m_UserState.getNode(this, x+1, y);
            if (n) {
                SearchStep(n);
            }
            
        }
        
        if (!node->isVisited &&
            node->m_UserState.isValid() &&
            ( node->m_UserState.GoalDistanceEstimate(m_Start->m_UserState) <= m_Limited )
            ) {
            
            auto n = node->m_UserState.getNode(this, x, y+1);
            if (n) {
                SearchStep(n);
            }
            
        }
    }
    
    
private:
    
    Node *m_Start;
    unsigned m_Limited;
    vector<Node *> m_ValidList;
    
};

#endif /* defined(__SanGuoYingJie__floodfill__) */
