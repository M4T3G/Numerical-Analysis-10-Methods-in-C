#include <stdio.h>
#include <math.h>
#define MAX 50
struct poly{
	int eleman;
	double katsayi[MAX];
	int us[MAX];
};
struct poly polinomAlma(){
	struct poly p1;
	int i;
	printf("Polinomun eleman sayisini giriniz.\n");
	scanf("%d",&p1.eleman);
	for(i=0;i<p1.eleman;i++){
		printf("Polinom uslerini giriniz\n");
		scanf("%d",&p1.us[i]);
	}
	for(i=0;i<p1.eleman;i++){
		printf("Polinom katsayilarini giriniz\n");
		scanf("%lf",&p1.katsayi[i]);
	}
	
	return p1;	
}
void polinomYazdirma(struct poly p) {
	int i;
	printf("\nPolinom:\n");
	for(i=0;i<(p.eleman-1);i++){
		printf("%lfx^%d + ", p.katsayi[i],p.us[i]);
	}
	printf("%lfx^%d  ", p.katsayi[p.eleman-1],p.us[p.eleman-1]);	
}

double F(double c, struct poly p){
    int i;
    double toplam = 0;
    for(i=0; i<p.eleman; i++){
        toplam = toplam + (p.katsayi[i] * pow(c,p.us[i]));
    }
    return toplam;
}

int kokKontrol(double a, double b, struct poly p){
    if(F(a, p)*F(b, p) < 0){
        return 1;
    }
    else{
        return 0;
    }
}

double turev(double c, struct poly p){
    int i;
    double toplam = 0;
    for(i=0; i<p.eleman; i++){
        if(p.us[i] != 0){
            toplam += p.katsayi[i] * p.us[i] * pow(c, (p.us[i]-1));
        }
    }
    return toplam;
}

void matrisAlma(double matris[][MAX],int n){
    int i, j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("Matrisin [%d][%d] elemani: ", i, j);
            scanf("%lf", &matris[i][j]);
        }
    }	
}


void bisection(){
	struct poly p;
	int c,iterasyon=0;
	double hata,orta,a,b;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nKok kontrolu icin iki deger giriniz.\n");
	printf("Kucuk Deger:\n");
	scanf("%lf",&a);
	printf("Buyuk Deger:\n");
	scanf("%lf",&b);
	c=kokKontrol(a,b, p);
	while(c==0){
		printf("Bu aralikta kok yok.Baska degerler deneyiniz.\n");
		printf("\nKok kontrolu icin iki deger giriniz.\n");
		printf("1.Deger:\n");
		scanf("%lf",&a);
		printf("2.Deger:\n");
		scanf("%lf",&b);
		c=kokKontrol(a,b, p);
	}
	printf("Hata degerinizi giriniz\n");
	scanf("%lf",&hata);

	while((b-a)/pow(2,iterasyon)>hata){
		orta=(a+b)/2;
		if(F(orta, p)*F(a, p)<0){
		b=orta;	
		}
		else if(F(orta, p)*F(b, p)<0){
			a=orta;
		}
		iterasyon++;
		printf("%d.Iterasyon=%lf\n",iterasyon,orta);
	}
	printf("Cevap=%lf Iterasyon=%d\n",orta,iterasyon);
	printf("\n");
}
void regulaFalsi(){
	struct poly p;
	int c,iterasyon=0;
	double hata,orta,a,b;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nKok kontrolu icin iki deger giriniz.\n");
	printf("Kucuk Deger:\n");
	scanf("%lf",&a);
	printf("Buyuk Deger:\n");
	scanf("%lf",&b);
	c=kokKontrol(a,b, p);
	while(c==0){
		printf("Bu aralikta kok yok.Baska degerler deneyiniz.\n");
		printf("\nKok kontrolu icin iki deger giriniz.\n");
		printf("1.Deger:\n");
		scanf("%lf",&a);
		printf("2.Deger:\n");
		scanf("%lf",&b);
		c=kokKontrol(a,b, p);
	}
	printf("Hata degerinizi giriniz\n");
	scanf("%lf",&hata);
	while((b-a)/pow(2,iterasyon)>hata){
		orta=(a*F(b, p)-b*F(a, p))/(F(b, p)-F(a, p));
		if(F(orta, p)*F(a, p)<0){
		b=orta;	
		}
		else if(F(orta, p)*F(b, p)<0){
			a=orta;
		}
		iterasyon++;
		printf("%d.Iterasyon=%lf\n",iterasyon,orta);
	}
	printf("Cevap=%lf Iterasyon=%d\n",orta,iterasyon);	
	printf("\n");
}
void newtonRaphson(){
	struct poly p;
	int c,iterasyon=1;
	double hata,kok1,kok2,a;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nBaslangic degeri giriniz:\n");
	scanf("%lf",&a);
	kok1=a;
	printf("Hata degerinizi giriniz\n");
	scanf("%lf",&hata);
	kok2=a-(F(a,p)/turev(a,p));
	printf("%d.Iterasyon=%lf\n",iterasyon,kok2);
	while(fabs(kok2-kok1)>hata){
		kok1=kok2;
		kok2=kok1-(F(kok1,p)/turev(kok1,p));
		iterasyon++;
		printf("%d.Iterasyon=%lf\n",iterasyon,kok2);
	}
	printf("Cevap=%lf Iterasyon=%d\n",kok2,iterasyon);	
	printf("\n");
}

