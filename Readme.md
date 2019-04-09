# **SmartDoor**
Sebuah sistem untuk membuka / mengunci pintu secara wireless dengan applikasi atau dengan menggunakan ketukan pintu.

# Latar Belakang
Seiring perkembangan zaman, penggunaan pintu dengan kunci konvensional seringkali memiliki keterbatasan seperti lupa mengunci pintu, tidak bisa membuka kunci jika pemilik rumah / kunci tidak ada ditempat, perlunya membawa kunci selalu saat bepergian dapat diselesaikan dengan teknologi. Smart-door adalah sebuah pintu yang dapat dibuka dan dikunci dengan sensor suara (pattern ketukan) atau secara wireless menggunakan device (dalam hal ini menggunakan Android sebagai controller and Arduino sebagai actuator).

# Deskripsi Sistem
Smart-door dibuat dengan arduino dan android. Pada smart-door terdapat sensor suara dan infrared yang terhubung dengan arduino. Sensor suara akan digunakan untuk menerima input ketukan sedangkan sensor infrared digunakan untuk mendeteksi keberadaan orang di depan pintu. Arduino dalam keadaan stand-by yang berada di dalam pintu digunakan untuk berkomunikasi dengan server dan android yang dimiliki oleh user. Selain membuka dan mengunci pintu melalui aplikasi android, user dapat menyimpan pattern ketukan saat inisiasi sistem, dan dengan ketukan tsb. pintu juga dapat dibuka. Setiap pembukaan / penguncian pintu akan disimpan dalam bentuk log di database dan dapat diakses melalui aplikasi android. Apabila tidak mengetahui pattern yang tepat, pengunjung dapat menekan tombol yang akan memberikan notifikasi pada user sehingga user dapat membuka pintu secara wireless. Pintu juga akan otomatis terkunci setelah beberapa saat setelah dibuka, hal ini untuk meminimalisir resiko pintu lupa dikunci saat bepergian. Salah satu komponen arduino yaitu display LCD berfungsi mengindikasikan kondisi pintu saat ini untuk user di dalam bangunan/rumah, sedangkan untuk pengunjung (diluar), disediakan display 7-segment agar setiap tindakan pengunjung juga mendapat feedback.

# Rancangan Solusi
1. Menerima request dari android / internal system untuk mengunci / membuka pintu
2. Menerima pattern suara ketukan pintu dengan sensor suara .
3. Mendeteksi keberadaan orang di depan pintu, dan menghidupkan system dari keadaan stand-by menggunakan sensor infrared .
4. Menampilkan pesan pada layar LCD & 7 segment sebagai feedback.
5. Memanfaatkan PWM pada lampu led sebagai feedback.
6. Memanfaatkan tombol yang berfungsi sebagai 'bel' yang akan memberi notifikasi ke android apabila tamu menekan tombol.
7. Mencocokan pattern ketukan dengan pattern yang disimpan.
8. Sinkronisasi history log ke database (FireBase)

# Cara Penggunaan Aplikasi

## Instalasi
1. Instalasi komponen arduino pada pintu yang diinginkan.
2. Sambungkan sistem ke sumber listrik (baterai / powerbank).
3. Nyalakan sistem
4. Pastikan Wifi tersedia
5. Tunggu sampai sistem meminta pattern untuk membuka pintu
6. Berikan pattern dengan mengetuk pintu
7. Tunggu instalasi selesai dan muncul tulisan "system's up".

## Use case tamu datang:
1. Dekatkan diri ke pintu
2. Tunggu Display 7 segment menyala memberikan sambutan
3. Tunggu LED berkedip" dan muncul `----` di display.
4. Ketuk pintu sesuai pattern
5. Tunggu pintu dibuka.

## Use case tamu datang:
1. Dekatkan diri ke pintu
2. Tunggu Display 7 segment menyala memberikan sambutan
3. Tunggu LED berkedip" dan muncul `----` di display.
4. Apabila tidak mengetahui pattern, pencet bel untuk menghubungi pemilik.
5. Tunggu sampai pintu dibukakan.

## Use case membuka / mengunci pintu dari aplikasi:
1. Buka aplikasi Smartdoor dari android
2. Pilih pintu yang ingin dibuka / ditutup
3. Apabila pintu sudah berhasil dikunci, akan terlihat simbol kunci di aplikasi. Begitu juga untuk membuka, jika berhasil dibuka, simbol kunci akan menghilang.

# Daftar Fitur
| No | Fitur | keterangan |
| ---|-------|------------|
| 1 | Wireless Lock / Unlock | User dapat menggunakan aplikasi android untuk membuka / mengunci pintu selama pintu dan aplikasi terhubung dengan internet. | 
| 2 | People detection | Mendeteksi adanya pengunjung / orang di depan pintu dan mengirimkan sambutan. | 
| 3 | Pattern Unlock | Membuka pintu dengan ketukan saja |
| 4 | Door Bell | Memberi notifikasi apabila ada pengunjung yang memencet bell |
| 5 | Lock Unlock Log | Mencatat setiap kali pintu dibuka / dikunci dan dapat diakses melalui aplikasi |
| 6 | Auto Lock | Pintu akan otomatis terkunci apabila sudah dibuka beberapa saat, untuk mengurangi resiko lupa mengunci saat keluar rumah. |

# Daftar Komponen
| No | Komponen | Fungsi |
| -- | -- | -- |
| 1 | Arduino uno | Controller komponen lainnnya |
| 2 | ESP8266 | Memungkinkan koneksi dengan Wifi dan melakukan HTTP request. |
| 3 | Servo | Berlaku sebagai kunci pintu. |
| 4 | Sensor suara (mic) | Menerima pattern ketukan |
| 5 | Sensor | Infrared Mendeteksi adanya pengunjung |
| 6 | Push Button | Berlaku sebagai bell. |
| 7 | 7 segment | Menampilkan feedback |
| 8 | LCD | Menampilkan feedback |
| 9 | LED | Menampilkan tanda sistem sedang mendengarkan ketukan |
| 10 | Level shifter | Mengubah sinyal output 3.3v menjadi 5v (untuk ESP8266) |
| 11 | Regulator | Mengubah Vcc 5v menjadi 3.3v (untuk ESP8266) |
| 12 | Shift register | Integrated Circuit Serial in Parallel out, mengurangi penggunaan pin arduino dan LCD |
| 13 | Potentiometer | Mengatur contrast dari LCD |

# Diagram
![SmartDoor Diagram](/Diagram.png)

# Author
Jessin Donnyson 	13516112    
Find me on : [Github](https://github.com/Jessinra?tab=repositories) [LinkedIn](https://www.linkedin.com/in/jessinra/) [GitLab](https://gitlab.com/Jessinra)
