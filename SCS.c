#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

// elde edilen yeni string in uzunluğu
int lenght; 
// başlangıç ve bitiş zamanlarını tutacak olan struct yapıları
struct timeval  tv1, tv2; 
/* kullanıcının girdiği her string ikilisinin
toplam sayısının bulunduğu dizi */
int len_inputs[20];
/* kullanıcının girdileriyle elde edilen her bir yeni
string in uzunluğunun bulunduğu dizi*/
int len_outputs[20];
/* her bir string oluşturma işlemi için geçen sürelerin
tutulduğu dizi */
double time_values[20];

/* iki string birleşimi için bir önceki sütun veya
bir önceki satırın değerlerini karşılaştıran
ve küçük olanı döndüren fonksiyon */
int min(int a, int b){ 
	if(a < b) return a;
    return b;
} 
/* yeni string in oluşturulduğu fonksiyon.
yukarıda tanımlanan "lenght" değişkenine 
değer ataması burada yapılır. ayrıca
bulunan string in ekrana yazdırıldığı fonksiyon*/
void makeString(char X[], char Y[]) { 
    int m = strlen(X); // X kelimesinin uzunluğu
    int n = strlen(Y); // Y kelimesinin uzunluğu
    
    /* iki kelime için de başlangıçta denk gelen 
	matris hücresine 0 dan kelime uzunluğuna kadar
	atama yapılır.
	bu işlem için kullanılacak matrisin tanımı*/
    int Matrix[m + 1][n + 1]; 
  	int i, j;

    for (i = 0; i <= m; i++){ 
        for (j = 0; j <= n; j++){ 
            if(i == 0) 
            /* ilk string için her bir harfin bulunduğu
			matris hücresine ilgili indis ataması 
			0 dan uzunluğun 1 eksiğine kadar yapılır*/ 
                Matrix[i][j] = j; 
            else if(j == 0) 
            /* ikinci string için her bir harfin bulunduğu 
			matris hücresine sütun doğrultusunda ilgili indis
			ataması 0 dan uzunluğun 1 eksiğine kadar yapılır*/
                Matrix[i][j] = i; 
            else if(X[i - 1] == Y[j - 1]) 
            /* iki string içindeki harflerin aynı olması durumunda
			o harfin yeni stringte daha önce gelmesini sağlamak için
			bulunulan matris hücresine, sol çapraz hücresindeki
			sayısal değerin bir fazlası yerleştirilir*/
                Matrix[i][j] = 1 + Matrix[i - 1][j - 1]; 
            else
            /* iki string içindeki harflerin aynı olmaması durumunda
			harfin yerleştirileceği indisin ataması, içinde bulunulan
			matris hücresinin bir sol ve bir üst değerlerinin 
			minimumunun bir fazlasının alınmasıyla yapılır.*/
                Matrix[i][j] = 1 + min(Matrix[i - 1][j], Matrix[i][j - 1]); 
        } 
    } 
    
    int index = Matrix[m][n]; // string uzunluğunu içerir
    char newString[20]; // yeni oluşturulacak string
  
    /* bundan sonraki kısımda stringlerde sondan başa doğru gidilir
	her işlemde indisler birer azaltılır
	iki stringten herhangi birinin uzunluğunun 0 lanması durumunda
	döngüden çıkılır
	yeni string in oluşturulması için "string concatenation"
	işlemi (strncat gömülü fonksiyonu) kullanılır.*/
    i = m; j = n; 
    while (i > 0 && j > 0){ 
        if (X[i - 1] == Y[j - 1]){ 
        	/* string içeriklerinin aynı olması durumunda
        	(herhangi birinin) son harf yazılmaya başlanır
			iki string için de aynı olduğundan
			iki indis de azaltılır */
            strncat(newString, &X[i - 1], 1); 
            i--, j--, index--; 
        } 
        else if (Matrix[i - 1][j] > Matrix[i][j - 1]){ 
    		/* sol hücrenin bir üst hücreden büyük olması
			durumunda ikinci string in harfi yazılır çünkü
			sütun sıralaması Y dedir ve küçük olan önceliklidir*/
            strncat(newString, &Y[j - 1], 1); 
            j--, index--; 
        } 
        else{ 
        	/* bir önceki durumun tam tersidir
			sol hücre bir üst hücreden küçüktür
			satır sıralaması X tedir ve küçük olan önceliklidir*/
            strncat(newString, &X[i - 1], 1); 
            i--, index--; 
        } 
    } 
    
  	/* yukarıdaki "while" döngüsünden çıkış. 
	iki string ten birinin artık bakılacak bir indisinin
	kalmaması yani m ya da n in 0 lanması */
    while (i > 0){
		/* ilk olarak verilen string (X)
		yeni string oluşumunda ortak harfler de
		bittikten sonra önceliklidir*/ 
        strncat(newString, &X[i - 1], 1); 
        i--, index--; 
    } 
    while (j > 0){ 
    	/* ilk verilen stringte harf kalmaması durumunda
		ikinci string in harflerine geçilir
		bitene kadar, yeni string e harf ekleme işlemi devam eder*/
        strncat(newString, &Y[j - 1], 1); 
        j--, index--; 
    } 
    
    /* başlangıçta belirtildiği gibi string e harf 
	ekleme işlemi sondan başa doğrudur, elde edilen 
	string, asıl olması gereken string in ters halidir
	bunun için string in tersini (reverse) alan
	gömülü "strrev" fonksiyonu kullanılır*/
    strrev(newString); 
    /* string sonunda fazladan harf, rakam vb olmaması için
	uzunluğun 1 eksiğine (son indise)
	bitiş göstergesi konur*/
    newString[strlen(newString) - 1] = '\0';
    // lenght değişkenine atama
    lenght = strlen(newString);
    printf("Result of string: %s\n", newString);
}
/* çalışmada istenen görsellik 
her bir çalışma zamanı için "*" işareti ile
yapıldı.parametre olarak kodun o anki çalışma
süresini alır*/
void print_star(double value){
	/* yazdırılabilir bir değer elde etmek için
	her bir sayı 10 ile çarpılıp integer bir 
	değere dönüştürülür*/
	int new_value = value * 10;
	int i;
	for(i = 0; i<new_value; i++){ 
		// asterisk işareti ekrana bastırılıyor
		printf("*");
	}
	/* histogramın düzgün görünmesi için
	geri kalan kısma boşluk bastırıldı*/
	for(i = 0; i<50 - new_value; i++){
		printf(" ");
	}
}
int main(){ 
	// kullanıcının gireceği stringler
    char X[15], Y[15]; 
    /* kullanıcının programdan çıkış yapıp yapmadığını
	kontrol etmek için kullanılacak değişken
	0 ise devam 1 ise çıkış */
    int flag = 0;
    /* başlangıçta tanımlanan input-output-time
	dizilerinin her bir girdi için atamasında 
	kullanılacak olan indis*/
    int in_out_index = 0;
    do{
    	/* işlem süresinin tutulduğu değişken*/
    	double time_result;
    	printf("Enter the first string:");
    	scanf("%s",&X);
    	printf("Enter the second string:");
    	scanf("%s",&Y);
    	/* işlem başlamadan önce zaman alınıyor*/
        gettimeofday(&tv1, NULL);
        /* alınan stringlerin uzunlukları toplamı
		ilgili diziye yerleştirilir*/
    	len_inputs[in_out_index] = (strlen(X) + strlen(Y));
    	// asıl işlemin yapıldığı fonksiyon çağrılıyor
    	makeString(X, Y);
    	//fonksiyon içinde bulunan lenght ekrana yazdırılıyor
    	printf("Length of the shortest supersequence is %d\n", lenght);
    	/* bulunan yeni string uzunluğu
		ilgili diziye yerleştiriliyor*/
		len_outputs[in_out_index] = lenght;	
		// işlem bittikten sonra yeniden zaman alınıyor
    	gettimeofday(&tv2, NULL);
    	// alınan iki zaman değerinin farkı bulunuyor
    	time_result = (double) (tv2.tv_sec + tv2.tv_usec) / 1e6 - (double) (tv1.tv_sec - tv1.tv_usec) / 1e6;
    	// bulunan fark ilgili diziye yerleştiriliyor
    	time_values[in_out_index] = time_result;
    	//yeni işlem için indis değeri 1 arttırılıyor
    	in_out_index++;
		printf ("Total time = %f seconds\n", time_result);
    	printf("---------------------------------------------\n");
    	printf("Do you want to continue?\nEnter 0 to continue or 1 to exit:");
    	scanf("%d",&flag);
	}while(flag == 0);
    
    /* kullanıcı programdan çıktıktan sonra
	bir histogram görüntüsü ekrana verilir
	her bir string girdilerinin ve yeni string in
	toplamı için, başlangıçta oluşturulan dizilerden
	sırası ile veriler alınır.*/
    printf("\n\n\t\t\t--------------HISTOGRAM--------------\n\n\n");
    int m;
    for(m = 0; m<in_out_index; m++){
    	print_star(time_values[m]);
    	printf("\t");
    	printf("For input lenght %d - output lenght %d ",len_inputs[m], len_outputs[m]);
    	printf("\n");
	}
    return 0; 
} 