void matrisTersi(){
	int n,i,j,k,ters=0;
	double matris[MAX][MAX],birim[MAX][MAX],kat=0,carpim=0;
	while(ters==0){
		printf("\nMatrisin boyutunu giriniz=\n");
		scanf("%d",&n);
		matrisAlma(matris,n);	
		for (i = 0; i < n; i++) {
        if (matris[i][i] == 0) {
            printf("Matrisin tersi yoktur.\n");
        }
		else{
			ters=1;
		}	
	}
    printf("Matris:\n");
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            printf("%lf ", matris[i][j]);
        }
        printf("\n");
    } 	
}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				birim[i][j]=1;
			}
			else{
				birim[i][j]=0;
			}
		}
	}
    for(k=0; k<n; k++){
        kat = matris[k][k];
        for(j=0; j<n; j++){
            matris[k][j] = matris[k][j]/kat;
            birim[k][j] = birim[k][j]/kat;
        }
        for(i=0; i<n; i++){
            if(i!=k){
                carpim = matris[i][k];
                for(j=0; j<n; j++){
                    matris[i][j] = matris[i][j] - carpim*matris[k][j];
                    birim[i][j] = birim[i][j] - carpim*birim[k][j];
                }
            }
        }
    }
    printf("Matrisin tersi:\n");
    for(i=0; i<n; i++){
    	printf("\n");
        for(j=0; j<n; j++){
            printf("%lf ", birim[i][j]);
        }    
    }   
    printf("\n");
}

