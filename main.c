#include <stdio.h>
#include <stdlib.h> // rand() ve srand() fonksiyonlarý için
#include <time.h>   // Rastgele sayý üretimi için zamaný kullanacaðýz
#include <ctype.h>  // toupper() fonksiyonu için (toupper küçük harf girildiðinde büyük harfe çevirmek için gerekli)

int main() {
    //Srand  Rastgele sayý üretimini baþlattýr (Her çalþtýrýþta farklý sonuçlar için)
    srand(time(NULL));

    // 4. Durum Yönetimi Deðiþkenleri 
    int saglik = 100;
    int enerji = 100;
    int yemek = 0;
    int siginak = 0; // 0: Yok, 1: Var
    
    char komut;
    int i; // Döngüler için sayaç
    int sifreGiris; // P komutu için

    printf("--- HAYATTA KALMA SIMULATORU ---\n");
    printf("Komutlar: [A]vlan, [S]iginak, [E]nvanter, [R]Dinlen, [F]Tehlike, [P]Sifre, [X]Cikis\n\n");

    // Oyun Döngüsü (Ana Do-While)
    do {
        // Kullanýcýdan komut alma
        printf("\n Ne yapmak istersin? > ");
        scanf(" %c", &komut); 
        komut = toupper(komut); // Küçük harf girilse bile büyük harf yapar.

        // 1. Komut Sistemi (SWITCH-CASE) 
        switch (komut) {
            
            case 'A': // Avlan
                // 2. Aritmetik ve Mantýksal Ýþlemler 
                if (enerji >= 15) {
                    enerji -= 15; // Enerji azalýr
                    int sans = rand() % 100;//bilgisayar hafýzasýndan rastgele sayý seçmek için kullanýlýr.

                    // Ýstenilen Mantýksal Operatörler (&&, ||) kullanýmý:
                    // %40 ihtimalle yemek bulur VE þanslýysa 2 yemek bulur.f
                    if (sans > 60) {
                        yemek++;
                        printf("Basarili av! Yemek kazandin. (Yemek: %d)\n", yemek);
                    } 
                    // %20 ihtimalle yaralanýr.
                    else if (sans < 20) {
                        saglik -= 10;
                        printf("Avlanirken yaralandin! Saglik -10\n");
                    } else {
                        printf("Hicbir sey bulamadin ama yoruldun.\n");
                    }
                } else {
                    printf("Avlanmak icin yeterli enerjin yok! (Gereken: 15)\n");
                }
                break;

            case 'S': // Sýðýnak Ara.
                // IF-ELSE Yapýlarýyla Olasýlýk :
                if (siginak == 1) {
                    printf("Zaten bir siginagin var.\n");
                } else if (enerji > 20) {
                    enerji -= 10;
                    int bulmaSansi = rand() % 100;
                    if (bulmaSansi > 50) {
                        siginak = 1;
                        printf("Guvenli bir magara buldun! Artik siginagin var.\n");
                    } else {
                        printf("Uygun bir yer bulamadin.\n");
                    }
                } else {
                    printf("Siginak aramak icin cok yorgunsun.\n");
                }
                break;

            case 'E': // Envanter Görüntüle.
                printf("\n--- DURUM RAPORU ---\n");
                printf("Saglik : %d\n", saglik);
                printf("Enerji : %d\n", enerji);
                printf("Yemek  : %d\n", yemek);
                printf("Siginak: %s\n", siginak ? "VAR" : "YOK");
                printf("--------------------\n");
                break;

            case 'R': // Dinlen
                // Saðlýk ve Enerji artýþý (Aritmetik) 
                if (yemek > 0) {
                    yemek--;
                    int artis = (siginak == 1) ? 30 : 15; // Sýðýnak varsa daha çok dinlenir.
                    enerji += artis;
                    saglik += 10;
                    
                    // Sýnýr kontrolü (100'ü geçmemeli).
                    if(enerji > 100) enerji = 100;
                    if(saglik > 100) saglik = 100;
                    
                    printf("Yemek yedin ve dinlendin. Enerji +%d, Saglik +10\n", artis);
                } else {
                    printf("Yiyecegin yok! Sadece biraz uyuyabilirsin. (Enerji +5)\n");
                    enerji += 5;
                    if(enerji > 100) enerji = 100;
                }
                break;

            case 'F': // Tehlike Dalgasý (FOR Döngüsü) 
                printf("TEHLIKE DALGASI BASLIYOR!\n");
                // Bölgedeki tehlike serisini simüle eder.
                for (i = 1; i <= 3; i++) {
                    int hasar = rand() % 15;
                    saglik -= hasar;
                    printf("%d. Dalga: Vahsi hayvan saldirdi! Hasar: -%d\n", i, hasar);
                    if (saglik <= 0) break; // Ölürse döngüden çýk.
                }
                printf("Tehlike gecti. Son Saglik: %d\n", saglik);
                break;

            case 'P': // Þifreli Ýlerleme (DO-WHILE) 
                printf("Kilitli bir sandik buldun. Sifreyi cozmelisin (10-20 arasi bir sayi).\n");
                int dogruSifre = 13; // Örnek sabit þifre
                
                // Doðru karakter/sayý girilene kadar döngü devam eder.
                do {
                    printf("Sifre tahmini gir: ");
                    scanf("%d", &sifreGiris);
                    
                    if (sifreGiris != dogruSifre) {
                        printf("Yanlis sifre! Tekrar dene.\n");
                        enerji -= 2; // Her hatada enerji düþer.
                    }
                } while (sifreGiris != dogruSifre && enerji > 0);

                if (enerji > 0) {
                    printf("Sifre Dogru! Sandiktan ekstra yemek cikti.\n");
                    yemek += 2;
                } else {
                    printf("Enerjin bitti, sandigi acamadan bayildin.\n");
                }
                break;

            case 'X': // Çýkýþ 
                printf("Simulasyondan cikiliyor...\n");
                break;

            default:
                printf("Gecersiz komut! Lutfen listeden bir komut secin.\n");
        }

        // Oyun sonu kontrolü (Ölüm durumu)
        if (saglik <= 0) {
            printf("\nSagligin tukendi. OYUN BITTI.\n");
            break;
        }
        if (enerji <= 0) {
            printf("\nEnerjin tukendi. Hareket edemiyorsun. OYUN BITTI.\n");
            break;
        }

    } while (komut != 'X'); // 'X' basýlmadýðý sürece devam eder.

    return 0;
}
