gcno=test/*.gcno
gcda=test/*.gcda
exe=test/*.exe
gcov=*.gcov

default:
	gcc src/*.c -I include/ -o ./bin/main.exe
	./bin/main.exe

.PHONY: test
test: testSelfCapture testQueen testBishop testPawn

testSelfCapture:
	gcc -fprofile-arcs -ftest-coverage test/testSelfCapture.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c -I include -o test/tSC.exe
	test/tSC.exe
	gcov test/tSC-makeMove.gcno

testQueen:
	gcc -fprofile-arcs -ftest-coverage test/testQueen.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c -I include -o test/tq.exe
	test/tq.exe
	gcov test/tq-queen.gcno

testBishop:
	gcc -fprofile-arcs -ftest-coverage test/testBishop.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c src/bishop.c -I include -o test/tb.exe
	test/tb.exe
	gcov test/tb-bishop.gcno

testKnight:
	gcc -fprofile-arcs -ftest-coverage test/testKnight.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c src/bishop.c -I include -o test/tn.exe
	test/tn.exe
	gcov test/tn-knight.gcno

testKing:
	gcc -fprofile-arcs -ftest-coverage test/testKing.c src/king.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c src/bishop.c -I include -o test/tk.exe
	test/tk.exe
	gcov test/tk-king.gcno

testPawn:
	gcc -fprofile-arcs -ftest-coverage test/testPawn.c src/king.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c src/bishop.c -I include -o test/tp.exe
	test/tp.exe
	gcov test/tp-pawn.gcno

clean:
	rm $(gcno) $(gcda) $(exe) $(gcov)
