COMPILER = g++ -std=c++11 #-Wall
#OMP = -Xpreprocessor -fopenmp -lomp #macosx
OMP = -fopenmp
CILK = -fcilkplus
TBB = -ltbb

%.o: %.cpp
	$(COMPILER) -c $< -o $@

benchmark: benchmark.cpp multtbbmatrix.cpp multcilkmatrix.cpp multompmatrix.cpp multseqmatrix.o matrix.o
	$(COMPILER) $(CILK) $(OMP) $^ -o $@	$(TBB)
multmatrix: multseqmain.o multseqmatrix.o matrix.o
	$(COMPILER) $^ -o $@
multmatrixtest: multmatrixtest.cpp multtbbmatrix.cpp multcilkmatrix.cpp multompmatrix.cpp multseqmatrix.o matrix.o
	$(COMPILER) $(CILK) $(OMP) $^ -o $@ $(TBB)