void gaussEliminasyon(){
	int n,i,j,k,m;
	double katsayilar[MAX][MAX],sonuc[MAX], X[MAX],kat=0,pivot=0,kok=0;
	printf("\nMatrisin boyutunu giriniz=\n");
	scanf("%d",&n);
	printf("Katsayilar matrisini giriniz.\n");
	matrisAlma(katsayilar,n);
	printf("Cevap matrisini giriniz.\n");
	for(i=0;i<n;i++){
		printf("sonuc[%d]=",i);
		scanf("%lf",&sonuc[i]);
	}
    printf("\nGirdiginiz Katsayilar Matrisi=\n");
    for(i=0;i<n;i++){
    	printf("\n");
    	for(j=0;j<n;j++){
    		printf("%lf ",katsayilar[i][j]);
		}
	}
	printf("\nGirdiginiz Sonuc Matrisi=\n");
    for(i=0;i<n;i++){
    	printf("sonuc[%d]=%lf\n",i,sonuc[i]);
	}
    for (k = 0; k < n - 1; k++) {
        for (i = k + 1; i < n; i++) {
            kat=katsayilar[i][k]/katsayilar[k][k];
            sonuc[i]=sonuc[i]-kat*sonuc[k];
            for (j = k; j < n; j++) {
                katsayilar[i][j]=katsayilar[i][j]-kat*katsayilar[k][j];
            }
        }
    }
    
    for(i=0;i<n;i++){
    	pivot=katsayilar[i][i];
    	for(j=0;j<n;j++){
    		katsayilar[i][j]=katsayilar[i][j]/pivot;
		}
		sonuc[i]=sonuc[i]/pivot;
	}

    for(i=n-1;i>=0;i--) {
        kok=0;
        for(j=i+1;j<n;j++) {
            kok=kok+katsayilar[i][j]*X[j];
        }
        X[i]=(sonuc[i]-kok)/katsayilar[i][i];
    }

    printf("\nKatsayilar Matrisi=\n");
    for(i=0;i<n;i++){
    	printf("\n");
    	for(j=0;j<n;j++){
    		printf("%lf ",katsayilar[i][j]);
		}
	}
	printf("\nSonuc Matrisi=\n");
    for(i=0;i<n;i++){
    	printf("sonuc[%d]=%lf\n",i,sonuc[i]);
	}
	printf("\nKokler=\n");
    for(i=0;i<n;i++){
    	printf("X[%d]=%lf\n",i+1,X[i]);
	}	
	printf("\n");
}



void gaussJordan(){
	int n,i,j,k;
	double katsayilar[MAX][MAX],sonuc[MAX],kat=0,carpim=0;
		printf("\nMatrisin boyutunu giriniz=\n");
		scanf("%d",&n);
		printf("Katsayilar matrisini giriniz.\n");
		matrisAlma(katsayilar,n);
		printf("Cevap matrisini giriniz.\n");
		for(i=0;i<n;i++){
			printf("sonuc[%d]=",i);
			scanf("%lf",&sonuc[i]);
		}
	printf("\nGirdiginiz katsayilar matrisi=\n");
    for(i=0;i<n;i++){
    	printf("\n");
    	for(j=0;j<n;j++){
    		printf("%lf ",katsayilar[i][j]);
		}
	}
	printf("\nGirdiginiz sonuc Matrisi=\n");
    for(i=0;i<n;i++){
    	printf("sonuc[%d]=%lf\n",i,sonuc[i]);
	}		
    for(k=0; k<n; k++){
        kat = katsayilar[k][k];
        for(j=0; j<n; j++){
            katsayilar[k][j] = katsayilar[k][j]/kat; 
        }
		sonuc[k]=sonuc[k]/kat;        
        for(i=0; i<n; i++){
            if(i!=k){
                carpim = katsayilar[i][k];
                for(j=0; j<n; j++){
                    katsayilar[i][j] = katsayilar[i][j] - carpim*katsayilar[k][j];
                }
                sonuc[i]=sonuc[i]-carpim*sonuc[k];
            }
        }
    }
    printf("\nKatsayilar matrisi=\n");
    for(i=0;i<n;i++){
    	printf("\n");
    	for(j=0;j<n;j++){
    		printf("%lf ",katsayilar[i][j]);
		}
	}    
    printf("\nSirasiyla bilinmeyenlerin degerleri(Sonuc matrisi)=\n");
    for(i=0;i<n;i++){
    	printf("x%d=%lf\n",i+1,sonuc[i]);
	}
	printf("\n");
}  

void satirDegis(double katsayilar[MAX][MAX],double sonuc[MAX],int satir1, int satir2, int n) {
    double temp;
    int i;
    for ( i = 0; i < n; i++) {
        temp= katsayilar[satir1][i];
        katsayilar[satir1][i] = katsayilar[satir2][i];
        katsayilar[satir2][i] = temp;
    }
    temp=sonuc[satir1];
    sonuc[satir1]=sonuc[satir2];
    sonuc[satir2]=temp;
}

