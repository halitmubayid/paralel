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






	printf("// sections bolgesi icin bir ornek\n");

#pragma omp parallel num_threads(5)//her section tek kere çalışıyor ve thread sayısına kaddar değir bölge tekrar edilecek
	{
		iplik_sayisi = omp_get_num_threads();
		printf("Merhaba İplik sayisi= %d \n", iplik_sayisi);
#pragma omp sections
		{
#pragma omp section 
			{
				tid = omp_get_thread_num();
				printf("1.iplik %d section \n", tid);
			}
#pragma omp section
			{
				tid = omp_get_thread_num();
				printf("2.iplik %d section \n", tid);
			}
#pragma omp section
			{
				tid = omp_get_thread_num();
				printf("3.iplik %d section \n", tid);
			}
#pragma omp section
			{
				tid = omp_get_thread_num();
				printf("4.iplik %d section \n", tid);
			}
#pragma omp section
			{
				tid = omp_get_thread_num();
				printf("5.iplik %d section \n", tid);
			}
		}
	}
	printf("\n\n\n\n\n\n");





	printf("// Single bölgesi için bir örnek\n");//single 0. thread tarafından çalışıyor ve tek safer çalışyor ve thread sayısına kaddar değir bölge tekrar edilecek single bitirmeden diğer bölgeler çalışmıyor
	int c;
#pragma omp parallel num_threads(3) shared(c)
	{
#pragma omp single
		{
			c = omp_get_thread_num();
			printf("Single yapisi iplik %d tarafindan yurutulur\n", omp_get_thread_num());
		}

		c = omp_get_thread_num();
		printf("bu kod iplik %d tarafindan yurutulur C = %d \n", omp_get_thread_num(), c);

	}
	printf("\n\n\n\n\n\n");





	printf("// Burada lastprivate kullanmasi icin bir ornek\n");
	int s = 1, n = 10, i = 0;
#pragma omp parallel for num_threads(6) private(i) lastprivate(s)  //en yüksek değiri//yoksa resgele
	for (i = 1; i<n; i++)
	{
		s = i + 1;
		printf("iplik id %d için s = %d ve i = %d\n", omp_get_thread_num(), s, i);
	}
	printf("Paralel donguden sonra s degiri = %d \n", s);
	printf("\n\n\n\n\n\n");






	/*printf("// pragma omp barrier kullanması için bir örnek\n");
	int TID;

	#pragma omp parallel private(TID)
	{
	TID = omp_get_thread_num();
	//if (TID < omp_get_num_threads() / 2) system("sleep 3");
	time(&now);

	ctime_s(str, sizeof str, &now);

	printf("Today is before: %s", str);
	for (int i = 0; i<10000; i++) {
	for (int d = 1; d <= 100000; d++)
	{
	}
	}

	#pragma omp barrier
	time(&now);

	ctime_s(str, sizeof str, &now);

	printf("Today is after : %s", str);*/






	/*printf("// private ve shared kullanması için bir örnek\n");
	int ic = 0;
	#pragma omp parallel num_threads(4) shared(n,ic) private(i)
	{
	for (i = 0; i<n; i++)
	{
	#pragma omp atomic
	ic = ic + 1;

	}
	printf("counter = %d\n", ic);
	}*/






	printf("// schedule ve nowait kullanması için bir örnek\n");
#pragma omp parallel num_threads(3) shared(n) private (i) //her for içinde bariyer var for bitirmeden tüm threadler bekliyor no wait
	{
#pragma omp for nowait schedule(dynamic) 
		for (i = 0; i < n; i++)
		{
			printf("iplik (%d) dongu yinelemesini %d numarli yurutur\n", omp_get_thread_num(), i);
		}
		printf("No wait sonra\n");

	}

	printf("\n\n\n\n\n\n");





	printf("// schedule kullanması için bir örnek\n");
#pragma omp parallel num_threads(3) shared(n) private (i) //her for içinde bariyer var for bitirmeden tüm threadler bekliyor no wait
	{
#pragma omp for
		for (i = 0; i < n; i++)
		{
			printf("iplik (%d) dongu yinelemesini %d numarli yurutur\n", omp_get_thread_num(), i);
		}
		printf("wait sonra\n");

	}

	printf("\n\n\n\n\n\n");




	printf("if (n > 5) ve(n < 5) kullanması için bir örnek\n");
	int TID;
	n = 6;
#pragma omp parallel if (n > 5) private(TID) shared(n) num_threads(3)//if doğru değilse seri çalışır
	{
		TID = omp_get_thread_num();
#pragma omp single
		{
			printf("n değeri = %d\n", n);
			printf("Paralel bölgedeki iplik sayısı = %d\n",
				omp_get_num_threads());
		}
		printf("İplik (%d) tarafından yürütülen print ifadesi \n", TID);
	} /*-- Paralel bölğe sonudur --*/
	printf("\n\n\n\n\n\n");






	printf("// critical kullanması için bir örnek\n");

	int toplamLokal = 0, toplam = 0;
	int a[] = { 1,2,3,4,5,6 };
#pragma omp parallel num_threads(3) shared(n,a,toplam) private(TID, toplamLokal) 
	{
		TID = omp_get_thread_num();
		toplamLokal = 0;
#pragma omp for
		for (i = 0; i<n; i++)
			toplamLokal += a[i];
#pragma omp critical (toplam)
		{
			toplam += toplamLokal;
			printf("TID=%d: toplamLokal =%d toplam = %d\n", TID, toplamLokal, toplam);
		}
	} /*-- Paralel "for" sonudur --*/
	printf("Paralel bölgeden sonra toplamın değeri: %d\n", toplam);
	printf("\n\n\n\n\n\n");






	printf("// Atomic kullanması için bir örnek\n");

	int ic = 0;
#pragma omp parallel num_threads(3) shared(n,ic) private (i) 
	{
#pragma omp for  
		for (i = 0; i < 6; i++)
		{
			printf("%d. iterasyon iplik (%d) tarafindan yurutulur. \n", i, omp_get_thread_num());
#pragma omp atomic
			ic += 1;
		}
	}

	printf("ic = %d\n", ic);
	printf("\n\n\n\n\n\n");







	/*printf("//  Master  kullanması için bir örnek \n");

	int a = 0;
	#pragma omp parallel shared(a,b) private(i) num_threads(3)
	{
	#pragma omp master
	{
	a = 10;
	printf("Master yapısı iplik %d tarafından yürütülür \n",
	omp_get_thread_num());
	}
	//#pragma omp barrier
	#pragma omp for
	for (i = 0; i<n; i++)
	{
	b[i] = a;
	printf("%d. İterasyon iplik (%d) tarafından yürütülmüş:\n", i, omp_get_thread_num());
	}

	printf("\n\n\n\n\n\n");*/

	return 0;
}

