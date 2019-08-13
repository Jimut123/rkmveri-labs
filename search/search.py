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
        action, stepCost), where 'successor' is a successor to the current
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
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    """
    #print("Start:", problem.getStartState())
    #print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    #print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    
    distance_list = []

    my_stack = util.Stack()
    current_state = problem.getStartState()
    #print("Started at => ",current_state)
    visited = []
    #visited.append(current_state)
    while problem.isGoalState(current_state) == False: 
      
      #print("State obtained => ",distance_list)
      get_sucessors = problem.getSuccessors(current_state)
      #get_sucessors.reverse()
      #print("Successors => ",get_sucessors)
      #my_stack.showStack()
      for items_coord in get_sucessors:
        if items_coord[0] not in visited:
          
          my_stack.push(items_coord)

      
      if my_stack.isEmpty():
        break
      else:
        # my_stack.showStack()
        current_state_tuple = my_stack.pop()
        visited.append(current_state_tuple[0])
        # if my_stack.inMyStack(current_state_tuple) == True:
        #   print("********* it's present")
        # my_stack.showStack()
        current_state = current_state_tuple[0]
        #print("cur coord => ",current_state)
        distance_list.append(current_state_tuple[1][0].lower())
      #util.pause()
    #util.pause()
    #util.raiseNotDefined()
    #print("State obtained => ",distance_list)
    #print("Distance list => ",distance_list)
    print(distance_list)
    d_list = []
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST
    for item in distance_list:
        if item == 's':
          d_list.append(s)
        if item == 'e':
          d_list.append(e)
        if item == 'n':
          d_list.append(n)
        if item == 'w':
          d_list.append(w)
    util.pause()
    return d_list

    """
    path = []
    visited = []
    parent = {}
    current_state = problem.getStartState()
    x = current_state
    y = (1,1)
    def dfs(current_state):
      visited.append(current_state)
      get_sucessors = problem.getSuccessors(current_state)

      for items_coord in get_sucessors:
        if items_coord[0] not in visited:
          if problem.isGoalState(items_coord[0]):
            y = items_coord[0]
            parent[items_coord[0]] = current_state
            return
            
          parent[items_coord[0]] = current_state
          dfs(items_coord[0])
    dfs(current_state)
    #print(parent)
    print(y)
    print(x)
    while parent[y] != x:
      z = parent[y]
      if y[0] == z[0]:
        if z[1] > y[1]:
          path.append('s')
        else:
          path.append('n')
      else:
        if y[1] > z[1]:
          path.append('e')
        else:
          path.append('w')
      y = z
    path.append('s')
    path.reverse()
    d_list = []
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    n = Directions.NORTH
    e = Directions.EAST
    for item in path:
        if item == 's':
          d_list.append(s)
        if item == 'e':
          d_list.append(e)
        if item == 'n':
          d_list.append(n)
        if item == 'w':
          d_list.append(w)
    print(path)
    return d_list

    

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
