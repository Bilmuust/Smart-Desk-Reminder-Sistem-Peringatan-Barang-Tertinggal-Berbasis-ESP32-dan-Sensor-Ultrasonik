# Smart Desk Reminder: Sistem Peringatan Barang Tertinggal Berbasis ESP32 dan Sensor Ultrasonik

Proyek ini dikembangkan sebagai bagian dari tugas mata kuliah **Mikroprosesor dan Mikrokontroler A** di Universitas Brawijaya[cite: 11]. Sistem ini dirancang untuk mendeteksi keberadaan barang penting (seperti dompet, kunci, dll.) di atas meja secara otomatis dan real-time guna mengurangi risiko barang tertinggal[cite: 11, 13].

## 👥 Anggota Tim
* **Muhammad Rusda Hadana** (225150307111067)[cite: 11]
* **Sang Pimandu Banjaran** (245150300111006)[cite: 11]
* **Nabil Tri Taufiq** (245150307111019)[cite: 11]

---

## 🚀 Fitur Utama
Sistem ini memiliki dua mode operasi utama yang dikendalikan menggunakan tombol *push button*[cite: 17, 18]:
1. **Mode ARRIVE:** Berfungsi memantau keberadaan barang secara terus-menerus saat pengguna berada di tempat[cite: 11]. Jika barang tidak ada atau diambil dari meja, sistem akan memicu alarm dan mengirimkan peringatan[cite: 17].
2. **Mode GO:** Berfungsi memastikan barang telah dibawa sebelum pengguna meninggalkan meja[cite: 11]. Jika barang masih tertinggal saat mode ini diaktifkan, alarm panjang akan berbunyi[cite: 17].
3. **Notifikasi Telegram (IoT):** Terintegrasi dengan Telegram Bot API untuk mengirimkan pesan peringatan dan status barang secara *real-time* ke perangkat pengguna[cite: 11, 15].
4. **Indikator Lokal:** Dilengkapi dengan layar LCD 16x2 I2C, LED, dan Buzzer untuk status visual serta audio secara langsung[cite: 17, 18].

---

## 🛠️ Alat dan Bahan
| No | Komponen | Jumlah |
| :--- | :--- | :--- |
| 1 | ESP32 Dev Module | 1[cite: 22] |
| 2 | Sensor Ultrasonik HC-SR04 | 1[cite: 22] |
| 3 | LCD I2C 16x2 | 1[cite: 22] |
| 4 | Tombol Push Button 2 kaki | 2[cite: 22] |
| 5 | Buzzer | 1[cite: 22] |
| 6 | Kabel Jumper | 1 pack[cite: 22] |
| 7 | Breadboard | 2[cite: 22] |

---

## 📐 Skema Rangkaian & Konfigurasi Pin
Berikut adalah pemetaan pin utama pada mikrokontroler ESP32:
* **Sensor Ultrasonik HC-SR04:** Trigger ke Pin 5, Echo ke Pin 18[cite: 18]
* **Tombol Push Button Arrive:** Pin 33 (dengan `INPUT_PULLUP`)[cite: 18, 19]
* **Tombol Push Button Go:** Pin 32 (dengan `INPUT_PULLUP`)[cite: 18, 19]
* **LED:** Pin 26[cite: 18]
* **Buzzer:** Pin 25[cite: 18]

---

## 💻 Kode Program
Kode utama sistem dapat dilihat pada file **`Projek.ino`** di dalam repository ini. Pastikan Anda menyesuaikan konfigurasi kredensial jaringan WiFi dan token Telegram Bot Anda pada bagian berikut sebelum mengunggah kode ke ESP32:

```cpp
const char* ssid = "NAMA_WIFI_ANDA";
const char* password = "PASSWORD_WIFI_ANDA";

String botToken = "TOKEN_TELEGRAM_BOT_ANDA";
String chatID = "CHAT_ID_ANDA";
