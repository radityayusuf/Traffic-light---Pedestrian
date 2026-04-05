// Definisi Pin
const int btnPin = 2; // Pin Interrupt

// Pin LED Kendaraan
const int vRed = 4, vYel = 5, vGrn = 6;
// Pin LED Pedestrian 1
const int p1Red = 7, p1Grn = 8;
// Pin LED Pedestrian 2
const int p2Red = 9, p2Grn = 10;

volatile bool request = false; // Variabel flag interupsi

void setup()
{
    for (int i = 4; i <= 10; i++)
        pinMode(i, OUTPUT);

    // Menggunakan internal pull-up resistor untuk tombol
    pinMode(btnPin, INPUT_PULLUP);

    // Memicu fungsi callCross saat tombol ditekan (sinyal HIGH turun ke LOW)
    attachInterrupt(digitalPinToInterrupt(btnPin), callCross, FALLING);

    // Kondisi Awal (Default): Kendaraan Hijau, Pedestrian Merah
    digitalWrite(vGrn, HIGH);
    digitalWrite(p1Red, HIGH);
    digitalWrite(p2Red, HIGH);
}

void loop()
{
    // Mengecek apakah ada interupsi dari tombol
    if (request)
    {
        delay(500); // Jeda singkat respons

        // 1. Kendaraan transisi ke Merah dengan Kuning kedip 3x
        digitalWrite(vGrn, LOW);
        for (int i = 0; i < 3; i++)
        {
            digitalWrite(vYel, HIGH);
            delay(300);
            digitalWrite(vYel, LOW);
            delay(300);
        }
        digitalWrite(vRed, HIGH);

        // 2. Pedestrian berubah Hijau (Waktu menyeberang 5 detik)
        digitalWrite(p1Red, LOW);
        digitalWrite(p2Red, LOW);
        digitalWrite(p1Grn, HIGH);
        digitalWrite(p2Grn, HIGH);
        delay(5000);

        // 3. Waktu menyeberang habis, Pedestrian kembali Merah
        digitalWrite(p1Grn, LOW);
        digitalWrite(p2Grn, LOW);
        digitalWrite(p1Red, HIGH);
        digitalWrite(p2Red, HIGH);

        // 4. Kendaraan transisi fase kuning sebelum kembali Hijau
        digitalWrite(vRed, LOW);
        digitalWrite(vYel, HIGH);
        delay(2000);
        digitalWrite(vYel, LOW);
        digitalWrite(vGrn, HIGH);

        // Reset status interupsi
        request = false;
    }
}

// Fungsi Interrupt Service Routine (ISR)
void callCross()
{
    request = true;
}