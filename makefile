gcno=test/*.gcno
gcda=test/*.gcda
exe=test/*.exe
gcov=*.gcov

default:
	gcc main.c src/*.c -I include/ -o ./bin/main.exe
	./bin/main.exe

.PHONY: test

test: testTrashInput testSelfCapture testQueen testBishop testPawn testRook testKing

testTrashInput:
	gcc -fprofile-arcs -ftest-coverage test/testTrashInput.c src/*.c -I include -o test/tTI.exe
	test/tTI.exe
	gcov test/tTI-makeMove.gcno

testSelfCapture:
	gcc -fprofile-arcs -ftest-coverage test/testSelfCapture.c src/*.c -I include -o test/tSC.exe
	test/tSC.exe
	gcov test/tSC-makeMove.gcno

testQueen:
	gcc -fprofile-arcs -ftest-coverage test/testQueen.c src/*.c -I include -o test/tq.exe
	test/tq.exe
	gcov test/tq-queen.gcno

testBishop:
	gcc -fprofile-arcs -ftest-coverage test/testBishop.c src/*.c -I include -o test/tb.exe
	test/tb.exe
	gcov test/tb-bishop.gcno

testKnight:
	gcc -fprofile-arcs -ftest-coverage test/testKnight.c src/*.c -I include -o test/tn.exe
	test/tn.exe
	gcov test/tn-knight.gcno

testRook:
	gcc -fprofile-arcs -ftest-coverage test/testRook.c src/*.c -I include -o test/tr.exe
	test/tr.exe
	gcov test/tr-rook.gcno 

testPawn:
	gcc -fprofile-arcs -ftest-coverage test/testPawn.c src/*.c -I include -o test/tp.exe
	test/tp.exe
	gcov test/tp-pawn.gcno

clean:
	rm $(gcno) $(gcda) $(exe) $(gcov)