void gaussSeidel() {
    int n, i, j, k, degisme=0,yakinsama= 0,iterasyon = 1;
    double katsayilar[MAX][MAX], sonuc[MAX], baslangic[MAX], x[MAX], eskix[MAX], max = 1, max1, esik, hata=0,toplam=0;

    printf("Matrisin boyutunu giriniz: ");
    scanf("%d", &n);

    printf("Katsayilar matrisini giriniz:\n");
    matrisAlma(katsayilar, n);

    printf("Cevap matrisini giriniz:\n");
    for (i = 0; i < n; i++) {
        printf("sonuc[%d] = ", i);
        scanf("%lf", &sonuc[i]);
    }
	printf("\nGirdiginiz katsayilar matrisi=\n");
    for(i=0;i<n;i++){
    	printf("\n");
    	for(j=0;j<n;j++){
    		printf("%lf ",katsayilar[i][j]);
		}
	}
	printf("\nGirdiginiz sonuc Matrisi=\n");
    for(i=0;i<n;i++){
    	printf("sonuc[%d]=%lf\n",i,sonuc[i]);
	}

    for (i=0;i<n;i++) {
        max = max * fabs(katsayilar[i][i]);
    }

    i = 0;
    while ((i < n) && (!degisme)) {
        j = 0;
        while ((j<n) && (!degisme)) {
            if (i!=j) {
                satirDegis(katsayilar, sonuc, i, j, n);
                max1=1.0;
                for (k=0;k<n;k++) {
                    max1 = max1*fabs(katsayilar[k][k]);
                }
                if (max1 > max) {
                    max = max1;
                    degisme=1;
                } else {
                    satirDegis(katsayilar, sonuc, i, j, n);
                }
            }
            j++;
        }
        i++;
    }

    printf("Kosegence Max Haldeki Katsayilar Matrisi:\n");
    for (k=0;k<n;k++) {
        printf("\n");
        for (j=0;j<n;j++) {
            printf("%lf ", katsayilar[k][j]);
        }
    }

    printf("\nKosegence Max Haldeki Sonuc Matrisi:\n");
    for (i=0;i<n;i++) {
        printf("sonuc[%d] = %lf\n", i, sonuc[i]);
    }

    printf("Baslangic degerlerini giriniz:\n");
    for (i=0;i<n;i++) {
        printf("baslangic[%d] = ", i);
        scanf("%lf", &baslangic[i]);
    }

    printf("Hata degerini giriniz: ");
    scanf("%lf", &esik);

    for (i=0;i<n;i++) {
        x[i]=baslangic[i];
    }

    while (!yakinsama) {

        for (i=0;i<n;i++) {
            eskix[i] = x[i];
        }

        for (i=0;i<n;i++) {
        	toplam = 0;
            for (j=0;j<n;j++) {
                if (j!=i) {
                    toplam=toplam+katsayilar[i][j] * x[j];
                }
            }
            x[i] = (sonuc[i]-toplam)/katsayilar[i][i];
        }
   		 printf("X degerleri:\n");
    	for (i=0;i<n;i++) {
    	    printf("x[%d]=%f\n",i,x[i]);
    	}

   		 printf("Iterasyon sayisi: %d\n", iterasyon);
        
        hata = 0;
        for (i=0;i<n;i++) {
            hata=hata+fabs(x[i] - eskix[i]);
        }
        if (hata<esik) {
            yakinsama=1;
        }

        iterasyon++;
    }
    printf("Cozumler:\n");
    for (i=0;i<n;i++) {
        printf("x[%d] = %f\n",i,x[i]);
    }
    printf("Iterasyon sayisi: %d\n", iterasyon);
    printf("\n");
}			

