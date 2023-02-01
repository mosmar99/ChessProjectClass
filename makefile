
gcno=test/*.gcno
gcda=test/*.gcda
exe=test/*.exe
gcov=*.gcov

default:
	gcc src/*.c -I include/ -o ./bin/main.exe
	./bin/main.exe

.PHONY: test
test: testSelfCapture testQueen testBishop

testSelfCapture:
	gcc -fprofile-arcs -ftest-coverage test/testSelfCapture.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c -I include -o test/testSelfCapture.exe
	test/testSelfCapture.exe
	gcov test/testSelfCapture-testSelfCapture.gcno

testQueen:
	gcc test/testQueen.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c -I include -o test/tq.exe
	test/tq.exe

testBishop:
	gcc test/testBishop.c src/knight.c src/makeBoard.c src/makeMove.c src/pawn.c src/queen.c src/Rook.c src/bishop.c -I include -o test/tb.exe
	test/tb.exe

clean:
	rm $(gcno) $(gcda) $(exe) $(gcov)
