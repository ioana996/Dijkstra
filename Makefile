run-var1:
	./Matrice_VectorSortat

run-var2:
	./Matrice_Heap

run-var3:
	./Lista_VectorSortat

run-var4:
	./Lista_Heap

build:
	gcc -Wall Matrice_VectorSortat.c -o Matrice_VectorSortat
	gcc -Wall Matrice_Heap.c -o Matrice_Heap
	gcc -Wall Lista_VectorSortat.c -o Lista_VectorSortat
	gcc -Wall Lista_Heap.c -o Lista_Heap
clean:
	rm -rf Matrice_VectorSortat Matrice_Heap Lista_VectorSortat Lista_Heap dijkstra.out