void sayisalTurev(){
	struct poly p;
	int iterasyon=0,yontem;
	double a,h,cevap=0;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nBaslangic noktasini giriniz.\n");
	scanf("%lf",&a);
	printf("h(aralik) degerini giriniz.\n");
	scanf("%lf",&h);
	do{
		printf("Geri(1),Merkezi(2),Ileri(3) farklar icin verilen sayilardan birini giriniz.\n");
		scanf("%d",&yontem);
	}
	while((yontem!=1)&&(yontem!=2)&&(yontem!=3));
	if(yontem==1){
		cevap=(F(a,p)-F(a-h,p))/h;
	}	
	if(yontem==2){
		cevap=(F(a+h,p)-F(a-h,p))/(2*h);
	}
	if(yontem==3){
		cevap=(F(a+h,p)-F(a,p))/h;
	}
	printf("Cevap=%lf\n",cevap);
	printf("\n");	
}

void trapez(){
	struct poly p;
	int iterasyon=0,yontem,i,adim=0;
	double a,b,h,n,cevap=0,deger=0;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nAlt siniri giriniz.\n");
	scanf("%lf",&a);
	printf("Ust siniri giriniz.\n");
	scanf("%lf",&b);
	printf("n(aralik) degerini giriniz.\n");
	scanf("%lf",&n);
	h=(b-a)/n;
	b=a+h;
	for(i=0;i<n;i++){
		deger=h*(F(a,p)+F(b,p))/2;
		cevap=cevap+deger;
		a=b;
		b=a+h;
		adim++;
		printf("%d.Parca=%lf\n",adim,deger);
	}
	printf("Cevap=%lf\n",cevap);
	printf("\n");		
}

void simpson1(){
	struct poly p;
	int iterasyon=0,yontem,i,adim=0;
	double a,b,h,n,cevap=0,deger=0;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nAlt siniri giriniz.\n");
	scanf("%lf",&a);
	printf("Ust siniri giriniz.\n");
	scanf("%lf",&b);
	printf("Her bir n parcasi kendi icinde 2'ye bolunuyor.Yani 2parca=1n=1Bolge sayiliyor.\n");	
	printf("Bu yuzden girmek istediginiz n'i 2'ye bolerek giriniz.\n");
	printf("Ornek:n=10 ise siz 5 giriniz.\n");
	printf("n(aralik)/2 degerini  giriniz.\n");
	scanf("%lf",&n);
	h=(b-a)/n;
	b=a+h;
	for(i=0;i<n;i++){
		deger=h*(F(a,p)+4*F((a+b)/2,p)+F(b,p))/6;
		cevap=cevap+deger;
		a=b;
		b=a+h;
		adim++;
		printf("%d.Bolge=%lf\n",adim,deger);		
	}
	printf("Cevap=%lf\n",cevap);
	printf("\n");		
}

void simpson2(){
	struct poly p;
	int iterasyon=0,yontem,i,adim=0;
	double a,b,h,n,cevap=0,deger=0;
	p=polinomAlma();
	polinomYazdirma(p);
	printf("\nAlt siniri giriniz.\n");
	scanf("%lf",&a);
	printf("Ust siniri giriniz.\n");
	scanf("%lf",&b);
	printf("Her bir n parcasi kendi icinde 3'ye bolunuyor.Yani 3parca=1n=1Bolge sayiliyor.\n");
	printf("Bu yuzden girmek istediginiz n'i 3'ye bolerek giriniz.\n");	
	printf("Ornek:n=6 ise siz 2 giriniz.\n");
	printf("n(aralik)/3 degerini  giriniz.\n");
	scanf("%lf",&n);
	h=(b-a)/n;
	b=a+h;
	for(i=0;i<n;i++){
		deger=h*(F(a,p)+3*F((a+(a+b)/3),p)+3*F(b-(a+b)/3,p)+F(b,p))/8;
		cevap=cevap+deger;
		a=b;
		b=a+h;
		adim++;
		printf("%d.Bolge=%lf\n",adim,deger);
	}
	printf("Cevap=%lf\n",cevap);		
}

