// Deklarasi Pin untuk Simpang Utara
const int utaraMerah = 2;
const int utaraKuning = 3;
const int utaraHijau = 4;

// Deklarasi Pin untuk Simpang Timur
const int timurMerah = 5;
const int timurKuning = 6;
const int timurHijau = 7;

// Deklarasi Pin untuk Simpang Selatan
const int selatanMerah = 8;
const int selatanKuning = 9;
const int selatanHijau = 10;

// Deklarasi Pin untuk Simpang Barat
const int baratMerah = 11;
const int baratKuning = 12;
const int baratHijau = 13;

void setup()
{
    // Inisialisasi semua pin dari 2 sampai 13 sebagai OUTPUT
    for (int i = 2; i <= 13; i++)
    {
        pinMode(i, OUTPUT);
    }

    // Kondisi default: Semua lampu dalam kondisi MERAH sebelum satu sisi aktif
    digitalWrite(utaraMerah, HIGH);
    digitalWrite(timurMerah, HIGH);
    digitalWrite(selatanMerah, HIGH);
    digitalWrite(baratMerah, HIGH);
}

void loop()
{
    // Lampu hijau menyala bergiliran searah jarum jam: Utara -> Timur -> Selatan -> Barat -> ulangi
    aktifkanSimpang(utaraMerah, utaraKuning, utaraHijau);
    aktifkanSimpang(timurMerah, timurKuning, timurHijau);
    aktifkanSimpang(selatanMerah, selatanKuning, selatanHijau);
    aktifkanSimpang(baratMerah, baratKuning, baratHijau);
}

// Gunakan fungsi untuk modularisasi (misalnya: aktifkanSimpang())
void aktifkanSimpang(int pinMerah, int pinKuning, int pinHijau)
{
    // 1. Matikan lampu merah di simpang ini, nyalakan hijau
    digitalWrite(pinMerah, LOW);
    digitalWrite(pinHijau, HIGH);

    // Lampu Hijau: Menyala selama 5 detik
    delay(5000);

    // Matikan lampu hijau untuk transisi ke kuning
    digitalWrite(pinHijau, LOW);

    // 2. Lampu Kuning: Diberikan efek kedip 3 kali
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(pinKuning, HIGH);
        delay(300); // Nyala sejenak (0.3 detik)
        digitalWrite(pinKuning, LOW);
        delay(300); // Mati sejenak (0.3 detik)
    }

    // ...dan menyala selama 2 detik
    digitalWrite(pinKuning, HIGH);
    delay(2000);
    digitalWrite(pinKuning, LOW);

    // 3. Lampu Merah: Menyala kembali setelah hijau (dan kuning) selesai
    digitalWrite(pinMerah, HIGH);
}