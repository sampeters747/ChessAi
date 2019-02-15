import chess
#Used to count how many board states have beeen visited on a search
COUNT = 0


def evaluate_board(board):
    #Score telling us the state of the game, positive means white is winning, negative means black is winning
    score = 0
    '''
    Adding the value of the white pieces to our board score
    board.occupied_co[WHITE] gives us a set of the squares WHITE occupies, and board.pawns give us all squares pawns occupy.
    I check where they overlap to count the number of white pawns, then multiply that by the value of the pawn piece
    Repeat the process for all other piece types (white rook, black king, etc...)
    '''
    score += bin(board.occupied_co[True] & board.pawns).count('1') * 1
    score += bin(board.occupied_co[True] & board.rooks).count('1') * 5
    score += bin(board.occupied_co[True] & board.bishops).count('1') * 3
    score += bin(board.occupied_co[True] & board.knights).count('1') * 3
    score += bin(board.occupied_co[True] & board.queens).count('1') * 10
    score += bin(board.occupied_co[True] & board.kings).count('1') * 50
    #We do the same thing for the black pieces
    score -= bin(board.occupied_co[False] & board.pawns).count('1') * 1
    score -= bin(board.occupied_co[False] & board.rooks).count('1') * 5
    score -= bin(board.occupied_co[False] & board.bishops).count('1') * 3
    score -= bin(board.occupied_co[False] & board.knights).count('1') * 3
    score -= bin(board.occupied_co[False] & board.queens).count('1') * 10
    score -= bin(board.occupied_co[False] & board.kings).count('1') * 50
    return score

def maximize(a, b, depth, board):
    global COUNT
    COUNT += 1
    legal_moves = board.legal_moves
    #Checking if the game is over, and sending back a score if it is
    if not any(legal_moves):
        result = board.result()
        #Black wins
        if result == "0-1":
            return -100
        #White wins
        if result == "1-0":
            return 100
        #Draw
        if result == "1/2-1/2":
            return 0
    #Evaluates the board if we reached prechosen depth
    if depth <= 0:
        return evaluate_board(board)
    for move in legal_moves:
        board.push(move)
        COUNT += 1
        branch_value = minimize(a, b, depth-1, board)
        board.pop()
        if branch_value >= b:
            return b
        if branch_value > a:
            a = branch_value
    return a

def minimize(a, b, depth, board):
    global COUNT
    COUNT += 1
    legal_moves = board.legal_moves
    #Checking if the game is over, and sending back a score if it is
    if not any(legal_moves):
        result = board.result()
        #Black wins
        if result == "0-1":
            return -100
        #White wins
        if result == "1-0":
            return 100
        #Draw
        if result == "1/2-1/2":
            return 0
    #Evaluates the board if we reached prechosen depth
    if depth <= 0:
        return evaluate_board(board)
    for move in legal_moves:
        board.push(move)
        branch_value = maximize(a, b, depth-1, board)
        board.pop()
        if branch_value <= a:
            return a
        if branch_value < b:
            b = branch_value
    return b

def sort_moves(board, best_move):
    '''Sorts our starting moves so the most promising are first, minimizing the amount of work we have to do'''
    moves = []
    for move in board.legal_moves:
        moves.append(move)
    for capture in board.generate_legal_captures():
        moves.remove(capture)
        moves.append(capture)
    if best_move:
        moves.remove(best_move)
        moves.append(best_move)
    moves.reverse()
    return moves

def iterative_deepening(board, maxdepth):
    '''Does multiple min-max searches of increasing depth'''
    best_move = None
    best_score = -1000
    depth = 2
    moves = sort_moves(board, best_move)
    a = -10000
    b = 10000
    while depth < maxdepth:
        for move in moves:
            board.push(move)
            value = minimize(a, b, depth, board)
            if value > best_score:
                best_score = value
                best_move = move
        depth += 1
    return best_move, best_score

def main():
    '''Game wrapper'''
    print('New game')
    #Creates board object
    #Argument is a board state a bit farther in, because opening is boring
    board = chess.Board('r5rk/p6p/1p1N1p1b/8/3PP2Q/2P2q2/P4PNP/R4K2 w - - 0 15')
    player_turn = True
    #Each loop either the player or the bot moves
    while True:
        if player_turn = True:
            move = input("Make a move:")
            if move == 'quit':
                break
            #Makes the player move
            board.push_san(move)
        else:
            move, score = iterative_deepening(board, 5)
            if move == None:
                break
            board.push(move)
            print(f'Computer move:{move} with score of {score}')
        print(board)
        print('\n')
        
main()
