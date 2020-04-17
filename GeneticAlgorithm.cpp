#include <iostream>
#include <stdlib.h>   
#include <ctime>
#include <string.h>
#include <stdio.h>

using namespace std;
//Algoritma
/*
	1.Bir baþlangýç populasyonu oluþturulur
	2.Populasyonun, belirlenen çevreye uyumu hesaplanýr
	3.Uyum deðerlerine oranla yeni bireyler üretilir
	4.Yeni bireyler sonraki nesle aktarýlýr(en baþtaki populasyonun yerine geçer)
	5.Ýstenilen iterasyon miktarýna ulaþýlmýþsa durulur
	6.Adým 2'ye dönülür
*/

//Diziler
/*
Population : ilk iterasyonda baþlangýç populasyonunun oluþturulduðu,
sonraki iterasyonlarda iþlemlerin devam ettiði dizi

newPopulation : Mutasyon, crossing over ve breeding iþlemlerinin gerçekleþtirilip population dizisine
aktarýldýðý geçici dizi

Fitness : Populasyon bireylerinin belirlenen ortama uyum deðerleri.

Probabilities : Ýhtimaller. Belirli bir sýraya konmamýþ halde. Yüzdelik dilimlere dönüþtürmek için
bir geçici dizi

percents : probabilities'in yüzdelik dilimlere dönüþtürülüp sýralanmýþ hali. Örneðin;
Probabilities dizisi deðerleri 10 üzerinden 1,0.2,4,4.8 ise percents dizisi 0,10,12,52,100 olacaktýr

individual : Populasyon dizisinden ebeveynler seçildikten sonraki çocuðu iþlemlerin yapýlacaðý newPopulationa
aktarmak için kullanýlan geçici bir dizi
*/

//Fonksiyonlar
/*
Generate() : 8 Sayýdan(Nükleoid de diyebiliriz) ve 10 canlýdan oluþan bir dizi oluþturur yani population dizisini doldurur
Bunu yaparken 1'den 6'ya kadar rastgele sayýlar oluþturur. Bu sayýlardan 4,5 ve 6 environment fonksiyonunda 1'e dönüþtürülecektir.
Bunun sebebi yüksek deðerli sayýlarýn dna'larda daha nadir olarak baþlamasýný istememdir.

ShowP() : Populasyondaki bireyleri(Individuals) göstermek için basit bir print fonksiyonu

ShowI() : Probabilities dizisinin üyelerini gösteren basit bir print fonksiyonu

ShowF() : Fitness dizisini gösteren basit bir print fonksiyonu

Environment() : Basitçe, populasyon dizisindeki sayýlara verdiðim aðýrlýklara göre her bireyin fitness'ini hesaplýyor ve generate fonksiyonunda belirttiðim
gibi yüksek deðerdeki sayýlarýn oranýný baþlangýç fonksiyonunda azaltýyor. Bu fonksiyonda önemli olan nokta fitness hesabýný yapýyor olmasý

Cal_Prob() : Fonksiyonun amacý bulunan fitness deðerlerini 100'e oranlamak ve 100e oranlanmýþ deðerleri %lik dilimlere çevirmek. Böylece rand komutuyla rastgele
bir parent seçilmeye kalkýldýðýnda 100 üzerinden gelen rastgele deðerin hangi aralýða düþtüðü yani hangi birey olduðu kolayca bulunabilir

randF() : Float deðeri randomlamaya yarýyor. Breeding adlý fonksiyonda iki ebeveyni rastgele seçerken kullanýldýlar

Breeding() : Üreyecek ebeveynleri seçiyor, ebeveyn fitnesslerine göre bir çocuk oluþturup bunu geçici individual dizisine aktarýyor. Geçici individual dizisindeki
deðerler newPopulation dizisinde boþ yer aranarak yerleþtiriliyor. Bulunan yerin adresi de alýnarak bu yere yerleþtirilen birey üzerinde mutation ve crossover 
fonksiyonlarý çaðýrýlýyor

Mutation(int adres) : Aldýðý adres deðeri newPopulation dizisi üzerinde mutasyona uðratýlacak bireyin bulunduðu konumu simgeler. Bireyin sahip olduðu 8 sayýdan
herhangi birine 1-2-3 deðerlerinden birisini %50 þans ile aktarýr yada hiçbir iþlem gerçekleþtirmeden devam eder

Crossover(int adres,int secim1,int secim2) : Aldýðý adres mutasyona uðrayacak bireyin konumu, secim1 ilk ebeveyniin, secim2 ise ikinci ebeveynin konumunu temsil eder.
Ýlk ebeveynin ilk dört, ikinci ebeveynin ise son dört sayýsýný alarak yeni bir birey oluþturur. Bu iþlemi %50 þans ile gerçekleþtirir yada gerçekleþtirmez 
*/

//Eksikler
/*
Bu programda test ettiðim algoritma için en büyük eksik þu ki, elimizdeki populasyon çok küçük ve fitness deðerlerinin bir fark yaratabilmesi için
çok kýsýtlý. Bu yüzden sonraki aþamadaki hedefim 10 tür ve 1'er bireyden oluþan bir populasyon yerine 10 tür ve çok sayýda bireyden oluþan bir populasyon ile
10 kez üreme gerçekleþtirmek yerine binlerce kez gerçekleþtirmek. Breeding() fonksiyonunda üreyecek ebeveynler seçilirken sadece 10ar kez seçiliyorlar. 
Bu durum ihtimalleri arasýnda %1'lik farklarýn olduðu bireyler içinçok yetersiz. Eðer seçim sayýsý artarsa ufak farklarýn sebep olacaðý etkiler 
daha iyi gözlemlenebilir. Haritalarda ölçek arttýrýldýðýnda ayrýntýnýn artmasý gibi

Bunun dýþýnda burada belirlenen türler ve çevre sadece test amaçlý. Yani burada bu tür bir elektrik devresi ve çevre de en efektif kablo dizayný olabilir.
Yada 3d rastgele araç modelleri ve rüzgar sürtünmesi/araç hacmi oranýnýn en düþük olduðu ortam olabilir. 
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
		cout<<"Toplam Ýhtimal		: "<<lsum<<"\n";
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
