// paralel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>

int main()
{
	int tid = omp_get_thread_num();
	int iplik_sayisi = omp_get_num_threads();


	printf("Merhaba iplik id = %d \n", tid);

	printf("Merhaba iplik sayisi= %d \n", iplik_sayisi);

	printf("\n\n\n\n\n\n");




	printf("// OMP Paralel bolge\n");
	omp_set_num_threads(6);//thread sayısına kaddar bo bölge tekrar edilecek
#pragma omp parallel 
	{
		// İplik numarasını al 
		tid = omp_get_thread_num();
		iplik_sayisi = omp_get_num_threads();

		printf("Merhaba Dunya iplik id = %d tiplik sayisi= %d\n", tid, iplik_sayisi);

	} // Tüm iplikler master ipliği ile birleştirir
	tid = omp_get_thread_num();
	printf("iplik %d bitti \n", tid);
	printf("\n\n\n\n\n\n");


	return 0;
}

