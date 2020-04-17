#include <iostream>
#include <stdlib.h>   
#include <ctime>
#include <string.h>
#include <stdio.h>

using namespace std;
//Algoritma
/*
	1.Bir ba�lang�� populasyonu olu�turulur
	2.Populasyonun, belirlenen �evreye uyumu hesaplan�r
	3.Uyum de�erlerine oranla yeni bireyler �retilir
	4.Yeni bireyler sonraki nesle aktar�l�r(en ba�taki populasyonun yerine ge�er)
	5.�stenilen iterasyon miktar�na ula��lm��sa durulur
	6.Ad�m 2'ye d�n�l�r
*/

//Diziler
/*
Population : ilk iterasyonda ba�lang�� populasyonunun olu�turuldu�u,
sonraki iterasyonlarda i�lemlerin devam etti�i dizi

newPopulation : Mutasyon, crossing over ve breeding i�lemlerinin ger�ekle�tirilip population dizisine
aktar�ld��� ge�ici dizi

Fitness : Populasyon bireylerinin belirlenen ortama uyum de�erleri.

Probabilities : �htimaller. Belirli bir s�raya konmam�� halde. Y�zdelik dilimlere d�n��t�rmek i�in
bir ge�ici dizi

percents : probabilities'in y�zdelik dilimlere d�n��t�r�l�p s�ralanm�� hali. �rne�in;
Probabilities dizisi de�erleri 10 �zerinden 1,0.2,4,4.8 ise percents dizisi 0,10,12,52,100 olacakt�r

individual : Populasyon dizisinden ebeveynler se�ildikten sonraki �ocu�u i�lemlerin yap�laca�� newPopulationa
aktarmak i�in kullan�lan ge�ici bir dizi
*/

//Fonksiyonlar
/*
Generate() : 8 Say�dan(N�kleoid de diyebiliriz) ve 10 canl�dan olu�an bir dizi olu�turur yani population dizisini doldurur
Bunu yaparken 1'den 6'ya kadar rastgele say�lar olu�turur. Bu say�lardan 4,5 ve 6 environment fonksiyonunda 1'e d�n��t�r�lecektir.
Bunun sebebi y�ksek de�erli say�lar�n dna'larda daha nadir olarak ba�lamas�n� istememdir.

ShowP() : Populasyondaki bireyleri(Individuals) g�stermek i�in basit bir print fonksiyonu

ShowI() : Probabilities dizisinin �yelerini g�steren basit bir print fonksiyonu

ShowF() : Fitness dizisini g�steren basit bir print fonksiyonu

Environment() : Basit�e, populasyon dizisindeki say�lara verdi�im a��rl�klara g�re her bireyin fitness'ini hesapl�yor ve generate fonksiyonunda belirtti�im
gibi y�ksek de�erdeki say�lar�n oran�n� ba�lang�� fonksiyonunda azalt�yor. Bu fonksiyonda �nemli olan nokta fitness hesab�n� yap�yor olmas�

Cal_Prob() : Fonksiyonun amac� bulunan fitness de�erlerini 100'e oranlamak ve 100e oranlanm�� de�erleri %lik dilimlere �evirmek. B�ylece rand komutuyla rastgele
bir parent se�ilmeye kalk�ld���nda 100 �zerinden gelen rastgele de�erin hangi aral��a d��t��� yani hangi birey oldu�u kolayca bulunabilir

randF() : Float de�eri randomlamaya yar�yor. Breeding adl� fonksiyonda iki ebeveyni rastgele se�erken kullan�ld�lar

Breeding() : �reyecek ebeveynleri se�iyor, ebeveyn fitnesslerine g�re bir �ocuk olu�turup bunu ge�ici individual dizisine aktar�yor. Ge�ici individual dizisindeki
de�erler newPopulation dizisinde bo� yer aranarak yerle�tiriliyor. Bulunan yerin adresi de al�narak bu yere yerle�tirilen birey �zerinde mutation ve crossover 
fonksiyonlar� �a��r�l�yor

Mutation(int adres) : Ald��� adres de�eri newPopulation dizisi �zerinde mutasyona u�rat�lacak bireyin bulundu�u konumu simgeler. Bireyin sahip oldu�u 8 say�dan
herhangi birine 1-2-3 de�erlerinden birisini %50 �ans ile aktar�r yada hi�bir i�lem ger�ekle�tirmeden devam eder

Crossover(int adres,int secim1,int secim2) : Ald��� adres mutasyona u�rayacak bireyin konumu, secim1 ilk ebeveyniin, secim2 ise ikinci ebeveynin konumunu temsil eder.
�lk ebeveynin ilk d�rt, ikinci ebeveynin ise son d�rt say�s�n� alarak yeni bir birey olu�turur. Bu i�lemi %50 �ans ile ger�ekle�tirir yada ger�ekle�tirmez 
*/

//Eksikler
/*
Bu programda test etti�im algoritma i�in en b�y�k eksik �u ki, elimizdeki populasyon �ok k���k ve fitness de�erlerinin bir fark yaratabilmesi i�in
�ok k�s�tl�. Bu y�zden sonraki a�amadaki hedefim 10 t�r ve 1'er bireyden olu�an bir populasyon yerine 10 t�r ve �ok say�da bireyden olu�an bir populasyon ile
10 kez �reme ger�ekle�tirmek yerine binlerce kez ger�ekle�tirmek. Breeding() fonksiyonunda �reyecek ebeveynler se�ilirken sadece 10ar kez se�iliyorlar. 
Bu durum ihtimalleri aras�nda %1'lik farklar�n oldu�u bireyler i�in�ok yetersiz. E�er se�im say�s� artarsa ufak farklar�n sebep olaca�� etkiler 
daha iyi g�zlemlenebilir. Haritalarda �l�ek artt�r�ld���nda ayr�nt�n�n artmas� gibi

Bunun d���nda burada belirlenen t�rler ve �evre sadece test ama�l�. Yani burada bu t�r bir elektrik devresi ve �evre de en efektif kablo dizayn� olabilir.
Yada 3d rastgele ara� modelleri ve r�zgar s�rt�nmesi/ara� hacmi oran�n�n en d���k oldu�u ortam olabilir. 
*/
int Population[8][10];
int newPopulation[8][10];
int Fitness[1][10];
float Probabilities[1][10];
float percents[1][11];
int individual[8][1];


