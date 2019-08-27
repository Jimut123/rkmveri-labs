# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import time
import util

RET_PATH = []


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the start
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    from util import Stack
    fringe = Stack()                
    fringe.push(problem.getStartState())
    visited = []                    
    path=[]                         
    pathdirection=Stack()           
    current = fringe.pop()
    while not problem.isGoalState(current):
        if current not in visited:
            visited.append(current)
            successors = problem.getSuccessors(current)
            for child,dir,cost in successors:
                fringe.push(child)
                tpath = path + [dir]
                pathdirection.push(tpath)
        current = fringe.pop()
        path = pathdirection.pop()
    return path
    
def breadthFirstSearch(problem):
    
    from util import Queue
    fringe = Queue()                        
    fringe.push(problem.getStartState())
    visited = []                            
    tpath=[]                             
    path=[]                                 
    pathdirection=Queue()                   
    current = fringe.pop()
    while not problem.isGoalState(current):
        if current not in visited:
            visited.append(current)    
            successors = problem.getSuccessors(current)
            for child,dir,cost in successors:
                fringe.push(child)
                tpath = path + [dir]
                pathdirection.push(tpath)
        current = fringe.pop()
        path = pathdirection.pop()
        
    return path

def uniformCostSearch(problem):

    from util import Queue,PriorityQueue
    fringe = PriorityQueue()                   
    fringe.push(problem.getStartState(),0)
    visited = []                                
    tpath=[]                                 
    path=[]                                  
    pathdirection=PriorityQueue()               
    current = fringe.pop()
    while not problem.isGoalState(current):
        if current not in visited:
            visited.append(current)
            successors = problem.getSuccessors(current)
            for child,dir,cost in successors:
                tpath = path + [dir]
                priority = problem.getCostOfActions(tpath)
                if child not in visited:
                    fringe.push(child,priority)
                    pathdirection.push(tpath,priority)
        current = fringe.pop()
        path = pathdirection.pop()    
    return path

def nullHeuristic(state, problem=None):
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):

    from util import Queue,PriorityQueue
    fringe = PriorityQueue()                    
    fringe.push(problem.getStartState(),0)
    current = fringe.pop()
    visited = []                                
    tpath=[]                                 
    path=[]                                     
    pathdirection=PriorityQueue()               
    while not problem.isGoalState(current):
        if current not in visited:
            visited.append(current)
            successors = problem.getSuccessors(current)
            for child,dir,cost in successors:
                tpath = path + [dir]
                priority = problem.getCostOfActions(tpath) + heuristic(child,problem)
                if child not in visited:
                    fringe.push(child,priority)
                    pathdirection.push(tpath,priority)
        current = fringe.pop()
        path = pathdirection.pop()    
    return path
    


bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch