"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    turns = 0;
    
    for i in board:
        for j in i:
            if j == X or j == O:
                turns += 1
        
    if turns % 2 == 1:
        return O
    elif turns % 2 == 0:
        return X
    
    if terminal(board) == True:
        return None


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    
    #Creating the set
    possibleActions = set()
    
    #Indexes for the tuple
    i = 0
    j = 0
    
    #Iterating through the board, keeping track of all of the possible actions
    for rows in board:
        for columns in rows:
            if columns == EMPTY:
                
                #Sets only take one argument
                possibleActions.add((i, j))
                
            j += 1
        i += 1
        j = 0
        
    return possibleActions

def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    turn = player(board)
        
    # Checking if the move is a valid move
    validActions = []
    validActions = list(actions(board))
    
    if action in validActions:
        
        newBoard = copy.deepcopy(board)
        
        newBoard[action[0]][action[1]] = turn
        
        return newBoard
    
    raise Exception

def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    
    Xcounter = 0
    Ocounter = 0
    
    #Checking for horizontal matches
    for rows in board:
        for columns in rows:
            if columns == X:
                Xcounter += 1
            elif columns == O:
                Ocounter += 1
                
            if Xcounter == 3:
                return X
            elif Ocounter == 3:
                return O
            
        Xcounter = 0
        Ocounter = 0
        
    #Checking for vertical matches
    i = 0
    j = 0
    
    while j < 3:
        while i < 3:
            if board[i][j] == X:
                Xcounter += 1
            elif board[i][j] == O:
                Ocounter += 1
                
            if Xcounter == 3:
                return X
            elif Ocounter == 3:
                return O
            
            i += 1
        
        Xcounter = 0
        Ocounter = 0
        
        j += 1
        i = 0
    
    #Checking for diagonals
    if board[0][0] == X and board[1][1] == X and board[2][2] == X:
        return X
    if board[0][0] == O and board[1][1] == O and board[2][2] == O:
        return O
    if board[0][2] == X and board[1][1] == X and board[2][0] == X:
        return X
    if board[0][2] == O and board[1][1] == O and board[2][0] == O:
        return O
    
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) == X or winner(board) == O:
        return True
    if winner(board) == None and len(actions(board)) == 0:
        return True
    return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    
    # Checking if the game is over
    if terminal(board):
        return None
    
    turn = player(board)
    
    optimalAction = None
    
    if turn == X:
        v = -1000
        
        # Looping through all the possible actions
        for action in actions(board):
            
            #Picking the smallest value, assuming the opponent is playing optimally 
            possibleV = minvalue(result(board, action))
            
            if possibleV > v:
                v = possibleV
                
                optimalAction = action
                
        return optimalAction
    
    elif turn == O:
        v = 1000
        
        #Looping 
        for action in actions(board):
            
            #Picking largest value
            possibleV = maxvalue(result(board, action))
            
            if possibleV < v:
                v = possibleV
                
                optimalAction = action
                
        return optimalAction

def minvalue(board):
    # Helper function that gets the minimum value
    
    # Checking if the board is a teminal (or finished) board
    if terminal(board):
        return utility(board)
    
    # Creating a variable that is at infinity, so the minimum gamestate is always better
    v = float("inf")
    
    for action in actions(board):
        # Reassigning the 'v' variable to the minimum value of maxvalue function, assuming played optimally
        v = min(v, maxvalue(result(board, action)))
    
    return v

def maxvalue(board):
    # Helper function that gets the maximum value
    
    # Checking if the board is a terminal (or finished) board
    if terminal(board):
        return utility(board)
    
    # Creating a variable that is at negative infinity, since the max value should always be higher
    v = float("-inf")
    
    for action in actions(board):
        # Reassigning the v variable 
        v = max(v, minvalue(result(board, action)))
                
    return v
    