void Generate(){
	srand(time(NULL));
	for(int i = 0;i<10;i++){
		for(int j = 0;j<8;j++){
			Population[j][i] = (rand() % 6)+1; 	
		}	
	}	
}

void ShowP(){
	for(int i = 0;i<10;i++){
		cout<<i+1<<". birey		: ";
		for(int j = 0;j<8;j++){
		cout<<Population[j][i] << " ";
		}
		cout<< "\n";
	}	
}

void ShowI(){
	float lsum=0;
	for(int i = 0;i<10;i++){
		cout<<i+1<<". ihtimali 		: "<< Probabilities[0][i]<<"\n";
		lsum += Probabilities[0][i];
		}
		cout<<"Toplam �htimal		: "<<lsum<<"\n";
}

void Environment(){
		for(int i = 0;i<10;i++){
			for(int j = 0;j<8;j++){
				if(Population[j][i] == 2){
					Fitness[0][i] += 1;
				}else if(Population[j][i] != 2 && Population[j][i] != 3){
					Population[j][i] =1;
				}else{
					Fitness[0][i] += Population[j][i]*4;
				}
			}	
		}
	}

void ShowF(){
	int sum = 0;
	for(int i = 0;i<10;i++){
		cout<<i+1<<". Fitness		: ";
		cout<<Fitness[0][i];
		sum += Fitness[0][i];
		cout<< "\n";
	}	
	cout<<"Toplam Fitness		: "<<sum<<"\n";
}

void Cal_Prob(){
	float sum 	= 0;
	float sum2 	= 0;
	for(int i = 0;i<10;i++){
		sum += Fitness[0][i];
	}
	for(int i = 0;i<10;i++){
		Probabilities[0][i] = (100*Fitness[0][i])/sum;
	}
	
	percents[0][0] = 0.00;
		for(int i = 1;i<11;i++){
			percents[0][i] = percents[0][i-1] + Probabilities[0][i-1];
		}	
		
}

float randF(){
	float sonuc=0;
	int firstrange=100,secondrange=1000;
	int first = rand() % firstrange;
	int sec = rand() % secondrange;
	float firstF = float(first);
	float secF = float(sec);
	sonuc = firstF+(secF/(secondrange));
	return sonuc;
}

void Crossover(int adres,int secim1,int secim2){
	int flag = rand()%2;
	if(flag == 0){
	}else{
		for(int i = 0;i <4;i++){
			newPopulation[i][adres] = Population[i][secim1];
		}
		for(int i = 4;i <8;i++){
			newPopulation[i][adres] = Population[i][secim2];
		}
	}
}

void Mutation(int adres){
	int flag = rand()%2;
	if(flag == 0){
	}else{
		newPopulation[rand()%8][adres] = (rand()%3)+1;
	}
}

void Breeding(){
	//Select parents with probability of fitness'
	//With low chance, apply crossing over or not
	//Create a new individual by using parents' DNA, Crossing overs and random mutation
	//Add child to new population to use at next iteration
		int secim1,secim2;
		for(int i = 0;i<10;i++){
			
			float randI1 = randF();
			float randI2 = randF();
			for(int j=1;j<11;j++){
				if(randI1 >= percents[1][j-1] && randI1<=percents[1][j]){
					secim1 =j-1;
				}
				if(randI2>=percents[1][j-1] && randI2<=percents[1][j]){
					secim2 =j-1;
				}
			}
			if(Fitness[0][secim1]>Fitness[0][secim2]){
				for(int k = 0;k<8;k++){
				individual[k][0] = Population[k][secim1];
				}	
			}else{
				for(int k = 0;k<8;k++){
				individual[k][0] = Population[k][secim2];
				}	
			}			
			
			int bireyadress =0;
			for(int i = 0;i<10;i++){
				if(newPopulation[0][i]==0){
					bireyadress = i;
					for(int j=0;j<8;j++){
						newPopulation[j][i]=individual[j][0];
					}
					break;
				}
			}
		//call mutation with bireyadress
		Mutation(bireyadress);
		Crossover(bireyadress,secim1,secim2);
		//call crossingover with bireyadress
		
		
		}
		
		for(int i = 0;i<10;i++){
					for(int j=0;j<8;j++){
						Population[j][i]=newPopulation[j][i];
						newPopulation[j][i] =0;
						Fitness[0][i]=0;
					}
				}
		
			
				
}


int main(){	
			int a=0;	
			cout<<"Iterasyon:"<<a<<"\n";
			Generate();
			Environment();
			ShowP();
			system("pause");	
			while(1==1){
			cout<<"Iterasyon:"<<a<<"\n";
			a++;
			srand(time(NULL));
			Environment();
			Cal_Prob();
			ShowF();
			ShowP();
			ShowI();
			Breeding();
			
			if(a == 500){
				a=0;
				system("pause");
			}
			system("cls");
			}
	return 0;	
}
