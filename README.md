# Smart Desk Reminder: Sistem Peringatan Barang Tertinggal Berbasis ESP32 dan Sensor Ultrasonik

Proyek ini dikembangkan sebagai bagian dari tugas mata kuliah **Mikroprosesor dan Mikrokontroler A** di Universitas Brawijaya. Sistem ini dirancang untuk mendeteksi keberadaan barang penting (seperti dompet, kunci, dll.) di atas meja secara otomatis dan real-time guna mengurangi risiko barang tertinggal.

## 👥 Anggota Tim
* **Muhammad Rusda Hadana** (225150307111067)
* **Sang Pimandu Banjaran** (245150300111006)
* **Nabil Tri Taufiq** (245150307111019)

---

## 🚀 Fitur Utama
Sistem ini memiliki dua mode operasi utama yang dikendalikan menggunakan tombol *push button*:
1. **Mode ARRIVE:** Berfungsi memantau keberadaan barang secara terus-menerus saat pengguna berada di tempat. Jika barang tidak ada atau diambil dari meja, sistem akan memicu alarm dan mengirimkan peringatan.
2. **Mode GO:** Berfungsi memastikan barang telah dibawa sebelum pengguna meninggalkan meja. Jika barang masih tertinggal saat mode ini diaktifkan, alarm panjang akan berbunyi.
3. **Notifikasi Telegram (IoT):** Terintegrasi dengan Telegram Bot API untuk mengirimkan pesan peringatan dan status barang secara *real-time* ke perangkat pengguna.
4. **Indikator Lokal:** Dilengkapi dengan layar LCD 16x2 I2C, LED, dan Buzzer untuk status visual serta audio secara langsung.

---

## 🛠️ Alat dan Bahan
| No | Komponen | Jumlah |
| :--- | :--- | :--- |
| 1 | ESP32 Dev Module | 1 |
| 2 | Sensor Ultrasonik HC-SR04 | 1 |
| 3 | LCD I2C 16x2 | 1 |
| 4 | Tombol Push Button 2 kaki | 2 |
| 5 | Buzzer | 1 |
| 6 | Kabel Jumper | 1 pack |
| 7 | Breadboard | 2 |

---

## 📐 Skema Rangkaian & Konfigurasi Pin
Berikut adalah pemetaan pin utama pada mikrokontroler ESP32:
* **Sensor Ultrasonik HC-SR04:** Trigger ke Pin 5, Echo ke Pin 18
* **Tombol Push Button Arrive:** Pin 33 (dengan `INPUT_PULLUP`)
* **Tombol Push Button Go:** Pin 32 (dengan `INPUT_PULLUP`)
* **LED:** Pin 26
* **Buzzer:** Pin 25

---

## 💻 Kode Program
Kode utama sistem dapat dilihat pada file **`Projek.ino`** di dalam repository ini. Pastikan Anda menyesuaikan konfigurasi kredensial jaringan WiFi dan token Telegram Bot Anda pada bagian berikut sebelum mengunggah kode ke ESP32:

```cpp
const char* ssid = "NAMA_WIFI_ANDA";
const char* password = "PASSWORD_WIFI_ANDA";

String botToken = "TOKEN_TELEGRAM_BOT_ANDA";
String chatID = "CHAT_ID_ANDA";
