#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Number of vertices in the graph
#define V 13

int dijkstra(int fmap[V][V], int src);
int mindist(int* fdist, bool *been);
void printsolution(int* print, size_t size);

int main()
{	//                   S  A  B  C  D  E  F  G  H  I  J  K  L
	int map[V][V] = {   {0, 7, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},	//0  S
						{7, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0},	//1  A
						{2, 3, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0},	//2  B
						{3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},	//3  C
						{0, 4, 4, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0},	//4  D 
						{0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 5, 0},	//5  E  
						{0, 0, 0, 0, 9, 0, 0, 0, 3, 0, 0, 0, 0},	//6  F 
						{0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0},	//7  G 
						{0, 0, 1, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0},	//8  H 
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 4, 4},	//9  I
						{0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 4, 4},	//10 J 
						{0, 0, 0, 0, 0, 5, 0, 0, 0, 4, 4, 0, 0},	//11 K 
						{0, 0, 0, 2, 0, 0, 0, 0, 0, 4, 4, 0, 0} };	//12 L 

    dijkstra(map, 0);

	return 0;
}

int dijkstra(int fmap[V][V], int src)
{
	bool been[V] = {0}; //Daha once bulunup bulunmadigimi kontrol etmek icin
	int dist[V] = {0}; //Bulundugum konuma gore olan mesafeleri bu diziye alacagiz
	int min_index = src;

	been[src] = 1;

	//başlangıçta tüm mesafelere sonsuz değer atandı
	for (size_t i = 1; i < V; i++)
		dist[i] = INT_MAX;

	//başlangıçta gidebileceğin noktaların kümesi
	for (size_t i = 0; i < V; ++i)
		if (fmap[min_index][i])//haritada mesafe bilgisi 0 olan mesafelere gidemeiyorduk, 
			dist[i] = fmap[min_index][i];

	for (size_t i = 0; i < V; ++i)
	{
		min_index = mindist(dist,been);//en küçük değerli indis bulunur

		been[min_index] = 1;// en kısa mesafeye ait olan yolun gidilmiş olarak işaretlenmesi

		for (size_t j = 0; j < V; j++)
			if(dist[j] > (dist[min_index] + fmap[min_index][j]) && !been[j] && fmap[min_index][j])
				dist[j] = dist[min_index] + fmap[min_index][j];	

	}
			printsolution(dist, V);
}

//dist dizisinin en küçük değerli indisini döndürür.
int mindist(int* fdist, bool *fbeen)
{
	int min = INT_MAX, min_index = 0;		
	for (int i = 0; i < V; i++)
		if (fdist[i] < min && fbeen[i] == 0) {
			min_index = i;
			min = fdist[i];
		}
	return min_index;
}

void printsolution(int* print, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		printf("%d ",print[i]);
	printf("\n");
}