void gregoryNewton(){
	double X[MAX],Y[MAX],F1[MAX],F2[MAX],F3[MAX],deger,cevap=0;
	int i,j,n;
	printf("Kac tane x ve y degeri gireceksiniz?\n");
	scanf("%d",&n);
	printf("x ve y degerlerini giriniz.\n");
	for(i=0;i<n;i++){
		printf("x[%d]=",i);
		scanf("%lf",&X[i]);
		printf("\n");
		printf("y[%d]=",i);
		scanf("%lf",&Y[i]);	
		printf("\n");	
	}
	
	for(i=0;i<n-1;i++){
		F1[i]=(Y[i+1]-Y[i])/(X[i+1]-X[i]);
	}
	for(i=0;i<n-2;i++){
		F2[i]=(F1[i+1]-F1[i])/(X[i+2]-X[i]);
	}	
	for(i=0;i<n-3;i++){
		F3[i]=(F2[i+1]-F2[i])/(X[i+3]-X[i]);
	}	
	printf("Yaklasik degerini hesaplamak istediginiz degeri giriniz.\n");
	scanf("%lf",&deger);
	cevap=Y[0]+(deger-(X[0]))*F1[0]+(deger-(X[0]))*(deger-(X[1]))*F2[0]+(deger-(X[0]))*(deger-(X[1]))*(deger-(X[2]))*F3[0];
	printf("Cevap=%lf\n",cevap);
	printf("\n");	
}

int main(){
int secenek;
do {
    printf("\nPrograma hosgeldiniz. Hangi yontemi kullanmak istersiniz?\n");
    printf("0.Cikis\n1.Bisection yontemi\n2.Regula-Falsi yontemi\n3.Newton-Rapshon yontemi\n4.NxN'lik bir matrisin tersi\n5.Gauss Eleminasyon\n6.Gauss Jordan yontemi\n7.Gauss Seidel yontemi\n8.Sayisal Turev (merkezi, ileri ve geri farklar opsiyonlu)\n9.Trapez yontemi\n10.Simpson yontemi(1/3)\n11.Simpson yontemi(3/8)\n12.Gregory newton Enterpolasyonu\n");
    scanf("%d", &secenek);

    while ((secenek<0)||(secenek>12)) {
        printf("Gecerli bir sayi giriniz.\n");
        scanf("%d", &secenek);
    }
    switch (secenek) {
        case 0:
            printf("Hoscakalin");
            break;
        case 1:
            printf("Bisection yontemi\n");
            bisection();
            break;
        case 2:
            printf("Regula-Falsi yöntemi\n");
            regulaFalsi();
            break;
        case 3:
            printf("Newton-Rapshon yontemi\n");
            newtonRaphson();
            break;
        case 4:
            printf("NxN'lik bir matrisin tersi\n");
            matrisTersi();
            break;
        case 5:
            printf("Gauss Eleminasyon\n");
            gaussEliminasyon();
            break;
        case 6:
            printf("Gauss Jordan yontemi\n");
            gaussJordan();
            break;
        case 7:
            printf("Gauss Seidel yontemi\n");
            gaussSeidel();
            break;
        case 8:
            printf("Sayisal Turev (merkezi, ileri ve geri farklar opsiyonlu)\n");
            sayisalTurev();
            break;
        case 9:
            printf("Trapez yontemi\n");
            trapez();
            break;
        case 10:
            printf("Simpson yontemi(1/3)\n");
            simpson1();
            break;
        case 11:
            printf("Simpson yontemi(3/8)\n");
            simpson2();
            break;
        case 12:
            printf("Gregory newton Enterpolasyonu\n");
            gregoryNewton();
            break;
    }
} while (secenek!=0);
	return 0;
}
