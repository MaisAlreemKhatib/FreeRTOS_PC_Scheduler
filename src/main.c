#include "scheduler.h"


int main(int argc, char *argv[])
{
    const char *input_file = "giris.txt";
// Eğer komut satırından dosya adı verilmişse onu kullan
    if (argc >= 2) {
        input_file = argv[1];
    }
    // Scheduler'ı giriş dosyası ile başlat
    if (!scheduler_init(input_file)) {
        fprintf(stderr, "Scheduler baslatilamadi. giris dosyasi: %s\n", input_file);
        return 1;
    }
    // Zamanlayıcıyı çalıştır
    scheduler_run();
    // Kullanılan kaynakları temizle
    scheduler_cleanup();

    return 0;
}
//işletim ödevi 
