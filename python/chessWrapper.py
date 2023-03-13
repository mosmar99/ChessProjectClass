
import ctypes as ct

chessLib = ct.CDLL("./bin/chess.dll")

class chessGame():

    direction = True

    def __init__(self):
        chessLib.init()
        self.board = [["--"]*8 for i in range(8)]
        self.updateBoard()

    def updateBoard(self):
        arr = ((ct.c_char_p * 8) * 8)()
        chessLib.readBoard(arr)
        for x in range(8):
            for y in range(8):
                self.board[self.coordInDir(7-y)][self.coordInDir(x)] = arr[x][y].decode("utf-8")

    def tryTurn(self, fx, fy, tx, ty, mp, cp):
        result = int(chessLib.tryTurn(self.coordInDir(7-fx), self.coordInDir(fy), self.coordInDir(7-tx), self.coordInDir(ty), mp.encode(), cp.encode()))
        if result == 1:
            self.swapDir()
        return result

    def getPiece(self,x,y) -> str:
        return self.board[x][y]
    
    def coordInDir(self, v):
        if self.direction:
            return (7-v)
        else:
            return v
        
    def swapDir(self):
        if self.direction == True:
            self.direction = False
        else:
            self.direction = True

