gcno=tests/unitTests/*.gcno
gcda=tests/unitTests/*.gcda
exe=tests/unitTests/*.exe
gcov=*.gcov

default:
	gcc main.c src/*.c -I include/ -o ./bin/main.exe

.PHONY: tests

run: default
	./bin/main.exe

intTests: intExit

intExit: default
	./bin/main.exe < ./tests/integrationTests/exit/input.txt > ./tests/integrationTests/exit/out.txt
	diff ./tests/integrationTests/exit/out.txt ./tests/integrationTests/exit/refOut.txt

unitTests: unitTrashInput unitSelfCapture unitQueen unitBishop unitPawn unitRook unitKing

unitTrashInput:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utTrashInput.c src/*.c -I include -o tests/unitTests/tTI.exe
	tests/unitTests/tTI.exe
	gcov tests/unitTests/tTI-makeMove.gcno

unitSelfCapture:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utSelfCapture.c src/*.c -I include -o tests/unitTests/tSC.exe
	tests/unitTests/tSC.exe
	gcov tests/unitTests/tSC-makeMove.gcno

unitQueen:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utQueen.c src/*.c -I include -o tests/unitTests/tq.exe
	tests/unitTests/tq.exe
	gcov tests/unitTests/tq-queen.gcno

unitBishop:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utBishop.c src/*.c -I include -o tests/unitTests/tb.exe
	tests/unitTests/tb.exe
	gcov tests/unitTests/tb-bishop.gcno

unitKnight:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utKnight.c src/*.c -I include -o tests/unitTests/tn.exe
	tests/unitTests/tn.exe
	gcov tests/unitTests/tn-knight.gcno

unitRook:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utRook.c src/*.c -I include -o tests/unitTests/tr.exe
	tests/unitTests/tr.exe
	gcov tests/unitTests/tr-rook.gcno 

unitPawn:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utPawn.c src/*.c -I include -o tests/unitTests/tp.exe
	tests/unitTests/tp.exe
	gcov tests/unitTests/tp-pawn.gcno

unitKing:
	gcc -fprofile-arcs -ftest-coverage tests/unitTests/utKing.c src/*.c -I include -o tests/unitTests/tk.exe
	tests/unitTests/tk.exe
	gcov tests/unitTests/tk-king.gcno

clean:
	rm $(gcno) $(gcda) $(exe) $(gcov)
